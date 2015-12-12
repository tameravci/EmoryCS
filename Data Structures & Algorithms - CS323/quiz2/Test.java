package sort;
public class Test<T extends Comparable<T>>  {
	
	public static void main(String[] args){
		
		for(int x = 100; x <= 1000; x+=100){
			AbstractSort<Integer> s1 = new ShellSort<Integer>();
			AbstractSort<Integer> s2 = new ShellSortHibbard<Integer>();

	
			Integer[] myarray = new Integer[x];
			Integer[] myarray2 = new Integer[x];


			for (int i = 0 ; i < x ; i++) { 
				myarray[i] = (int) (Math.random () * x);
			}
		
			for (int i = 0 ; i < x ; i++) { 
				myarray2[i] = myarray[i];
			}
			
				
			s1.sort(myarray, 0, x);
			System.out.println(s1.getComparisonCount());
			System.out.println(s1.getAssignmentCount());
			System.out.println();

			s2.sort(myarray2, 0, x);
			System.out.println(s2.getComparisonCount());
			System.out.println(s2.getAssignmentCount());
			System.out.println("-----");
			
		
			s1.resetCounts();
			s2.resetCounts();
			s1 = null;
			s2 = null;
			myarray = null;
			myarray2 = null;
		
		}
	}
}	