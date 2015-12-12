/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #5 - CS551
Communicaton with sockets on a network

--------------
Design:

Manage coordinates all computes and report programs.
Communication is done by TCP/IP sockets. Manage runs first
and listens to up to 30 connections (20 computes and 10 report).
It uses polling to listen to messages sent by other programs.

rpcgen rountine is used to generate XDR routines to encode the data
between processes. After rpcgen, mdata.h and mdata_xdr.c are produced.

There is a Makefile included in the tcp directory for proper compilation.

Each program has its own unique incoming message type that is declared in
mdata.x file. All the outgoing communication is done properly and using XDR.

manage : struct manageData
report : struct reportData
compute : struct computeData

After initializations manage is sitting in a while loop polling requests.
It looks at the message.type to determine what to do.

DynamicMap function is essential to give ranges to computes. It is a linked-list
map with start and offset attributes. Manage gets the range boundaries by looking
at the linked list and finding an appropriate range that is closest to the desired
starting point but also disjoint from all the other tested ranges.

For offset, the program learns to give better approximate range sizes by a simple
ratio calculation. Initially, the offset is given as 30,000. Later, this is adjusted
for 15 seconds by looking at the offset saved in the previous attempt.

When report connects to manage, manage collects up-to-date number tested info from all
the computes. After all computes deliver this information, manage sends it to report.
-k procedure is also conducted similarly, except manage also tells computes to terminate.

Compute implements threads to compute perfect numbers. The main thread allows us to listen
to manage queries whenever they are available while the other thread computes perfect numbers
and sends them to manage as it finds them.

Report waits for the response again by polling. Here, report listens to a particular message
called endOfdata to know that it got all the information needed.

Communicaton Map:

Compute >> Manage [struct manageData]
Type:1 Requesting a range
Type:4 Perfect number submission
Type:5 numTested submission before terminate

Manage >> Compute [struct computeData]
Type:1 Range delivery
Type:2 Requesting numTested
Type:3 Terminate request

Report >> Manage [struct manageData]
Type:2 Requesting stats
Type:3 -k terminate procedure

Manage >> Request [struct reportData]
No types. Uses fd=-1 to signal
that all results are delivered.

-------------------------
Assumptions:

Ranges are stored in a fixed array of size 1000. This means
report can only print 1000 past range data. Range data structure
to allow the report to print ranges is a circular buffer that
overwrites past ranges if it is above 1000.

In the DynamicMap function where ranges are given, the closest
point is assigned and the length of the range is adjusted to fill the gaps

Linked-List is handling in-between placement as well as
to the extreme ends to deal with gaps.

statistics[0] is left intentionally as -1 to be consistent
with pollarray's index. (pollarray[0] is manage's socket)
That way poll() will ignore sockets with fd -1.

Each compute is able to find maximum 6 perfect numbers on their
own(being optimistic :)  (perfArray of size 6)

In the case of -k everything shuts down as requested in the handout.

As per TA's instruction, in the case of a signal received by manage shuts down computation.

Host names must be under 20 characters.

There is no checks for correct port & hostnames. Assumed typed correctly.
-------------
manage.c
-------------
*/
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <poll.h>
#include "mdata.h"
#include <time.h>

reportData statistics[21]; //to hold statistics for computes
struct reportData endofData; //end of message for report
struct computeData range; //compute message


typedef struct node { //node for dynamic map
	int init;
	int offset;
	struct node *next;
}node;

int x_offset; //new adjusted length
struct hostent *hostentp;
node* head;

struct sockaddr_in sin; /* structure for socket address */
int s;
int i;
int fd;
int len;
XDR handle;
FILE *stream;
struct pollfd pollarray[31]; //30 + 1


/*Takes in a desired start position and traverses a linked list
to find a perfect range with a desired offset (length) and updates
range message attributes */
void dynamicMap(int start) {
	
	node* current = head;
	
	while (1) {
		
		if(current->next == NULL) {//add it all the way to the right
			
			node* new_node = malloc(sizeof(node));
			current->next = new_node;
			new_node->init = start;
			new_node->offset = x_offset;
			new_node->next = NULL;
			range.start = start;
			range.end = start + x_offset;
			break;
			
		}
		
		else if(start < (current->next->init)) {
			if((start+x_offset) < (current->next->init)) {//add to the left with enough space
				
				node* new_node = malloc(sizeof(node));
				new_node->next = current->next;
				current->next = new_node;
				new_node->init = start;
				new_node->offset = x_offset;
				range.start = start;
				range.end = start +x_offset;
				break;
			}
			
			else { // to the left without enough space - adjust offset
				
				node* new_node = malloc(sizeof(node));
				new_node->next = current->next;
				current->next = new_node;
				new_node->init = start;
				x_offset = ((new_node->next->init) - start) -1;//offset change to cover the gap
				new_node->offset = x_offset;
				range.start = start;
				range.end = start +x_offset;
				break;
			}
		}
		
		else if( start >= (current->next->init)) {//moving right
			
			
			if(start > ((current->next->init) + (current->next->offset))) {//no need to change start
				
				current = current->next;
			}
			else {
				start = (current->next->init) + (current->next->offset) + 1;//change the start number
				current = current->next;
			}
		}
		
	}
	
	
	
}

/*This function is called when a signal is received
As per TA's instruction, in the case of a signal received by manage shuts down computation. */
void terminate(int signo) {
	
	if(signo==SIGINT) printf("MANAGE: signal INTR received\n");
	else if(signo==SIGHUP) printf("MANAGE: signal HUP received\n");
	else if(signo==SIGQUIT) printf("MANAGE: signal QUIT received\n");
	
	struct computeData terminate;
	terminate.type = 3;
	terminate.start =0;
	terminate.end =0;
	
	for(i=1; i<=30; i++) {
		if(pollarray[i].fd != -1) {
			
			/*send computes a msg to terminate*/
			if ((stream=fdopen(pollarray[i].fd,"w")) == (FILE *) -1 ) {
				perror("fdopen:");
				exit(1);
			}
			
			xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
			xdr_computeData(&handle, &terminate);
			
			fflush(stream);
			//printf("MANAGE: Terminate request sent to socket:%d\n", pollarray[i].fd);
			
			struct pollfd poller[1];
			poller[0].fd=pollarray[i].fd;     /* Accept Socket*/
			poller[0].events=POLLIN;
			poll(poller, 1, -1);
			struct manageData numtestmsg;
			if ((stream=fdopen(poller[0].fd,"r")) == (FILE *) -1 ) {
				perror("fdopen:");
				exit(1);
			}
			
			xdrstdio_create(&handle,stream,XDR_DECODE); /* get XDR handle */
			xdr_manageData(&handle, &numtestmsg);
			
			fflush(stream);
			//printf("MANAGE: numTest for terminate returned:%d from socket:%d\n", numtestmsg.value, pollarray[i].fd);
				statistics[i].numTested += numtestmsg.value;
			pollarray[i].fd = -1; //get rid of that compute- terminated
			
		}
		
	}
	
	
	
	exit(0);
}

int main(int argc, char* argv[]) {
	
	if(argc!=2) { printf("MANAGE: USAGE: ./manage portnumber \nTerminating.\n"); exit(1); }
	
	head = malloc(sizeof(node));//initialization of the linked list
	
	head->next = NULL;
	head->init = 0;
	head->offset = 0;
	
	
	for(i=0; i<21; i++) { //initialization
		statistics[i].numRange=0;
		statistics[i].numTested=0;
		statistics[i].perfIndex=0;
		statistics[i].fd = -1;
	}
	
	/* terminate routine will handle signals */
	signal(SIGINT, terminate);
	signal(SIGHUP, terminate);
	signal(SIGQUIT, terminate);
	
	
	
	/* set up IP addr and port number for bind */
	sin.sin_addr.s_addr= INADDR_ANY;
	sin.sin_port = atoi(argv[1]);
	
	/* Get an internet socket for stream connections */
	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("Socket");
		exit(1);
	}
	
	/* Do the actual bind */
	if (bind (s, (struct sockaddr *) &sin, sizeof (sin)) <0) {
		perror("bind");
		exit(2);
	}
	
	/* Allow a connection queue for up to 20 computes and 10 reports */
	listen(s,30);
	
	
	pollarray[0].fd=s;     /* Accept Socket*/
	pollarray[0].events=POLLIN;
	/* 30 possible */
	for (i=1;i<=30;i++) {pollarray[i].fd=-1;pollarray[i].events=POLLIN;}
	
	/* Now loop accepting connections */
	while (1) {
		
		poll(pollarray,31,-1);   /* no timeout, blocks until some activity*/
		
		/* Check first for new connection */
		if (pollarray[0].revents & POLLIN) {
			
			//printf("MANAGE: New connection established\n");
			len =sizeof(sin);
			if ((fd= accept (s, (struct sockaddr *) &sin, &len)) <0) {
				perror ("accept");
				exit(3);
			}
			
			for (i=1;i<=30;i++) if (pollarray[i].fd == -1) break;
				pollarray[i].fd=fd;
			
			hostentp=gethostbyaddr((char *)&sin.sin_addr.s_addr,
			sizeof(sin.sin_addr.s_addr),AF_INET);
			strcpy(statistics[i].hostName, hostentp->h_name);
			
		}
		
		else for(i=1;i<=30;i++) {
			if ((pollarray[i].fd !=-1) && pollarray[i].revents) {
				fd = pollarray[i].fd;
				
				
				struct manageData message;
				
				if ((stream=fdopen(fd,"r")) == (FILE *) -1 ) {
					perror("fdopen:");
					exit(1);
				}
				
				xdrstdio_create(&handle,stream,XDR_DECODE); /* get XDR handle */
				xdr_manageData(&handle, &message);
				fflush(stream);
				
				switch(message.type) {
					
					case(1): //new range request by a compute
						//printf("MANAGE: New range request received from socket:%d\n",fd);
						statistics[i].fd = fd;
						range.type = 1;
						
						if(message.time==-1) { //first time compute(no time info)
							x_offset = 30000; //fixed length for the first time
							dynamicMap(message.value); //find a range for us
						}
						
						else {
							//printf("time it took %d\n", message.time);
							if(message.time!=0) //to avoid floating point precision error dividing by zero
							/*simple ratio algorithm to adjust the length of the range*/
							x_offset = (15 * statistics[i].offset) / (message.time);
							else
								x_offset=30000;
							
							dynamicMap(message.value);
						}
						
						/*updating stat*/
						statistics[i].offset = x_offset;
						statistics[i].rangeArray[statistics[i].numRange].start =  range.start;
						statistics[i].rangeArray[statistics[i].numRange].end =  range.end;
						statistics[i].numRange++;
						
						if(statistics[i].numRange == 1000) { /*e.g. Assumptions*/
							//printf("number of ranges exceeded. Past range info will be overwritten\n");
							statistics[i].numRange=0;
						}
						
						
						if ((stream=fdopen(fd,"w")) == (FILE *) -1 ) {
							perror("fdopen:");
							exit(1);
						}
						
						xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
						
						xdr_computeData(&handle, &range);
						
						fflush(stream);
						//printf("MANAGE: New range sent to socket:%d\n", fd);
						break;
					
					
					case(2):; //stat request received from report --- ; for initialization
					//printf("MANAGE: Stat request received from socket:%d\n",fd);
					
					struct computeData test;
					test.type = 2;
					test.start =0;
					test.end =0;
					pollarray[i].fd = -1; // get rid of report
					
					
					for(i=1; i<=30; i++) {
						
						if(pollarray[i].fd != -1) {
							
							/*stat request send it to compute to get numTested*/
							if ((stream=fdopen(pollarray[i].fd,"w")) == (FILE *) -1 ) {
								perror("fdopen:");
								exit(1);
							}
							
							xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
							xdr_computeData(&handle, &test);
							
							fflush(stream);
							
							//printf("MANAGE: Stat request sent to socket:%d\n", pollarray[i].fd);
							
							struct pollfd poller[1];
							poller[0].fd=pollarray[i].fd;
							poller[0].events=POLLIN;
							poll(poller, 1, -1); //wait for the compute to answer
							struct manageData numtestmsg;
							if ((stream=fdopen(poller[0].fd,"r")) == (FILE *) -1 ) {
								perror("fdopen:");
								exit(1);
							}
							
							xdrstdio_create(&handle,stream,XDR_DECODE); /* get XDR handle */
							xdr_manageData(&handle, &numtestmsg);
							
							fflush(stream);
							//printf("MANAGE: numTest for stat request returned:%d from socket:%d\n", numtestmsg.value, pollarray[i].fd);
								statistics[i].numTested += numtestmsg.value;
						}
						
					}
					//send all the results to report. use fd
					
					for(i=1; i<21; i++) {
						
						if(statistics[i].fd != -1) {
							
							if ((stream=fdopen(fd,"w")) == (FILE *) -1 ) {
								perror("fdopen:");
								exit(1);
							}
							
							xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
							xdr_reportData(&handle, &statistics[i]);
							
							fflush(stream);
							sleep(1); //let report read it
						}
					}
					
					/*let report know that was all*/
					endofData.fd=-1;
					if ((stream=fdopen(fd,"w")) == (FILE *) -1 ) {
						perror("fdopen:");
						exit(1);
					}
					
					xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
					xdr_reportData(&handle, &endofData);
					
					fflush(stream);
					
					break;
					
					case(3): //report sent -k
					//printf("MANAGE: -k report received from socket:%d\n",fd);
					pollarray[i].fd = -1; // get rid of report.
					
					struct computeData terminate;
					terminate.type = 3;
					terminate.start =0;
					terminate.end =0;
					
					for(i=1; i<=30; i++) {
						if(pollarray[i].fd != -1) {
							
							/*send computes a msg to terminate*/
							if ((stream=fdopen(pollarray[i].fd,"w")) == (FILE *) -1 ) {
								perror("fdopen:");
								exit(1);
							}
							
							xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
							xdr_computeData(&handle, &terminate);
							
							fflush(stream);
							//printf("MANAGE: Terminate request sent to socket:%d\n", pollarray[i].fd);
							
							struct pollfd poller[1];
							poller[0].fd=pollarray[i].fd;    
							poller[0].events=POLLIN;
							poll(poller, 1, -1); //wait for computes to send a message back
							struct manageData numtestmsg;
							if ((stream=fdopen(poller[0].fd,"r")) == (FILE *) -1 ) {
								perror("fdopen:");
								exit(1);
							}
							
							xdrstdio_create(&handle,stream,XDR_DECODE); /* get XDR handle */
							xdr_manageData(&handle, &numtestmsg);
							
							fflush(stream);
							//printf("MANAGE: numTest for terminate returned:%d from socket:%d\n", numtestmsg.value, pollarray[i].fd);
								statistics[i].numTested += numtestmsg.value;
							pollarray[i].fd = -1; //get rid of that compute- terminated
							
						}
						
					}
					
					//send final results to report. use fd
					for(i=1; i<21; i++) {
						
						if(statistics[i].fd != -1) {
							if ((stream=fdopen(fd,"w")) == (FILE *) -1 ) {
								perror("fdopen:");
								exit(1);
							}
							
							xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
							xdr_reportData(&handle, &statistics[i]);
							
							fflush(stream);
							sleep(1);
						}
					}
					
					/*let report know that was all*/
					struct reportData endofData;
					endofData.fd=-1;
					if ((stream=fdopen(fd,"w")) == (FILE *) -1 ) {
						perror("fdopen:");
						exit(1);
					}
					
					xdrstdio_create(&handle,stream,XDR_ENCODE); /* get XDR handle */
					xdr_reportData(&handle, &endofData);
					
					fflush(stream);
					
					exit(0);
					
					break;
					
					
					case(4): //computes sending perf numbers
					//printf("MANAGE: Perfect number received:%d from socket:%d\n",message.value, fd);
					
					statistics[i].perfArray[statistics[i].perfIndex] = message.value;
					statistics[i].perfIndex++;
					
					break;
					
					
					case(5): //computes sending numTest after a signal
					//printf("MANAGE: received numTested from a terminating compute\n");
					
					statistics[i].numTested+=message.value;
					pollarray[i].fd = -1;
					
					break;
					
				}
				
			}
		}
	}
	return 0;
}

