* First,you must transform the for loop into a while
* So there are 2 nested while loops - with an if inside...

        xdef Start,Start2,Stop,End
        xdef A,B

        xref BubbleSort
	xref WriteInt,WriteLn

*****************************************************************************
* Main program: call BubbleSort twice to sort 2 different arrays
*	 	and print the sorted arrays out
*
* DO NOT change the main program.
* Write your BubbleSort routine starting at the "BubbleSort:" label below
*****************************************************************************
Start:
	move.l #A,D0			* Pass address of the array in D0
	move.l #5,D1			* Pass size of the array in D1
	jsr    BubbleSort		* Sort array A


Start2:
	nop

        move.l #B,D0			* Pass address of the array in D0
        move.l #10,D1			* Pass size of the array in D1
        jsr    BubbleSort		* Sort array B

	move.l #C, D0
	move.l #15, D1
	jsr BubbleSort



* ********************************************************************
* Don't touch the stop label - you need it to stop the program
* ********************************************************************
Stop:   nop
        nop

A:      dc.l 6,-3,-8,4,11
B:      dc.l 78,-1,8,45,11,-89,56,9,12,-19
C:	dc.l 15, 123, -45, 32, 123, -983, 0, -21, 32, 34, 51, 12, 42, -3, -9


* ********************************************************************
* Add more variables below if you need them
* ********************************************************************

End:

        end

