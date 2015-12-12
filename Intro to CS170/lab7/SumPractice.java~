/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/

import java.util.Scanner;
public class SumPractice {
  
  // Calculates the sum of the first N odd
  // numbers.

  public static void main(String[] args) { //runtime error Main > main
    Scanner in = new Scanner(System.in);

    System.out.print("We will compute the sum of some odd numbers.  How many odd numbers would you like to add? ");
    int n = in.nextInt();  //According to the textbook this is also a potential runtime error in case of Input mismatch.
    int count = 0;
    int odd = 1;
    int sum = 0; 
    
    while (count != n) {
      System.out.println("Adding " + odd + " to my current sum " + sum);
      sum = sum + odd;
      odd = odd + 2; //syntax error Odd + logic error odd numbers increase by 2
      count++;
    }
    
    System.out.println("The sum of the first " + n + " odd numbers is " + sum + "."); //syntax error ;
  }
}
