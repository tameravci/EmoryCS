/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #3 - CS551
Shared memory and signals on System V 

This project computes perfect numbers using a shared memory and IPC. It also demonstrates
usage of signals and shared memory control by a single process.

--------------
Design:
 
Manage creates the shared memory segment and compute processes attach themselves to this shared memory.
Manage also sets up a single message queue for IPC. Compute and report(-k) communicate to the manage via this queue.
Manage receives messages in a while loop. It only receives messages sent with types 1, 2, and 3. (msgrcv with -3) 
Manage also memsets and clears up the shared memory (making everything 0)

Type=1 is the message that manage receives from a newly initialized compute process.
Compute processes send their pid to manage and manage finds an empty slot in processArray in the shared segment. 
Then it sends back a message with data equal to that empty slot index and with type equal to their unique pid. This allows the message to be received
only by that compute process with that particular pid so messages are not consumed arbitrarily. 

Type=2 is the message that manage receives from compute processes as perfect numbers. Manage updates the perfect number array.
It does not send a message back. 
When manage receives a perfect number, it first checks whether that number is already in the perfect array.
This is for the extremely rare atomic case where two or more computes test the same perfect number and send it to manage.
After checking that it sorts and shifts the array in order before putting the perfect number.

Type=3 is the message it receives from report process indicating -k shutdown procedure. It calls the terminate handler.


-------------------------
Assumptions: 

Only one manage process can be run at a given time.
Semaphore is not used for bitmap control per instructed and for efficiency. (No harm in updating the bit (1) more than once)
Computes call their terminate handlers and clean up before exiting when they finish scanning the bitmap. In this case,
process statistics will no longer be available for report process.
total number tested only counts the numbers tested in the CURRENTLY running computes. 



-------------
 manage.c 
-------------
*/
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/msg.h>
#include "hw3.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define KEY (key_t)59050	/*key for shared memory segment */

struct memory *mem; //shared memory pointer
int sid;	    //shared memory id
int qid;	    //message queue id



/*This function is called when a signal is received or -k is used by report */
void terminate(int signo) {
	
	if(signo==SIGINT) printf("MANAGE: signal INTR received\n");
	else if(signo==SIGHUP) printf("MANAGE: signal HUP received\n");
	else if(signo==SIGQUIT) printf("MANAGE: signal QUIT received\n");

	int i = 0;
	/* sending INTR to all compute processes */
	while(i<20) {
		if(mem->processArray[i].pid != 0) {
			if(kill(mem->processArray[i].pid, SIGINT)!=0)
			perror("kill");
		}
		i++;
	}
	
	sleep(5);
	
	printf("MANAGE: deallocating shared memory and removing IPC\n");
	
	if (shmdt((char  *) mem) == -1) {
		perror("shmdt");
		exit(3);
	}

	if (shmctl(sid,IPC_RMID,0) == -1) {
		perror("shmctl");
		exit(3);
	}
	
	if (msgctl(qid, IPC_RMID,0) == -1) {
		perror("msgctl");
		exit(4);
	}
	
	printf("MANAGE: Goodbye world!\n");
	exit(0);
}

/* Main method sets up shared memory & message queue and then listens to messages and maintains shared memory*/
main() {
	
	/*create shared segment*/
	if ((sid=shmget(KEY,sizeof (struct memory),IPC_CREAT |0660))== -1) {
		perror("shmget");
		exit(1);
	}
	
	/* map it into our address space*/
	if (( mem= ( (struct memory *) shmat(sid,0,0) )) == (struct memory *) -1) {
		perror("shmat");
		exit(2);
	}

	memset(mem,0,128404);
	
	/* terminate routine will handle signals */
	signal(SIGINT, terminate);
	signal(SIGHUP, terminate);
	signal(SIGQUIT, terminate);
	
	/* bitmap initialized to all 0s */
	int j;
	for (j=0;j<=SIZE;j++) mem->bitmap[j]=0;
	
	/*message struct*/	
	struct  {
		long type;
		int data;
	} my_msg;
	
	/* create message queue */
	if ((qid=msgget(KEY,IPC_CREAT |0660))== -1) {
		perror("msgget");
		exit(1);
	}
	
	/* Now read the messages */
	int processIndex; //processArray index
	int n = 0; //number of perfect numbers in the perfArray

	printf("MANAGE: initialized waiting for messages\n");
	while (1) {

		
		msgrcv(qid,&my_msg,sizeof(my_msg.data),-3,0);   //only read messages with type <=3

		if(my_msg.type == 1 ) { //if it's a registration request
			
			printf("MANAGE: received registry request (msg type:%d msg data:%d)\n", my_msg.type, my_msg.data);			
			my_msg.type = my_msg.data; //type of the message to be sent back = pid of the compute			
			
			processIndex = 0;	//empty slot index reset for intermediate empty slots

			while(processIndex<20) {
				if(mem->processArray[processIndex].pid == 0) { //found an empty slot
					my_msg.data = processIndex; //put the processIndex into the msg_data to be sent
					break; 
				}
				else processIndex++; //keep looking for an empty slot
					
			}
			
			if(processIndex == 20) { //handling exception if processIndex reaches 20
				printf("MANAGE: No more compute slots are available. Compute has to terminate\n"); 
				my_msg.data = 21; //21 will indicate the compute to terminate
			}

		
			msgsnd(qid,&my_msg,sizeof(my_msg.data),0); //send the process index as a message
			printf("MANAGE: sending process array index (msg type:%d msg data:%d)\n", my_msg.type, my_msg.data); 
		}
		
		else if(my_msg.type == 2) { //if it's a perfect number submission
			
			printf("MANAGE: received perfect number (msg type:%d msg data:%d)\n", my_msg.type, my_msg.data);
			int perfCandidate = my_msg.data; //take the perfect number candidate
			
			if(n==0) { //if the array is empty no need to sort
				mem->perfArray[0] = perfCandidate;
				n++;
				continue;
			}
			

			int i;
			int contains = 0;
			for (i=0; i < n; i++) {
       				 if (mem->perfArray[i] == perfCandidate) {
					contains = 1;
					break;
				}
       			}
		
			/*sort the array to put the candidate in the right spot*/

			if(contains!=1) {

				i = n-1;
				while(perfCandidate < mem->perfArray[i] && i>=0) {
					mem->perfArray[i+1] = mem->perfArray[i];
					i--;
				}

				mem->perfArray[i+1] = perfCandidate;
				n++;
			}

			
		}
		
		else if(my_msg.type == 3) { //report sending a message to manage
			printf("MANAGE: received -k from report shutdown in progress\n");
			terminate(0);
		}
	}

	return;
}
