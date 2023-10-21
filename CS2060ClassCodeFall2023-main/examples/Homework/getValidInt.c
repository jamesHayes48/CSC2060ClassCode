#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 80

bool getValidInt(char* input, int min, int max, int* update);

int main(void) {
	char inputStr[LENGTH];
	int result = 0;
	
	fgets(inputStr, LENGTH, stdin);
	
	if (inputStr[strlen(inputStr) - 1] == '\n') {
		inputStr[strlen(inputStr) - 1] = '\0';
	}

	bool isValid = getValidInt(inputStr, 1, 14, &result);
	
	if (isValid == true) {
		puts("Valid :)");
	}
	else {
		puts("Invalid >:(");
	}
}

bool getValidInt(char* input, int min, int max, int* update) {
	// Declare end pointer
	char* endPtr;
	// Declare and intialize valid status as false
	bool valid = false;
	// Place into test value
	long intCheck = strtol(input, &endPtr, 10);
	
	// If end pointer never updates, then it starts with a character
	if (endPtr == input) {
		valid = false;
	}
	// Return false if exceeds min or max
	else if ((intCheck < min) || (intCheck > max)) {
		valid = false;
	}
	// Check if endPtr is at an invalid value update if so and valid status is true
	else if (*endPtr != '\0') {
		// Update input string if is a decimal or has a character at the end
		input[strlen(endPtr)] = '\0';
		intCheck = strtol(input, &endPtr, 10);
		valid = true;
	}
	// If no problems detected, it is true
	else {
		valid = true;
	}
	// Place integer from string into an int variable
	*update = (int)intCheck;
	return valid;
}