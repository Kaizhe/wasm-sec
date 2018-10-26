#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>

EM_JS(void,showAdminPassword,(),{ 
  alert("Secret Password!"); 
}); 

int main() { 
  char user[] = "guest"; 
  char input[5]; 
  memset(input, '\0', 5);
  strcpy(input,"BBBBBBadmin"); 
  printf("input address: %p\n", &input);
  printf("input: %s\n", input);
  printf("user address: %p\n", &user);
  printf("user: %s\n", user);
  if(strcmp(user, "admin") == 0) { 
    showAdminPassword(0);
    return 0; 
  }
}

