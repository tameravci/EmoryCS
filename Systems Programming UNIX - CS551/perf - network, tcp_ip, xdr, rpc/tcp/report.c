	/*
	THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
	CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

	Author: Tamer Avci
	Assignment #5 - CS551


	Design and assumptions are in manage.c


	 report.c */
	#include <signal.h>
	#include <errno.h>
	#include <setjmp.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <ctype.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <netdb.h>
	#include "mdata.h"
	#include <poll.h>

	int cmpfunc (const void * a, const void * b) //quick sort compare function
{
   return ( *(int*)a - *(int*)b );
}

	int main(int argc, char* argv[]) {

		if(argc>4 || argc<3) { printf("REPORT: USAGE: ./report hostname portnumber (-k)\nTerminating.\n"); exit(1); }   //Usage
		if(argc==4) {
			if((strcmp(argv[3], "-k")))
				{ printf("REPORT: USAGE: ./report hostname portnumber (-k)\nTerminating.\n"); exit(1); }
		}
		
		
		struct sockaddr_in sin; /* socket address for destination */
		int s;
		
		long address;
		int i,j;
		XDR handle;
		FILE *stream;

		int perfNumberArray[10];
		for(i=0; i<10; i++)
			perfNumberArray[i]=0;

				
		address = *(long *) gethostbyname(argv[1])->h_addr;
		
		sin.sin_addr.s_addr= address;
		sin.sin_family= AF_INET;
		sin.sin_port = atoi(argv[2]);
		struct pollfd pollarray[1];


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

			//printf("REPORT: Connection successful to MANAGE\n");
			pollarray[0].fd=s;     /* Accept Socket*/
			pollarray[0].events=POLLIN;
			break; 
		}




		struct manageData message;


		if(argc==4 && strcmp(argv[3], "-k") == 0) {
			message.type = 3; //terminate
		}
		else 
			message.type = 2; //innocent report

		message.value = 0; //placeholders
		message.time =0; //placeholders

		if ((stream=fdopen(s,"w")) == (FILE *) -1 ) {
			perror("fdopen:");
			exit(1);
			}

		//printf("REPORT: Sending a message to MANAGE\n");
		xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
		
		xdr_manageData(&handle, &message);
		fflush(stream);

		
		j=0;
		while(1) {

			poll(pollarray, 1, -1); //wait for a response

			if ((stream=fdopen(s,"r")) == (FILE *) -1 ) {
				perror("fdopen:");
				exit(1);
			}


			
			struct reportData stat;
			xdrstdio_create(&handle,stream,XDR_DECODE); /* get XDR handle */			
			xdr_reportData(&handle, &stat);

			if(stat.fd==-1) break; //if it is end of message

			printf("\n");
			printf("REPORT:\nCompute host name: %s\n", stat.hostName);
			printf("Perf numbers found: ");
			for(i=0; i<stat.perfIndex; i++) {
				printf("%d ",stat.perfArray[i]);
				perfNumberArray[j] = stat.perfArray[i];
				j++;
			}
			printf("\n");
			printf("Total number tested:%d\n",stat.numTested);
			printf("Ranges this compute worked on: \n");
			for(i=0; i<stat.numRange-1; i++) {
				printf("Start:%d End:%d\n",stat.rangeArray[i].start, stat.rangeArray[i].end);
				
			}
			printf("Current range:\nStart:%d end:%d\n",stat.rangeArray[i].start, stat.rangeArray[i].end);


			
		}	


		qsort (perfNumberArray, 10, sizeof (int), cmpfunc);
		printf("\n");
		printf("REPORT: All perfect numbers found in the computation ");
		for(i=0; i<10; i++){
			if(perfNumberArray[i]!=0)
				printf("%d ",perfNumberArray[i]);
		}
		printf("\n");

		
		return 0;
	}

