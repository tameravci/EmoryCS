/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #3 - CS551
Shared memory and signals on System V

Design and assumptions are in manage.c
 
/* compute.c */
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include "hw3.h"
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define KEY (key_t)59050	/*key for shared memory segment */

int index_number; //process array designated slot
int sid;	/* segment id of shared memory segment */
struct memory *mem;	/* pointer to shared segment*/
int qid;	/* message queue id */

int testBit( int A[ ],  int k )
{
	return ( (A[k/(sizeof(int)*8)] & (1 << (k%(sizeof(int)*8)) )) != 0 ) ;
}


void  setBit( int A[ ],  int k )
{
	A[k/(sizeof(int)*8)] |= 1 << (k%(sizeof(int)*8));  // Set the bit at the k-th position in A[i]
}


/*Terminate subroutine called when a signal is received*/
void terminate(int signo)
{
	if(signo==SIGINT) printf("COMPUTE: signal INTR received\n");
	else if(signo==SIGHUP) printf("COMPUTE: signal HUP received\n");
	else if(signo==SIGQUIT) printf("COMPUTE: signal QUIT received\n");
	printf("COMPUTE: Deleting process entry\n");
	
	/*entry deletion - reset */
	mem->processArray[index_number].pid = 0;
	mem->processArray[index_number].numberFound = 0;
	mem->processArray[index_number].numberSkipped = 0;
	mem->processArray[index_number].numberTested = 0;
	
	if (shmdt((char  *) mem) == -1) {
		perror("shmdt");
		exit(3);
	}
	
	exit(0);
}

/* Main method takes an argument from the command line, attaches itself to the shared mem segment,
sends a message to manage to register, computes perfect numbers and sends them to manage*/
int main(int argc, char* argv[]) {
	
	if(argc!=2) { printf("COMPUTE: no arguments passed. Terminating.\n"); exit(1); }   //Usage
	int startPosition = atoi(argv[1]); //begin from this number

	/* create shared segment if necessary - in case compute is run before manage*/
	if ((sid=shmget(KEY,sizeof (struct memory),IPC_CREAT |0660))== -1) {
		perror("shmget");
		exit(1);
	}
	
	/* map it into our address space*/
	if (( mem= ( (struct memory *) shmat(sid,0,0) )) == (struct memory *) -1) {
		perror("shmat");
		exit(2);
	}
	
	int pid = getpid(); // get your pid for registration purposes
		
	struct  { //message structure
		long type; // = 1 for manage to recognize this is registry
		int data;  //store your pid
	} my_msg;
	
	/* create queue if necessary */
	if ((qid=msgget(KEY,IPC_CREAT |0660))== -1) {
		perror("msgget");
		exit(1);
	}

	/* terminate routine will handle SIGNALS */
	
	signal(SIGINT, terminate);
	signal(SIGHUP, terminate);
	signal(SIGQUIT, terminate);
	
	my_msg.type= 1; //asking for a new registry
	my_msg.data=pid; //storing pid
	printf("COMPUTE: sending a registry request (msg type:%d msg data:%d)\n", my_msg.type, my_msg.data);
	msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
	
	/*wait for your process index - slot as a message*/
	
	msgrcv(qid,&my_msg,sizeof(my_msg.data),pid,0); //only receive the message if type matches your pid
	
	printf("COMPUTE: received process array index (msg type:%d msg data:%d)\n", my_msg.type, my_msg.data);

	index_number = my_msg.data;
	if(index_number == 21) { //21 sent by manage to indicate failed registry- no slots available
		printf("COMPUTE: No space for me. Terminating\n");		
		terminate(0); //
	}
	
	/*initialize */

	mem->processArray[index_number].pid = pid;
	mem->processArray[index_number].numberFound = 0;
	mem->processArray[index_number].numberSkipped = 0;
	mem->processArray[index_number].numberTested = 0;
	

	
	
	/*start testing bits and computing numbers */

	int j;		/*loop counter */
	for (j=startPosition; j<=1024000; j++) {
	
		if(testBit(mem->bitmap, j) == 0) { //Test the bit
			setBit(mem->bitmap, j); //set the bit
			mem->processArray[index_number].numberTested++; //Test the number for perfect Number
			int i;
			int sum=1;
			for (i=2;i<j;i++)
				if (!(j%i)) sum+=i;
			
			if (sum==j && j!=1) {
				mem->processArray[index_number].numberFound++;
				my_msg.type = 2;
				my_msg.data = j;
				printf("COMPUTE: sending a perfect number (msg type:%d msg data:%d)\n",my_msg.type, my_msg.data);
				msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
			}
			
			continue; // skip numberSkipped because this number has been tested
		}
		
		mem->processArray[index_number].numberSkipped++;
		
	}

	printf("COMPUTE: Scanning finished. Exiting normally. Will also clean-up\n");
	terminate(0);

	return;
}



