#include <stdio.h>
#include <stdlib.h>

/* ------------------------
   Node definition
   ------------------------ */
struct Node {
   int          value;
   struct Node* next;
};

void printList( struct Node* h ) {
   while ( h != NULL ) {
      printf(" %d\n", h->value );   	// Print current

      h = h->next;			// Go to next element in list
   }
   printf("\n");
}


struct Node* insertHead(struct Node* head, struct Node* elem) {
   elem->next = head;	// make "elem" point to "head"

   return(elem);		// return address of new head
}

struct Node* deleteHead ( struct Node* h ) {
struct Node* deleted;
   struct Node* newHead;

   if ( h == NULL ) {
      return (NULL);        // Nothing to delete....
   }

   deleted = h;            // Save the location of the deleted element
   newHead = h->next;      // We will return this value

   free(deleted);          // Un-reserve memory cells 

   return (newHead);      // Make the second element the new head       
}


int main(int argc, char *argv[]) {
   struct Node* head;   // Head of list
   struct Node* p;      // Help variable to allocate new list element

   head = NULL;           // Empty list

   /* ========================================================
      Insert 123
      ======================================================== */
   p = malloc( sizeof(struct Node) ); 
   p->value = 123;			
   head = insertHead( head, p);		

   /* ========================================================
      Insert 444
      ======================================================== */
   p = malloc( sizeof(struct Node) ); 
   p->value = 444;
   head = insertHead( head, p);		

   /* ========================================================
      Insert 789
      ======================================================== */
   p = malloc( sizeof(struct Node) ); 
   p->value = 789;
   head = insertHead(head, p);		

   printList(head);


   head = deleteHead(head);		
   printList(head);

}