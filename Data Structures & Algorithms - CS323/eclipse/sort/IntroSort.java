package sort;
import java.lang.Math;

public class IntroSort<T extends Comparable<T>> extends AbstractSort<T> {

public int depth = 1;
public boolean key = false;

	public void sort(T[] array, int beginIndex, int endIndex)
	{
		
		int maxDepth = getMaxDepthForIntroSort(beginIndex, endIndex);
		
		introsort(array, maxDepth, beginIndex, endIndex);
	}
	
	public void introsort(T[] array, int maxDepth, int beginIndex, int endIndex) 
	{
			if (beginIndex + 1 < endIndex)	
				{

					int pivotIndex = partition(array, maxDepth, beginIndex, endIndex);
					
					if(key)
						return;

					introsort(array, maxDepth, beginIndex, pivotIndex);

					introsort(array, maxDepth, pivotIndex+1, endIndex);
					
					depth--;
				}
			
					
	}
	
	protected int partition(T[] array, int maxDepth, int beginIndex, int endIndex)
	{
		int fst = beginIndex, snd = endIndex;
		if (depth>maxDepth) 
		{
			heapsort(array, beginIndex, endIndex);
			key=true;
			return endIndex;	
		}
			while (true)
			{
					while (++fst < endIndex   && compareTo(array, beginIndex, fst) >= 0);	// Find where endIndex > fst > pivot 
					while (--snd > beginIndex && compareTo(array, beginIndex, snd) <= 0);	// Find where beginIndex < snd < pivot
					if (fst >= snd) break;
					swap(array, fst, snd);
			}

			swap(array, beginIndex, snd);
			depth++;
			key=false;
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
