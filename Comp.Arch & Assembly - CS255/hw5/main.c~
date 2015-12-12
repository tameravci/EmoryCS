
#define EXTERN

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char *argv[])
{
   int N, numOfPrimes;

   if ( argc == 1 )
   {
      fprintf(stderr, "Usage: %s  N\n", argv[0]);
      fprintf(stderr, " - you must specify N\n");
      fprintf(stderr, " - Example: %s 10000\n", argv[0]);
      exit(1);
   }

   N = atoi(argv[1]);

   sieveOfE( N );

   numOfPrimes = countPrimes( N );

   printf("Number of primes found = %d\n", numOfPrimes );

   if ( numOfPrimes <= 100 ) 
      printPrimes( N );
}
