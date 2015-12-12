// Collaboration Statement:
// TAMER AVCI tamer.avci@emory.edu  2105024. I worked on this assignment alone, using only this semester's course materials.

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void clearAll()
{
	int i;
	for(i=0; i < MAX; i++) //set everything in the array up until max to zero
		prime[i] = 0;
	
}

void  setBit(int n)
{
      int i = n/32;  //find the index
      int pos = n%32; //find the position

      unsigned int flag = 1;   // flag = 0000.....00001

      flag = flag << pos;      // flag = 0000...010...000   (shifted n positions)

      prime[i] = prime[i] | flag;      // Set the bit at the n-th position in prime[i]
 }


int testBitIs0(int n)
{
      int i = n/32; //find the index
      int pos = n%32; //find the pos

      unsigned int flag = 1;  // flag = 0000.....00001

      flag = flag << pos;     // flag = 0000...010...000   (shifted n positions)

      if ( prime[i] & flag )      // Test the bit at the n-th position in A[i]
         return 0; // not prime
      else
         return 1; // prime
}

void sieveOfE(int N)
{
	clearAll(); //clear everything in the array for new setup (setting 0)
	setBit(0); // 0 is not prime
	setBit(1); // 1 is not prime

 
  
      int k = 2;   // Start with 2 to find all primes

      while ( k <= N )  // run until the input N
      {

	int i;
    
         for (i = k; i <= N; i++ )
             if ( testBitIs0(i) == 1 ) //prime found
                break;            

	int j;

         for (j = 2*i; j <= N; j = j + i ) //mark every multiple of that number as not prime
             setBit(j);

         k = i+1;    // Set up k for next iteration !!!   
      }


   }

int countPrimes(N)
{	
	int count = 0;
	int i;
	for(i=0; i<=N; i++) {
		if(testBitIs0(i) == 1) // prime number
			count++;       //increase count
	}
	return count;

}

void printPrimes(N)
{	
	int i;
	for(i=0; i<=N; i++) {
		if(testBitIs0(i) == 1) { // if prime print
			printf("%d\n", i);
		}
			
	}
}


