/*
 * Author: Isaiah Mann
 * Desc: Reads in file of ints. Finds min and max
 */

#include <stdio.h>
#include <stdlib.h>

// Gets min value in an int array
int min(int* arr, int len)
{
     int index;
     int minVal = arr[0];
     for(index = 1; index < len; index++)
     {
          if(minVal > arr[index])
          {
               minVal = arr[index];
          }
     }
     return minVal;
}

// Gets max value in an int array
int max(int* arr, int len)
{
     int index;
     int maxVal = arr[0];
     for(index = 1; index < len; index++)
     {
          if(maxVal < arr[index])
          {
               maxVal = arr[index];
          }
     }
     return maxVal;
}

int main()
{
    // Open a file with the appropriate pointer
    FILE *filePointer;
    filePointer = fopen("data.txt", "r"); // 1st number is # of lines
                                         // then 1 int per line
    if (feof(filePointer)) {
        printf("Empty file!\n\n");
        // Custom error code:
        return -1;
    }

    int arrLength;
    // get the number of lines
    fscanf(filePointer, "%d", &arrLength);

    // Allocate an array of the indicated number of integers
    int* arr = malloc(arrLength * sizeof(int));

    // Read in the integers in the file one by one
    int index;
    for(index = 0; index < arrLength; index++)
    {
         fscanf(filePointer, "%d", &arr[index]);
    }
    fclose(filePointer);

    // Calculate the min and max
    int minVal = min(arr, arrLength);
    int maxVal = max(arr, arrLength);

    // Free the allocated array
    free(arr);

    // Print the results
    printf("The min value is %d and the max value is %d\n", minVal, maxVal);

    // Return 0 to indicate no errors
    return 0;
}
