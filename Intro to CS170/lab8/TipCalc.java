import java.util.Scanner;

public class TipCalc {
	//TODO: Write the method bill

	static double bill(int a, int b) {
		double costWaffle = a * 3.35;
                double costHashbrowns = b * 1.45;
                double c = costWaffle + costHashbrowns;
                System.out.println("You bought " + a + " waffle(s) " + "and " + b + " hashbrown(s).");
		return c;

	}

	//TODO: Write the method tip
 	static double tip(double d) {
		double e = d * 0.15;
		return e;
	}

	//TODO: Write the method info
	static void info(double c, double d) {
			
		System.out.println("Calculated bill before tip: $" + c);
		System.out.println("Calculated 15% tip: $" + d);	
		System.out.println("Total bill is $" + (d+c) + ", rounded up to $" + Math.ceil(d+c));
		
 	}
	
	public static void main(String[] args) {
		//DO NOT change any code in the main method

		Scanner in = new Scanner(System.in);
		
		//get the number of waffles
		System.out.print("How many waffles? ");
		int w = in.nextInt();

		//get the number of hashbrowns from the user
		System.out.print("How many hashbrowns? " );
		int h = in.nextInt();

		//Calculate the total bill for 5 waffles and 2 hashbrowns
		double b = bill(w, h);
		double t = tip(b);
		info(b, t);	

	}

}
