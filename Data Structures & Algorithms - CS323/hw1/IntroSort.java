/*TAMER AVCI #2105024 
I worked on this assignment alone, using only this semester's course materials.
*/

package sort;
import java.lang.Math;

public class IntroSort<T extends Comparable<T>> extends AbstractSort<T> {
	private HeapSort<T> heapsort;
	
	public IntroSort() {
		heapsort = new HeapSort<>();
	}


	public void sort(T[] array, int beginIndex, int endIndex)
	{
		
		int maxDepth = getMaxDepthForIntroSort(beginIndex, endIndex);
		
		introsort(array, maxDepth, beginIndex, endIndex);
	}
	
	public void introsort(T[] array, int maxDepth, int beginIndex, int endIndex) 
	{
		if (maxDepth==0)
			heapsort.sort(array, beginIndex, endIndex);
		
		else if (beginIndex + 1 < endIndex) {
				// more than one key in the range
				
					//Sort current partition
					int pivotIndex = partition(array, beginIndex, endIndex);
					//Sort left partition
					introsort(array, maxDepth-1, beginIndex, pivotIndex);
					//Sort right partition
					introsort(array, maxDepth-1, pivotIndex+1, endIndex);
				
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
}
