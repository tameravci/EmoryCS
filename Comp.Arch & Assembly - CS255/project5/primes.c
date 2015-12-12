#include <stdio.h>
#include "header.h"

/* ---------------------------------------------------------
   setBit( n ): set the bit corresponding to the number n
   --------------------------------------------------------- */
void setBit( int n ) {
   int i;       // Index of prime[]
   int pos;     // Bit position in prime[i]

   i = n/32;
   pos = n%32;

   prime[i] = prime[i] | (1 << pos) ;
}

/* -------------------------------------------------
   testBit( n ): return 1 if bit n is RESET
   ------------------------------------------------- */
int testBitIs0( int n ) {
   int i;       // Index of prime[]
   int pos;     // Bit position n in prime[i]
   int r;       // result

   i = n/32;
   pos = n%32;

   r = prime[i] & (1 << pos) ; // Get bit at pos in prime[i]

   if ( r == 0 )
      return 1;        // return 1 to indicate that n is still prime
   else
      return 0;
}

int countPrimes( int N ) {
   int count, i;

   count = 0;

   for ( i = 2; i <= N; i++ )
      if ( testBitIs0(i) )
         count++;

   return count;
}

void printPrimes(int N)
{
   int i;

   for ( i = 2; i <= N; i++ )
      if ( testBitIs0(i) )
         printf("%d ", i );
   printf("\n\n");
}


void sieveOfE( int N )
{
   int i, j, k;

   /* ------------------------
      Initialize prime[]
      ------------------------ */
   for ( i = 0; i < N/MAX+1; i++ )
      prime[i] = 0;

// PrintBits(N);

   setBit( 0 );    // 0 is not prime
   setBit( 1 );    // 1 is not prime

   /* ------------------------
      Perform the sieve of E
      ------------------------ */
   k = 2;   // Start with 2 to find all primes

   while ( k <= N )   {
   //    PrintBits(N);
      /* ----------------------------------------
         Starting from k, find next 
         prime number number i

         A prime number is detected by:  

                      isPrime[i] == true
         ---------------------------------------- */
      for ( i = k; i <= N; i++ )
          if ( testBitIs0(i) )
             break;             // Found !

      /* --------------------------------------
         Set:  isPrime[2*i] = false,
               isPrime[3*i] = false,
               ....
               (upto isPrime[N])
         -------------------------------------- */
      for ( j = 2*i; j <= N; j = j + i )
	  	setBit(j);

      k = i+1;    // Set up k for next iteration !!!   
   }
}

