* Collaboration Statement:
* TAMER AVCI #2105024 I worked on this assignment alone, using only this semester's course materials.


        xdef BubbleSort


BubbleSort:
******************************************************
* Write your bubble sort assembler subroutine here
******************************************************

	move.l D0, A0		*Moving the address to the address register
	move.l #0, done		*done=0
	move.l #1, k		*k=1

Part1:				*while-partI
	move.l done, D2		*moving done to D2
	cmp.l #0, D2		*beginning of while check if done equals 0
	bne Finish		*if not, everything is sorted go to finish
	move.l #1, done		*otherwise done=1
	move.l #0, i		*prepare the for loop i=0
	move.l D1, D3		*move n, size of the array to D3
	sub.l k, D3		*subtract k from n put it to D3
	
InsideFor:
	cmp.l i, D3		*for loop begins, checks iterative condition
	ble Part2		*if n-k is less than or equal to i, break from the for loop proceed in while loop
	move.l i, D6		*move i to D6 to use it as index
	muls #4, D6		*array of integers
	move.l (A0, D6), D4	*put A[i] to D4
	add.l #4, D6		*off-set 4, array of integers
	move.l (A0, D6), D5	*put A[i+1] TO d5
	cmp.l D4, D5		*compare
	bge Increment		*if A[i+1] is greater or equal to A[i] don't swap

Swap:
	move.l D4, help		*otherwise swap A[i] with A[i+1]
	sub.l #4, D6
	move.l D5, (A0, D6)
	add.l #4, D6
	move.l help, (A0, D6)
	move.l #0, done

Increment:
	
	add.l #1, i		*increase i by one for the "for" loop
	bra InsideFor		*go back to for loop

Part2:				*while-partII
	add.l #1, k		*increase k by one
	bra Part1		*go back to the beginning of the while loop


Finish:
	rts

* *****************************************************************************
* If you need local variables, you can add variable definitions below this line
* *****************************************************************************
done:	dc.l 0
help:	ds.l 1
k:	dc.l 1
i:	ds.l 1
        end
