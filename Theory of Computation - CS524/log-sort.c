/* log-sort.c: this program sorts a list of strings in "log space".
That is, using a strategy that could work for a log-space Turing machine,
with access to its input via a read-only tape, and producing output
with a write-only output tape.

The string argv[1] acts as our read-only input string, of length n.
Each "random access" read could take O(n) time for a logspace TM.
We print our output string to stdout, using putchar(c).

Our variables are integers needing O(lg n) bits, where n is the input
length.  We use subroutines but no recursion, so stack depth is O(1).
There are no arrays or strings, other than the input.  The input is a
comma-separated list of strings, and the output is the same list but
in sorted order.  For example:

% cc log-sort.c -o log-sort
% ./log-sort baa,ab,aab,ba,abba,ab
aab,ab,ab,abba,ba,baa
%

The algorithm needs O(n^3) time in C (usual unit-cost RAM model), or
about O(n^4 log n) steps on a logspace Turing machine.
(Small bug: we ignore an empty string at the end of the input list.)  */

#include <stdio.h>              /* fprintf, stderr, putchar */

const char *TAPE;               /* read-only input, NUL terminated  */

int end_of_tape(int i) { return TAPE[i] == '\0'; } /* NUL? */

int end_char(int i) { char c = TAPE[i]; return c==',' || c=='\0'; }

int end_string(int i) { while (!end_char(i)) ++i; return i; }

int next_string(int i) { i=end_string(i); if (TAPE[i]==',') ++i; return i; }

void print_string(int i) { while (!end_char(i)) putchar(TAPE[i++]); }

int sorts_before(int i, int j)  /* compare strings starting at i and j */
{
  if (i==j) return 0;
  while (1) {
    int end_i = end_char(i), end_j = end_char(j);
    if (end_i && end_j) return (i < j); /* stable sort */
    if (end_i || end_j) return end_i; /* prefixes first */
    if (TAPE[i]!=TAPE[j]) return (TAPE[i] < TAPE[j]);
    ++i; ++j;
  }
}

/* rank(i) == number of strings which should appear before the string at i */
int rank(int i)
{
  int ret=0, j;
  for (j=0; !end_of_tape(j); j=next_string(j))
    if (sorts_before(j,i)) ++ret;
  return ret;
}

void sort()
{
  int i=0, r=0, j;
  while (1)                     /* for each r = 0, 1, ... */
  {
    for (j=0; !end_of_tape(j); j=next_string(j))
      if (rank(j)==r) break;    /* find string of rank r */
    print_string(j);            /* and print it */
    ++r;
    i = next_string(i);
    if (end_of_tape(i)) break;  /* last r done? */
    putchar(',');
  }
  putchar('\n');
}

int main(int argc, const char **argv)
{
  if (argc!=2) {
    fprintf(stderr, "%d: expected one argument, got %d\n", argv[0], argc-1);
    return 1;
  }
  TAPE = argv[1];
  sort();
  return 0;
}
