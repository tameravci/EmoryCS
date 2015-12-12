
package sort;
import java.lang.Math;
public class ShellSortHibbard<T extends Comparable<T>> extends InsertionSort<T>{ 
	@Override
	public void sort(T[] array, int beginIndex, int endIndex)
	{
		int h = getMaxH(endIndex - beginIndex);
		
		while (h >= 1)
		{
			//Insertion sort with the gap of h
			sort(array, beginIndex, endIndex, h);
			h = getNextH(h);
		}
	}
	
	public int getMaxH(int n)
	{
		final int upper = n / 2;	//Estimate the upper bound of the sequence
		int h = 1, t=1;
		
		while (h<upper)
		{
			h = (int) (Math.pow(2, t)) - 1;
			t++;
		}
		
		return h;
	}
	
	public int getNextH(int h)
	{
		return h/2 ;
	}
}


