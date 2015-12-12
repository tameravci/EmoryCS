/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER AVCI
*/
public class Recursive{

	public static void main(String[] args) {
		String word = "BcDaUiOlK";
		alphabeticalOrder(word);
		System.out.println();
		word = "orchestra";
		alphabeticalOrder(word);
		System.out.println();
		System.out.println("areAnagrams("+word + ",carthorse) ->" +areAnagrams(word, "carthorse"));
		replace("kind", 'k', 'm');		
	}

	public static boolean areAnagrams(String str1, String str2){ 
		int c = str1.length();
		if (str1.length()!=str2.length())
			return false;
		for (int b=0 ; b<str2.length(); b++) {		
			if (str1.charAt(0) == str2.charAt(b)) { // add this code || str1.charAt(0)-32 == str2.charAt(b) || str1.charAt(0) == str2.charAt(b)-32) 							        {if uppercase/lowercase letter difference doesn't matter}
				str1 = remove(str1, 0);
				str2 = remove(str2, b);
				return areAnagrams(str1,str2);	
			}
		}
		if (str1.length()==0)
			return true;
		return false;
	}

	
	public static void alphabeticalOrder(String word) {
		if (word.length()<=1) {
			System.out.print(word);
			return;
		}
		else		
			System.out.print(word.charAt(minimum(word)));
                alphabeticalOrder(remove(word,minimum(word)));
	}

	public static int minimum(String word) {
		String str = word.toLowerCase();
		char c = str.charAt(0);	
		for ( int i = 0; i < str.length(); i++) {
			if(c>str.charAt(i))
				c=str.charAt(i);
		}
		if(c==str.charAt(0))
			return 0;
		return str.indexOf(c);
	}			

	
	public static void replace(String word, char char1, char char2) {	
		if(word.length()==0) {
			return;
		}
		else if (word.charAt(0)==char1) {
			System.out.print(char2);
			word = remove(word, 0);
		}
		else {
			System.out.print(word.charAt(0));
			word = remove(word, 0);
		}	
		replace(word, char1, char2);
	}

	public static String remove(String s, int i) {
		String s1 = "";
		String s2 = "";

		if (i >= s.length()) {
			s1 = s.substring(0,s.length()-1);
		} else if (i <= 0) {
			s2 = s.substring(1);
		} else {
			s1 = s.substring(0,i);
			s2 = s.substring(i+1, s.length());
		}

		return s1+s2;
	}	
	
}
