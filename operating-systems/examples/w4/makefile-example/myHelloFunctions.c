#include <stdio.h>
#include <string.h>
#include "myHelloFunctions.h"

void printHello(){
	printf("Hello World!\n");
}

void printHelloName(char* str){
	printf("Hello %s\n", str);
	printf("Name Length: %d\n", (int)strlen(str) - 1);
}
