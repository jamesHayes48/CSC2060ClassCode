#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maximum length of a string
#define  STRING_LENGTH 80

// Two dimensional array storage amounts for rows and columns of survey data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3

// Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1

// Rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

typedef struct {
	char propertyName[STRING_LENGTH];
	char propertyLocation[STRING_LENGTH];
	int interval1;
	int interval2;
	int rentalRate;
	int discount;
	double totalCharge;
	int totalNights;
	int totalRenters;
	int survey[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
	double averages[RENTER_SURVEY_CATEGORIES];
} Property;

// Functions
bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);
void removeNewLineChar(char* string);
void setupProperty(Property* propertyPtr, const int minNights, const int maxNights, const int minRate, const int maxRate);
int getValidInt(const int min, const int max);
void scanInt(char* input, int* result);
void displayPropertyInfo(Property* propertyPtr);

int main(void) {
	Property property1;
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	if (ownerLogin == true) {
		setupProperty(&property1, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE);
		displayPropertyInfo(&property1);
	}
	else {
		puts("Goodbye");
	}
}

bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts) {
	unsigned int attemptCount = 0;
	bool loginStatus = false;
	char userID[STRING_LENGTH];
	char userPasscode[STRING_LENGTH];

	// Keep prompting for login, until attempts reaches max amount of attempts
	// Or if user entered login correctly
	while (attemptCount < maxAttempts && loginStatus == false) {
		// Prompt user for ID
		printf("%s", "Enter User ID: ");
		fgets(userID,STRING_LENGTH,stdin);

		removeNewLineChar(userID);

		puts("");

		// Prompt user for passcode
		printf("%s", "Enter User Passcode: ");
		fgets(userPasscode,STRING_LENGTH,stdin);
		removeNewLineChar(userPasscode);

		puts("");

		// Compare id and passcode, retun 0 if true
		int compareId = strcmp(correctID, userID);
		int comparePasscode = strcmp(correctPasscode, userPasscode);

		// If both are true, return login staus as true
		// Else, iterate through loop
		if ((compareId == 0) && ( comparePasscode == 0)) {
			loginStatus = true;
		}
		else {
			puts("Wrong ID or Passcode.");
			attemptCount++;
		}
	}
	return loginStatus;
}

void removeNewLineChar(char* string) {
	// If the end of string is a new line char, replace with null char
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

void setupProperty(Property* propertyPtr, const int minNights, const int maxNights, const int minRate, const int maxRate) {
	propertyPtr->totalCharge = 0;
	propertyPtr->totalNights = 0;
	propertyPtr->totalRenters = 0;
	
	printf("%s", "Enter name of property: \n");
	fgets(propertyPtr->propertyName, STRING_LENGTH, stdin);

	printf("%s", "Enter location of property: \n");
	fgets(propertyPtr->propertyLocation, STRING_LENGTH, stdin);

	printf("Enter first interval between %d and %d: ", minNights, maxNights);
	propertyPtr->interval1 = getValidInt(minNights, maxNights);

	printf("Enter second interval between %d and %d: ", (propertyPtr->interval1), maxNights);
	propertyPtr->interval2 = getValidInt((propertyPtr->interval2), maxNights);

	printf("Enter rental rate between %d and %d: ", minRate, maxRate);
	propertyPtr->rentalRate = getValidInt(minRate, maxRate);

	printf("Enter a discount between %d and %d: ", minRate, (propertyPtr->rentalRate));
	propertyPtr->discount = getValidInt(minRate, (propertyPtr->rentalRate));
}

int getValidInt(const int min, const int max) {
	bool isValid = false;
	char inputStr[STRING_LENGTH];
	int result = 0;

	while (isValid == false) {
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLineChar(inputStr);
		scanInt(inputStr, &result);

		if ((result < max) && (result > min)) {
			isValid = true;
		}
		else {
			puts("Invalid input, please another number: ");
		}
	}
	return result;
}

void scanInt(char* input, int* result) {
	char* endPtr;
	long intCheck = strtol(input, &endPtr, 10);
	*result = (int)intCheck;
}

void displayPropertyInfo(Property* propertyPtr) {
	printf("The first interval is %d, the second is %d\n", (propertyPtr->interval1), (propertyPtr->interval2));
	printf("The rental rate is %d and the discount is %d\n", (propertyPtr->rentalRate), (propertyPtr->discount));
	printf("The name of the property is %s, the location is %s\n", (propertyPtr->propertyName), (propertyPtr->propertyLocation));
}
