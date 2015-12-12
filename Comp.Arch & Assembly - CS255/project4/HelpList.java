
class Node {
   int  value;
   Node next;
}

public class HelpList {
   /* =====================================================
      InsertList(h,e): write the algorithm in Java first !

      Correct output:
			List = 30
			List = 30 10
			List = 50 30 10
			List = 50 30 20 10
			List = 50 40 30 20 10
      ===================================================== */
   public static Node InsertList(Node h, Node e) {
	if ( h == null ) { 
		e.next = null;
		return e;
	}

	else if ( h.value <= e.value ) {
		e.next = h;
		return e;
	}
	
	else	{
		Node bridge = new Node();
		bridge = InsertList(h.next,e);
		h.next = bridge;
		return h;
	}
	
	

		

	
		//Note: this must be a RECURSIVE implementation
		//Insert in DESCENDING order

   }

   public static void main(String[] args) {
      int[] v = {30, 50, 10, 40, 20};
      Node head = null;
      Node elem;

      for ( int i = 0; i < v.length; i++ ) {
         elem = new Node(); 
         elem.value = v[i];
         head = InsertList(head, elem);
         System.out.print("List = ");
         PrintList( head );
         System.out.println();
      }
   }

   public static void PrintList(Node h) {
      if ( h == null )
         return;
      else {
			 System.out.print(h.value + " ");
			 PrintList(h.next);
      }
   }
}

