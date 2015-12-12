/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
I FEEL LIKE PROGRAMMING IS AN ART AFTER WRITING THIS CODE :)
*/
import java.util.*;
public class Goldbach {
    public static boolean IsPrime(int n) { //method: prime or not
        int a=2;
        if (n==1)                          //1 is not prime
            return false;
        while (a < n) {                    //prime numbers can only be divided by 1 and by themselves
            if (n%a==0) {                  //if this condition can ever be satisfied by an "a" less than "n", then it means that "n" is not a prime number
                return false;
            }
        a++;                              //approaching to n
        } 
        return true; 
    }
    public static void main(String[] args) {
        Scanner input = new Scanner (System.in);
	System.out.println("Please provide an even number bigger than 2:");  //asking for input
	int evenNum = input.nextInt();  
        
        int element1;                    //first prime number
        int evenNumx;                    //this integer is intended to protect the initial value of evenNum
        int element2;                    //second prime number
        while (evenNum % 2 != 0 || evenNum <=2 ) {  // verifying the input
	    System.out.println("Please provide an even number bigger than 2:");
	    evenNum = input.nextInt(); 
        }
        evenNumx = evenNum;              //initializing evenNumx
        while (true) {
                evenNumx-=1;             // easiest way to find the first prime number is to decrease evenNum one by one              
                element1 = evenNumx - 1; //initializing first possible prime number
                if (IsPrime(element1)) { //verfying if element1 is prime or not
                     element2 = evenNum - element1; //if it is, we'll verify if the difference between element1 and evenNum is a prime number

                     if (IsPrime(element2)) { //verify
                         System.out.println(evenNum + " = " + element1 + " + " + element2); //if the condition is satisfied, we can print the addition
                         break;         // and exit
                     }
                     if (evenNumx==0) {      // the very less likely scenario
                         System.out.println("The given integer cannot be expressed as the sum of two prime numbers");    
                     }             
                }
        }           
    }
}



