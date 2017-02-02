# pimontecarlo.py
# author: Isaiah Mann
# adapted from code by Dominique Thiebaut
#
# Uses Monte Carlo Algorithm to calculate Pi
# Leverages multiprocessing

from __future__ import print_function
import multiprocessing
import random
import time

circle_const = 4.0

class WorkerProcess(multiprocessing.Process):
    """
    The main worker Process, as a class.
    It gets initialized via __init__ with the interval
    and steps it sums up.  It saves the accumulated
    count of points inside the unit circle in self.inside
    """

    def __init__(self, args):
        """
        args must contain steps, queue, in that order.
        """
        multiprocessing.Process.__init__( self, args=args )
        self.count = args[0]
        self.queue = args[1]
        self.inside = 0

    def run( self ):
        """
        This will be called automatically by start() in
        main.
        """
        sum = 0
        for i in range(self.count):
            # get a random point on the Unit Circle
            x = random.random()
            y = random.random()

            # calculate whether the point is inside the circle
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
    steps =input("How many steps?")

    # get the number of processes running
    process_count = input("How many processes?")

    start_time = time.time()
    
    # start T
    jobs = []
    queue = multiprocessing.Queue()

    # launch the proceses
    for i in range(process_count):
        job = WorkerProcess(args=(steps / process_count, queue))
        job.start()
        jobs.append(job)

    # gather the sums
    sum = 0
    for i in range(process_count):
        sum += queue.get()

    elapsed_time = time.time() - start_time
    # print result
    print("Approximation of PI = %1.9f" % (circle_const * sum / steps))
    print("Ran in %1.9f seconds" % elapsed_time)

main()
