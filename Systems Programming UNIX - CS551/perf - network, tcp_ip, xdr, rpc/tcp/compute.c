		/*
		THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
		CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

		Author: Tamer Avci
		Assignment #5 - CS551


		Design and assumptions are in manage.c
	compute.c */
	#include <signal.h>
	#include <setjmp.h>
	#include <errno.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <ctype.h>
	#include <sys/types.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <netdb.h>
	#include "mdata.h"
	#include <poll.h>
	#include <pthread.h>
	#include <time.h>


	pthread_cond_t suspend = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	time_t starttime, stop;
	int start, end;
	int numTested = 0;
	int startPosition;
	int idle = 0;
	FILE *stream;
	struct computeData range;
	int s;
	XDR handle;

	/*thread procedure call. Computes perfect numbers and sends them to manage
	Also requests a new range*/
	void* computePerf() {
			
			time(&starttime);
			int sum, i;
			while (start<=end) { //check every number in this block

				numTested++;
				sum=1;
				for (i=2;i<start;i++)
					if (!(start%i)) sum+=i;
						if(start==1 || start==0) { start++; continue; }
							if (sum==start) { //FOUND A PERF NUMBER!!!
								pthread_mutex_lock(&mtx);
								while(idle==1) { //to avoid sending perf numbers while manage asked for numTest
												 //also to avoid sending more perf numbers when terminate is running
									pthread_cond_wait(&suspend,&mtx);
								}
								pthread_mutex_unlock(&mtx);	
								if ((stream=fdopen(s,"w")) == (FILE *) -1 ) {
											perror("fdopen:");
											exit(1);
								}
								struct manageData message;
								message.type = 4;
								message.value = sum;
								xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
								xdr_manageData(&handle, &message);
								//printf("COMPUTE: Sent a perfect number:%d to socket:%d\n",sum, s);
								fflush(stream);
								sleep(1);  //let the manage read it
								
							}
			start++;
			}
			time(&stop);
			struct manageData message;
			startPosition = end+1;
			message.type = 1;
			message.value = startPosition;
			message.time = difftime(stop,starttime); //send the time

			if ((stream=fdopen(s,"w")) == (FILE *) -1 ) {
				perror("fdopen:");
				exit(1);
			}
			//printf("COMPUTE: New range request sent to socket:%d\n", s);
			xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
										
			xdr_manageData(&handle, &message);
			fflush(stream);

			pthread_exit(NULL);
										
	}

	/*Terminate subroutine called when a signal is received*/
	void terminate(int signo)
	{
		if(signo==SIGINT) printf("COMPUTE: signal INTR received\n");
		else if(signo==SIGHUP) printf("COMPUTE: signal HUP received\n");
		else if(signo==SIGQUIT) printf("COMPUTE: signal QUIT received\n");

		struct manageData message;
		message.type = 5;
		message.value = numTested;

		if ((stream=fdopen(s,"w")) == (FILE *) -1 ) {
			perror("fdopen:");
			exit(1);
		}

		//printf("COMPUTE: Sending numTested:%d to MANAGE before terminate\n", numTested);
		xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
				
		xdr_manageData(&handle, &message);
		fflush(stream);

		//printf("COMPUTE: Terminating\n");
		sleep(2);

		exit(0);
	}

	int main(int argc, char* argv[]) {
		
		if(argc!=4) { printf("COMPUTE: USAGE: ./compute hostname portnumber startingNumber\nTerminating.\n"); exit(1); }   //Usage
		

		pthread_attr_t tattr;
		pthread_attr_init(&tattr);	
		pthread_attr_setscope(&tattr,PTHREAD_SCOPE_SYSTEM);

		pthread_t tid;


		/* terminate routine will handle SIGNALS */
		
		signal(SIGINT, terminate);
		signal(SIGHUP, terminate);
		signal(SIGQUIT, terminate);
		
		struct sockaddr_in sin; /* socket address for destination */
		
		
		long address;
		
		
		
		
		struct pollfd pollarray[1];

				/* Fill in Mary's Address */
		address = *(long *) gethostbyname(argv[1])->h_addr;
		//printf("adress %d\n", address);
		sin.sin_addr.s_addr= address;
		sin.sin_family= AF_INET;
		sin.sin_port = atoi(argv[2]);
		//printf("port number %d\n",sin.sin_port);

		startPosition = atoi(argv[3]); //begin from this number

		while(1) { 

				/* create the socket */
			if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0) {
				perror("Socket");
				exit(1);
				}

			/* try to connect to MANAGE */
			if (connect (s, (struct sockaddr *) &sin, sizeof (sin)) <0) {
				close(s);
				sleep(10);
				continue;
				}

			//printf("COMPUTE: Connection successful to MANAGE\n");
			pollarray[0].fd=s;     /* Accept Socket*/
			pollarray[0].events=POLLIN;
			break; 
		}
			
		// Initialization
				struct manageData message;
				message.type = 1;
				message.value = startPosition;
				message.time = -1;



				if ((stream=fdopen(s,"w")) == (FILE *) -1 ) {
					perror("fdopen:");
					exit(1);
					}

				//printf("COMPUTE: Sending a range request to MANAGE\n");
				
				xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
				
				xdr_manageData(&handle, &message);
				fflush(stream);

			
			while(1) {
				poll(pollarray, 1, -1);

					if ((stream=fdopen(s,"r")) == (FILE *) -1 ) {
							perror("fdopen:");
							exit(1);
					}
					
					
					xdrstdio_create(&handle,stream,XDR_DECODE); /* get XDR handle */			
					xdr_computeData(&handle, &range);

					switch(range.type) {
									
								case(1): //Range message received
									//printf("COMPUTE: Range received. start:%d end:%d\n", range.start, range.end);
									start = range.start;
									end = range.end;
									pthread_create(&tid, &tattr, computePerf, NULL);
									break;

								case(2): //manage asks for numTested
								pthread_mutex_lock(&mtx);
									idle = 1;
									pthread_mutex_unlock(&mtx);
									struct manageData message;
									message.type = 2;
									message.value = numTested;
									

									if ((stream=fdopen(s,"w")) == (FILE *) -1 ) {
										perror("fdopen:");
										exit(1);
									}

									//printf("COMPUTE: Sending number tested:%d to MANAGE for stat\n", numTested);
									xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
											
									xdr_manageData(&handle, &message);
									fflush(stream);
									
									pthread_mutex_lock(&mtx);
									idle = 0;
									pthread_cond_signal(&suspend);
									pthread_mutex_unlock(&mtx);
									break;


								case(3): //manage asks for terminate
									pthread_mutex_lock(&mtx);
									idle = 1;
									pthread_mutex_unlock(&mtx);
									//printf("COMPUTE: Terminate msg rcv\n");
									terminate(0);
									break;
								
					}
					
			}
			
		
		return 0;
	}





