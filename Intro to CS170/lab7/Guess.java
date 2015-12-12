/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/
import java.util.Scanner;
import java.util.Random;

/**
 * The Guess class is an application that uses a Random object to 
 * to play a number guessing game with one computer player and one
 * human player.
 *
 * Bugs: There are three bugs. Can you find them?
 * //YOU WILL ONLY NEED TO MAKE MINOR CHANGES/ADDITIONS TO FIX THEM!
 * 
 * @author Valerie Summet, modified 2013
 * @author Jim Skrentny, modified 2009-2012
 * @author Daniel Wong, modified 2008
 * @author Eva Schiffer, copyright 2006, all rights reserved
 */
public class Guess {

    // YOU MAY ASSUME THE COMMENTS CORRECTLY DESCRIBE WHAT SHOULD HAPPEN.
    public static void main(String[] args) {
        
        //THESE DECLARATIONS ARE CORRECT.
        //FOR DEBUGGING USE A SEED TO MAKE THE EXECUTION REPEATABLE!
        Random ranGen = new Random();   // pseudo-random number generator  //did not use the seed instead I printed the computer's guess (cheated)
        final int sides = 6;            // number of sides for a die

        Scanner userInput = new Scanner(System.in);
        int userguess = -1;             // user's guess,  1 - 6 inclusive
        int rolled = -1;                // number rolled, 1 - 6 inclusive
        int computerPoints = 0;         // computer's score, 0 - 5 max
        int humanPoints = 0;            // human user's score, 0 - 5 max
        boolean rightGuess = false;     // flag for correct guess
        int numGuesses = 0;             // counts the number of guesses per round

        //MAKE SURE THE PROGRAM PLAYS BY THESE RULES!!!
        System.out.println("Welcome to the Guess Game!\n\n RULES:");
        System.out.println("1. We will play five rounds.");
        System.out.println("2. Each round you will guess the number rolled on a six-sided die.");
        System.out.println("3. If you guess the correct value in three or fewer tries\n" +
            "   then you score a point, otherwise I score a point.");
        System.out.println("4. Whoever has the most points after five rounds wins.");
        
        //BUGS ARE IN THE CODE BELOW.
        // play five rounds
        for (int r = 1; r < 6; r++) { //changed 5 to 6 to play 5 rounds

            // roll the die to start the round
            System.out.println("\n\nROUND " + r);
            System.out.println("-------");
            rolled = ranGen.nextInt(sides)+1;
            System.out.println("The computer has rolled the die.");  // I added + rolled here before to see the random number 1-6
            System.out.println("You have three guesses.");

            // loop gives user up to three guesses
            numGuesses = 0;
            rightGuess = false; // this part of code is crucial after the first round. 
                               //If you do not put this, the game will not execute the while loop for the upcoming rounds once your guess is correct.
            while (numGuesses < 3 && !rightGuess) {

                // input & validation: must be in range 1 to 6 inclusive
                 if (userguess < 1 || userguess > 6);{    //do we really need this if?
                     System.out.print("\nWhat is your guess [1-6]? ");

                     userguess = userInput.nextInt();
		 }
                 while ((userguess < 1) || (userguess > 6)) {    // must be "||" not "&&" also it must be a while loop so that invalid input won't count as a guess
                     System.out.println("   Please enter a valid guess [1-6]!");
 		     userguess = userInput.nextInt(); //input valid guess
                 }
                

                // did the user guess right?
                if (rolled == userguess) {
                    rightGuess = true;
                    System.out.println("   Correct!");
                } else {
                    System.out.println("   Incorrect guess.");
                }
                numGuesses++; // so that the computer gives us only 3 chances to guess per round
            }

            // if the user guessed right, they get a point
            // otherwise the computer gets a point
            if (rightGuess) {
                humanPoints++;
            } else {
                computerPoints++;
            }

            // display the answer and scores
            System.out.println("\n*** The correct answer was: " + rolled + " ***\n");
            System.out.println("Scores:");
            System.out.println("  You: \t\t" + humanPoints);
            System.out.println("  Computer: \t" + computerPoints);
            System.out.println("");

        }

        // tell the user if they won or lost
        if (computerPoints > humanPoints) {
            System.out.println("*** You Lose! ***");
        } else {
            System.out.println("*** You Win! ***");
        }

        System.out.println("Thanks for playing the Guess Game - bug free!");
    } // end main

}  // end class Guess

