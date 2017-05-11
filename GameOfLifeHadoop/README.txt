AUTHOR
Isaiah Mann

ABSTRACT
Running Game of Life on Hadoop Map Reduce (using the Python code developed in class)

RUN TIME
The code took approximately 39 seconds to run on a single m3.medium node on AWS EC2

PROCESS
1. Created a dish text file using a modified version of initDish.c from the MPI Game of Life assignment
2. Synced the dish0.txt source file and the necessary Python scripts for MapReduce and measuring performance to the hadoop0 server using WGet
3. Uploaded these files to Hadoop using StarCluster's put command
4. Ran the Python MapReduce process using the Python Streaming JAR packaged within Hadoop
5. Analyzed the Hadoop jobs using the provided Python tool script
6. Generated an area graph of jobs using Google Sheets
