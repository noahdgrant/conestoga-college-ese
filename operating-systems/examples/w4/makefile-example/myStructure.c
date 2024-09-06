#include "myStructure.h"

float processStruct(struct myStruct str){
	return str.myFloat * str.myInt;
}

int isGreaterThanStructProduct(struct myStruct thisStr, float guess){
	return (guess > processStruct(thisStr));
}
