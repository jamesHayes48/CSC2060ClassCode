/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;

	// Point to address of houseNum
	int *houseNumPtr = &houseNum;
	
	// Point to houseNumPtr
	int *calchouseNumPtr = &calcHouseNum1;

	// Print the value of houseNum
	printf("houseNum %d\n", houseNum);

	// Print the address of houseNum
	printf("&houseNum %p\n\n", &houseNum);

	// Print the value of address houseNumPtr contains
	printf ("*houseNumPtr  %d\n", *houseNumPtr);

	// Print the address houseNumPtr holds
	printf ("houseNumPtr %p\n\n", houseNumPtr);

	// Print address of the pointer variable (Address that holds an address)
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);

	// Add the value houseNumPtr points to and store in calcHouseNum1
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	// Print the added value
	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);

	// Variable next to * dictates if it will print the value at an address
	// or multiply
	calcHouseNum2 = 2 * (*houseNumPtr);

	// Same value as before
	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);

	// Prints the same value, address of houseNum
	// First prints the address of the value accessed by houseNumPtr
	// Second prints the value store in the address of houseNumPtr 
	// (which is the same address as houseNum)
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);

	// Goofy scenario
	int goofyCalc = 0;

	// Returns same value as calcHouseNum1 and 2
	// Compiler descerns how to approach the problem
	goofyCalc = 2**houseNumPtr;
	printf("Goofy calculation: %d\n", goofyCalc);

	// Adding addresses?
	// int addingAddress = 0;
	
	// Cannot compute, must have integral type (can't add two pointers)
	// Multiply also does not work
	//addingAddress = houseNumPtr + houseNumPtr;

	// Subtracting?
	int subtract = 0;

	// Can subtract houseNumPtr
	subtract = houseNumPtr - houseNumPtr;
	printf("Subtracting calculation: %d\n", subtract);

	// Subtract two different pointers
	subtract = calchouseNumPtr - houseNumPtr;
	printf("Subtracting two different pointers: %d\n", subtract);

	subtract = houseNumPtr - calchouseNumPtr;
	printf("Subtracting two different pointers again: %d\n", subtract);

	// Dividing?
	//int divide = 0;
	
	// Cannot :(
	//divide = (houseNumPtr) / (houseNumPtr);

	return 0;
}
