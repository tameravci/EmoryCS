/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS OR OTHER SOURCES- TAMER AVCI #2105024

Author: Tamer Avci
Assignment #4 - CS551
Computation with POSIX Threads

This project computes perfect numbers using POSIX Threads. 

*/

int idx = 0; //index to store threads
int perfIndex = 0; //index to store perfect numbers
int count = 0; //for control thread = number of threads running

int BLOCK; 
int MAX;
int* bitmap_block; //bitmap
clock_t start_clock, end;
double cpu_time_used;
time_t start, stop;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //mutex for shared resources
pthread_attr_t tattr;
pthread_cond_t count_cond = PTHREAD_COND_INITIALIZER; //condition variable for control thread


struct threadStat *report_stat; //pointer to struct for report statistics


struct threadStat { //struct for report thread statistics
	pthread_t tid;
	int numTested;
	int numSkipped;
	int blockNumber;
	int isIdle;
	pthread_cond_t cond;
};

struct entry *perfectArray; //struct to store perfect numbers with thread ids

struct entry { // single entry for struct perfectArray
	pthread_t tid;
	int perfectNumber;
};


void *computePerfect(); //algorithm in signals.c
void quit(); //algorithm for quit call
void *terminate(); //algorithm for control thread

	int cmpfunc (const void * a, const void * b) //quick sort compare function
{
   return ( *(int*)a - *(int*)b );
}

int testBit( int A[ ],  int k) {

	return ( (A[k/(sizeof(int)*8)] & (1 << (k%(sizeof(int)*8)) )) != 0 ) ;
}


void  setBit( int A[ ],  int k ) {

	A[k/(sizeof(int)*8)] |= 1 << (k%(sizeof(int)*8));  // Set the bit at the k-th position in A[i]
}
