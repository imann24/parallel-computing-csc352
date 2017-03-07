#include <stdio.h>
#include <string.h>

int main() {
     char fullName[] = "Isaiah Mann";
     int length = strlen(fullName);
     printf("%s\n", fullName);
     // Source: http://stackoverflow.com/questions/14678948/how-to-repeat-a-char-using-printf
     // More memory solution
     printf("%.*s\n", length, "______________________________________________");
     return 0;
}
