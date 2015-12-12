/* Collaboration Statement:
TAMER AVCI #2105024 I worked on this assignment alone, using only this semester's course materials.
*/

#include <stdlib.h>
#include <stdio.h>
#include "header.h"


void clearAll()   
{

	seg * current = head; // start at first element
	int i;
	while( current != NULL ) {
    		for(i=0; i<256; i++ ) // go through every bit[]
        		current->bits[i] = 0;  // modify bits inside
    	current = current->next; // go to next segment
	}
}
	


/* ---------------------------------------------------------
   setBit( n ): set the bit corresponding to the bit position n
   --------------------------------------------------------- */
void setBit( int n ) // bit position not the number
{ 

	int x;       //segment number
	int i;       // Index of bits[] (#row) -- max 256 rows per segment
	int pos;     // Bit position in bits[i] -- which bit of those 32

	x = n / (8*sizeof(int)*256); // which segment are we at
	seg * p = head; //starting at first segment
	int j;
	for( j=0; j < x; j++) // go to that segment
		p = p->next;  

	i = n/32 %256; // Index of bits[] -32 bits per row (#row) --  % max 256 rows per segment
	pos = n%32; //which bit of those 32

	p->bits[i] = p->bits[i] | (1 << pos) ; //set that bit to 1 ---not prime
}

/* -------------------------------------------------
   testBit( n ): return 1 if bit n is RESET
   ------------------------------------------------- */
int testBitIs0( int n ) //bit position
{
	int x;        //segment number
	int i;       // Index of bits[]
	int pos;     // Bit position in bits[i]
	int r;       // result

	x = n / (8*sizeof(int)*256); // which segment are we at
	seg * p = head;   //starting at first segment
	int j;
	for( j=0; j < x; j++) // go to that segment
		p = p->next; 
	
	i = n/32 %256; // Index of bits[] -32 bits per row (#row) --  % max 256 rows per segment
	pos = n%32;  //which bit of those 32

	r = p->bits[i] & (1 << pos) ; // Get bit at pos in bits[i] -- r will be 0 if prime, else r will be 1

	if ( r == 0 ) 
		return 1;        // return 1 to indicate that n is still prime
	else
		return 0;        // not prime
}

int countPrimes( int n ) // number!
{  
	int count, i;
	count = 1; // start by counting 2 as prime
	int x = ((n-1)/2) / (8*sizeof(int)*256);  // which segment are we at -- divide (n-1)/2 because n is the number (n-1)/2 is the bit position

	for (i=0; i<=(n-1)/2; i++) { // go through every bit up until the bit that represents n
		if(testBitIs0(i)) // check if prime
			count++;  // increment
	}

	return count;
		
}

void printPrimes(int n)
{
   
	int i;
	printf("2 "); //start with 2
	for ( i = 0; i <=(n-1)/2; i++ ) { // print until the bit that represents the number
		if ( testBitIs0(i) ) // check if prime
			printf("%d ", 2*i+1 ); // print
	}
   	printf("\n\n");  	
}


void sieveOfE(int N)
{
	int i, j, k;

	setBit( 0 );    // 1 is not prime

   /* ------------------------
      Perform the sieve of E
      ------------------------ */
	k = 1;   // Start with 3 to find all primes skip 1

	while ( k <= (N-1)/2 )   {

	
		j=0; // reset j
      /* ----------------------------------------
         Starting from k, find next 
         prime number number 2*i + 1 located at i
         ---------------------------------------- */
		for ( i = k; i <= (N-1)/2; i++ )
			if ( testBitIs0(i) )
				break;             // Prime number Found !

      /* --------------------------------------
         Set:  every odd multiple of that prime number 
         -------------------------------------- */
		
		for ( j = 3*i+1; j <= (N-1)/2; j= j+2*i+1 )
	  		setBit(j);

		k = i+1;    // Set up k for next iteration !!!   
	}
}


void factor(int n) {


	int i;
	if ( n > 9999999) 
		printf("large number..computing...please wait\n");


	/*
	the following part guarentees to create the required number of segments in case the program ran with a smaller number before in the main method. 
	Because sometimes if a number requires to be factored with a large prime number, that prime number's segment might not have been created in the main method depending on which number gets called in the first place.
	*/
	seg * p;
	NSegs = n/(2*BITS_PER_SEG) + 2; // You need NSegs segments -- one factor might need a greater number of segment than the number invoked in the main method
   	head = NULL;                      // Empty list
	for (i = 0; i < NSegs; i++) {
		p = (  seg *) malloc(sizeof (seg));  // Make a new segment
		p->next = head;             // Add the next segment to the list
		head = p; 
	}

	/*
	clearAll();
	sieveofE(n);
	for speed/performance purposes I omit these two lines above
	*/

	if(n<=0) return; // edge case

	while(n%2==0) { // as long as we can divide by 2, keep dividing by 2
		printf("%d\n", 2);
		n = n/2; // divide and replace n
	}

	i = 1; // start with 3
	while(n!=1) { // terminate condition
		while(testBitIs0(i) && (n%(2*i+1))==0) { // as long as 2*i+1 is prime and can divide n
			printf("%d\n", (2*i+1));
			n = n / (2*i+1); // divide and replace n
		}
		i++; // increment i
	}
}

