
public class Test3
{
   public static void main( String[] args )
   {
      int i;
      int win=0, N=0;

      Roulette x = new Roulette( );

      System.out.println("Test3: value method in class Roulette\n");

      N = 1000;
      for ( i = 1; i <= N; i++ )
      {
         x.spin();
         System.out.print( "Bet on 13, spin = " + x.value() + " " );

         if ( "13".equals( x.value() ) )
         {
            win++;
            System.out.println("WIN");
         }
         else
            System.out.println("lose");
      }

      System.out.println();
      System.out.println("Total spins = " + N + "  Total wins = " + win);
      System.out.println("*** Should be approximately equal to " + N/38);
      System.out.println();
   }
}
