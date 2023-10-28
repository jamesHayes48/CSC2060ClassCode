#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maximum length of a string
#define  STRING_LENGTH 80

// Two dimensional array storage amounts for rows and columns of surve data
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

// Functions
bool login(const char* correctID, const char* correctPasscode, const int unsigned maxAttempts);
void removeNewLineChar(char* string);
void setupPropertyInfo();

int main(void) {
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	if (ownerLogin == true) {
		puts("Hello");
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