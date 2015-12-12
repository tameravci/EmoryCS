* Collaboration Statement:
* TAMER AVCI tamer.avci@emory.edu  2105024. I worked on this assignment alone, using only this semester's course materials.
* 
*
   xdef Start, Stop, End
   xdef Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10
   xdef A, B, C
   xdef i, j, k
   xdef head
   xdef ans_b, ans_w, ans_l

Start:
*******************************************************************
* Put your assembler instructions here
* Write the answer to each question after the corresponding label.
* DO NOT REMOVE ANY LABEL IN THIS ASSIGNMENT
* *** Failure to do so will result in point dedections !!! ***
*******************************************************************

Q1:
*         ans_b = A[5];
   	movea.l #A, A0
   	move.b 5(A0), ans_b






Q2:
*         ans_l = B[4];
   	movea.l #B, A0
   	move.w 8(A0), D0
   	ext.l D0
   	move.l D0, ans_l





Q3:
*         ans_l = C[k];
	movea.l #C, A0
   	move.l k, D0
   	muls #4, D0
   	move.l 0(A0, D0), ans_l





Q4:
*         ans_w = A[j + k];
	movea.l #A, A1
	move.w j, D1
	add.l k, D1
	move.b 0(A1, D1), D1
	ext.w D1
	move.w D1, ans_w     




Q5:
*         ans_w = C[i + k];
	movea.l #C, A2
	move.l k, D2
	add.b i, D2
	muls #4, D2
	move.l 0(A2, D2), D2
	move.w D2, ans_w


 
Q6:
*         ans_l = A[j] + B[i];
	movea.l #A, A3
	move.w j, D3
	move.b 0(A3, D3), D3 *A[j] is now is D3 but A[j] could be negative: extension needed
	ext.w D3
	ext.l D3
	movea.l #B, A4
	move.b i, D4
	muls #2, D4
	move.w 0(A4, D4), D4 *B[i] is now in D4 but B[i] could be negative: extension needed
	ext.l D4
	add.l D3, D4
	move.l D4, ans_l	



Q7:
*         ans_l = A[A[j] - 50];
	movea.l #A, A3
	move.w j, D3
	move.b 0(A3, D3), D3
	ext.w D3 *A[j] could be negative: extension needed
	ext.l D3
	add.l #-50, D3
	move.b 0(A3, D3), D3
	ext.w D3
	ext.l D3
	move.l D3, ans_l


   
Q8:
*         ans_w = B[ 13 ]      B[13] goes to the latter two bytes of C[1] which is -2222 because C is an array of long words
	movea.l #B, A4
	move.l #26, D4
	move.w 0(A4, D4), ans_w





Q9:
*    ans_l = head.value1;
	move.l head, A4
	move.l 0(A4), ans_l




Q10:
*    ans_w = head.next.next.value2;
	move.l head, A4
	move.l 6(A4), A4
	move.l 6(A4), A4
	move.w 4(A4), ans_w



*************************************************
* Don't write any code below this line
*************************************************

Stop: nop
   nop

*************************************************
* Don't touch these variables
* You do NOT need to define more variables !!!
*************************************************

************************************************************************
* Note the use of the even directive to locate the variables ans_w and j
* at an EVEN address due to the variables ans_b and i being bytes
* Short and int variables MUST start on an even address (or you 
* will get an "odd address" error)
************************************************************************

ans_b: ds.b 1
   even
ans_w: ds.w 1
ans_l: ds.l 1

i:     dc.b  3
   even
j:   dc.w  4
k:   dc.l  5

A:  dc.b   11, -22, 33, -44, 55, -66, 77, -88, 99, -123

B:  dc.w   111, -222, 333, -444, 555, -666, 777, -888, 999, -5432

C:  dc.l   1111, -2222, 3333, -4444, 5555, -6666, 7777, -8888, 9999, -9876


head:   dc.l  list1

list3:  dc.l 3456
        dc.w 67
   dc.l list4
list2:  dc.l 2345
        dc.w 78
   dc.l list3
list4:  dc.l 4567
        dc.w 56
   dc.l list5
list1:  dc.l 1234
        dc.w 89
   dc.l list2
list5:  dc.l 5678
        dc.w 45
   dc.l 0


End:
   end

