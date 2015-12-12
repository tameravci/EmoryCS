import java.util.Scanner;
public class Hw0 {
        public static void main(String[] args) {
		String s1;
		Scanner input = new Scanner(System.in);
		System.out.println("Please enter a character");
		String newChar = input.next();
		char letter = newChar.charAt(1);
		System.out.println(letter);
/*
	if ((int)letter >= 65 && (int)letter <= 90); {
		System.out.println("");
	}
	if ((int)letter >= 97  && (int)letter <= 122); {
		char upperChar = (char) ( (letter - 65) );
		System.out.println(upperChar);
	}
		System.out.println("The character" + letter + " is not a letter.");

*/
}
}
