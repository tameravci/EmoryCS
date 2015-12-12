
package sort;

import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Random;

import org.junit.Test;

import utils.DSUtils;

public class ProbabilityBucketSortTest
{
	@Test
	public void test()
	{
		final int ITERATIONS = 10;
		final int SIZE = 100;
		
		test(ITERATIONS, SIZE, new ProbabilityBucketSort());
		
	}
	
	void test(final int ITERATIONS, final int SIZE, AbstractSort<Double> engine)
	{
		final Random rand = new Random();
		Double[] original, sorted;
		for (int a=0; a<ITERATIONS; a++)
		{
			System.out.println("---------");
			System.out.println("List number: "+a);
			System.out.println("Buckets: (unsorted)");
			original = getRandomDoubleArray(rand, SIZE);
			sorted = Arrays.copyOf(original, SIZE);
			
			engine.sort(original);
			Arrays.sort(sorted);
		
			assertTrue(DSUtils.equals(original, sorted));
			System.out.println();
			System.out.println("List sorted by ProbabilityBucketSort");
			for (int i=0; i<SIZE; i++) {
				System.out.println(original[i] + " ");
			}
			System.out.println();
			System.out.println("List sorted by Java library");
			for (int i=0; i<SIZE; i++) {
				System.out.println(sorted[i] + " ");
			}
			
		}
	}

	
	static public Double[] getRandomDoubleArray(Random rand, int SIZE)
	{
		Double[] array = new Double[SIZE];
		
		for (int i=0; i<SIZE; i++)
			array[i] = rand.nextDouble();
		
		return array;
	}
	
}