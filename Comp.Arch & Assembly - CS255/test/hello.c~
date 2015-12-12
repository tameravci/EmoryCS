
#include <stdio.h>

void printBits( int a )
{
   int i;

   /*                    10987654321098765432109876543210  */
   unsigned int mask = 0b10000000000000000000000000000000;

   for ( i = 31; i >= 0; i-- )
   {
      if ( (a & mask) != 0 )
         putchar('1');
      else
         putchar('0');

      mask = mask >> 1;     /* Shift mask bit to right */
   }

}



int main( int argc, char* argv[] )
{
   int a;

   printf( "a = " );
   scanf( "%d", &a );

   printf( "a = %d\n", a );
   printf( "Binary representation = " );

   printBits( a );
   putchar('\n');
}
