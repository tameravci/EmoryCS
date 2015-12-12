
public class Test2
{
   public static void main( String[] args )
   {
      int i;

      boolean found = false;

      Roulette x = new Roulette( );

      System.out.println("Test2: spin method in class Roulette\n");

      for ( i = 1; i < 1000; i++ )
      {
         x.spin();
         System.out.print( x.outcome + " " );

         if ( x.outcome == 37 )
            found = true;

         if ( x.outcome < 0 || x.outcome  > 37 )
         {
            System.out.println("Illegal result of spin(): " + x.outcome );
	    System.out.println("The outcome must be between 0 and 37 !!!");
	    System.out.println("**** Test failed !!! ****");
	 }

         if (i%25 == 0)
            System.out.println();
      }

      System.out.println();

      if ( found )
      {
         System.out.println("Test was passed successfully !");
      }
      else
      {
         System.out.println("The outcome 37 was not found; run test again");
         System.out.println("If you have tried it for 5 times and did not");
         System.out.println("pass the test, your program has a bug");
         System.out.println("You probably used 37 instead of 38 in");
         System.out.println("computation of the random number");
      }

   }
}
