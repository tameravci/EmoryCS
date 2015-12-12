/* log-mult.c

This program should multiply two binary integers in "log space".  That
is, using a strategy that would work for a log-space Turing machine,
with access to its input via a read-only tape, and producing output
with a write-only output tape.

The strings argv[1] and argv[2] are our two input integers, in binary
notation (so you may assume that every char is either '0' or '1').
They are "read-only".  Our output is their product integer, also
represented in binary.  We print our output string to stdout, using
putchar(c).

Note each "random access" read, which is O(1) time for us, would
take O(n) time for a logspace TM.

Our variables are integers needing O(lg n) bits, where n is the input
length.  We use subroutines but no recursion, so stack depth is O(1).
There are no arrays or strings, other than the input.
in sorted order.  For example:

% cc log-mult.c -o log-mult
% ./log-mult 101 01011
110111
%

For full credit, you should produce the output with most significant
bit first, and no leading zeros (unless the number itself is zero).

*/

#include <stdio.h>              /* fprintf, stderr, putchar */
#include <stdlib.h>
#include <string.h>

const char *TAPE1;               /* read-only first input, NUL terminated  */
const char *TAPE2;               /* read-only second input, NUL terminated  */

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* TODO: finish.  Borrow code as you like from log_sort.c

*/

void mult()
{

  printf("%s\n",TAPE1 );
  printf("%s\n", TAPE2);

/*
multiply(a[1..p], b[1..q], base)                  // Operands containing rightmost digits at index 1
    tot = 0
    for ri = 1 to p + q - 1                       //For each digit of result
        for bi = MAX(1, ri - p + 1) to MIN(ri, q) //Digits from b that need to be considered
            ai = ri − bi + 1                      //Digits from a follow "symmetry"
            tot = tot + (a[ai] * b[bi])
        product[ri] = tot mod base
        tot = floor(tot / base)
    product[p+q] = tot mod base                   //Last digit of the result comes from last carry
    return product

*/
    int p = strlen(TAPE1);
    int q = strlen(TAPE2);
    char * product = malloc(sizeof(char) * (p+q+1));

    int tot = 0;
    int r;
    int b;
    int a;

    for (r=1; r<p+q-1;r++) {
      for(b = MAX(1, r-p+1) ; b<MIN(r,q); b++) {
        a = r - b +1;
        tot = tot + (atoi(TAPE1[a]) * atoi(TAPE2[b]));
      }
      printf("tot %d\n",tot);
      char buffer[1];
      product[p+q] = sprintf(buffer, 1,"%d",tot%2);
    }
    int i;
    printf("before final\n");
    for(i=0; i<p+q+1; i++)
      putchar(product[i]);

    printf("%s\n",product );

    }


  /* Goal: read TAPE1 and TAPE2, and write output via putchar,
     using the equivalent of O(log n) space, where n is the total
     input length. */


int main(int argc, const char **argv)
{
  if (argc!=3) {
    fprintf(stderr, "%d: expected two arguments, got %d\n", argv[0], argc-1);
    return 1;
  }
  TAPE1 = argv[1];
  TAPE2 = argv[2];
  mult();
  return 0;
}
