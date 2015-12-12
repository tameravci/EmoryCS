
#ifndef EXTERN
#define EXTERN extern
#endif

#define SIZE_OF_SEG      256       // 256 int per segment

#define BITS_PER_SEG     (8*SIZE_OF_SEG*sizeof(int))

typedef struct _seg 
{
   int  bits[SIZE_OF_SEG];    // # bits in bits[] array = SIZE_OF_SEG

   struct _seg *next;         // Link to the next segment
} seg;

EXTERN int NSegs;

EXTERN seg *head;             // This variable will point to the 
                              // start of the linked list of segments !!!

EXTERN void clearAll( );            // Uses head to find the "bit array" (list)
EXTERN void sieveOfE( int N );      // Uses head to find the "bit array" (list)
EXTERN int  countPrimes( int N );   // Uses head to find the "bit array" (list)
EXTERN void printPrimes( int N );   // Uses head to find the "bit array" (list)

