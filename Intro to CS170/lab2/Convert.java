import java.util.Scanner;

public class Convert
{
public static void main(String [] args) {
// declaration of the variables
double km, miles;
// create a Scanner
Scanner input;
input = new Scanner(System.in);
// Enter distance in kilometer
System.out.print("Please enter a distance in km: ");
km = input.nextDouble(); // Read in input from terminal
// and stores it in the variable "km"
// Calculate distance in miles
miles = 0.62 * km;
// print out the result
System.out.print(km);
System.out.print(" kilometers = ");
System.out.print(miles);
System.out.println(" miles");
}
}

