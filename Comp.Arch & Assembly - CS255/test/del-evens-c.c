#include <stdio.h>
#include <stdlib.h>

struct Node {
   int data;
   struct Node* next;
}; 

void printList(struct Node* n) {
   struct Node* temp = n;
   while(temp != NULL) {
      printf("%d -> ", temp->data);
      temp = temp->next;
   }
   printf("NULL\n");
}

//MUCH easier recursive solution
//to this problem
struct Node* delEvensRecursive(struct Node* head) {
   if (head == NULL) { //base case
      return NULL;
   } 
   
   else {
      if(head->data % 2 == 0) {
         //even data so need to delete
         
         //temp pointer to next node in list
         struct Node* temp = head->next;
         //deallocate current Node
         free(head);
         head = temp;
         //return result of rest of list
         return delEvensRecursive(temp);
      } else {
         //current Node is odd, so keep node in list
         
         head->next = delEvensRecursive(head->next);
         return head;
      }
   
   }
}


struct Node* delEvens(struct Node* head) {
   struct Node* deleted = NULL;

   //use this to keep track of previous item in list
   //initialize to NULL since first node will not have
   //a "previous" node
   struct Node* prev = NULL;

   //check for empty list
      if(head == NULL) {
         return head;
      } 
      
      //temporary Node for iterating over list
      //keeps track of current Node
      struct Node* current = head;
      
      while(current != NULL) {   
         if(current->data % 2 == 0) {  //even data!  need to remove current node
               if(prev == NULL) { //even at start of list
                  head = current->next;
                  
                  //deallocate memory
                  deleted = current; 
                  free(deleted);
                  
                  //advance to next node in list
                  current = head;
               } else {
                  //skip over even node
                  prev->next = current->next;
                  
                  //deallocate memory and advance
                  deleted = current;
                  current = current->next;
                  free(deleted);
               }
         } else {
            //odd node so we keep it in the list
            //just advance pointers
            prev = current;
            current = current->next;
         }  
      }
      return head;
}

void delEvensRef(struct Node** head) {
   struct Node* deleted = NULL;

   //use this to keep track of previous item in list
   //initialize to NULL since first node will not have
   //a "previous" node
   struct Node* prev = NULL;

   //check for empty list
      if(*head == NULL) {
         return;
      } 
      
      //temporary Node for iterating over list
      //keeps track of current Node
      struct Node* current = *head;
      
      while(current != NULL) {   
         if(current->data % 2 == 0) {  //even data!  need to remove current node
               if(prev == NULL) { //even at start of list
                  *head = current->next;
                  
                  //deallocate memory
                  deleted = current; 
                  free(deleted);
                  
                  //advance to next node in list
                  current = *head;
               } else {
                  //skip over even node
                  prev->next = current->next;
                  
                  //deallocate memory and advance
                  deleted = current;
                  current = current->next;
                  free(deleted);
               }
         } else {
            //odd node so we keep it in the list
            //just advance pointers
            prev = current;
            current = current->next;
         }  
      }
}



int main(int argc, char* argv[]) {
   int i;
   struct Node* head = NULL;
   
   //useful test cases
   //for(i=4; i < 4; i++) { //empty list
   //for(i=4; i < 5; i++) { //single even node
   //for(i=5; i < 6; i++) { //single odd node
   //for(i=4; i < 16; i++) { //list starts w/ odd, ends w/even
   for(i=5; i < 15; i++) { //list starts w/ even, ends w/ odd
   //for(i=5; i < 16; i++) { //list starts w/ odd, ends w/ odd
   //for(i=4; i < 15; i++) { //list starts w/ even, ends w/ even 
   //for(i=5; i < 16; i=i+2) { //list of all odds
   //for(i = 4; i < 15; i=i+2) { //list of all evens*/
      struct Node* n = malloc(sizeof(struct Node));
      n->data = i;
      n->next = head;
      head = n;
   }
   
   //printList before removal
   printList(head); 

   //delete even nodes 
   //delEvensRef(&head);
   head = delEvensRecursive(head);
   //head = delEvens(head);

   //print list again
   printList(head);
    
}