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

// Survey Min and Max
#define MIN_RATING 1
#define MAX_RATING 5
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
	unsigned int currentUser;
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
void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], const char* categories[], size_t currentUser, size_t totalCategories);

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
	if (ownerLogin == true) {
		setupProperty(&property1, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE);
		rentalMode(&property1, SENTINEL_NEG1, CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	}
	puts("Exiting Air UCCS...");
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
	// Set Data members to zero
	propertyPtr->totalCharge = 0;
	propertyPtr->totalNights = 0;
	propertyPtr->totalRenters = 0;
	propertyPtr->currentUser = 0;
	
	// Set survey to zero
	for (int i = 0; i < VACATION_RENTERS; i++) {
		for (int j = 0; j < RENTER_SURVEY_CATEGORIES; j++) {
			propertyPtr->survey[i][j] = 0;
		}
		
	}

	// Set averages to zero
	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
		propertyPtr->averages[i] = 0;
	}

	// Ask for property name
	printf("%s", "Enter name of property: \n");
	fgets(propertyPtr->propertyName, STRING_LENGTH, stdin);

	// Ask for location of property
	printf("%s", "Enter location of property: \n");
	fgets(propertyPtr->propertyLocation, STRING_LENGTH, stdin);

	// Ask for first interval
	printf("Enter first interval between %d and %d: ", minNights, maxNights);
	propertyPtr->interval1 = getValidInt(minNights, maxNights);

	// Ask for second interval
	printf("Enter second interval between %d and %d: ", (propertyPtr->interval1), maxNights);
	propertyPtr->interval2 = getValidInt((propertyPtr->interval2), maxNights);

	//Ask for rental rate
	printf("Enter rental rate between %d and %d: ", minRate, maxRate);
	propertyPtr->rentalRate = getValidInt(minRate, maxRate);

	// Ask for discount
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
		// Check if greater than long value
		// It it is within range, it is valid
		if ((result <= max) && (result >= min)) {
			isValid = true;
		}
		// If not, print error
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
	bool surveyExsits = false;
	int userNights = 0;
	double currentCharge = 0;
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };

	do {
		displayPropertyInfo(propertyPtr);

		// Display survey if previously existing data exists
		if (surveyExsits == true) {
			printSurveyResults((propertyPtr->survey), (propertyPtr->currentUser), RENTER_SURVEY_CATEGORIES);
		}
		
		// Prompt vacationer for number of nights
		if ((propertyPtr->currentUser) < VACATION_RENTERS) {
			puts("Enter number of nights");
			userNights = getValidSentinel(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, sentinel);
		}
		
		// If sentinel value is entered, prompt for login
		if (userNights == sentinel || propertyPtr->currentUser == VACATION_RENTERS) {
			validSentinel = login(correctID, correctPasscode, maxAttempts);

			// Print Final information if login was valid 

		}
		else {
			propertyPtr->totalNights += userNights;
			currentCharge = calculateCharges(userNights, (propertyPtr->interval1), (propertyPtr->interval2), (propertyPtr->rentalRate), (propertyPtr->discount));
			propertyPtr->totalCharge += currentCharge;
			printNightsCharges(userNights, currentCharge);
			
			printSurveyInformation(MIN_RATING, MAX_RATING, surveyCategories, RENTER_SURVEY_CATEGORIES);
			getRatings(MIN_RATING, MAX_RATING, (propertyPtr->survey), surveyCategories, (propertyPtr->currentUser), RENTER_SURVEY_CATEGORIES);
			surveyExsits = true;
			propertyPtr->currentUser++;
		}
	} while ((validSentinel == false) && ((propertyPtr->currentUser) <= VACATION_RENTERS));
}

void displayPropertyInfo(Property* propertyPtr) {
	printf("The first interval is %d, the second is %d\n", (propertyPtr->interval1), (propertyPtr->interval2));
	printf("The rental rate is %d and the discount is %d\n", (propertyPtr->rentalRate), (propertyPtr->discount));
	printf("The name of the property is %s the location is %s\n", (propertyPtr->propertyName), (propertyPtr->propertyLocation));
}

int getValidSentinel(const int min, const int max, const int sentinel) {
	bool isValid = false;
	char inputStr[STRING_LENGTH];
	int result = 0;

	// Prompt the user for 
	while (isValid == false) {
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLineChar(inputStr);
		scanInt(inputStr, &result);
		// Check if long integer
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

void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories) {
	printf("We want your feed back, please enter your rating from %d to %d for each category.\n",
		minRating, maxRating);
	printCategories(categories, totalCategories);
}

/*
Purpose: Print the categories the user will be rating on
Parameters: array with categories and the number of categories
Return: Does not return anything, but prints out the categories horizontally
*/
void printCategories(const char* categories[], size_t totalCategories)
{
	// Loop to display each category horizontally
	printf("%s", "Rating Categories:\t");
	for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
	{
		printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
	}
	// Start new line of output
	puts("");
}

void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], const char* categories[], size_t currentUser, size_t totalCategories) {
		// Print current survey
		printf("Survey %zu\n", currentUser + 1);

		// Iterate through column (categories)
		for (size_t category = 0; category < totalCategories; ++category) {

			// Print which category will be rated
			printf("Enter your rating for %s\n", categories[category]);
			
			// Store user input into array
			survey[currentUser][category] = getValidInt(minRating, maxRating);
			
		}
}


/*
Purpose: Print the survey's results
Parameters: array with survey data, number of users, and number of categories
Return: Does not return anything but prints results of survey formatted
*/
void printSurveyResults(const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	// Iterate through rows (users)
	for (size_t i = 0; i < totalUsers; ++i) {
		// Print which survey
		printf("Survey %zu:", i + 1);

		// Iterate through columns (categories)
		for (size_t j = 0; j < totalCategories; ++j) {
			// Print the rating for the category formatted
			printf("%30u", survey[i][j]);
		}
		// Print new line
		printf("\n");
	}
}

/*
Purpose: Calculate the averages for each category and store in array
Parameters: array with averages, array with survey results, number of users and number of categories
Return: Does not return anything, but modifies initialized array with averages
*/
void calculateCategoryAverages(double averages[], int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	// Iterate through rows (users)
	for (size_t i = 0; i < totalUsers; ++i) {

		// Iterate through columns (categories)
		for (size_t j = 0; j < totalCategories; ++j) {
			// Calculate the average for each category and store in array
			averages[j] += ((double)(survey[i][j]) / totalUsers);
		}
	}
}

/*
Purpose: Print the averages of categories
Parameters: constant array with averages, number of users, and number of categories
Return: Does not return anything, but prints the averages for each category formatted
*/
void printCategoryData(const double averages[], size_t totalUsers, size_t totalCategories) {
	// Print the title
	printf("%s", "Rating Averages:\t");

	// Iterate through average category data
	for (size_t i = 0; i < totalCategories; ++i) {
		// Print the average for the category
		printf("%.1f\t", averages[i]);
	}
}