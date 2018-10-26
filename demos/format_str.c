#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>
int main(int argc, const char *argv[]) 
{ 
   char secret[] = "AAAA";
   printf("%x.%x.%x.%x.%x.\n"); 
   return 0; 
}

