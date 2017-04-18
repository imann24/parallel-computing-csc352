public class PiSerial {
        
        private static double f( double x ) {
                return 4.0 / ( 1 + x*x );
        }
        
        public static void main( String[] args ) {
        
                //--- syntax: java -jar PiSerial.jar N ---
                if ( args.length == 0 ) {
                        System.out.println( "Syntax: PiSerial N\nwhere N is the number of iterations\n\n" );
                        return;
                }
                
                int N = Integer.parseInt( args[0] );
                if ( N==0 ) N = 1000;
                
                double sum = 0;
                double deltaX = 1.0/N;
                
                //--- iterate ---
                for ( int i=0; i<N; i++ ) 
                        sum += f( i * deltaX );
                
                System.out.println( N + " iterations.  Result = " + sum*deltaX + "\n\n" );
        }
}
