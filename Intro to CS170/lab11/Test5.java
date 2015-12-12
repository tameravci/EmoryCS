
public class Test5
{
   public static void main( String[] args )
   {
      int i;
      int win=0, N=0;

      Roulette x = new Roulette( );

      System.out.println("Test5: toString method in class Roulette\n");

      N = 10;
      for ( i = 1; i <= N; i++ )
      {
         x.spin();
         System.out.println( "x = " + x );
      }

      System.out.println();
      System.out.println("If you don't see '0 G' or '00 G', run again");
      System.out.println();
   }
}
