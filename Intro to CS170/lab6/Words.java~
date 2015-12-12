//specify the import statements needed to use
//a Scanner object and File objects
import java.io.*;
import java.util.Scanner;

public class Words {
	// add a throws exception to the main method
	public static void main(String[] args) throws IOException {
		int wordCount = 0;
		int lineCount = 0;

		//declare and initialize a file built from poe.txt

		File myFile = new File("poe.txt");

		//declare and initialize a Scanner which reads the File object

		Scanner in = new Scanner(myFile);
		String x;

		//write a while-loop to count all *words* in the file

		while (in.hasNext())
		{
			x = in.next();
			wordCount++;
		}
		
		//reset your Scanner
		
		Scanner In = new Scanner(myFile);		

		//write a while-loop to count all *lines* in the file
		
		while (In.hasNextLine()) 
		{
			x = In.nextLine();			
			lineCount++;
		}
		System.out.println("Total words = " + wordCount);
		System.out.println("Total lines = " + lineCount);
	}
}

