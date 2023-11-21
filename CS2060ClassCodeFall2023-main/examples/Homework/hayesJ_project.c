#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Maximum length of a string
#define  STRING_LENGTH 80

// Two dimensional array storage amounts for rows and columns of survey data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 4

// Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "abcd"
#define LOGIN_MAX_ATTEMPTS 2
#define SENTINEL_NEG1 -1

// Rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

// Survey Min and Max
#define MIN_RATING 1
#define MAX_RATING 5

// Property structure and its information
typedef struct property {
	char propertyName[STRING_LENGTH];
	char propertyLocation[STRING_LENGTH];
	unsigned int interval1;
	unsigned int interval2;
	unsigned int rentalRate;
	int discount;
	double totalCharge;
	int totalNights;
	int totalRenters;
	int currentUser;
	int survey[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
	double averages[RENTER_SURVEY_CATEGORIES];

	struct property* nextPropertyPtr;
} Property;

// Prompt user login
bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);

// Display Property information for vacationer
void displayPropertyInfo(Property* propertyPtr, int minNights, int maxNights);

// Print Properties
void printProperties(Property* headPtr, int minNights, int maxNights);

// Print min and maxes of owner set up
void maxOwnerSetUp(const int minInterval, const int maxInterval, const double minRate, const double maxRate);

// Remove new line character in user input
void removeNewLineChar(char* string);

// Set all characters in string to lowercase
void lowerString(char string[]);

// Prompt set up property
void setupProperty(Property* propertyPtr, int minNights, int maxNights, int minRate, int maxRate, int maxRenters, int maxCategories);

// Get valid integer, within min and max
int getValidInt(const int min, const int max);

// Scan user input and put into result
void scanInt(char* input, int* result);

// Insert Property on linked list
void insertProperty(Property** headPtr, int minNights, int maxNights, int minRate, int maxRate, int maxRenters, int maxCategories);

// Prompt for (y)es or (n)o
char yesOrNo();

// Prompt vacationer for number of nights and rating
bool rentalMode(Property* propertyPtr, const int minNights, const int maxNights, const int sentinel,
	const int maxRenters, const int maxCategories, const int minRating, const int maxRating,
	const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);

// Prompt user which property to rent
Property* selectProperty(Property** headPtr, char selectName[]);


int main (void) {
	Property* headMainPropertyPtr = NULL;
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	char userContinue;

	if (ownerLogin == true) {
		do {
			printProperties(headMainPropertyPtr, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);

			insertProperty(&headMainPropertyPtr, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE, VACATION_RENTERS, RENTER_SURVEY_CATEGORIES);

			puts("Continue adding properties?");
			userContinue = yesOrNo();
		} while (userContinue == 'y');

		do {

			bool rentalMode = true;
		} while (rentalMode == true);
	}
	else {
		puts("Login unsuccessful");
	}
	puts("Exiting Air UCCS...");
	return 0;
}

/*
Purpose: Allows owner to login to set up property information
Parameters: Correct ID string, correct passcode string, and max amount of attempts
Return: Returns true or false if user correctly enters id and passcode within max amount of attemtps
*/
bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts) {
	unsigned int attemptCount = 0;
	bool loginStatus = false;
	char userID[STRING_LENGTH];
	char userPasscode[STRING_LENGTH];

	// Keep prompting for login, until attempts reaches max amount of attempts
	// Or if user entered login correctly
	while (attemptCount < maxAttempts && loginStatus == false) {
		int correct = 0;

		// Prompt user for ID
		printf("%s", "Enter User ID: ");
		fgets(userID, STRING_LENGTH, stdin);
		removeNewLineChar(userID);

		// Prompt user for passcode
		printf("%s", "Enter User Passcode: ");
		fgets(userPasscode, STRING_LENGTH, stdin);
		removeNewLineChar(userPasscode);

		// Print new line
		puts("");

		// Compare id and passcode, return 0 if true
		int compareId = strcmp(correctID, userID);
		int comparePasscode = strcmp(correctPasscode, userPasscode);

		// If both are true, return login staus as true
		if ((compareId == correct) && (comparePasscode == correct)) {
			loginStatus = true;
			puts("Login Successful");
		}
		// Else, iterate through loop
		else {
			puts("Wrong ID or Passcode.");
			attemptCount++;
		}
	}
	return loginStatus;
}

void printProperties(Property* headPtr, int minNights, int maxNights) {
	// Print pets if there are any properties in list
	if (headPtr != NULL) {
		puts("Properties: ");

		Property* currentPtr = headPtr;
		while (currentPtr != NULL) {
			displayPropertyInfo(currentPtr, minNights, maxNights);
			currentPtr = currentPtr->nextPropertyPtr;
			puts("");
		}
	}
	// If not, then print message
	else {
		puts("No properties");
		puts("");
	}
}

/*
Purpose: Print information of data members formatted
Parameters: address of property, min nights, and max nights
Return: Does not return a value, but prints several pieces of data
*/
void displayPropertyInfo(Property* propertyPtr, int minNights, int maxNights) {
	printf("Property name: %s\n", (propertyPtr->propertyName));
	printf("Property location: %s\n", (propertyPtr->propertyLocation));
	printf("Property can be rented for %d to %d nights\n", minNights, maxNights);
	printf("The price for the first %d nights is $%d.00\n", (propertyPtr->interval1), (propertyPtr->rentalRate));
	printf("Discount rate of $%d.00 for nights %d to %d\n", (propertyPtr->discount), (propertyPtr->interval1), (propertyPtr->interval2));
	printf("Discount rate of $%d.00 for nights over %d\n", (propertyPtr->discount) * DISCOUNT_MULTIPLIER, (propertyPtr->interval2));

}

/*
Purpose: Removes new line characters at the end of strings entered by user
Parameters: User input string
Return: Does not return a value, but modifies string to remove new line character
*/
void removeNewLineChar(char* string) {
	// If the end of string is a new line char, replace with null char
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

void lowerString(char string[]) {
	for (size_t stringChar = 0; stringChar < strlen(string); stringChar++) {
		string[stringChar] = tolower(string[stringChar]);
	}
}

/*
Purpose: Prints mins and maxes that user can enter for setting up property values
Parameters: minimum interval, maximum interval, minimum rental rate and maximum rental rate
Return: Does not return value, but prints values
*/
void maxOwnerSetUp(const int minInterval, const int maxInterval, const double minRate, const double maxRate) {
	printf("The minimum interval is %d, the maximum interval is %d\n", minInterval, maxInterval);
	printf("The minimum rental rate is $%.2lf and the maximum rental rate is $%.2lf\n", minRate, maxRate);
}

/*
Purpose: to allow owner to enter information for a property
Parameters: address of property, min rental nights, max rental nights,
min rental rate, max rental rate, number of categories, and number of max users
Return: Does not return value but instead modifies several data members in the property structure
*/
void setupProperty(Property* propertyPtr, const int minNights, const int maxNights, const int minRate, const int maxRate, const int maxRenters, const int maxCategories) {
	// Initialize property data members to zero
	propertyPtr->totalCharge = 0;
	propertyPtr->totalNights = 0;
	propertyPtr->totalRenters = 0;
	propertyPtr->currentUser = 0;

	// Set survey to zero
	for (int i = 0; i < maxRenters; i++) {
		for (int j = 0; j < maxCategories; j++) {
			propertyPtr->survey[i][j] = 0;
		}

	}

	// Set averages to zero
	for (int i = 0; i < maxCategories; i++) {
		propertyPtr->averages[i] = 0;
	}

	// Ask for property name
	printf("%s", "Enter name of property: ");
	fgets(propertyPtr->propertyName, STRING_LENGTH, stdin);
	removeNewLineChar(propertyPtr->propertyName);

	// Ask for location of property
	printf("%s", "Enter location of property: ");
	fgets(propertyPtr->propertyLocation, STRING_LENGTH, stdin);
	removeNewLineChar(propertyPtr->propertyLocation);

	// Ask for first interval
	printf("Enter first interval between %d and %d: ", minNights, maxNights);
	propertyPtr->interval1 = getValidInt(minNights, maxNights);

	// Ask for second interval
	printf("Enter second interval between %d and %d: ", (propertyPtr->interval1), maxNights);
	propertyPtr->interval2 = getValidInt((propertyPtr->interval1), maxNights);

	//Ask for rental rate
	printf("Enter rental rate between %d and %d: ", minRate, maxRate);
	propertyPtr->rentalRate = getValidInt(minRate, maxRate);

	// Ask for discount
	printf("Enter a discount between %d and %d: ", minRate, (propertyPtr->rentalRate));
	propertyPtr->discount = getValidInt(minRate, (propertyPtr->rentalRate));
}

/*
Purpose: To get user input with between range
Parameters: min and max
Return: a valid integer within range of min and max and not above or below long int
*/
int getValidInt(int min, int max) {
	// Intialize test values for user input and validation
	bool isValid = false;
	char inputStr[STRING_LENGTH];
	int result = 0;

	while (isValid == false) {

		// Get user input
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLineChar(inputStr);

		// Set error value to zero
		errno = 0;

		// Scan user input
		scanInt(inputStr, &result);

		// Check if greater than long value, if so print error message
		if ((result == LONG_MIN || result == LONG_MAX) && ERANGE == errno) {
			printf("Out of range of type long, please enter a number between or equal to %d and %d: ", min, max);
		}
		// If it is within range, it is valid
		else if ((result <= max) && (result >= min)) {
			isValid = true;
		}
		// If not in range, print error
		else {
			printf("Invalid input, please enter a number between or equal to %d and %d: ", min, max);
		}
	}
	return result;
}

/*
Purpose: to scan user input from either getValid or getValidSentinel
Parameters: user string input and the address of string converted
Return: does not return value, but modifies value of address of user input
converted to integer
*/
void scanInt(char* input, int* result) {
	// Check for user input
	char* endPtr;
	long intCheck = strtol(input, &endPtr, 10);
	unsigned int fail = 0;

	// If characters at the end are not integers, set it to fail value
	if ('\0' != *endPtr) {
		intCheck = fail;
	}

	*result = (int)intCheck;
}


void insertProperty(Property** headPtr, int minNights, int maxNights, int minRate, int maxRate, int maxRenters, int maxCategories) {
	Property* newPropertyPtr = malloc(sizeof(Property));

	char lowerCurrentName[STRING_LENGTH];
	char lowerInputName[STRING_LENGTH];

	setupProperty(newPropertyPtr, minNights, maxNights, minRate, maxRate, maxRenters, maxCategories);

	if (newPropertyPtr != NULL) {
		Property* previousPtr = NULL;
		Property* currentPtr = *headPtr;

		if (currentPtr != NULL) {
			strcpy(lowerCurrentName, currentPtr->propertyName);
			lowerString(lowerCurrentName);
		}

		strcpy(lowerInputName, newPropertyPtr->propertyName);
		lowerString(lowerInputName);

		int comparison = strcmp(lowerCurrentName, lowerInputName);

		while (currentPtr != NULL && comparison <= 0) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPropertyPtr;

			if (currentPtr != NULL) {
				strcpy(lowerCurrentName, currentPtr->propertyName);
				lowerString(lowerCurrentName);
			}
			comparison = strcmp(lowerCurrentName, lowerInputName);
		}
		if (previousPtr == NULL) {
			*headPtr = newPropertyPtr;
		}
		else {
			previousPtr->nextPropertyPtr = newPropertyPtr;
		}
		newPropertyPtr->nextPropertyPtr = currentPtr;
		
	}
	else {
		puts("No memory to place more properties!");
	}

}

char yesOrNo() {
	char validResponse = '\0';

	// Prompt user until y or n is entered
	while (validResponse != 'y' && validResponse != 'n') {
		puts("Enter (y)es or (n)o:");
		validResponse = getchar();
		while (getchar() != '\n');
		validResponse = tolower(validResponse);
	}

	// Return character to main
	return validResponse;
}

Property* selectProperty(Property** headPtr, char selectName[]) {
	//Property* previousPtr = NULL;
	Property* currentPtr = *headPtr;

	char currentName[STRING_LENGTH];
	char compareSelectName[STRING_LENGTH];

	if (currentPtr != NULL) {
		strcpy(currentName, currentPtr->propertyName);
		lowerString(currentName);
	}

	strcpy(compareSelectName, selectName);
	lowerString(compareSelectName);

	int comparison = strcmp(currentName, compareSelectName);

	if (currentPtr != NULL) {

		while (currentPtr != NULL && comparison !=0 ) {
			//previousPtr = currentPtr;
			currentPtr = currentPtr->nextPropertyPtr;

			strcpy(currentName, currentPtr->propertyName);
			lowerString(currentName);
		}
		if (currentPtr != NULL) {
			return currentPtr;
		}
		else {
			printf("%s is not in the list of properties!", selectName);
		}
	}
}

/*
Purpose: Allows vacationer to enter number of nights
Parameters: address of property, min rental nights, max rental nights, sentinel value, max renters,
max categories,correct id, correct passcode, and max attempts
Return: Does not return a value, but handles the renter's user story of entering nights and ratings
*/
/*
bool rentalMode(Property* propertyPtr, int minNights, int maxNights, int sentinel,
	int maxRenters, int maxCategories, int minRating, int maxRating,
	const char* correctID, const char* correctPasscode, int unsigned maxAttempts) {
	bool validSentinel = false;
	bool surveyExsits = false;
	int userNights = 0;
	double currentCharge = 0;
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities", "cat4" };

	// Allow vacationers to enter number of nights and ratings until sentinel value is entered
	// or number of vacationers exceed max amount of users 
	do {
		puts("");
		displayPropertyInfo(propertyPtr, minNights, maxNights);
		bool validNight = false;

		// Display survey if previously existing data exists
		if (surveyExsits == true) {
			printCategories(surveyCategories, maxCategories);
			printSurveyResults((propertyPtr->survey), (propertyPtr->currentUser), maxCategories);
		}

		// Prompt vacationer for number of nights
		if ((propertyPtr->currentUser) < maxRenters) {
			printf("%s", "Enter number of nights: ");
			userNights = getValidSentinel(minNights, maxNights, sentinel);

			// Prompt User for login if sentinel value is entered
			if (userNights == sentinel) {
				validSentinel = login(correctID, correctPasscode, maxAttempts);
			}
			// Set normal validNight to true if other valid inputs were entered
			else {
				validNight = true;
			}
		}

		// If sentinel value is entered, complete all of these tasks
		if (validSentinel == true) {

			// Print total number of renters, nights booked, and total charge
			printf("Number of renters: %d\n", propertyPtr->currentUser);
			puts("Number of total nights and total charge: ");
			printNightsCharges(propertyPtr->totalNights, propertyPtr->totalCharge);

			// Calculate and print category averages
			calculateCategoryAverages(propertyPtr->averages, propertyPtr->survey, propertyPtr->currentUser, maxCategories);
			printCategories(surveyCategories, maxCategories);
			printCategoryData(propertyPtr->averages, propertyPtr->currentUser, maxCategories);
			puts("");
		}
		// If number of nights entered, caculate charge and get rating
		else if (validNight == true) {

			// Add to total amount of nights booked of property
			propertyPtr->totalNights += userNights;

			// Calculate and add to total charge of property
			currentCharge = calculateCharges(userNights, (propertyPtr->interval1), (propertyPtr->interval2), (propertyPtr->rentalRate), (propertyPtr->discount));
			propertyPtr->totalCharge += currentCharge;

			// Print the vacationer's number of nights and charge
			printNightsCharges(userNights, currentCharge);

			// Prompt user to enter rating for three categories
			printSurveyInformation(minRating, maxRating, surveyCategories, maxCategories);
			getRatings(minRating, maxRating, (propertyPtr->survey), surveyCategories, (propertyPtr->currentUser), maxCategories);
			surveyExsits = true;

			// Iterate current user to keep track of total users who entered nights and ratings
			propertyPtr->currentUser++;
		}
	} while ((validSentinel == false) && ((propertyPtr->currentUser) < maxRenters));
}
*/