/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER AVCI
*/
public class Fake{

	public static void main(String[] args) {
		System.out.println(F(-1, 4, 4));
		System.out.println(F(-1, 4, 4));
		System.out.println(F(-1, 4, 4));
		System.out.println(F(-1, 4, 4));
	}

	public static int F(int i, int j, int k) {
			int s, t;
if ( i <= 0 || j <= 0 )
return 1;
else if ( i + k < j )
return (i+j);
else {
s = 0;
for (t = 1; t < k; t++) {
s = s + F(i-t, j-t, k-1) + 2;
}
return s;
}
}
	}

	

}
