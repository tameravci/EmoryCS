/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024
myar - a replication of Linux ar
Author: Tamer Avci
Assignment #1 - CS551
*/

/*
Assumptions: Following the assignment handout as is, especially, 'all the files are in the same directory' and 'file names are tops 15 characters'. myar executable should be placed in the same directory as the files. Smybolic links must also be in the current directory and should be created linking files in the same directory
giving the filename only. Ex: ln -s file1 link1  => pathnames should be avoided as they are both in the same directory.
In addition, I also assumed not to create symbol table for .o object files as per teacher's instruction. ar.h header structure is used as is. Also assuming enough disk space to write files.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ar.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ar.h>
#include <errno.h>
#include <string.h>
#include <utime.h>
#include <dirent.h>
#include <fcntl.h>

/*
Declaration of functions and global variables to be used in the code
*/
int isArchive(int fd);
char * get_fileName(struct ar_hdr * header);
void createArchive(char * archive);
int fd; //archive's file descriptor
void myAppend(char *archive, char *file);
int fd2; //input file descriptor
struct ar_hdr* getHeader(char * archive);
void header_skip(struct ar_hdr * header);
void qlink(char * archive, char * file, struct stat buf);
void extract(char * name, int size);
void extracto(char * name, int size, int mtime, struct ar_hdr *header);
int contentSize;struct dirent *ep;
void appendLink(char *file);

/*
Creates a string and reads the first 8 bytes of the alleged archive file
and returns 0 if the comparison is correct with the magic string
Parameters: fd of the archive file
Output: 0 if the comparison is correct, -1 otherwise
*/ 
int isArchive(int fd) {
    char magic_string[SARMAG];
    read(fd, magic_string, SARMAG);
    magic_string[SARMAG] = '\0';
    if (strcmp(magic_string, ARMAG))
        return 0;
    return -1;
}

/*
Using the ar_name in header file this function turns ar_name into a string by placing
\0 at the place where we have a / and returns ar_name string
Parameters: header pointer
Output: Returns the name without the slash
*/
char *get_fileName(struct ar_hdr * header) {
    int i = 0;
    while(header->ar_name[i] != '/') //assuming no path names given due to assumption declared above (same directory)
        i++;
    header->ar_name[i] = '\0';
    return header->ar_name;   
}

/*
Creates an archive if the archive did not exist with the given name archive input
Writes the magic string into file's first 8 bytes
Parameters: archive name pointer
*/
void createArchive(char * archive) {
    
    fd = open(archive, O_RDWR | O_CREAT, 0666);
    if(fd < 0){ perror("Error"); return;}
    char buf[SARMAG] = ARMAG;
    buf[SARMAG]= '\0';
    write(fd, buf, SARMAG);
}

/*
Checks if file exists and then appends it at the end of the file by
creating a header first and writing the content after
Checks if the boundary is odd or even and puts /n appropriately
Parameters: Archive name and file name
*/
void myAppend(char * archive, char * file) {
    lseek(fd, 0, SEEK_END); //going to the end of file
    fd2 = open(file, O_RDONLY); 
    if(fd2 < 0){ perror("Error"); return;}
    struct stat st;
    if (stat(file, &st)==-1) printf("stat did not work\n");
    struct ar_hdr header; //creating the header
    sprintf(header.ar_name, "%-16s", file);
    header.ar_name[strlen(file)] = '/'; // putting the terminating character
    sprintf(header.ar_date, "%-12d", (int)st.st_mtime);
    sprintf(header.ar_uid, "%-6d", (int)st.st_uid);
    sprintf(header.ar_gid, "%-6d", (int)st.st_gid);
    sprintf(header.ar_mode, "%-8o", st.st_mode);
    sprintf(header.ar_size, "%-10d", (int)st.st_size);
    sprintf(header.ar_fmag, "%s", ARFMAG);

    write(fd, (char*)&header, sizeof(header)); //writing the header

    //writing the content
    int a = st.st_size;
    char *buffer = malloc(a);
    read(fd2, buffer, a);
    write(fd, buffer, a);

    //even odd boundary check
    if ((st.st_size % 2) == 1) {
        write(fd, "\n", 1);
    }
    free(buffer);
}

/*
Almost same as myAppend, except this time we put the contents of the symbolic link as file content
however keep the file name as the smybolic name's name. Inspired by ar. For function q
Parameters: Archive name, symbolic link name(char*file), lstat struct for symlink)
*/
void qlink(char * archive, char * file, struct stat buf) { // THIS IS FOR function q for symbolic links
    char * bufferpath = malloc(buf.st_size);
    readlink(file, bufferpath, buf.st_size);
    lseek(fd, 0, SEEK_END); //going to the end of file
    fd2 = open(bufferpath, O_RDONLY); 
    if(fd2 < 0){ perror("Error"); return;}
    struct stat st;
    if (stat(file, &st)==-1) printf("stat did not work\n");
    struct ar_hdr header; //creating the header
    sprintf(header.ar_name, "%-16s", file);
    header.ar_name[strlen(file)] = '/'; // putting the terminating character
    sprintf(header.ar_date, "%-12d", (int)st.st_mtime);
    sprintf(header.ar_uid, "%-6d", (int)st.st_uid);
    sprintf(header.ar_gid, "%-6d", (int)st.st_gid);
    sprintf(header.ar_mode, "%-8o", st.st_mode);
    sprintf(header.ar_size, "%-10d", (int)st.st_size);
    sprintf(header.ar_fmag, "%s", ARFMAG);

    write(fd, (char*)&header, sizeof(header)); //writing the header

    //writing the content
    int a = st.st_size;
    char *buffer = malloc(a);
    read(fd2, buffer, a);
    write(fd, buffer, a);

    //even odd boundary check
    if ((st.st_size % 2) == 1) {
        write(fd, "\n", 1);
    }
    free(buffer);
}



/* Appends symbolic link by using lstat-- this function is for A
Parameter: file name
*/
void appendLink(char *file) {
    lseek(fd, 0, SEEK_END);
    // create Header
    struct stat st;
    if (lstat(file, &st)==-1) printf("stat did not work\n");
    struct ar_hdr header;
    
    sprintf(header.ar_name, "%-16s", file);
    header.ar_name[strlen(file)] = '/';
    sprintf(header.ar_date, "%-12d", (int)st.st_mtime);
    sprintf(header.ar_uid, "%-6d", (int)st.st_uid);
    sprintf(header.ar_gid, "%-6d", (int)st.st_gid);
    sprintf(header.ar_mode, "%-8o", st.st_mode);
    sprintf(header.ar_size, "%-10d", (int)st.st_size);
    sprintf(header.ar_fmag, "%s", ARFMAG);

    write(fd, (char*)&header, sizeof(header));
    
    // put content
    int a = st.st_size;
    char *buffer = malloc(a); 
    if(read(fd2, buffer, a)!=a) printf("read did not work");
    if(write(fd, buffer, a)!=a) printf("write did not work");

    //boundary check
    if ((st.st_size % 2) == 1) {
        write(fd, "\n", 1);
    }
    free(buffer);
}


/* Printing permissions
Parameters: ar_mode in the header
*/
void print_mode(char * st_mode){

  char *ptr;
  long mode;

   mode = strtol(st_mode, &ptr, 8);

    if (mode & 00400)
        putchar('r');
    else
        putchar('-');
    
    if (mode & 00200) // look into this
        putchar('w');
    else
        putchar('-');
    
    if (mode & 00100)
        putchar('x');
    else
        putchar('-');
    
    if (mode & 00040)
        putchar('r');
    else
        putchar('-');
    
    if (mode & 00020)
        putchar('w');
    else
        putchar('-');
    
    if (mode & 00010)
        putchar('x');
    else
        putchar('-');
    
    if (mode & 00004)
        putchar('r');
    else
        putchar('-');
    
    if (mode & 00002)
        putchar('w');
    else
        putchar('-');
    
    if (mode & 00001)
        putchar('x');
    else
        putchar('-');
}

/*
Creates / overwrites a new file with the given name and size from the header
Reads the content from the archive. Puts the cursor in the archive back to the end of header (the main function skips the content)
Writes in the file created for extraction. The amount is specified by the size of the file
Parameters: File name and size
*/
void extract(char * name, int size) {
    int newFile = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(newFile < 0){ perror("Error"); return;}
    char * buffer = malloc(size);
    read(fd, buffer, size);
    lseek(fd, -size, SEEK_CUR);
    write(newFile, buffer, size);
    close(newFile);
}

/* Same function except this time we change the mtime to the time we stored in the header ar_date
Permission are also transferred directly from the header
Parameters: Name, size of the file + mtime of the file in the header, and the header
*/
void extracto(char *name, int size, int mtime, struct ar_hdr *header) {
    
    int newFile = open(name, O_RDWR | O_CREAT | O_TRUNC, header->ar_mode);
    if(newFile < 0){ perror("Error"); return;}
    char * buffer = malloc(size);
    read(fd, buffer, size);
    lseek(fd, -size, SEEK_CUR);
    write(newFile, buffer, size);
    //mtime modification
    struct stat st;
    if (stat(header->ar_name, &st)==-1) printf("stat did not work\n");
    struct utimbuf time;
    struct tm* timeinfo;
    time_t totaltime = atoi(header->ar_date);
    time.modtime = totaltime;
    time.actime =  totaltime;
    
    utime(name, &time); //setting-changing the time of the file
    close(newFile);
}

/*
Main function uses if-else if operators to control command line arguments.
It prints the usage if user failed to comply with usage settings.
*/

int main( int argc, char * argv [] ) {
    struct ar_hdr *header;
    char buffer[60]; // buffer to use for headers
    char *file_name; // pointer for the file names in the headers
    char * archive; // pointer to header names


     //USAGE
	if(argc<3) {

		printf("\nUsage: %s key afile name ... \n", argv[0]);
		printf("q quickly append named files to archive \n");
		printf("x extract named file \n");
		printf("xo extract named file restoring mtime \n");
		printf("t print a concise table of contents of the archive \n");
		printf("tv print a verbose table of content of the archive \n");
		printf("d delete named files from archive \n");
		printf("A quickly append all regular files in the current directory \n\n");
		exit(0);

	}
    // t - LIST OF FILES IN THE ARCHIVE -------------------------------------
         else if(strcmp(argv[1], "t")==0) {
            archive = argv[2]; //Setting archive name
            fd = open(archive, O_RDONLY); //Opening archive read-only with fd
            
            if (fd < 0) {
                perror("Error");
                return -1;
            }
            
            if(!isArchive(fd)) { //Checking if archive exists
                printf("Error: invalid archive type \n");
                exit(EXIT_FAILURE);
            }
            
            while(read(fd, buffer, sizeof(buffer)) == sizeof(buffer)) { //Reading the first header into the buffer(global variable)
                header = (struct ar_hdr *) malloc(sizeof(struct ar_hdr));
                header = (struct ar_hdr*)buffer;
                file_name = malloc(sizeof(char)*16); //Allocating memory for the file name in the header
                file_name = get_fileName(header); //Getting ar_name in the header
		printf("%s\n", file_name); //Printing the file names
                contentSize = atoi(header->ar_size);
                
                if(contentSize%2) contentSize += 1; //Skipping appropriate content sizes (even-odd)
                lseek(fd, contentSize, SEEK_CUR);
            }
            
            if (close(fd) == -1)
                exit(EXIT_FAILURE);
         }
               // tv - VERBOSE LIST ----------------------------------------------
         else if(strcmp(argv[1], "tv")==0) {
            
            archive = argv[2];
            fd = open(archive, O_RDONLY);
            
            if (fd < 0) {
                perror("Error");
                return -1;
            }
            
            if(!isArchive(fd)) { //check if archive is really an archive file
                printf("Error: invalid archive type \n");
                exit(EXIT_FAILURE);
            }
            
            while(read(fd, buffer, sizeof(buffer)) == sizeof(buffer)) {
                header = (struct ar_hdr*) malloc(sizeof(struct ar_hdr));
                header = (struct ar_hdr*)buffer;
                file_name = (char*)malloc(sizeof(char)*16);
                file_name = get_fileName(header);
                print_mode(header->ar_mode); //This function handles printing of the permissions

		//Calculating the current time
                char date[30];
                struct tm* timeinfo;
                time_t totaltime = atoi(header->ar_date); //gets the mtime
                timeinfo = localtime(&totaltime);
                strftime(date, 30, "%b %d %R %Y", timeinfo);
                printf(" %d/%d%7d %s %s\n", atoi(header->ar_uid),atoi(header->ar_gid), atoi(header->ar_size), date, file_name);
                
                // skip content
                contentSize = atoi(header->ar_size);
                
                if(contentSize%2) contentSize += 1;
                // jump to next header
                lseek(fd, contentSize, SEEK_CUR);
            }
        }

	// q - APPEND ----------------------------------------------------- Assumption: Even the symbolic links must refer to files in the same directorymy
   else if(strcmp(argv[1], "q")==0) {

            archive = argv[2];
            fd = open(archive, O_RDWR);

            if (fd < 0) { // archive does not exist
		printf("myar: creating file %s\n", argv[2]);
                close(fd);
                createArchive(archive);  //create one with magic string
                int i;

                for (i=3; i<argc; i++) {

		        struct stat buf; //Reserve buf for stat
			int x = lstat (argv[i], &buf);
			if (S_ISLNK(buf.st_mode)) { //if the file is a symbolic link
				qlink(archive, argv[i], buf);
			} 
			else	 
				myAppend(archive, argv[i]); // All regular files	

                  
                }
                
            }
            else { // archive exists or user trying to input a different file

                if(!isArchive(fd)) {
                    printf("myar: File format not recognized\n"); // archive is not the right format
                    return -1;
                }

                else {  //archive exists, append files to the end
                    int i;
                    for (i=3; i<argc; i++) {
                         struct stat buf;
			int x = lstat (argv[i], &buf);
			if (S_ISLNK(buf.st_mode)) {
				qlink(archive, argv[i], buf);
			} 
			else {	 
				myAppend(archive, argv[i]);
			}
                     
                    }

                }
            }
            
        }
	  // x - EXTRACT ---------------------------------------------------
          else if(strcmp(argv[1], "x") == 0) {
            archive = argv[2];
            fd = open(archive, O_RDWR);
            
            if (fd < 0) {
                printf("myar: %s: No such archive found\n", argv[2]);
                return -1;
            }
            
            if(!isArchive(fd)) { //check if archive is really an archive file and skip magic string
                printf("Error: invalid archive type \n");
                exit(EXIT_FAILURE);
            }
            
            while(read(fd, buffer, sizeof(buffer)) == sizeof(buffer)) { //read the headers
                header = (struct ar_hdr *) malloc(sizeof(struct ar_hdr));
                header = (struct ar_hdr*)buffer;
                file_name = malloc(sizeof(char)*16);
                file_name = get_fileName(header); //get the file names in the header
                int i;
                for (i=3; i<argc; i++) {
                    if(strcmp(argv[i], file_name) == 0) 
			extract(file_name, atoi(header->ar_size)); //extract
                }
                 contentSize = atoi(header->ar_size); //Skip contents accordingly
                if(contentSize%2) contentSize += 1;
                lseek(fd, contentSize, SEEK_CUR);
            }
	}

	// d - DELETE ------------------------------------------------------
	else if(strcmp(argv[1], "d") == 0) { 
 
            archive = argv[2];
            fd = open(archive, O_RDONLY);
            
            if (fd < 0) {
                perror("Error");
                return -1;
            }
            
            if(!isArchive(fd)) { //check if archive is really an archive file and skip magic string
                printf("Error: invalid archive type \n");
                exit(EXIT_FAILURE);
            }
	    int oldfd = fd; // create a new fd - essentially a new archive
	    unlink(archive); // remove old one - the archive is still open though
	    createArchive(archive); // create the new archive = fd

		while(read(oldfd, buffer, sizeof(buffer)) == sizeof(buffer)) { //read from the old archive
		        header = (struct ar_hdr *) malloc(sizeof(struct ar_hdr)); // old header
		        header = (struct ar_hdr*)buffer;
		        file_name = malloc(sizeof(char)*16);
		        file_name = get_fileName(header); // get the file names from old archive
		        int i;
		        int skip=0;
			for(i=3; i<argc; i++) {
				if(strcmp(argv[i], file_name) == 0) { //check if the input argument files match the file names in the header
					skip = 1; //if that's true we should not copy this file to the new archive because we want to get rid of it so skip is flagged
					break;
				}
			}
				        
			if(!skip) { //if the skip is not flagged, we have got a file that we do not want to delete, so copy it to new archive
				write(fd, buffer, 60); // we had stored the header into buffer. Write it to the new archive
				contentSize = atoi(header->ar_size); 
				char *contentbuf = malloc(contentSize);
				read(oldfd, contentbuf, contentSize); //Put the content from the old archive to contentbuf
				write(fd, contentbuf, contentSize); //Write the content to the new archive			

					 
				if(contentSize%2) { //even odd boundary
					lseek(oldfd, 1, SEEK_CUR); //for the old archive
					write(fd, "/n", SEEK_CUR); //for the new archive do not lseek because you are at EOF. Write one character /n
				}
		        }

			else { // if the skip is flagged we just need to continue
				argv[i][0] = 0; //this is due to operation on the first file matched in the archive. We do not want to delete all instances of one file in an archive, so change the name of the input argument so we can copy the other instances of the same file if there are any
				contentSize = atoi(header->ar_size);
                		if(contentSize%2) contentSize += 1; //even odd boundary
                		lseek(oldfd, contentSize, SEEK_CUR);
		        }
               }
	       close(oldfd);
	}

	// A - APPEND ALL IN THE CURRENT DIR -------------------------------------------------
	 else if(strcmp(argv[1], "A")==0) {
		archive = argv[2];
                fd = open(archive, O_RDWR);
		if (fd < 0) { // archive does not exist
		printf("myar: creating file %s\n", argv[2]);
                close(fd);
                createArchive(archive);  //create one with magic string
		}
	
 		if(!isArchive(fd)) {
                    printf("myar: File format not recognized\n"); // given file is not the right format
                    return -1;
		}
;
		DIR *dp; ;
		//struct dirent *ep;

		dp = opendir ("./");
		if (dp != NULL) {
		    int x;
		    
		    while (ep = readdir (dp)) { //Read the dir entries one by one
			struct stat buf;
			x = lstat ((ep->d_name), &buf);
			if (S_ISLNK(buf.st_mode)) { // if it's a symbolic link
				fd2 = open(ep->d_name, O_RDWR);
				if(strcmp(ep->d_name, argv[2])!=0) //all files except the archive itself
					appendLink(ep->d_name); //append the link itself not the file
			}

			else {
			x = stat ((ep->d_name), &buf);
			if (S_ISREG(buf.st_mode)) {
				fd2 = open(ep->d_name, O_RDWR);
				if(strcmp(ep->d_name, argv[2])!=0) //all files except the archive itself			
					myAppend(archive, ep->d_name); //append regular files
		   	}
			}
		    }
		    (void) closedir (dp);
	      }
	      else
		  perror ("Couldn't open the directory");

	}

	// xo - EXTRACT WITH RESTORED TIME -------------------------------------------------
  	 else if(strcmp(argv[1], "xo") == 0) {
	    archive = argv[2];
            //archive = argv[3]; //read archive file
            fd = open(archive, O_RDWR);
            
            if (fd < 0) {
                perror("Error");
                return -1;
            }
            
            if(!isArchive(fd)) { //check if archive is really an archive file and skip magic string
                printf("Error: invalid archive type \n");
                exit(EXIT_FAILURE);
            }
            
            while(read(fd, buffer, sizeof(buffer)) == sizeof(buffer)) { //print the file names
                header = (struct ar_hdr *) malloc(sizeof(struct ar_hdr));
                header = (struct ar_hdr*)buffer;
                file_name = malloc(sizeof(char)*16);
                file_name = get_fileName(header);
                int i;
                for (i=3; i<argc; i++) {
                    if(strcmp(argv[i], file_name) == 0) {
		    	struct stat st;
			if (stat(file_name, &st)==-1) printf("stat did not work\n");
			int mtime = (int) st.st_mtime; 
			extracto(file_name, atoi(header->ar_size), atoi(header->ar_date), header); //extract it and pass ar_date and header to restore mtime and permissions
		    }
                }
                 contentSize = atoi(header->ar_size);
                if(contentSize%2) contentSize += 1;
                lseek(fd, contentSize, SEEK_CUR);
            }
	}

	else { //Print usage
		printf("\nUsage: %s key afile name ... \n", argv[0]);
		printf("q quickly append named files to archive \n");
		printf("x extract named file \n");
		printf("xo extract named file restoring mtime \n");
		printf("t print a concise table of contents of the archive \n");
		printf("tv print a verbose table of content of the archive \n");
		printf("d delete named files from archive \n");
		printf("A quickly append all regular files in the current directory \n\n");
	}		                
}
