/*
Name: James Hayes
Class: CSC 2060
Project Name: UCCS Air
OS: Windows 10 and Windows 11
Description: 
Rental Owner Login: The program first prompts the owner to login, if the owner logs in successfully 
within the max number of attemtps, the program can start. If not, the program ends.

Rental Property Owner Set up: After logging in, the owner is prompted to enter the name, location, intervals
1 and 2, rental rate, and discount for a property. The owner can input more than one at a time. The set up ends
only when the owner puts yes or no to continue the set up for another property. The properties are stored
in a linked list alphabetically from a to z.

Vacationer Rental Mode: Once the properties are entered, the vacationer will then be prompt with a selection
from all of the properties entered to enter the name of the property to rent (not case-sensitive). 
Once selected, the program will then prompt for the number of nights and then the ratings. It will keep prompting
until a valid integer is selected for both. If the sentinel value is entered, it will then prompt for a login.
If the login fails, it will take them back to prompt for the name of the property. The user also cannot
enter more than the max number of renters, but can use the sentinel value to exit rental mode with a login.

Rental Owner Property Report Mode: Once the sentinel value was entered and the login was successful, 
the program then prints the final information for the selected property. It will also print to a .txt file 
with the name of the property selected in folder called fundraiser. The program will then end. 
*/

// Header files
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
#define RENTER_SURVEY_CATEGORIES 3

// Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "abcd"
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

// Folder and file path
#define FOLDER_FILE_PATH "C:\\fundraiser\\"

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

// Functions
// Prompt user login
bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);

// Display Property information for vacationer
void displayPropertyInfo(Property* propertyPtr, int minNights, int maxNights, const char* categories[], int maxCategories);

// Print Properties
void printProperties(Property* headPtr, int minNights, int maxNights, const char* categories[], int maxCategories);

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
bool rentalMode(Property* propertyPtr, int minNights, int maxNights, int sentinel,
	int maxRenters, int maxCategories, int minRating, int maxRating, const char* categories[],
	const char* correctID, const char* correctPasscode, int unsigned maxAttempts);

// Prompt user which property to rent
Property* selectProperty(Property** headPtr, char selectName[]);

// Display property information for vacationer
void displayPropertyInfo(Property* propertyPtr, int minNights, int maxNights, const char* categories[], int maxCategories);

// Get valid integer, within min and max and accept sentinel value
int getValidSentinel(int min, int max, int sentinel);

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

// Create file name
void createFileName(char fileName[]);

// Print property information to a file
void printPropertyToFile(Property* propertyPtr, char path[], const char* categories[], size_t maxCategories);

// Free memory in list of properties
void freeRemainingProperties(Property** headPtr);

int main (void) {
	Property* headMainPropertyPtr = NULL;

	// Prompt for user login
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);

	char userContinue = ' ';
	bool rentalContinue = true;
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };
	Property* selectedProperty = NULL;
	char filePath[STRING_LENGTH];
	char fullPath[STRING_LENGTH];
	strcpy(fullPath, FOLDER_FILE_PATH);

	// If owner login was successful, allow for program to continue
	if (ownerLogin == true) {
		// Keep adding properties until user stops
		do {
			// Insert and set up properties in linked list
			insertProperty(&headMainPropertyPtr, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE, VACATION_RENTERS, RENTER_SURVEY_CATEGORIES);

			// Prompt user to continue 
			puts("Continue adding properties?");
			userContinue = yesOrNo();
		} while (userContinue == 'y');

		// Keep prompting user for names of properties until sentinel value is entered
		do {
			char selectedPropertyName[STRING_LENGTH];

			// Print all of the properties and their rental information
			printProperties(headMainPropertyPtr, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, surveyCategories, RENTER_SURVEY_CATEGORIES);

			// Prompt for property name (not case-sensitive)
			puts("Select a property:");
			fgets(selectedPropertyName, STRING_LENGTH, stdin);
			removeNewLineChar(selectedPropertyName);

			// Return the address of property vacationer wants to stay at
			selectedProperty = selectProperty(&headMainPropertyPtr, selectedPropertyName);

			// If the property does exist, enter rental mode
			if (selectedProperty != NULL) {
				rentalContinue = rentalMode(selectedProperty, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1, VACATION_RENTERS, RENTER_SURVEY_CATEGORIES, MIN_RATING, MAX_RATING, surveyCategories, CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
			}
			
		} while (rentalContinue == true);

		// Print to file if rental mode is done and sentinel value is entered
		if (rentalContinue != true) {
			// Create name of .txt file
			strcpy(filePath, selectedProperty->propertyName);
			createFileName(filePath);

			// Create full path of where .txt should be located
			strcat(fullPath, filePath);

			// Print final property info to file
			puts("Printing to file");
			printPropertyToFile(selectedProperty, fullPath, surveyCategories, RENTER_SURVEY_CATEGORIES);
		}
	}
	// Print error message if login was incorrect
	else {
		puts("Login unsuccessful");
	}

	// Deallocate memory from linked list and end program
	freeRemainingProperties(&headMainPropertyPtr);
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

/*
Purpose: Print every property in the linked list
Parameters: head pointer, minNights, maxNights, categories string, and max categories
Return: Does not return a value, but prints every property in list with information
*/
void printProperties(Property* headPtr, int minNights, int maxNights, const char* categories[], int maxCategories) {
	// Print pets if there are any properties in list
	if (headPtr != NULL) {
		puts("");
		puts("Properties: ");

		Property* currentPtr = headPtr;
		while (currentPtr != NULL) {
			displayPropertyInfo(currentPtr, minNights, maxNights, categories, maxCategories);
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
Parameters: address of property, min nights, max nights, category array and number of categories
Return: Does not return a value, but prints several pieces of data and prints ratings if any were entered
*/
void displayPropertyInfo(Property* propertyPtr, int minNights, int maxNights, const char* categories[], int maxCategories) {
	printf("Property name: %s\n", (propertyPtr->propertyName));
	printf("Property location: %s\n", (propertyPtr->propertyLocation));
	printf("Property can be rented for %d to %d nights\n", minNights, maxNights);
	printf("The price for the first %d nights is $%d.00\n", (propertyPtr->interval1), (propertyPtr->rentalRate));
	printf("Discount rate of $%d.00 for nights %d to %d\n", (propertyPtr->discount), (propertyPtr->interval1 + 1), (propertyPtr->interval2));
	printf("Discount rate of $%d.00 for nights over %d\n", (propertyPtr->discount) * DISCOUNT_MULTIPLIER, (propertyPtr->interval2));

	// Print ratings if any were entered
	if (propertyPtr->survey[0][0] != 0) {
		printCategories(categories, maxCategories);
		printSurveyResults(propertyPtr->survey, propertyPtr->currentUser, RENTER_SURVEY_CATEGORIES);
	}
	else {
		puts("No Ratings Currently");
	}
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
Purpose: Turn chars in string lowercase, used for non-case sensitive comparisons
Parameters: array of characters
Return: Does not return value, but modifies a string to be all lowercase
*/
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
	printf("Enter second interval between %d and %d: ", (propertyPtr->interval1 + 1), maxNights);
	propertyPtr->interval2 = getValidInt((propertyPtr->interval1 + 1), maxNights);

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
Purpose: To dynamically store property structures alphabetically in a linked list while setting up properties
Parameters: head pointer, minNights, maxNights, minRate, maxRate, max number of vacationers, 
and number of categories
Return: Does not return a value, but stores all structures set up by owner in a linked list alphabetically
*/
void insertProperty(Property** headPtr, int minNights, int maxNights, int minRate, int maxRate, int maxRenters, int maxCategories) {
	Property* newPropertyPtr = malloc(sizeof(Property));

	char lowerCurrentName[STRING_LENGTH];
	char lowerInputName[STRING_LENGTH];

	// Start set up process for property owner
	setupProperty(newPropertyPtr, minNights, maxNights, minRate, maxRate, maxRenters, maxCategories);

	// Start inserting properties if memory exists
	if (newPropertyPtr != NULL) {
		Property* previousPtr = NULL;
		Property* currentPtr = *headPtr;

		// Copy and make name of current property lowercase
		if (currentPtr != NULL) {
			strcpy(lowerCurrentName, currentPtr->propertyName);
			lowerString(lowerCurrentName);
		}

		// Copy and make name lowercase of owner's input
		strcpy(lowerInputName, newPropertyPtr->propertyName);
		lowerString(lowerInputName);

		// Compare the two names
		int comparison = strcmp(lowerCurrentName, lowerInputName);

		// Insert properties alphabetically while the name is earlier in alphabet
		while (currentPtr != NULL && comparison <= 0) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPropertyPtr;

			// Make new current property name lowercase
			if (currentPtr != NULL) {
				strcpy(lowerCurrentName, currentPtr->propertyName);
				lowerString(lowerCurrentName);
			}
			// Compare again
			comparison = strcmp(lowerCurrentName, lowerInputName);
		}
		// If name apears earlier in alphabet than other names, make it the first property
		if (previousPtr == NULL) {
			*headPtr = newPropertyPtr;
		}
		// If not, connect the previous property to the new one
		else {
			previousPtr->nextPropertyPtr = newPropertyPtr;
		}
		// Connect new property to the next one in list
		newPropertyPtr->nextPropertyPtr = currentPtr;
		
	}
	// Print error message if there is no address to allocate for
	else {
		puts("No memory to place more properties!");
	}

}

/*
Purpose: To prompt owner for y or n to continue adding properties
Parameters: None
Return: returns a char indicating whether or not to continue
*/
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

/*
Purpose: to prompt vacationer to select a property to rent
Parameters: head pointer and name of selected property
Return: The address of the property the vacationer selected
*/
Property* selectProperty(Property** headPtr, char selectName[]) {
	Property* currentPtr = *headPtr;
	Property* selectedProperty = NULL;

	char currentName[STRING_LENGTH];
	char compareSelectName[STRING_LENGTH];

	// If current pointer exsits, make a copy of name and make it lowercase
	if (currentPtr != NULL) {
		strcpy(currentName, currentPtr->propertyName);
		lowerString(currentName);
	}

	// Make copy of name and make it lowercase
	strcpy(compareSelectName, selectName);
	lowerString(compareSelectName);

	// Compare the two
	int comparison = strcmp(currentName, compareSelectName);

	// Start searching if the list exists
	if (currentPtr != NULL) {

		// Search through linked list while names are not the same
		while (currentPtr != NULL && comparison !=0 ) {
			currentPtr = currentPtr->nextPropertyPtr;

			// Make a copy of the current property and make it lowercase and compare again
			if (currentPtr != NULL) {
				strcpy(currentName, currentPtr->propertyName);
				lowerString(currentName);
				comparison = strcmp(currentName, compareSelectName);
			}
		}
		// If the property was found, make the selected property the address of the seleted property
		if (currentPtr != NULL) {
			selectedProperty = currentPtr;
		}
		// If not, print error message
		else {
			printf("%s does not match any properties listed, please enter the name again.\n", selectName);
		}
	}
	// Return address of selected propertyz
	return selectedProperty;
}

/*
Purpose: Allows vacationer to enter number of nights
Parameters: address of property, min rental nights, max rental nights, sentinel value, max renters, 
array of categories, max categories,correct id, correct passcode, and max attempts
Return: Does not return a value, but handles the renter's user story of entering nights and ratings
*/
bool rentalMode(Property* propertyPtr, int minNights, int maxNights, int sentinel,
	int maxRenters, int maxCategories, int minRating, int maxRating, const char* categories[],
	const char* correctID, const char* correctPasscode, int unsigned maxAttempts) {
	bool validSentinel = false;
	bool validNight = false;
	bool rentalContinue = true;
	int userNights = 0;
	double currentCharge = 0;

	// Display Information 
	puts("");
	displayPropertyInfo(propertyPtr, minNights, maxNights, categories, maxCategories);

	// Prompt vacationer for number of nights
	if ((propertyPtr->currentUser) <= maxRenters) {
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

		// Rental Mode ends
		rentalContinue = false;
		
		// Print total number of renters, nights booked, and total charge
		puts("");
		puts("Rental Property Report");
		puts("");
		printf("Property Name: %s\n", propertyPtr->propertyName);
		printf("Property Location: %s\n", propertyPtr->propertyLocation);
		puts("");
		printf("Total number of renters: %d\n", propertyPtr->currentUser);
		printf("Total number of nights: %d\n", propertyPtr->totalNights);
		printf("Total number of charges: $%.2f\n", propertyPtr->totalCharge);

		// Calculate and print category averages
		calculateCategoryAverages(propertyPtr->averages, propertyPtr->survey, propertyPtr->currentUser, maxCategories);
		printCategories(categories, maxCategories);
		printCategoryData(propertyPtr->averages, propertyPtr->currentUser, maxCategories);
		puts("");
	}
	// If valid night was entered and it the property has room, caculate charge and get rating
	else if (validNight == true && propertyPtr->currentUser < maxRenters) {

		// Add to total amount of nights booked of property
		propertyPtr->totalNights += userNights;

		// Calculate and add to total charge of property
		currentCharge = calculateCharges(userNights, (propertyPtr->interval1), (propertyPtr->interval2), (propertyPtr->rentalRate), (propertyPtr->discount));
		propertyPtr->totalCharge += currentCharge;

		// Print the vacationer's number of nights and charge
		printNightsCharges(userNights, currentCharge);

		// Prompt user to enter rating for three categories
		printSurveyInformation(minRating, maxRating, categories, maxCategories);
		getRatings(minRating, maxRating, (propertyPtr->survey), categories, (propertyPtr->currentUser), maxCategories);

		// Iterate current user to keep track of total users who entered nights and ratings
		propertyPtr->currentUser++;
		}
	// Print message stating it has the max number of renters
	else if(propertyPtr->currentUser == maxRenters) {
		printf("%s has max vacancy!\n", propertyPtr->propertyName);
	}
	// Return whether or not to continue rental mode
	return rentalContinue;
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
	// Initialize both count and charges
	unsigned int count = 1;
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
Parameters: Min rating, max rating, array of surveys, array of categories, 
current number of users, and number of categories
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

/*
Purpose: To create the name of file to print to and fill in whitespace with _
Parameters: name of file
Return: Does not return a value, but creates the name of file with property name
*/
void createFileName(char fileName[]) {
	// Fill in whitespace with _
	for (size_t nameChar = 0; nameChar < strlen(fileName); nameChar++ ) {
		if (fileName[nameChar] == ' ') {
			fileName[nameChar] = '_';
		}
	}
	// Concatentate .txt to end of name
	strcat(fileName, ".txt");
}

/*
Purpose: To print the final property information to a file
Parameters: Property selected, path, the array of categories, and number of categories
Return: Does not return a value, but prints the final information of properties into a file
*/
void printPropertyToFile(Property* propertyPtr, char path[], const char* categories[], size_t maxCategories) {
	FILE* fPtr = NULL;
	
	// Print error message if file or folder could not be found
	if ((fPtr = fopen(path,"w")) == NULL) {
		puts("File or folder cannot be found");
	}
	// Print to file if both exist
	else{
		fputs("Rental Property Report\n", fPtr);
		fprintf(fPtr, "Name: %s\n", propertyPtr->propertyName);
		fprintf(fPtr, "Location: %s\n", propertyPtr->propertyLocation);

		fputs(" \n", fPtr);
		fputs("Rental Property Totals\n", fPtr);
		fprintf(fPtr, "Total Renters: %d\n", propertyPtr->currentUser);
		fprintf(fPtr, "Total Nights: %d\n", propertyPtr->totalNights);
		fprintf(fPtr, "Total Charge: $%.2f\n", propertyPtr->totalCharge);

		fputs(" \n", fPtr);
		fputs("Category Rating Averges\n", fPtr);
		for (size_t category = 0; category < maxCategories; category++) {
			fprintf(fPtr, "%s: %.1f\n", categories[category], propertyPtr->averages[category]);
		}
		// Close access to file
		fclose(fPtr);
	}
}

/*
Purpose: To deallocate memory from linked list once the program ends
Parameters: Address of the headPtr on main
Return: does not return value, but deallocates memory on linked list
*/
void freeRemainingProperties(Property** headPtr) {
	
	// Deallocate memoty from property pointer list if it exists
	if (*headPtr != NULL) {
		Property* currentPtr = *headPtr;
		Property* nextFreePtr = NULL;

		// While currentPtr is not null, deallocate every node in list
		while (currentPtr != NULL) {
			nextFreePtr = currentPtr->nextPropertyPtr;
			free(currentPtr);
			currentPtr = nextFreePtr;
		}
		*headPtr = NULL;
	}
	// If not, print error message
	else {
		puts("No properties to deallocate memory");
	}
}