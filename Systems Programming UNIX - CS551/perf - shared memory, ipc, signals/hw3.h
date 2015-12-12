/* header file for data structures used in shared mem */

struct stat {
	int pid;
	int numberFound;
	int numberTested;
	int numberSkipped;
};

#define SIZE ((1024000/(sizeof(int)*8))+1)  //integers covering from 0 to 1024000    (+1 for 1024000)

struct memory {
	int bitmap[SIZE]; // because of +1 also covering bit 1024000 in bitmap[32001]
	int perfArray[20];
	struct stat processArray[20];
};





  
