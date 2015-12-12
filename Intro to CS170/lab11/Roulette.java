/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER AVCI
*/
public class Roulette {

   public String[] value; //changed them to private, got compilation errors
   public String[] color;

   public int outcome;

   /* ================================================
      TODO: Task 1: write the constructor
      ================================================ */
   public Roulette( ) {
      value = new String[38];
      color = new String[38];
      for (int i=0; i<value.length; i++) {
         if (i==37) {
            value[i] = "00";
         }
         else { 
            value[i] = ""+i;
         }
      }
      for (int i=0; i<color.length; i++) {
         if (i==0 || i==37) {
            color[i] = "G";
         }
         else if (i<11 && i%2 == 0) {
            color[i] = "B";
         }
         else if (i<11 && i%2 != 0) {
            color[i] = "R";
         }
         else if (i>10 && i<19 && i%2 == 0) {
            color[i] = "R";
         }
         else if (i>10 && i<19 && i%2 != 0) {
            color[i] = "B";
         }
         else if (i>18 && i<29 && i%2 == 0) {
            color[i] = "B";
         }
         else if (i>18 && i<29 && i%2 != 0) {
            color[i] = "R";
         }
         else if (i>28 && i<37 && i%2 == 0) {
            color[i] = "R";
         }
         else if (i>28 && i<37 && i%2 != 0) {
            color[i] = "B";
         }
      }
   }


   /* ================================================
      TODO: Task 2: write the spin() method
      ================================================ */
   public void spin() {
      outcome = (int)(Math.random()*38);
   }


   /* ************************************************
      TODO: Task 2b: change the instance variable to  

                   private

      and recompile Test1.java and Test2.java

      You should get errors
      ************************************************ */

   /* ================================================
      TODO Task 3: write the value() method
      ================================================ */
   public String value() {
      return value[outcome]; //this return statement is wrong, write a correct one.
   }

   /* ================================================
      TODO Task 4: write the color() method
      ================================================ */
   public String color() {
      return color[outcome]; //this return statement is wrong, write a correct one.
   }

   /* ================================================
      TODO Task 5: write the toString() method
      ================================================ */
   public String toString() {	
      return value[outcome]+" "+color[outcome] ; //this return statement is wrong, write a correct one.
   }

}



