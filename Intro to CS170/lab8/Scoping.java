public class Scoping {
   static double a = 123;                 /* ....................... location (1) */

   public static void F( double a )       /* ....................... location (2) */
   {
      System.out.println("------ inside F( double a ) !!!!!!!!!!!!!!!!");

      System.out.println("a at (2) = " + a);
      // TODO: Write a System.out.println() statement that prints a on location (2)

      System.out.println("a at (1) = " + Scoping.a);
      // TODO: Write a System.out.println() statement that prints a on location (1)
   }

   public static void F( String a )       /* ....................... location (3) */
   {
      System.out.println("------ inside F( String a ) ");

      System.out.println("a at (3) = " + a);
      // TODO: Write a System.out.println() statement that prints a on location (3)

      System.out.println("a at (1) = " + Scoping.a);
      // TODO: Write a System.out.println() statement that prints a on location (1)

   }



   public static void main( String[] args )
   {
      double x = -444444444;              /* ....................... location (4) */
      // TODO: Write a method call to F() that passes x at location (4)
      F(x);    // I have given you the answer for the first problem.

      {
         double a = 9999;                 /* ....................... location (5) */

         // TODO: Write a method call to F() that passes a on location (5)   
         F(a);      

     		 // TODO: Write a method call to F() that passes a on location (1)
	 F(Scoping.a);
      }									 /* ........................ location (6) */

      // TODO: Write a method call to F() that passes x at location (4)
	 F(x);
	

      // TODO: Write a method call to F() that passes a on location (5)
         System.out.println("Impossible: Write a method call to F() that passes a on location (5)");
      {
         String a = "9999";               /* ....................... location (7) */
 		
         // TODO: Write a method call to F() that passes x at location (4)

         F(x);
         // TODO: Write a method call to F() that passes a on location (7)

         F(a);
         // TODO: Write a method call to F() that passes a on location (1)
	 F(Scoping.a);

      }
   }
}
