package sort;
import java.lang.Math;

public class IntroSort1<T extends Comparable<T>> extends AbstractSort<T> {


	public void sort(T[] array, int beginIndex, int endIndex)
	{
		
		int maxDepth = getMaxDepthForIntroSort(beginIndex, endIndex);
		
		introsort(array, maxDepth, beginIndex, endIndex);
	}
	
	public void introsort(T[] array, int maxDepth, int beginIndex, int endIndex) 
	{
		if (maxDepth==0)
			heapsort(array, beginIndex, endIndex);
		
		else {
			if (beginIndex + 1 < endIndex)	// more than one key in the range
				{
					//Sort current partition
					int pivotIndex = partition(array, beginIndex, endIndex);
					//Sort left partition
					introsort(array, maxDepth-1, beginIndex, pivotIndex);
					//Sort right partition
					introsort(array, maxDepth-1, pivotIndex+1, endIndex);
				}
		}
					
	}
	
	protected int partition(T[] array, int beginIndex, int endIndex)
	{
		int fst = beginIndex, snd = endIndex;
			while (true)
			{
					while (++fst < endIndex   && compareTo(array, beginIndex, fst) >= 0);	// Find where endIndex > fst > pivot 
					while (--snd > beginIndex && compareTo(array, beginIndex, snd) <= 0);	// Find where beginIndex < snd < pivot
					if (fst >= snd) break;
					swap(array, fst, snd);
			}

			swap(array, beginIndex, snd);
			return snd;			
			
			
	}
	
	protected int getMaxDepthForIntroSort(int beginIndex, int endIndex)
	{
		return 2*(int)log2(endIndex - beginIndex);
	}
	
	private double log2(int i)
	{
		return Math.log(i) / Math.log(2);
	}
	
	
	public void heapsort(T[] array, int beginIndex, int endIndex)
	{
		//Heaping all elements
		for (int k=getParentIndex(beginIndex, endIndex); k>=beginIndex; k--)
			sink(array, k, beginIndex, endIndex);
		
		//Swap the endIndex element with the root element and sink it
		while (endIndex > beginIndex+1)
		{
			swap(array, beginIndex, --endIndex);
			sink(array, beginIndex, beginIndex, endIndex);
		}
	}
	
	private void sink(T[] array, int k, int beginIndex, int endIndex)
	{
		for (int i=getLeftChildIndex(beginIndex, k); i<endIndex; k=i,i=getLeftChildIndex(beginIndex, k))
		{
			if (i+1 < endIndex && compareTo(array, i, i+1) < 0) i++;
			if (compareTo(array, k, i) >= 0) break;
			swap(array, k, i);
		}
	}
	
	private int getParentIndex(int beginIndex, int k)
	{
		return beginIndex + (k-beginIndex)/2 - 1;
	}
	
	private int getLeftChildIndex(int beginIndex, int k)
	{
		return beginIndex + 2*(k-beginIndex) + 1;
	}
	
}
