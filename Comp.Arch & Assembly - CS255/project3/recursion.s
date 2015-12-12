* Collaboration Statement:
* TAMER AVCI #2105024 I worked on this assignment alone, using only this semester's course materials.


* ====================================================================
* Do not touch the following xdef:
* ====================================================================
        xdef F



* **************************************************************************
* You can add more xdef directives above if you need more external labels
*
* - Remember that you can only add a label as a break point (stop location) 
*   in EGTAPI if the label has been xdef
* **************************************************************************

F:
	move.l A6, -(A7) *save caller's frame pointer A6
	move.l A7, A6    *setup frame pointer
	suba.l #8, A7    *creating 2 local variables
	move.l 16(A6), D0   *putting i to D0

	cmp.l #0, D0     * check if i <=0
	ble then         * if is less than or equal to 0 go to then

	move.l 12(A6), D0  *putting j to D0

	cmp.l #0, D0       *compare j=<0
	ble then           *go to then if it is fulfilled
	bra elseif         *otherwise go to elseif part

then:
	move.l #1, D0     *moving 1 to D0
	move.l A6, A7     *deallocate local variables
	move.l (A7)+, A6  *restore frame pointer
	rts                * return

elseif:
	move.l 16(A6), D0    *put i to D0
	move.l 8(A6), D1     *put k to D0
	add.l D1, D0         * add k + i
	move.l 12(A6), D2	 * put j to D2
	cmp.l D0, D2		*compare i+k to j
	ble else            * if i+k greater or equal to j go to else
	move.l 16(A6), D0	*moving i to D0
	add.l 12(A6), D0	*adding j to D0  i+j >> return
	move.l A6, A7		*deallocate local variables
	move.l (A7)+, A6  	*restore frame pointer
	rts

else:
	move.l #0, -4(A6)      *set s=0
	move.l #1, -8(A6)      *set t=1
	
forloop:
	move.l -8(A6), D0   *putting t to D0
	move.l 8(A6), D1	*putting k to D1
	cmp.l D1, D0	    *check if t<k
	bge finish		*if not break

recursion:
	move.l 16(A6), D0	*put i to D0
	sub.l -8(A6), D0	* subtract t from i in D0
	move.l D0, -(A7)	* put i-t on top of the stack

	move.l 12(A6), D0 	* put j to D0
	sub.l -8(A6), D0 	* subtract t from j in D0
	move.l D0, -(A7) 	* put j-t on top

	move.l 8(A6), d0 	* put k to D0
	sub.l #1, D0 		* subtract 1 from k in d0
	move.l D0, -(A7) 	* put k-1 on top
	
	bsr F               *call F
	adda.l #12, A7	    *parameter deallocation
	add.l #2, D0        * add 2 to D0
	move.l -4(A6), D2	* move s to D2
	add.l D2, D0        * add s to D0
	move.l D0, -4(A6)   * put (s+ F(..) + 2) into s
	
	add.l #1, -8(A6)    * t++
	bra forloop         *continue for loop

finish:
	move.l -4(A6), D0   * move s to D0
	move.l A6, A7       *deallocate local variables
	move.l (A7)+, A6  *restore frame pointer
	rts                *return s in D0
	
	
* ********************************************************************
* Put your (recursive) function F here 
*
* F receives the parameters i, j, k on the stack
* F returns the function value in register d0
*
* Make sure you use the "rts" instruction to return to the caller
* Also: Make sure you DE-ALLOCATE the local variables and restore a6
*       BEFORE you return to the caller !!!
* ********************************************************************







*====================================================================
* Don't add anything below this line...
* ====================================================================
        end
