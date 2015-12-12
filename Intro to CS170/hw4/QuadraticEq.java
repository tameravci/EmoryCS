/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/

import java.util.Scanner; 
public class QuadraticEq {
	public static void main(String args[]) {
	
		double x_min=-10,x, step = 0.001, x_max=10;
		double x1, x2, y;
		int max_iter = 0;
		Scanner input = new Scanner(System.in);
		
		/*Enter 4 parameters using Command Line Arguments. If there are less than 4 parameters, write a message explaining the error, and exit.*/
		if(args.length<4){
			System.out.println("Not enough parameters. We should have four parameters: tolerance, a, b, and c");
			System.exit(1);  /*Exit with 1 means there was some problem for which we had to exit */
		}

	
		/* The first parameter is the Tolerance (or tol). The second, third, and fourth parameters will be a, b, and c respectively, i.e. the coefficients for the equation ax^2+bx+c.*/
		double tol=Double.parseDouble(args[0]);	
		double b=Double.parseDouble(args[2]);
		double c=Double.parseDouble(args[3]);

	
		/*Tolerance has to be less than 0.01, but greater than 0. Otherwise, ask the user for another value until the value entered is in the appropriate range. */

		while (tol >= 0.01 || tol <=0 ) {
			System.out.print("The value of tolerance has to be between 0.01 and 0. Try again \ntol=");
			tol = input.nextDouble();
		}

		/*The value of a has to be different from 0. If it is 0, ask the user for another value for a, until the value entered is different from 0.*/

		double a=Double.parseDouble(args[1]);
		while(a == 0){
			System.out.print("a cannot be zero. Try again \na=");
			a=input.nextDouble();
		}

	
		/*If b^2-4ac is less than 0, then the equation has no solution, so we need to ask for new values for b and c. Ask for new values of b and c until the user enters coefficients so that b^2-4ac >=0    */
		double det = b*b-4*a*c;
		while (det < 0) {	
			System.out.print("The equation has no solution within real numbers, please provide new values for b and c. \nb=");
			b=input.nextDouble();
			System.out.print("c=");
			c=input.nextDouble();
			det = b*b-4*a*c;

		}
	

		/*Using x_min, set an initial value for y, using the equation for the quadratic formula (i.e. y = ax^2+bx+c). if |y|>Tolerance, then avance x to x+step, and calculate a new y. Check again if 			|y|>Tolerance. Continue doing this until |y|<=Tolerance.*/

		x=x_min;
		y=a*x*x+b*x+c;
		while (Math.abs(y) >= tol) {
			x+=step;
			y=a*x*x+b*x+c;
			max_iter++;
			/*However, if your program keeps running for more than max_iter cycles, display a message saying that the solution was not found in the range and exit. */
			if (max_iter >=100000){
				System.out.println("The solution was not found in the range.");
				System.exit(1);
			}
			else {
			}
			
		}
		
		/*Once |y|<=Tolerance, save in the variable x1 the x that made this possible. In other words, x1 will be such that |ax1*x1+b*x1+c| <= Tolerance.*/
		x1=x;
	

		/*If you want (+5 points), you can keep looking for the next solution x2 in the same way you found x1*/

		/*Display the results x1 (and x2). Compare your results with the exact values 
		x1 = (-b+Math.sqrt(b*b-4*a*c))/(2*a) and x2 = (-b-Math.sqrt(b*b-4*a*c))/(2*a)    */	

		x=x_max;
		y=a*x*x+b*x+c;
		while (Math.abs(y) >= tol) {
			x-=step;
			y=a*x*x+b*x+c;
			max_iter++;
			/*However, if your program keeps running for more than max_iter cycles, display a message saying that the solution was not found in the range and exit. */
			if (max_iter >=100000){
				System.out.println("The solution was not found in the range.");
				System.exit(1);		
			}
			else {
			}
		}
		x2=x;

		/*Check if b*b-4*a*c ==0. If it is, there is only one solution, so you can display the result and exit.           */

		if (b*b-4*a*c == 0) {
			System.out.println("Equation " + a + "*x^2+" + b + "*x" + c + "=0 has a solution in x1 = " + x1);
			System.out.println("exact solution1:" + (-b +Math.sqrt(b*b-4*a*c))/(2*a));
		}
		else {	
			System.out.println("Equation " + a + "*x^2+" + b + "*x+" + c + "=0 has a solution in x1 = " + x1+ "\nand in x2 = " +x2);
			System.out.println("exact solution x1:" + (-b +Math.sqrt(b*b-4*a*c))/(2*a));
			System.out.println("exact solution x2:" + (-b -Math.sqrt(b*b-4*a*c))/(2*a));
		}	

	
   	}
}
