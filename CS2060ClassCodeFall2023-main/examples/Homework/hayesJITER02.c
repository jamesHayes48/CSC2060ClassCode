#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Maximum length of a string
#define  STRING_LENGTH 80

//Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3

//Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1

//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

bool login(const char* correctID, const char* correctPasscode, const int maxAttempts);

int main(void) {
	bool ownerLogin = login(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS);
	if (ownerLogin == true) {
		puts("Hello");
	}
	else {
		puts("Goodbye");
	}
}

bool login(const char* correctID, const char* correctPasscode, const int maxAttempts) {
	unsigned attemptCount = 0;
	bool loginStatus = false;
	char userID[STRING_LENGTH];
	char userPasscode[STRING_LENGTH];


	while (attemptCount < maxAttempts && loginStatus == false) {
		printf("%s", "Enter User ID: ");
		fgets(userID,STRING_LENGTH,stdin);

		puts("");

		printf("%s", "Enter User Passcode: ");
		fgets(userPasscode,STRING_LENGTH,stdin);
		if ((strcmp(correctID,userID) == 0) && (strcmp(correctPasscode,userPasscode))) {
			loginStatus = true;
		}
		else {
			attemptCount++;
		}
	}
	return loginStatus;
}

void removeNewLineChar(char* string) {
	if (string[strlen[] - 1] == '\n') {
		string[strlen[] - 1] == '\0';
	}
}