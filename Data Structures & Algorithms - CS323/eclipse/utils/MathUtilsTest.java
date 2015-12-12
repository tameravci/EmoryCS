package utils;
import static org.junit.Assert.assertEquals;
import org.junit.Test;


public class MathUtilsTest {
	@Test
	public void getMiddleIndexTest()
	{
	    assertEquals(MathUtils.getMiddleIndex(0, 10), 5);
	}

}
