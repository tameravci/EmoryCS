* Collaboration Statement:
* TAMER AVCI #2105024 I worked on this assignment alone, using only this semester's course materials.
* 

* ********************************************************************
* Do not touch the following 2 xdef lists:
* ********************************************************************
        xdef Start, Stop, End
        xdef a, b, len_a, len_b, min, max, sum, common, i

* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
* You can add more xdef here to export labels to EGTAPI
* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	xdef ArrayStartA, AfterCommon, ArrayStartB


* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*      Put your assembler program here - between the start and stop label
*      DO NOT define any variables here - see the variable section below
* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Start:
* *******************************************************************
* initializing quantities to 0, and setting min and max to be a[0], i for the loop starts from 0
* *******************************************************************
	move.l #0, i
	move.l #0, sum
	move.l #0, common
	move.l a, max
	move.l a, min

ArrayStartA:
* *******************************************************************
* checks if we exceed the array size a, if it does go to array B
* setting j equal to zero to use it in CommonElement finder branch Common
* *******************************************************************
	
	move.l i, D0
	cmp.l #len_a, D0
	bge ArrayStartB1
	move.l #0, j

********************
*find the next element and add it to the sum
*find if the first element is in the other array using common
********************

	
	movea.l #a, A0
	muls #4, D0
	move.l 0(A0, D0), D0
	add.l D0, sum


	bra Common
	

* ********************************************************************
* after common branch has worked come back and put the element in min or max if necessary and increment i to continue looping in A
* ********************************************************************
AfterCommon:

	cmp.l max, D0
 	ble MinimumA
	move.l D0, max
	bra IncrementA



* ********************************************************************
* add it to minimum and increment i
* ********************************************************************
MinimumA:
	cmp.l min, D0
	bge IncrementA
	move.l D0, min


IncrementA:
	move.l i, D0
	add.l #1, D0
	move.l D0, i
	bra ArrayStartA

* ********************************************************************
* go back toArrayStartA to evaluate the next element [a++]
* ********************************************************************

ArrayStartB1:

	move.l #0, i

* ********************************************************************
* put i equal to zero so that we start evaluating array B
* ********************************************************************

ArrayStartB:
* ********************************************************************
*check if we exceeded the size of the array	
* ********************************************************************
	move.l i, D0
	cmp.l #len_b, D0
	bge Finish
* ********************************************************************
* finish the program
* ********************************************************************

	movea.l #b, A0
	move.l i, D0
	muls #4, D0
	move.l 0(A0, D0), D0
	add.l D0, sum
* ********************************************************************
*evaluate the next element and add it to the sum
* ********************************************************************

	cmp.l max, D0
 	ble MinimumB
	move.l D0, max
	bra IncrementB
* ********************************************************************
*put the element in the max or min if necessary
* ********************************************************************

MinimumB: 	
	
	cmp.l min, D0
	bge IncrementB
	move.l D0, min
* ********************************************************************
*check if its the minimum
* ********************************************************************

IncrementB:
	move.l i, D0
	add.l #1, D0
	move.l D0, i
	bra ArrayStartB

* ********************************************************************
*increment i [b++]
* ********************************************************************

Common:
* ********************************************************************
*check every element in the array b, once its done go back to ArrayStartA
* ********************************************************************
	move.l j, D3
	cmp.l #len_b, D3
	bge AfterCommon

* ********************************************************************
*currently the element of the ArrayA is in D0 check it versus all the elements in b
* ********************************************************************

	movea.l #b, A3
	move.l j, D3
	muls #4, D3
	move.l 0(A3, D3), D3
	cmp.l D0, D3
	beq CommonCounter
	bra IncrementCommon

* ********************************************************************
* increment the counter to keep track of the number of commonelements
* *******************************************************************
CommonCounter:

	move.l common, D4
	add.l #1, D4
	move.l D4, common
	bra IncrementCommon


IncrementCommon:
	move.l j, D2
	add.l #1, D2
	move.l D2, j
	bra Common

* ********************************************************************
* increment j to traverse B
* *******************************************************************


Finish:


* ********************************************************************
* Don't touch the stop label - you need it to stop the program
* ********************************************************************
Stop:   nop


End:    nop

* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*    Variable Section -   Put your variables here
*
*    Do not define any of the variables specified in the program
*    They are already defined below
*    This section is for any temporary variables you might need
* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

i:	ds.l 1
j:	ds.l 1

* ********************************************************************
* XXXX Don't touch anything below this line !!!
* ********************************************************************
a:      dc.l  1, 2, 3, 4, 5
b:      dc.l  6, 7, 8, 9, 10
len_a: 	equ 5
len_b:	equ 5
min:	ds.l 1
max:	ds.l 1
sum:	ds.l 1
common:	ds.l 1

        end
