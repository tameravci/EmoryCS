
public class Test1
{
   public static void main( String[] args )
   {
      int i;

      Roulette x = new Roulette( );

      System.out.println("Test1: constructor method in class Roulette\n");

      for ( i = 0; i < 38; i++ )
      {
         System.out.print( "value[" + i + "] = " + x.value[i] +
                             " color[" + i + "] = " + x.color[i] + "  " );

         if (i%2 == 1)
            System.out.println();
      }

      System.out.println();
   }
}
