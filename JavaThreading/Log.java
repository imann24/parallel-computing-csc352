/**
 * Author: Dominique Thiebaut
 * Log class
 * Maintains a log file, stored at location defined in Constants.logFile.
 * Appends messages to log file with a date/time stamp.
 */
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Calendar;


public class Log {
    int Id = 0;
    String logFileName = null;

    public Log( int id ) {
	Id = id;
	logFileName = String.format( "log%d.txt", id );
    }

    public void log( String msg ) {
	Calendar cal = Calendar.getInstance();
	SimpleDateFormat sdf = new SimpleDateFormat( "yyyy-MM-dd HH:mm:ss" );
	String dateTime =  sdf.format( cal.getTime() );

	try {
	    PrintWriter out = new PrintWriter(
			       new BufferedWriter(
				 new FileWriter( logFileName, true)));
	    out.println( dateTime + ": " + msg );
	    out.flush();
	    out.close();
	} catch (IOException e) {
	    //exception handling left as an exercise for the reader
	}

    }

    public static void main(String[] args) {
	for ( int i=0; i<4; i++ )
	    (new Log(i)).log( "this is the first message for Id " + i );
	(new Log(0)).log( "this is the second message for 0" );
	(new Log(1)).log( "this is the second message for 1" );
    }

}
