/*
Name: James Hayes
Class: CSC 2060
Project Name: UCCS Air
OS: Windows 10 and Windows 11
Description: 
Rental Owner Login: This program first prompts the owner to login, if the owner 
successfully logs in within the number of attempts, they are allowed to enter. 
If not, then the program ends.

Rental Property Owner Set Up: After logging in, the owner is prompted to enter the name, location,
interval 1 and 2, rental rate, and discount for their property. It will keep prompting until the 
data is valid. These values are then stored to be used to prompt vacationers 
for number of nights and rating.

Vacationer Rental Mode: Once the owner sets upt property information, the program asks the vacationer
to enter the number of nights. The program will keep prompting until valid data is entered. It will
then ask the vacationer to enter a rating for three categories. The program will also keep prompting
until it is a valid rating. This mode ends when either the sentinel value is entered 
when prompted number of nights or the max number of users has been exceeded.

Rental Owner Property Report Mode: Once the sentinel value is entered or the max number of users 
was exceeded, the program will then prompt for a login. If the login fails, it will return to rental 
mode or end the program if the number of users was exceeded. If the login is successful, 
the program will display the total number of nights and charges and the averages of 
every category entered by the vacationer. The program will then end.
*/

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
#define RENTER_SURVEY_CATEGORIES 4

// Rental property login and sentinal values
#define CORRECT_ID "id"
#define CORRECT_PASSCODE "ab"
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
typedef struct {
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
} Property;

// Functions
// Prompt user login
bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);

// Print min and maxes of owner set up
void maxOwnerSetUpt(const int minInterval, const int maxInterval, const double minRate, const double maxRate);

// Remove new line character in user input
void removeNewLineChar(char* string);

// Prompt set up property
void setupProperty(Property* propertyPtr, const int minNights, const int maxNights, const int minRate, const int maxRate, const int maxRenters, const int maxCategories);

// Get valid integer, within min and max
int getValidInt(const int min, const int max);

// Scan user input and put into result
void scanInt(char* input, int* result);

// Prompt vacationer for number of nights and rating
void rentalMode(Property* propertyPtr, const int minNights, const int maxNights, const int sentinel,
	const int maxRenters, const int maxCategories, const int minRating, const int maxRating,
	const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);

// Display property information for vacationer
void displayPropertyInfo(Property* propertyPtr, const int minNights, const int maxNights);

// Get valid integer, within min and max and accept sentinel value
int getValidSentinel(const int min, const int max, const int sentinel);

// Calcualte the charges for number of nights
double calculateCharges(unsigned int nights, unsigned int interval1, unsigned int interval2, double rate, double discount);

// Print the number of nights and charges
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
void calculateCategoryAverages(double averages[], const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Print the averages for each category
void printCategoryData(const double averages[], size_t totalUsers, size_t totalCategories);

int main(void) {
	// Property Defined
	Property property1;
	// Prompt owner login
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	
	// If owner login was successful, prompt for set up property and start rental mode
	if (ownerLogin == true) {
		maxOwnerSetUpt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE);
		setupProperty(&property1, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE, VACATION_RENTERS, RENTER_SURVEY_CATEGORIES);
		rentalMode(&property1, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1, VACATION_RENTERS, RENTER_SURVEY_CATEGORIES, MIN_RATING, MAX_RATING, CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	}
	// Else, print error message
	else {
		puts("Login unsuccessful");
	}
	// Print exit message and end program 
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
		fgets(userID,STRING_LENGTH,stdin);
		removeNewLineChar(userID);

		// Prompt user for passcode
		printf("%s", "Enter User Passcode: ");
		fgets(userPasscode,STRING_LENGTH,stdin);
		removeNewLineChar(userPasscode);

		// Print new line
		puts("");

		// Compare id and passcode, return 0 if true
		int compareId = strcmp(correctID, userID);
		int comparePasscode = strcmp(correctPasscode, userPasscode);

		// If both are true, return login staus as true
		if ((compareId == correct) && ( comparePasscode == correct)) {
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

/*
Purpose: Prints mins and maxes that user can enter for setting up property values
Parameters: minimum interval, maximum interval, minimum rental rate and maximum rental rate
Return: Does not return value, but prints values
*/
void maxOwnerSetUpt(const int minInterval, const int maxInterval, const double minRate, const double maxRate) {
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

/*
Purpose: Allows vacationer to enter number of nights
Parameters: address of property, min rental nights, max rental nights, sentinel value, max renters, 
max categories,correct id, correct passcode, and max attempts
Return: Does not return a value, but handles the renter's user story of entering nights and ratings
*/
void rentalMode(Property* propertyPtr, int minNights, int maxNights, int sentinel,
	int maxRenters, int maxCategories, int minRating, int maxRating,
	const char* correctID, const char* correctPasscode, int unsigned maxAttempts) {
	bool validSentinel = false;
	bool surveyExsits = false;
	int userNights = 0;
	double currentCharge = 0;
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities", "cat4"};
	
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
Purpose: Allows user to enter a valid integer within range and a sentinel to end program
Parameters: min, max, and sentinel
Return: Returns a valid integer that is within range or is the sentinel value
*/
int getValidSentinel(int min, int max, int sentinel) {
	// Initialize values for user input and validation
	bool isValid = false;
	char inputStr[STRING_LENGTH]; 
	int result = 0;

	// Prompt the user for input until it is true
	while (isValid == false) {
		// Get user input
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLineChar(inputStr);

		errno = 0;

		// Scan user input
		scanInt(inputStr, &result);

		// Check if long integer, if so print error message
		if ((result == LONG_MIN || result == LONG_MAX) && ERANGE == errno) {
			printf("Out of range of type long, please enter a number between or equal to %d and %d: ", min, max);
		}
		// Check if within range, if so it is valid
		else if ((result <= max) && (result >= min)) {
			isValid = true;
		}
		// If it is the sentinel value, it is valid
		else if (result == sentinel) {
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
Purpose: Calculates charges vacationer has based on number of nights entered
Parameters: number of nights, 1st interval, 2nd interval, rental rate, and discount
Return: Returns a double value in dollars based on number of nights and intervals
*/
double calculateCharges(unsigned int nights, unsigned int interval1, unsigned int interval2, double rate, double discount) {
	// Intialize count
	unsigned int count = 1;

	// Intialize charges
	double charges = 0;

	// Loop until count is greater than number of nights
	while (!(count > nights)) {

		// Add charge each time
		charges += rate;

		// If count is greater than 1st interval apply discount
		if (count > interval1) {
			charges -= discount;

			// If count is greater than 2nd interval apply discount
			if (count > interval2) {
				charges -= discount;
			}
		}

		// Iterate count
		count++;
	}
	return charges;
}

/*
Purpose: Print the categories the user will be rating on
Parameters: array with categories and the number of categories
Return: Does not return anything, but prints out the categories horizontally
*/
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

/*
Purpose: Print the survey information to the vacationer
Parameters: min rating, max rating, category array, total amount of categories
Return: Does not return anything, but prints instructions for user
*/
void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories) {
	printf("We want your feed back, please enter your rating from %d to %d for each category.\n", minRating, maxRating);
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

/*
Purpose: Allows user to enter a rating for stay at property
Parameters: Min rating, max rating, array of surveys, number of users, and number of categories
Return: Does not return a value, but prompts user to enter a rating for a category then
stores rating in an array of surveys
*/
void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], const char* categories[], size_t currentUser, size_t totalCategories) {
		// Print current survey
		printf("Survey %zu\n", currentUser + 1);

		// Iterate through column (categories)
		for (size_t category = 0; category < totalCategories; ++category) {

			// Print which category will be rated
			printf("Enter your rating for %s: ", categories[category]);
			
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
	for (size_t user = 0; user < totalUsers; ++user) {
		// Print which survey
		printf("Survey %zu:", user + 1);

		// Iterate through columns (categories)
		for (size_t category = 0; category < totalCategories; ++category) {
			// Print the rating for the category formatted
			printf("%30u", survey[user][category]);
		}
		// Start a new line for next user
		puts("");
	}
}

/*
Purpose: Calculate the averages for each category and store in array
Parameters: array with averages, array with survey results, number of users and number of categories
Return: Does not return anything, but modifies initialized array with averages
*/
void calculateCategoryAverages(double averages[], const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	// Iterate through rows (users)
	for (size_t user = 0; user < totalUsers; ++user) {

		// Iterate through columns (categories)
		for (size_t category = 0; category < totalCategories; ++category) {
			// Calculate the average for each category and store in array
			averages[category] += ((double)(survey[user][category]) / totalUsers);
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
	printf("%s", "Rating Averages:");

	// Iterate through average category data
	for (size_t category = 0; category < totalCategories; ++category) {
		// Print the average for the category
		printf("%27.1f", averages[category]);
	}
}