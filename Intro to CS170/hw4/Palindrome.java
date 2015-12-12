/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/

public class Palindrome {
	public static void main(String args[]) {
	
		// Check if there is any command line argument
      		if (args.length == 0 ) {
			System.err.println("Not enough input arguments!");
			System.exit(1);
		}
		int i = 0;
		String word = "";
		boolean a = false;

		for (i=0; i < args.length; i++) {
		word = word + args[i];
		}
		
	
		int left = 0;
		int right = word.length() - 1;
		while (left < right && left != right){
			if (word.charAt(left) != word.charAt(right)) {
				a = false;
				break;
			}
			else {
				a = true;
			}
			left++;
			right--;
			
		}
		System.out.println(a);	
		


      }
}





