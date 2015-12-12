/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
I FEEL LIKE PROGRAMMING IS AN ART AFTER WRITING THIS CODE :)
*/
import java.util.*;
public class PositionFinder {
    public static void main(String[] args) {
        if (args.length != 2) {        //checking if there are two command line args
            	System.err.println("*** Program requires 3 arguments ***"); 
                System.exit(1);
        }
        String unique = args[0];      //first argument
        String word = args[1];        //second argument
        int n = unique.length();      //declaring and initializing n with the length of the first "supposedly" unique word
        int c = 1;                    // this integer will be used to scan the "supposedly" unique word, starting from the second char
        for (int b = 0; b < n; b++) { //this main loop indicates the starting character 
            while (c < n)  {          //this loop keeps the starting char constant and changes c, the integer starting from second char
                if (unique.charAt(b) == unique.charAt(c)) { //checking whether they are the same characters
                    System.err.print("The first word does not have unique characters");
                    System.exit(1);
                }
            c++;                       //now keeping the first char constant, the second char must proceed to the following char
            }                          // now we are done with the while loop, but there may still be same characters
                                       // the for loop increases the starting character by 1. 
        c = b + 2;                     // The old "second" char c must now be assigned to third character, if there are any
        }                              // b < n this condition makes sure that we don't run into any char.Exception errors
        for (int a = 0; a < word.length(); a++) { // this loop serves for position finding
            System.out.print((int)(unique.indexOf(word.charAt(a))) + 1); // + 1 is necessary to find the position accurately
        }
    }   
}    
