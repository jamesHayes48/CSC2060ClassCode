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
#define SENTINEL_NEG1 -1

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
void rentalMode(Property* propertyPtr, int sentinel, const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);
void displayPropertyInfo(Property* propertyPtr);
int getValidSentinel(const int min, const int max, const int sentinel);
double calculateCharges(unsigned int nights, unsigned int interval1, unsigned int interval2, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);

// Print survey information
void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories);

// Print categories for rating
void printCategories(const char* categories[], size_t totalCategories);

// Loop and add input into 2D array
void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], const char* categories[], size_t totalUsers, size_t totalCategories);

// Get valid input
int getValidInt(int minRating, int maxRating);

// Print the results of the survey
void printSurveyResults(const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Calculate the average for each category
void calculateCategoryAverages(double averages[], int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Print the averages for each category
void printCategoryData(const double averages[], size_t totalUsers, size_t totalCategories);

int main(void) {
	Property property1;
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	while (ownerLogin == true) {
		setupProperty(&property1, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE);
		rentalMode(&property1, SENTINEL_NEG1, CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
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
	//propertyPtr->averages[] = {0};
	//propertyPtr->survey[] = {0};

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

		if ((result <= max) && (result >= min)) {
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

void rentalMode(Property* propertyPtr, int sentinel, const char* correctID, const char* correctPasscode, const int unsigned maxAttempts) {
	bool validSentinel = false;
	int userNights = 0;
	double currentCharge = 0;

	do {
		displayPropertyInfo(propertyPtr);
		if (propertyPtr->averages[0] != 0) {
			puts("Teehee");
		}
		puts("Enter number of nights");
		userNights = getValidSentinel(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, sentinel);
		if (userNights == sentinel) {
			login(correctID, correctPasscode, maxAttempts);
			validSentinel = true;
		}
		else {
			propertyPtr->totalNights += userNights;
			currentCharge = calculateCharges(userNights, (propertyPtr->interval1), (propertyPtr->interval2), (propertyPtr->rentalRate), (propertyPtr->discount));
			propertyPtr->totalCharge += currentCharge;
			printNightsCharges(userNights, currentCharge);
		}
	} while (validSentinel == false);
}

void displayPropertyInfo(Property* propertyPtr) {
	printf("The first interval is %d, the second is %d\n", (propertyPtr->interval1), (propertyPtr->interval2));
	printf("The rental rate is %d and the discount is %d\n", (propertyPtr->rentalRate), (propertyPtr->discount));
	printf("The name of the property is %s, the location is %s\n", (propertyPtr->propertyName), (propertyPtr->propertyLocation));
}

int getValidSentinel(const int min, const int max, const int sentinel) {
	bool isValid = false;
	char inputStr[STRING_LENGTH];
	int result = 0;

	while (isValid == false) {
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLineChar(inputStr);
		scanInt(inputStr, &result);

		if ((result <= max) && (result >= min)) {
			isValid = true;
		}
		else if (result == sentinel) {
			isValid = true;
		}
		else {
			puts("Invalid input, please another number: ");
		}
	}
	return result;
}

double calculateCharges(unsigned int nights, unsigned int interval1, unsigned int interval2, double rate, double discount) {
	// Intialize count
	int unsigned count = 1;

	// Intialize charges
	double charges = 0;

	// Loop until count is greater than number of nights
	while (!(count > nights)) {

		// Add charge each time
		charges += rate;

		// If count is greater than 1st interval apply discount
		if (count > interval1) {
			charges -= discount;

			// If count is greatert than 2nd interval apply discount
			if (count > interval2) {
				charges -= discount;
			}
		}

		// Iterate count
		count++;
	}
	return charges;
}

void printNightsCharges(unsigned int nights, double charges) {
	// If no rentals were made, then print then no rentals were made
	if (nights == charges) {
		puts("\nThere were no rentals\n");
	}
	//  If there were inputs, output the result
	else {
		printf("\nNights: %d Charge: $%.2f\n", nights, charges);
	}
}

