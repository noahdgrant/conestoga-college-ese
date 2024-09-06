#include <stdio.h>
#include <stdlib.h>
#include "myStructure.h"
#include "myHelloFunctions.h"

struct myStruct sampleStruct;

int main(){

	char input[20];
	sampleStruct.myInt = 20;
	sampleStruct.myFloat = 12.1;
	
	printHello();
	
	printf("Your Name? ");
	fgets(input, 20, stdin);
	
	printHelloName(input);
	
	printf("Give me a number: ");
	fgets(input, 20, stdin);
	
	if(isGreaterThanStructProduct(sampleStruct, (float)atof(input))){
		printf("Your number is greater than mine!\n");
	}
	else{
		printf("Your number is smaller than or equal to mine!\n");
	}
	
	return 0;
}
