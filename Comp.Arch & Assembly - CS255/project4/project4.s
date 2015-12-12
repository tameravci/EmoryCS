* Project4: Insert into ordered list in DESCENDING ORDER using recursion
* ====================================================================
      xref ReadInt, malloc
      xref InsertList
      xdef Start, Stop, End
      xdef Check
      xdef head, elem

Start:
      jsr ReadInt            * Read next integer
      move.l d0, n

      move.l #0, head        * head = NULL

      move.l #0, i           * i = 0
ForStart:
      move.l i, d4
      cmp.l  n, d4
      beq ForEnd             * if i >= n then stop

      move.l #8, d0          * Allocate 8 bytes
      jsr malloc
      move.l a0, elem

      jsr ReadInt            * Read next integer
      move.l elem, a0
      move.l d0, (a0)        * elem.value = integer read


      move.l head, -(a7)      * pass parameter: push head on stack
      move.l elem, -(a7)      * pass parameter: push elem on stack
      jsr InsertList

      adda.l #8, a7            * clean up the stack
      move.l d0, head

Check:
      nop

      move.l i, d1            * i = i+1
      add.l #1, d1
      move.l d1, i
      bra ForStart
      
      
ForEnd:      


* ====================================================================
* Don't touch the stop label - you need it to stop the program
* ====================================================================
Stop:   nop
        nop

head:   ds.l 1
elem:   ds.l 1
i:      ds.l 1
n:      ds.l 1

End:
        end
