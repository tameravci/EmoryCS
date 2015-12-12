
public class Test4
{
   public static void main( String[] args )
   {
      int i;
      int win=0, N=0;

      Roulette x = new Roulette( );

      System.out.println("Test4: color method in class Roulette\n");

      N = 1000;
      for ( i = 1; i <= N; i++ )
      {
         x.spin();
         System.out.print( "Bet on Red, spin = " + x.color() + " " );

         if ( "R".equals( x.color() ) )
         {
            win++;
            System.out.println("WIN");
         }
         else
            System.out.println("lose");
      }

      System.out.println();
      System.out.println("Total spins = " + N + "  Total wins = " + win);
      System.out.println("*** Should be approximately equal to " + 18*N/38);
      System.out.println();
   }
}
