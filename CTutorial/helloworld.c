#include <stdio.h>
#include <string.h>

int main() {
     char hello[] = "Hello";
     char world[] = "World!";
     char sentence[100] = "";

     strcpy(sentence, hello); // sentence <- "Hello"
     strcat(sentence, " "); // sentence <- "Hello "
     strcat(sentence, world); // sentence <- "Hello World!"

     printf("sentence = %s\n", sentence);

     // Means "no error":
     return 0;
}
