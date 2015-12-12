/* 
TAMER AVCI
tamer.avci@emory.edu  2105024
I worked on this assignment alone, using only this semester's course materials. 
*/

public class PentaNumber {
	public static char[] penta = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'Z', 'Q', 'J', 'G'};

	public static int parsePenta(String s) {
		if(s.length()==0) {
			return 0;
		}
		int number = 0;
		if(s.charAt(0) == '-') {
			for (int i = s.length()-1; i>-1; i--) {
				for(int j = 0; j<penta.length; j++) {
					if(s.charAt(i) == penta[j]) {
						number = (int) (number + j * (int) Math.pow(15, s.length()-1-i));
						break;
					}
				}
			}
			return -1*number;
		}
		else {
			for (int i = s.length()-1; i>-1; i--) {
				for(int j = 0; j<penta.length; j++) {
					if(s.charAt(i) == penta[j]) {
						number = (int) (number + j * (int) Math.pow(15, s.length()-1-i));
						break;
					}
				}
			}
			return number;
		}
		
	}
	public static String toString(int a) {
		if(a==0)
			return "0";
		
		if(a<0) {
			a=-1*a;
			String number = "";
			while (a > 0) {
				number = penta[a%15] + number;
				a = a / 15;
			}
			return "-"+number;
		}
		else {
			String number = "";
			while (a > 0) {
				number = penta[a%15] + number;
				a = a / 15;
			}
			return number;
		}
	}
}

