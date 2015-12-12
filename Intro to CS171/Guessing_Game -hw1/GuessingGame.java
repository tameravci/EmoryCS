/*
      THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
      CODE WRITTEN BY OTHER STUDENTS. TAMER AVCI
*/
import java.util.ArrayList;
import java.util.Random;
import javax.swing.JOptionPane;

public class GuessingGame {

	ArrayList<Integer> game;
	int guesscounter;
	int random;
	int myguess;

	public GuessingGame ( ) {
		game = new ArrayList<Integer>();
		guesscounter = 0;
		for (int i=1000; i<10000; i++)
			game.add(i);
	}

	public int myGuessIs() {
		random = (int)(Math.random()*(game.size()));
		if (game.size() < 1)
			return -1;
		myguess = game.get(random);
		return myguess;
	}
	
	public int totalNumGuesses() {
		return guesscounter;
	}
 
	public void updateMyGuess(int nmatches) {
		guesscounter++;
		if (nmatches == 0) {
			int i=0;
			while (i<game.size()) {
				if (howmanymatch(myguess,game.get(i)) !=0 ) {
					game.remove(i);
					i=0;
				}
				else
					i++;
			}	
		}
		else if (nmatches == 1) {
			int i = 0;
			while(i<game.size()) {
				if(howmanymatch(myguess,game.get(i)) != 1 ) {
					game.remove(i);
					i=0;
				}
				else
					i++;
			}
		}
		else if (nmatches == 2) {
			int i = 0;
			while(i<game.size()) {
				if(howmanymatch(myguess,game.get(i)) != 2 ) {
					game.remove(i);
					i=0;
				}
				else
					i++;
			}	
		}
		else if (nmatches == 3) {
			int i = 0;
			while(i<game.size()) {
				if(howmanymatch(myguess,game.get(i)) != 3 ) {
					game.remove(i);
					i=0;
				}
				else
					i++;
			}
		}
	}
		
	public int howmanymatch(int a, int b) {
		int counter=0;
		if ((a % 10) == (b) % 10)
			counter++;
		
		if (((a % 100) / 10) == ((b % 100) / 10))
			counter++;

		if (((a % 1000) / 100) == ((b % 1000) / 100))
			counter++;
			
		if (a / 1000 == (b / 1000)) 
			counter++;
		return counter;
	}

	// you shouldn't need to change the main function
	public static void main(String[] args) {

		GuessingGame gamer = new GuessingGame( );
  
		JOptionPane.showMessageDialog(null, "Think of a number between 1000 and 9999.\n Click OK when you are ready...", "Let's play a game", JOptionPane.INFORMATION_MESSAGE);
		int numMatches = 0;
		int myguess = 0;
		
		do {
			myguess = gamer.myGuessIs();
			if (myguess == -1) {
				JOptionPane.showMessageDialog(null, "I don't think your number exists.\n I could be wrong though...", "Mistake", JOptionPane.INFORMATION_MESSAGE);
				System.exit(0);
			}
			String userInput = JOptionPane.showInputDialog("I guess your number is " + myguess + ". How many digits did I guess correctly?");
			// quit if the user input nothing (such as pressed ESC)
			if (userInput == null)
				System.exit(0);
			// parse user input, pop up a warning message if the input is invalid
			try {
				numMatches = Integer.parseInt(userInput.trim());
			}
			catch(Exception exception) {
				JOptionPane.showMessageDialog(null, "Your input is invalid. Please enter a number between 0 and 4", "Warning", JOptionPane.WARNING_MESSAGE);
				numMatches = 0;
				continue; //since nummatches=0, updateMyGuess would shrink the array despite an invalid input, so we need to skip that statement 
			}
			// the number of matches must be between 0 and 4
			if ((numMatches < 0 || numMatches > 4)) {
				JOptionPane.showMessageDialog(null, "Your input is invalid. Please enter a number between 0 and 4", "Warning", JOptionPane.WARNING_MESSAGE);
				numMatches = 0;
				continue; //since nummatches=0, updateMyGuess would shrink the array despite an invalid input, so we need to skip that statement
			}
			if (numMatches == 4) {
				gamer.updateMyGuess(numMatches); //I put the guesscounter to the update method, so that invalid inputs won't count as turns
				break;
			}
			// update based on user input
			gamer.updateMyGuess(numMatches);
			
		} while (true);
		
		// the game ends when the user says all 4 digits are correct
		System.out.println("Aha, I got it, your number is " + myguess + ".");
		System.out.println("I did it in " + gamer.totalNumGuesses() + " turns.");
	}
}
