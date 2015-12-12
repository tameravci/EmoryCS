
#include <stdio.h>


int main( int argc, char* argv[] )
{
   printf("4 == 3 = %d\n",  (4==3) );
   printf("4 > 3 = %d\n",  (4 > 3) );

   printf("4 && 3 = %d\n",  (4 && 3) );
   printf("4 && 0 = %d\n",  (4 && 0) );
   printf("4 || 0 = %d\n",  (4 || 0) );
   printf("0 || 0 = %d\n",  (0 || 0) );
}
