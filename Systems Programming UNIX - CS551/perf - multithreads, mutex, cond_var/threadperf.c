/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #4 - CS551
Computation with POSIX Threads

This project computes perfect numbers using POSIX Threads. 

--------------
Design:

The main thread handles standard inputs and parses the commands. 
For each start command, a new thread is created to compute perfect numbers.
There is an additional control thread that checks if all threads finished 
testing all numbers. It then calls quit. 

There is one single mutex to control shared resources. However, there are
unique conditional variables for each thread to be able to make them idle
and restart. 

Each thread decrements a count variable to signalize that they will terminate.
The control thread checks this count variable upon a signal sent by each thread
before termination. This reduces constant check of the variable and reduces CPU
usage. 

isIdle variable:
0: RUNNING
1: IDLE
2: EXITED 
Report will always report thread statistics even if a thread has exited.

For "report", there is  a data structure called report_stat to hold certain attributes about each thread.
Each entry is filled by a thread.

Perfect array structure holds the perfect numbers with associated thread id's.


-------------------------
Assumptions: 

Block size must be a divisor of MAX.

Maximum 20 threads can be run.

BLOCK and MAX cannot be <1. BLOCK cannot be >MAX

Block numbers reported start with 0

start cannot be run with a number greater than MAX, 0 or a negative integer.
idle and restart do not run if thread N does not exist. These commands are then ignored

If a running thread is put on idle, but never restarted, the program will never end unless
quit is called. This is because some numbers may have not been tested by that idle 
thread and that particular thread will not terminate while idle. (Condition to terminate
the process depends on every thread to terminate. It is user's responsibility to appropriately
call restart)

Elapsed time is precision 1 digit, whereas CPU time is 3.

When a thread ends, thread statistics are not deleted from report_stat. 

For testing purposes scanf is being checked with EOF.

threadperf.h is included in the directory. 

To print the perfect numbers in a sorted fashion, I use library function qsort.

------------------------
*/


		#include <stdio.h>
		#include <sys/types.h>
		#include <unistd.h>
		#include <stdlib.h>
		#include <pthread.h>
		#include <sys/syscall.h>
		#include <string.h>
		#include "threadperf.h"
		#include <time.h>

	
		/*Main thread to parse stdin commands*/
		int main(int argc, char **argv) {

			time(&start); //start elapsed time
			start_clock = clock(); //start cpu time

			if(argc < 3 || argc > 3) { 
				printf("USAGE: ./threadperf MAX BLOCK\n"); 
				exit(1);
			}

			MAX = atoi(argv[1]);
			BLOCK = atoi(argv[2]);
			if(MAX<1 || BLOCK < 1 || BLOCK>MAX) { printf("Invalid input\n"); exit(1);}
			if(MAX % BLOCK!=0) { printf("Invalid block number. Not a divisor\n"); exit(1);}

			int size = (MAX/BLOCK); //how many blocks

			int bitmap_size = (size/(sizeof(int)*8))+1; 
			
			bitmap_block = malloc(bitmap_size);

			int j;
			for (j=0; j<=bitmap_size; j++) bitmap_block[j]=0;

			report_stat = malloc(sizeof(struct threadStat)*20);
			perfectArray = malloc(sizeof(struct entry)*20);

			pthread_attr_t tattr;
			pthread_attr_init(&tattr);	
			pthread_attr_setscope(&tattr,PTHREAD_SCOPE_SYSTEM);

			pthread_t tid;

			while(1) {
					
					char str[10];
					int startNum;

					printf( "Enter a command: ");
					while(scanf("%s", str)==EOF); //to test

					if(strcmp(str, "report") == 0) {

						for (j=0; j<20; j++) {
							if(report_stat[j].tid == 0) continue;
							printf("\nThread Number: %d ID: %lu\nNumber Tested: %d, Number Skipped: %d, Working on block: %d,",j+1, report_stat[j].tid, report_stat[j].numTested, report_stat[j].numSkipped, report_stat[j].blockNumber);
							if(report_stat[j].isIdle==0)
								printf(" RUNNING\n");
							else if(report_stat[j].isIdle==1)
								printf(" IDLE\n");
							else 
								printf(" EXITED\n");
						}	

						printf("\n");
						for (j=0; j<20; j++) {
							pthread_t id = report_stat[j].tid;
							if(report_stat[j].tid == 0) continue;
							int i;
							for(i=0; i<20; i++) {
								if(perfectArray[i].tid == id)
									printf("Perfect number found: %d by Thread number:%d ID:%lu\n",perfectArray[i].perfectNumber, j+1, id);
							}
						}
					
				}

					else if(strcmp(str, "quit") == 0) {
						printf("User wants to quit\n");
						quit();
					}

					else if(strcmp(str, "start") == 0) {
						scanf("%d", &startNum);
						if(startNum>MAX || startNum<1) {
							printf("Invalid starting integer\n");
							continue;
						}
						pthread_mutex_lock(&mtx);
						count++;
						if(count==1) {
							//special thread checking if all threads are done
							//this will only be created once
							pthread_create(&tid, &tattr, terminate, NULL); 
						}
						pthread_mutex_unlock(&mtx);
						printf("Thread Number:%d is starting\n",idx+1);
						pthread_create(&(report_stat[idx].tid),&tattr, computePerfect, &startNum); //compute threads
						idx++;


					}

					else if(strcmp(str, "idle") == 0) {
						scanf("%d", &startNum);
						if(startNum>idx || startNum==0) {
							printf("No such thread exists\n");
							continue;
						}
						
						pthread_mutex_lock(&mtx);
						startNum--; //n starts at 1
						if(report_stat[startNum].isIdle==2) {
							printf("This thread has already exited\n");
							pthread_mutex_unlock(&mtx);
							continue;
						}
						else if(report_stat[startNum].isIdle==1) {
							printf("This thread is already idle\n");
							pthread_mutex_unlock(&mtx);
							continue;
						}
						else {
							report_stat[startNum].isIdle=1;
							printf("Making the %dth thread idle\n", startNum+1);
						}
						pthread_cond_init(&(report_stat[startNum].cond), NULL);
						pthread_mutex_unlock(&mtx);


					}
					else if(strcmp(str, "restart") == 0) {
						scanf("%d", &startNum);
						
						if(startNum>idx || startNum==0) {
							printf("No such thread exists\n");
							continue;
						}
						
						pthread_mutex_lock(&mtx);
						startNum--; //n start at 1
						if(report_stat[startNum].isIdle==2) {
							printf("This thread has already exited\n");
							pthread_mutex_unlock(&mtx);
							continue;
						}
						else if(report_stat[startNum].isIdle==0) {
							printf("This thread was not idle anyway\n");
							pthread_mutex_unlock(&mtx);
							continue;
						}
						printf("Resuming the %dth thread \n", startNum+1);
						report_stat[startNum].isIdle = 0;
						pthread_cond_signal(&(report_stat[startNum].cond));
						pthread_mutex_unlock(&mtx);


					}

					else if(strcmp(str, "wait") == 0) {
						scanf("%d", &startNum);
						printf("Waiting for %d seconds...\n",startNum);
						sleep(startNum);

					}

					else {

						printf("USAGE:Choose one of the following\nstart K\nidle N\nrestart N\nwait S\nreport\nquit\n");
					}

				}

			return 0;		
			
		}

/* ------------------------------------------------------------------------ */
		/* computePerfect is the function to compute perfect numbers
		Input is starting integer address, used to find initial block */

		void *computePerfect(int* startNum) {

			pthread_mutex_lock(&mtx);
			report_stat[idx].numTested=0;
			report_stat[idx].numSkipped=0;
			report_stat[idx].isIdle = 0;
			pthread_mutex_unlock(&mtx);

			pthread_t threadId = pthread_self();


			//find your threadIndex
			int i;
			int threadIndex;
			for(i=0; i<20; i++) {
				if(report_stat[i].tid == threadId) {
					threadIndex = i;
					break;
				}
			}

			//Find the initial block number containing startNum (integer K)
			int blockNumber = 0;
			int x = 1;
			if(x!=*startNum){
				while((x+BLOCK-1)<*startNum){
					x+=BLOCK;
					blockNumber++;
				}
				
			}


			int start;
			int end;
			int original_block=blockNumber;
			int sum;


			do {
				pthread_mutex_lock(&mtx);
				if(testBit(bitmap_block, blockNumber)==0) {//test the block mutex needed


					report_stat[threadIndex].blockNumber = blockNumber;
							setBit(bitmap_block, blockNumber); //set the block
							pthread_mutex_unlock(&mtx);
							start = (blockNumber * BLOCK) +1 ;
							if(start>MAX) start = MAX;
							end = start + BLOCK-1;
							if(end>MAX) end = MAX;
							
							while (start<=end) { //check every number in this block
								report_stat[threadIndex].numTested++;
								sum=1;
								for (i=2;i<start;i++)
									if (!(start%i)) sum+=i;
								if(start==1) { start++; continue; }
								if (sum==start) { //FOUND A PERF NUMBER!!!
									
									
									pthread_mutex_lock(&mtx);
									
									perfectArray[perfIndex].tid = threadId;
									perfectArray[perfIndex].perfectNumber = start;
									perfIndex++;
									
									pthread_mutex_unlock(&mtx);
									
								}
								start++;
								pthread_mutex_lock(&mtx);
								while(report_stat[threadIndex].isIdle==1) { //am I idle?
									
									pthread_cond_wait(&(report_stat[threadIndex].cond),&mtx);
								}
								pthread_mutex_unlock(&mtx);	
							}

							if(blockNumber==((MAX/BLOCK)-1)) blockNumber=0; //wrap around
							else blockNumber++; 
						}

						else { //if the block is tested

							if(blockNumber==((MAX/BLOCK)-1)) blockNumber=0; //wrap around
							else blockNumber++; 
							report_stat[threadIndex].numSkipped+=BLOCK;
							pthread_mutex_unlock(&mtx);
						}
			}
			while(blockNumber!=original_block); //get out of the loop if you are testing the block you started with
			pthread_mutex_lock(&mtx);
			report_stat[threadIndex].isIdle = 2; //2 means thread exited
			count--;
			pthread_cond_signal(&count_cond); //signal the control thread to check count
			pthread_mutex_unlock(&mtx);
			pthread_exit(NULL);
		}

/* ------------------------------------------------------------------------------ */
				/* quit function terminates the process. Either called by user
				or gets called after all threads end */

				void quit() {

					int array[20];
					memset(array,0,sizeof(array));

					int j = 0;

					while(perfectArray[j].perfectNumber !=0 ) { //copy the perfect numbers in a different array
						array[j] = perfectArray[j].perfectNumber;
						j++;
					}

					qsort (array, j, sizeof (int), cmpfunc); //sort it
					printf("PERFECT NUMS FOUND: ");
					int i=0;
					for(i=0; i<j; i++)
						printf("%d ", array[i]);
					printf("\n");

					int total_test = 0;
					for(i=0; i<20; i++) {
						if(report_stat[i].tid != 0) {
							total_test += report_stat[i].numTested; //total numbers tested
						}
					}
					printf("Total number tested: %d\n", total_test);
					end = clock();
					cpu_time_used = ((double) (end - start_clock)) / CLOCKS_PER_SEC;
					time(&stop);
					printf("Total cpu time used: %0.2f seconds\n",cpu_time_used);
					printf("Total elapsed time: %.0f seconds\n", difftime(stop,start));
					exit(EXIT_SUCCESS);
				}


/*----------------------------------------------------------------------- */
				/* control thread function to check if threads are all finished */

				void *terminate() {

					pthread_mutex_lock(&mtx);
					while(count>0) {
					    // DON'T BURN CPU, ONLY CHECK IT WHEN A THREAD ENDS 
						pthread_cond_wait(&count_cond, &mtx); 
					}
					pthread_mutex_unlock(&mtx);
					printf("\nAll numbers have been tested. Terminating process...\n");
					quit();
					return NULL;
				}
