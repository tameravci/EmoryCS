
#define EXTERN

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char *argv[])
{
   int i, N, numOfPrimes, inp;
   seg * p;

   if ( argc == 1 )
   {
      fprintf(stderr, "Usage: %s  N\n", argv[0]);
      fprintf(stderr, " - you must specify N\n");
      fprintf(stderr, " - Example: %s 10000\n", argv[0]);
      exit(1);
   }

   N = atoi(argv[1]);        // Read in N

   /* =======================================================
      Allocate the linked list of segments containing pieces 
      of the bit array
      ======================================================= */

   NSegs = N/(2*BITS_PER_SEG) + 2;      // You need NSegs segments



   head = NULL;                      // Empty list


	printf("Need %d for input %d\n", NSegs, N);

   for (i = 0; i < NSegs; i++)
   {
      p = (  seg *) malloc(sizeof (seg));  // Make a new segment
      p->next = head;             // Add the next segment to the list
      head = p; 
   }

   /* ------------------------
      Initialize bit array
      ------------------------ */


   clearAll();

   /* ------------------------
      Find primes
      ------------------------ */
   sieveOfE( N ); 

   // Modify my solution in C project 1 !!!

   numOfPrimes = countPrimes( N );

   printf("Number of primes found = %d\n", numOfPrimes );

   if ( numOfPrimes <= 3000 ) 
      printPrimes( N );


   while (1)
   {
      printf("Enter number >> ");

     if ( scanf("%d", &inp) == EOF )
     {
        break;
     }

     factor(inp);
   }

   printf("Done.\n");
}
