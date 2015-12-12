public class Sample {
  public static void indentCharLine(int i, char c, int n) {
	String out = "";

	//build up indentation using spaces
	for(int x = 0; x < i; x++) {
		out += " ";
	}

	//build up characters
	for(int x = 0; x < n; x++) {
		out += c;
	}
	
	//print out the new string
	System.out.println(out);
}


   public static void main(String[] args)
   {
      int i;

      /* -----------------------------------------
         Make sure user provides 1 argument
         ----------------------------------------- */
      if ( args.length != 1 )
      {
         System.err.println("Error: Program needs 1 integer as input");
         System.exit(1);
      }

      /* -----------------------------------------
         Convert first argument to integer
         ----------------------------------------- */
      int n = Integer.parseInt( args[0] );

      /* -----------------------------------------------
         Use indentCharLine() to print a nxn square

         Print n rows of character 'X' of width n
         ----------------------------------------------- */
      for ( i = 0; i < n; i++ )
      {
         indentCharLine(1, 'X', n);
      }
   }
}
