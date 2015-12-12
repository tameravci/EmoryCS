
/*
TAMER_AVCI
tamer_avci@emory.edu #2105024
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/

import java.util.Scanner;
public class Hw3 {
        public static void main(String[] args) {
		String s1;


		System.out.println("EXERCISE 1");
		System.out.println();

		
		/*Exercise 1: Make your program read a number in feet (double typed), and then converts it to meters and centimeters. Your program should say how many whole meters and how many whole centimeters it has. Remember that one foot is 0.3048 meters. Here is a sample run:
	Enter a value for feet: 16.08
	16.08 feet is equivalent to 4 meters and 90 centimeters.
*/
		
		// Create a scanner
		Scanner input = new Scanner(System.in);
		System.out.print("Enter a a value for feet:");
		double feet = input.nextDouble();
		// Conversion
		double feetInMeters = feet * 0.3048 ;
		// Casting
		int meters = (int)(feetInMeters * 100);
		// Find the numbero of whole meters
		int wholeMeters = meters / 100 ;
		int wholeCentimeters = meters % 100;
		//Display results
		System.out.println(+ feet + " feet is equivalent to " + wholeMeters + " meters and " + wholeCentimeters + " centimeters ");
		
		

		System.out.println();
		System.out.println("EXERCISE 2");
		System.out.println();



		/*Exercise 2: Make your program read a char typed alphabetic character from the user. If it is a capital letter, your program should not print anything. If the user enters a lower case letter, the program should print its capital letter, and if it is not a letter, then the program should print "The entered character is not a letter".  Here are 3 sample runs:
		Please enter a character:  a
		You originally entered a. The upper case is A.

		Please enter a character: A
	
	
		Please enter a character: !
		The character ! is not a letter.


		Hint: To read only one character, you can read the input as a string and then take the first character

*/

		// Asking for a character
		System.out.print("Please enter a character:");
		String newChar = input.next();
		// Reading the first letter of the string
		char letter = newChar.charAt(0);
		
		// first condition for the uppercase letters
	if ((int)letter >= 65 && (int)letter <= 90) {
		System.out.println();
	}

		//second condition for the lowercase letters
	if ((int)letter >= 97  && (int)letter <= 122) {
		//turning a lowercase letter into an uppercase
		char upperChar = (char)((int)letter - 32);
		System.out.println("You originally entered " + letter + ". The upper case is " + upperChar);
	}
		//third condition for the non-letter characters
	if  ((int)letter <=64 || (int)letter >90 && (int)letter <=96 || (int)letter >122) {
		System.out.println("The character "  + letter + " is not a letter.");
	}
       



		System.out.println();
		System.out.println("EXERCISE 3");
		System.out.println();



		s1 = "When shall we three meet again? In thunder, lightning, or in rain?";
		/*Exercise 3: Make your program read two integer numbers, and then print a substring of s1 starting in the first read integer and ending in the second read integer (including that character). Here is a sample run:
		Enter the index of the starting character:  35
		Enter the index of the ending character:  41
		The substring is: thunder
*/
      		// For the convenience I print the s1
		System.out.println(s1);
		//Asking for a starting character
		System.out.print("Enter the index of the starting character:");      
		int startingChar = input.nextInt();
		//Asking for an ending character
		System.out.print("Enter the index of the ending character:");
		int endingChar = input.nextInt();
		//Displaying result
		System.out.println("The substring is: " + s1.substring(startingChar,endingChar+1));

        
        }     
} 
