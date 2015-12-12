package sort;

public class ProbabilityBucketSort extends AbstractBucketSort<Double>{

	public ProbabilityBucketSort() {
			super(10, true);
	}
		
	@Override
	protected int getBucketIndex(Double key)
	{
		return (int) (key * 10);
	}
}
