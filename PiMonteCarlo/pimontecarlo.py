# pimontecarlo.py
# Mann, Isaiah
#
# Uses Monte Carlo to calculate Pi
# Uses multiprocessing

from __future__ import print_function
import multiprocessing
import random

circle_const = 4.0

def f( x ):
    """
    The function being integrated, and which returns
    an approximation of Pi when summed up over an interval
    of integers.
    """
    return 4.0 / ( 1 + x*x )

class WorkerProcess(multiprocessing.Process):
    """
    That's the main worker Process, as a class.
    It gets initialized via __init__ with the interval
    and deltaX it sums up on.  It saves the accumulated
    sum in self.sum
    """

    def __init__(self, args):
        """
        args must contain n1, n2, and deltaX, in that order.
        """
        multiprocessing.Process.__init__( self, args=args )
        self.count = args[0]
        self.queue = args[1]
        self.inside = 0

    def run( self ):
        """
        This will be called automatically by start() in
        main.  It's the method that does all the work.
        """
        sum = 0.0
        for i in range(self.count):
            x = random.random()
            y = random.random()
            d = x ** 2 + y ** 2
            if(d < 1):
                self.inside += 1
        self.queue.put(self.inside)

def main():
    """
    Gets a number of terms from the user, then sums
    up the series and prints the resulting sum, which
    should approximate Pi.
    """

    # get the number of terms
    steps =input("How many steps?"
    )   #int( input( "# steps > " ) )
    process_count = input("How many processes?")         #int( input( "# processes? > " ) )

    # start T
    jobs = []
    queue = multiprocessing.Queue()

    for i in range(process_count):
        job = WorkerProcess(args=(steps / process_count, queue))
        job.start()
        jobs.append(job)

    # wait for the threads to be done
    #for p in jobs:
    #    p.join()

    # gather the sums
    sum = 0
    for i in range(process_count):
        sum += queue.get()

    # print result
    print( "Approximation of PI = %1.9f" % (circle_const * sum / steps))

main()
