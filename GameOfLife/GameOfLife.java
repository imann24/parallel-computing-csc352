/*  
 Game of life
 D. Thiebaut
 Heavily adapted from code found in java section at this
 URL:  https://rosettacode.org/wiki/Conway%27s_Game_of_Life#Java

 This code works in console mode, displaying successive generations
 of the game of life on the screen, and clearing the screen between
 each one.

 The initial pattern is defined in the array dish (as in petri dish)
*/

public class GameOfLife{
    
    public static void main(String[] args){
	String[] dish2= {
	    "                                                                                  ",
	    "   #                                                                              ",
	    " # #                                            ###                               ",
	    "  ##                                                                              ",
	    "                                                                                  ",
	    "                                                      #                           ",
	    "                                                    # #                           ",
	    "                                                     ##                           ",
	    "                                                                                  ",
	    "                                                                                  "
	};

	String[] dish3 = {
	    "     ",
	    "  #  ",
	    "  #  ",
	    "  #  ",
	    "     " 
	};
	String[] dish= {
	    "                                                                                  ",
	    "   #                                                                              ",
	    " # #                                            ###                               ",
	    "  ##                                                                              ",
	    "                                                                                  ",
	    "                                                      #                           ",
	    "                                                    # #                           ",
	    "                                                     ##                           ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "             #                                                                    ",
	    "           # #                                                                    ",
	    "            ##                                                                    ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  ",
	    "                                                                                  "
	};
	
	int gens= 30000;

	for (int i= 0;i < gens;i++) {
	    //System.out.println("Generation " + i + ":\n\n\n");
	    print(dish);
	    dish= life(dish);
	    
	    clearScreen();
	    // add a bit of a delay to better see the visualization
	    // remove this part to get full timing.
	    try {
		Thread.sleep(50);                
	    } catch(InterruptedException ex) {
		return;
	    }
	}
    }

    public static void clearScreen(){
	final String ANSI_CLS = "\u001b[2J";
        final String ANSI_HOME = "\u001b[H";
        //System.out.print(ANSI_CLS + ANSI_HOME);
        System.out.print( ANSI_HOME);
        System.out.flush();
    }
    
    public static String[] life(String[] dish){
	String[] newGen= new String[dish.length];

	for ( int row= 0; row < dish.length; row++ ) {//each row

	    newGen[row]= "";

	    for ( int i= 0; i < dish[row].length(); i++ ) {//each char in the row

		int neighbors = 0;
		char current = dish[row].charAt(i);

		// loop in a block that is 3x3 around the current cell
		// and count the number of '#' cells.  
		for ( int r=row-1; r<=row+1; r++ )  {

		    // make sure we wrap around from bottom to top
		    int realr = r;
		    if ( r==-1 )         realr = dish.length-1;
		    if ( r==dish.length) realr = 0;

		    for ( int j=i-1; j<=i+1; j++ ) {
			
			// make sure we wrap around from left to right
			int realj = j;
			if ( j==-1 )                 realj = dish[row].length()-1;
			if ( j==dish[row].length() ) realj = 0;

			if (r==row && j==i ) continue; // current cell is not its
			                               // neighbor
			if (dish[realr].charAt(realj) == '#' )
			    neighbors++;
		    }
		}

		if ( current=='#' ) 
		    if (neighbors < 2 || neighbors > 3) 
			newGen[row] +=  " "; 
		    else
			newGen[row] += "#";  

		if ( current==' ' )
		    if ( neighbors == 3 )
			newGen[row] += "#";
		    else
			newGen[row] += " ";

		
	    }
	}
	return newGen;
    }
    
    public static void print( String[] dish ) {

	for ( String s: dish )
	    System.out.println(s);
	
    }
}
