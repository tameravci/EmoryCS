/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/

import java.io.*;
import java.util.Scanner;
import java.util.Arrays;
public class ArrayMethods{
	
	public static void main(String[] args)throws IOException{
	    int[] Array = ReadFromFile("ArrayFile.txt");
            int sum = sum_even(Array);
	    int mult = MultiplyEachN(Array,5);
	    int middle = MiddleValue(Array);
        
	    Printer("sum of even numbers ", sum);
	    Printer("multiplication of each 5 numbers ", mult);
	    Printer("middle value of the array ", middle);
	    Printer("original array is ", Array);

	    int[] shifted = ArrayShifter(Array,1,"right");
	    Printer("array shifted by 1 to the right is: ", shifted);
	
            shifted = ArrayShifter(Array,4,"right");
	    Printer("array shifted by 4 to the right is: ", shifted);

	    shifted = ArrayShifter(Array,7,"left"); 
	    Printer("array shifted by 7 to the left is: ", shifted);
		
	    int[] sorted = sort(Array);
	    Printer("array sorted is: ", sorted);

            double[] ra = RandomArray(Array.length);
	    Printer("A random array is: ", ra);
		
	    int[] pos = Positions(ra);
	    Printer("The positions of Array are: ", pos);

	    int[] sh = Shuffler(Array);
	    Printer("a shuffled version of the array is: ", sh);
		
	}


	public static int[] ReadFromFile(String FileName)throws IOException{
		
	    File myFile = new File(FileName);
	    Scanner in = new Scanner(myFile);
	    int counter=0;
            while (in.hasNextInt()) {
                int x = in.nextInt();
                counter++;
            }				
            int[] a = new int[counter];
		
            in = new Scanner(myFile);

            while (in.hasNextInt()) {
                for (int i=0; i<a.length; i++) {
                a[i] = in.nextInt();
                }
            }
	    return a;
	}

	public static int sum_even(int[] A){
            int sum = 0;
            for (int i=0; i<A.length; i++) {
                if (A[i]%2==0) {
                sum+=A[i];
                }
            }
            return sum;
	}

	public static int MultiplyEachN(int[] A, int n){
            if (n>=A.length) {
            System.err.println("Please give a number less than 6 next time. Program will exit");
            System.exit(1);
            }
            if (n+2>=A.length) {
                return A[n-1];
            }
            else {
                return A[n-1]*A[n+2];
            }
        }

	public static int MiddleValue(int[] A){
            if (A.length%2==0) {
                System.err.println("There is no middle value for this array. Program will exit.");
                System.exit(1);
            }
            return A[A.length/2];
        }

        public static int[] ShifterHelpRight(int[] A) {
            int [] B = new int[A.length];
            for (int i=1; i<A.length; i++) {
                if (i==A.length-1) {
                    B[0]=A[A.length-1];
                    B[A.length-1]=A[A.length-2];
                }
                else {
                    B[i] = A[i-1];
                }
           }
           return B;
        }
      
        public static int[] ShifterHelpLeft(int[] A) {
            int [] B = new int[A.length];
            for (int i=0; i<A.length; i++) {
                if (i==0) {
                    B[A.length-1]=A[0];
                    B[0]=A[i+1];
                }
                else {
                B[i-1] = A[i];
                }
            }
            return B;
        }
       
        public static int[] ArrayShifter(int [] A, int k, String dir) {
            int[] B = new int[A.length];
            if (dir.equals("right")) { 
                B = ShifterHelpRight(A);
                for (int i=1; i<k; i++) {
                    B = ShifterHelpRight(B);
                }
            } 
            else {
                B = ShifterHelpLeft(A);
                for (int i=1; i<k; i++) {
                    B = ShifterHelpLeft(B);
                }
            }
            return B;
        }

        public static int[] sort(int[] A) {
            for (int i=0; i<A.length-1; i++) {
                 int currentMin = A[i];
                 int currentMinIndex = i;
                 for (int j = i+1; j < A.length; j++) {
                     if (currentMin > A[j]) {
                         currentMin = A[j];
                         currentMinIndex = j;
                     }
                 }
                 if (currentMinIndex != i) {
                     A[currentMinIndex] = A[i];
                     A[i] = currentMin;
                 }
            }
            return A;
        }


        public static double[] RandomArray(int n) {
            double[] A = new double [n];
            for (int i=0; i<n; i++) {
                A[i] = Math.random();
            }
            return A;
        }
	
        public static int[] Positions(double[] A) {
            double[] B = new double[A.length];
            for (int i=0; i<A.length; i++) {
                B[i]=A[i];
            }
            for (int i=0; i<A.length-1; i++) {
                 double currentMin = A[i];
                 int currentMinIndex = i;
                 for (int j = i+1; j < A.length; j++) {
                     if (currentMin > A[j]) {
                         currentMin = A[j];
                         currentMinIndex = j;
                     }
                 }
                 if (currentMinIndex != i) {
                     A[currentMinIndex] = A[i];
                     A[i] = currentMin;
                 }
            }
            for (int i=0; i<A.length; i++) {
                for (int j=0; j<A.length; j++) {
                    if(B[i]==A[j]) {
                        B[i] = j;
                    }
                 }
            }
            int[] C = new int[B.length];
            for (int i=0; i<C.length; i++)
                C[i] = (int) B[i]; 
            return C;
        }
	
	
        public static int[] Shuffler(int[] A) {
            double[] B = new double[A.length];
            for (int i=0; i<B.length; i++) {
               B[i] = Math.random();
            }
            int[] abc = Positions(B);
            int[] shuffled = new int [A.length];
            for (int i=0; i<A.length; i++) {
                shuffled[i] = A[abc[i]];
            }
            return shuffled;

       }

       public static void Printer(String a, int n) {
            System.out.println(a + n);
       }

       public static void Printer(String a, int[] b) {
            System.out.println(a + Arrays.toString(b));
       }

       public static void Printer(String a, double[] b) {
            System.out.println(a + Arrays.toString(b));
       }

}
