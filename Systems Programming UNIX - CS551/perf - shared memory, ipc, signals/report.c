/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #3 - CS551
Shared memory and signals on System V

Design and assumptions are in manage.c


/* report.c */
#include <signal.h>
#include <errno.h>
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

int main(int argc, char* argv[]) {
	
	
	int sid;	/* segment id of shared memory segment */
	struct memory *mem;	/* pointer to shared array*/
	
	/* create shared segment if necessary in case report run before manage*/
	if ((sid=shmget(KEY,sizeof (struct memory),IPC_CREAT |0660))== -1) {
		perror("shmget");
		exit(1);
	}
	
	/* map it into our address space*/
	
	if (( mem= ( (struct memory *) shmat(sid,0,0) )) == (struct memory *) -1) {
		perror("shmat");
		exit(2);
	}
	
	
	/* read from shared segment and print perfect numbers */
	int a = 0;
	printf("\nREPORT: Perfect Number Array: ");
	while(mem->perfArray[a] != 0) {
		printf("%d ", mem->perfArray[a]);
		a++;
	}
	printf("\n\n");
	
	
	a=0; //reset
	int totalnumber = 0;
	/*read process statistics and print*/	
	while(a<=20) {
		if(mem->processArray[a].pid != 0) {
			printf("Process id: %d\n", mem->processArray[a].pid);
			printf("Number tested: %d\n", mem->processArray[a].numberTested);
			printf("Number skipped: %d\n", mem->processArray[a].numberSkipped);
			printf("Number found: %d\n", mem->processArray[a].numberFound);
			printf("\n");
			totalnumber+=mem->processArray[a].numberTested;
		}
		a++;
	}
	printf("Total number tested: %d\n\n", totalnumber);	

	/* is -k flag called? */
	if((argv[1]!= NULL) && strcmp(argv[1], "-k") == 0) {
		
		/*send a message to manage to indicate shutdown */
		struct  {
			long type;
			int data;
		} my_msg;
		
		int qid;
		/* create queue if necessary */
		if ((qid=msgget(KEY,IPC_CREAT |0660))== -1) {
			perror("msgget");
			exit(1);
		}
		
		my_msg.type= 3; //important type
		my_msg.data=1;  //irrelevant - any data
		printf("REPORT: sending -k shutdown request\n");
		msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
		
	}

	if (shmdt((char  *) mem) == -1) {
		perror("shmdt");
		exit(3);
	}

	
	return 0;
}

