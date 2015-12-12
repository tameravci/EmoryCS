*
* TAMER AVCI tamer.avci@emory.edu  2105024. I worked on this assignment alone, using only this semester's course materials.
*
*
*
	xdef Start, Stop, End
	xdef Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10
	xdef v1, v2, v3, v4, v5, v6, v7, v8, v9, v10

Start:
        bra     Q1
        dc.b    -123
        dc.b       0
        dc.w    -314
        dc.l    -4321

*******************************************************************
* DO NOT make any changes to the line ABOVE
*
* Write the assembler instruction to each question after the 
* CORRESPONDING LABEL:
*                       Q1, Q2, Q3, ..... Q10
* Define the variable (with ds or dc) for each question after the
* CORRESPONDING LABEL:
*                       v1, v2, v3, ..... v10
*
* The v1, v2,.. labels are towards the end of the file,
*
* *** Failure to do so will result in point dedections !!! ***
*******************************************************************

*******************************************************************
* Put your assembler instructions AFTER this line
*******************************************************************

**************************************************************************
* Define an uninitialized byte variable at label v1 (see the end of
* this file) and  write the assembler instruction at label Q1 to
* move the byte value 8 into this variable.
*
* Do NOT forget to SKIP some space (or use TAB) !!!
**************************************************************************
Q1:	move.b #8, v1

* moving byte value 8 into v1
**************************************************************************
* Define an initialized byte variable at label v2 with initial value -14
* and write the assembler instruction at label Q2 to move the byte value
* at memory location B into this variable.
*
* Do NOT forget to SKIP some space (or use TAB) !!!
**************************************************************************
Q2:	move.b B, v2


* moving byte value at memory location B into this variable B was 24
**************************************************************************
* Define an initialized byte variable at label v3 with initial value -101
* and write the assembler instruction at label Q3 to move the byte value
* at memory location 5634 into this variable.
*
* Do NOT forget to SKIP some space (or use TAB) !!!
**************************************************************************
Q3:	move.b 5634, v3


* moving byte value at location 5634 into v3
**************************************************************************
* Define an initialized byte variable at label v4 with initial value -12
* and write the assembler instruction at label Q4 to move the byte value
* from this variable to memory location 5635.
**************************************************************************
Q4:	move.b v4, 5635

* moving v4 to memory location 5635
**************************************************************************
* Define an uninitialized short variable at label v5 and write 
* the assembler instruction at label Q5 to move the short value -130 
* into this variable. 
**************************************************************************
Q5:	move.w #-130, v5

* moving short value -130 into v5
**************************************************************************
* Define an initialized short variable at label v6 with initial value -15 
* and write the assembler instruction at label Q6 to move the short value 
* at memory location S into this variable - you should see -4 moved
**************************************************************************
Q6:	move.w S, v6


* moving short value at location S into v6. S was -8 not -4 typo
**************************************************************************
* Define an initialized short variable at label v7 with initial value -1 
* and write the assembler instruction at label Q7 to move the short value 
* at memory location 5636 into this variable. 
**************************************************************************
Q7:	move.w 5636, v7

* moving short value at location 5636 into v7
**************************************************************************
* Define an uninitialized int variable at label v8 and write the assembler 
* instruction at label Q8 to move the int value -500000 into this variable. 
**************************************************************************
Q8:	move.l #-500000, v8

* moving an int value into v8
**************************************************************************
* Define an initialized int variable at label v9 with initial value -12 
* and write the assembler instruction at label Q9 to move the int value 
* at memory location L into this variable. 
**************************************************************************
Q9:	move.l L, v9

* moving an int value at L into v9. L was -8
**************************************************************************
* Define an initialized int variable at label v10 with initial value -200 
* and write the assembler instruction at label Q10 to move the int value 
* at memory location 5638 into this variable. 
**************************************************************************
Q10:	move.l 5638, v10

* moving the int value at 5638 into v10

Stop:	nop
	nop

*************************************************
* Write your variable definitions here...
*
* Do NOT forget to SKIP some space (or use TAB) !!!
*************************************************

v1:	ds.b 1


v2:	dc.b -14


v3:	dc.b -101


v4:	dc.b -12


v5:	ds.w 1


v6:	dc.w -15


v7:	dc.w -1


v8:	ds.l 1


v9:	dc.l -12


v10:	dc.l -200


*************************************************
* Don't touch the variables below this line
*************************************************

End:
	ds.b    20

B:      dc.b    24
        dc.b     0
S:      dc.w    -8
L:      dc.l    -8

	end

