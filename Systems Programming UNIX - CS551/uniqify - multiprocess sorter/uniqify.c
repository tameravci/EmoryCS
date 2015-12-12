/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #2 - CS551
uniqify: To read a text file and output the unique words in the file sorted in alphabetic order. 

--------------
Design:
 
Main is the parent and also the parser. Parser distributes parsed words to a group of 
sorter children in a round-robin fashion. The number of sort processes is a command line
argument. The only limitation is bound to UNIX OS fd-descriptor and number of processes that can run
at one time. Finally, the sort processes write their individually sorted outputs to a single 
pipe that connects all of them to a suppressor process which is also a child of the main. 

Sort processes write their output only to a single pipe. This pipe is read by the suppressor process.
This makes the implementation of suppressor easier to read sorted outputs vs reading multiple pipes between
sorters and suppressors to avoid filling up/blocking as well as finding the EOF of multiple pipes. 

Suppressor creates a temp file stream and writes the inputs from the sorter processes.
Because the inputs were individually sorted, suppressor uses the sort command with that
file stream argument before counting duplicates.

This makes the implementation of counting the duplicates much more efficient than an alternative
sorting algorithm that would compare each word against all the other words leading to a huge
time complexity.  

Sorter processes create intermediate file streams that are deleted at the end of the program
from the directory. 

Parsing is called after all the processes are up and running and waiting to read from the pipes. This is 
crucial and makes sure that no pipe is blocked with input data.

Parent waits for all children to complete and returns. 

-------------------------
Assumptions: 

Since apostrophe (') does not delimit a word, I wanted the parser to treat (')s as an acceptable character.  
For example:
don't, isn't, aren't, or even '''' (or any combination of ' and alphabetic chars) would all count as a word.

Uniqify is tested up to and including 5 sort processes. Any number greater than that also seemed to work. However, I cannot
guarentee that unexpected behavior will not occur with more than 5 processes.

Parser waits two seconds in case the pipe is full for a given child sorter to drain the data
in the pipe.

Tested with 34 MB, 6.5 MB, and various smaller input file sizes as well as stdin. 

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


/*
Declaration of functions and global variables to be used in the code
*/
void parse(FILE *input, int numProc, FILE** file_ps, int fd_ps[][2]);
void usage();

/*
PARSER---------------------------

Parse function starts reading input from stdin until it hits EOF or user hits CTRL-D. It only takes alphabetics words and makes them lower-case.
It distributes each word round-robin to sort-processes available. 
It also closes down parent's write pipes. Note that parse function gets called in the parent process after every process has been created including the sorts and suppressor.
Input: FILE stream, in this case stdin, number of processes, file streams that are opened by the write-pipe of the parent, and write pipes of the parent
Output: void
*/ 
void parse(FILE *input, int numProc, FILE** file_ps, int fd_ps[][2])
{
	int index = 0; //process distributor
	int c; //character to be read
	int countChar = 0; //character count for a single word parsed
	int found_word = 0; //flag
	char wordarray[41]; //array to store words
	int pipe = 0; //pipe counter to close
	while ((c = fgetc(input)) != EOF) //read until CTRL+D is hit or EOF is reached
	{
		if((!isalpha(c)) && (countChar>40)) countChar=0; //for words above 40 char find a delimiter and reset countChar (truncate)
		if ((isalpha(c) && countChar<40) || (c==39 && countChar<=40) ) //alphabetic char or apostrophe'
		{
			
			found_word = 1; //found-word set 1, not gonna store it yet, waiting for word to be complete (then goes to else)
			if(c!=39)
				c = tolower(c); //if it's not ' lower case it
			wordarray[countChar] = c; //add to word
			countChar++;
		}
		else {
			if(countChar<3) { //words shorter than 3 chars
				countChar=0; 
				continue;
			}
			if (found_word || countChar==40) {
				
				wordarray[countChar] = '\n';
				countChar++;
				
				while(fwrite(wordarray, 1, countChar, file_ps[index])!=countChar) { //try to write, wait otherwise
					sleep(2);
				}
				fflush(file_ps[index]);
				found_word=0; //go to next word
				
				if(countChar!=41) countChar=0; // don't reset it if it's longer than 40, because we want to truncate the word
				
				if(index==numProc-1) {  //round-robin distribution requires process reset
					index=0;  //go back to process 1
				}
				else index++; // next sort-process
				}
		}
	}
	//printf("parsing is done...(parent)\n");
	for(pipe; pipe<numProc; pipe++){ //close all the write-pipes of the parent
		close(fd_ps[pipe][1]);
	}
	return;
}
/*
Prints usage if the user has not given the number of processes they wish to use and exits the program.
*/ 
void usage() {
	printf("You have to pass a number of processes as an argv command\n");
	exit(0);
}




/* MAIN PARENT PROCESS -----------------------------
*/
int main (int argc, char **argv)
{
	if (argc != 2 || atoi(argv[1]) < 1) {
		usage();
	}

	int numProc = atoi(argv[1]);   // Number of sort processes

	int fd_ps[numProc][2]; //pipes between parent and sort processes
	int fd_ss[numProc][2]; //pipes between sorts and suppressor

	//File streams for pipe I/O
	FILE * file_ps[numProc]; //file stream for parent to write on after parsing - must be open with parents write pipe
	FILE *incoming_sort[numProc]; //file stream for sorter to read whatever is in the pipe
	FILE* fd_sorted[numProc]; //file stream for writing whatever's read from parent pipe in sorter
	
	pid_t childPid[numProc]; //to store child pids in an array to wait after


	/* this creates intermediate file-names for sort processes to write on. 
        They will be used in giving the file names in open in sort processes 
	Also allows unlimited number of sort processes to be created --- NO SOLID TEST DATA ABOVE 5 Processes*/

	int i=0;
	char name[numProc][50];
	//printf("creating sorting processes...(parent)\n");
	for(i; i<numProc; i++) { 
		char number[50];
		sprintf(number, "%d", i);
		sprintf(name[i], "%s", "file");
		strcat(name[i], number);
	}

	i=0; // resetting i
	
	for(i; i<numProc; i++) {
		
		pipe(fd_ps[i]); //pipes open between parent and sorts
		pipe(fd_ss[i]); //pipes open between sorts and suppressor
		
		childPid[i] = fork(); //fork-off all the sort processes


/* SORTER PROCESSES -------------------------------------
*/
		if (childPid[i] == 0) { //Sorter-child

			char buf[40]; //buffer to read
			close(fd_ps[i][1]); //closing write pipe of child from parser
			close(fd_ss[0][0]); //closing read pipe of child to suppressor

			int numRead;
			
			fd_sorted[i] = fopen(name[i], "a+"); //create a file to write on as parsed words are read from the read-pipe
			if(fd_sorted[i]==NULL) perror("Error opening the file");
			incoming_sort[i] = fdopen(fd_ps[i][0], "r");
			if(incoming_sort[i]==NULL) perror("Error opening the file");
			
			//printf("waiting for parse output...(sort%d)\n", i+1);
			

				/* start reading the pipe to make sure we drain bytes from the pipe to avoid filling up */

				while(fgets(buf, 42, incoming_sort[i])!=NULL) {

					int read = fputs(buf, fd_sorted[i]);
					if(read == EOF) { 
						perror("fputs failed");
					}
				}
			
			fclose(fd_sorted[i]);                              /* to flush the file stream */
			fd_sorted[i] = fopen(name[i], "r");		/* to re open*/
			if(fd_sorted[i]==NULL) perror("Error opening the file");		   
			
			if (dup2(fileno(fd_sorted[i]), 0) == -1) {                  /* re-directing the file to stdin so that sort thinks the file is stdin */
				perror("Failed to redirect stdin");
			}
			
			if (dup2(fd_ss[0][1], 1) == -1)  {                   /* re-directing the pipe to stdout so sort outputs everything to the pipe between sort and 										suppressor */
				perror("Failed to redirect stdout");
			}

			
			if(execl("/bin/sort", "sort", NULL)==-1) printf("sort failed\n");
			_exit(-1);
		}
		
		else { // Back to parent
			close(fd_ps[i][0]); //close read pipe of parser to sorter
			file_ps[i] = fdopen(fd_ps[i][1], "w"); // open up a file stream to write the parsed words and use the write pipe for that
			if(file_ps[i]==NULL) perror("Error opening the file");
		}
		
	}
	

	pid_t childpid; // to get the suppressor's pid
	
	childpid = fork();


/* SUPPRESSOR PROCESS ----------------------------------------
*/
	if(childpid == 0) { //Suppressor

		i=0;
		for(i; i<numProc; i++)
			close(fd_ps[i][1]); //close down the write pipe of the parent to sorter. This allows sorter to not hang in forever because every fd is cloned.
		
		FILE * merge_file = fopen("merge_file", "a+"); //open up a merge-file
		if(merge_file==NULL) perror("Error opening the file");
		FILE * incoming_file;

		close(fd_ss[0][1]); // close the write pipe of the sorter
		incoming_file = fdopen(fd_ss[0][0], "r"); //open the incoming file from one single huge pipe that all sorters wrote to
		if(incoming_file==NULL) perror("Error opening the file");
		
		i=0;
		
		char str[40];
		//printf("reading and writing from sort...(suppressor)\n");
		while(fgets(str, 42, incoming_file)!=NULL)  {
			fwrite(str, strlen(str), 1, merge_file);
		}
		
		fclose(merge_file);

		if(numProc!=1) {  /* because the incoming files were only individually sorted */
			if(system("sort -o merge_file merge_file")==-1) 
				printf("error sorting the merge file\n");
		}

		merge_file = fopen("merge_file", "r");
		if(merge_file==NULL) perror("Error opening the file");

		char oldst[40];
		char string[40];
		int count = 0;
		int first = 1; //to copy the first string only
		int empty = 1; //for empty inputs & for inputs that have no parsed words
		//printf("counting almost there...(suppressor)\n");
		while (fgets(string, 42, merge_file)!=NULL) {
			empty = 0;
			if(count==0 && first == 1) strcpy(oldst, string); //only for the first time
			
			if(strcmp(string, oldst) == 0) {
				count++;
			}
			
			else {
				printf("%5d %s", count, oldst);
				strcpy(oldst, string);
				count = 1; //not reset to 0 because you already found a different word
				first = 0;
			}
		}
		if(!empty)
			printf("%5d %s", count, oldst);
		else
			printf("Parser returned no words.\nIt means any combination of the following:\n1- You typed nothing\n2- You have failed to enter alphabetic words\n3- You have entered words that are shorter than 3 characters\n");
		system("rm merge_file");
		exit(-1);
	}
	
	
	/* Call parse only when all the processes are up and running to avoid blocking of the pipes. 
	This means every process is ready to read from the pipes */
	
	parse(stdin, numProc, file_ps, fd_ps);  

	i=0;
	for(i; i<numProc; i++) {

		close(fd_ss[0][1]); //close down all sorter-suppressor write pipes in the parent process
		waitpid(childPid[i], NULL, 0); //wait for all sort-processes to die. Avoid zombies!!

		/* delete all the intermediate files that sorters used from the dir */
		char src[50], dest[50];
		strcpy(src,  name[i]);
		strcpy(dest, "rm ");
		strcat(dest, src);
		system(dest);
	}

	waitpid(childpid, NULL, 0); //wait for suppressor to die
	return 0;
}
