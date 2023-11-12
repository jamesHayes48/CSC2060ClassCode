#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STRING_LENGTH 80

typedef struct pet {
	char petName[STRING_LENGTH];
	int petAge;

	struct pet* nextPetPtr;
} Pet;

void removeNewLineChar(char string[]);
void insertPet(Pet** headPtr, char name[STRING_LENGTH], int age);
void lowerString(char string[]);
void printPet(Pet* headPtr);
char yesOrNo();
void deletePet(Pet** headPtr, char deleteName[STRING_LENGTH]);

int main(void) {
	Pet* headMainPetPtr = NULL;
	char name[STRING_LENGTH] = "";
	char deleteName[STRING_LENGTH] = "";
	int age = 0;
	char userContinue = ' ';

	do {
		printPet(headMainPetPtr);
		printf("%s", "Enter name: ");
		fgets(name, STRING_LENGTH, stdin);
		removeNewLineChar(name);

		printf("%s", "Enter age: ");
		scanf("%d", &age);

		while (getchar() != '\n');

		insertPet(&headMainPetPtr, name, age);

		puts("");

		printPet(headMainPetPtr);
		puts("Continue adding pets?");
		userContinue = yesOrNo();
		puts("");
	} while (userContinue == 'y');

	do {

		puts("Enter name of pet to delete: ");
		fgets(deleteName, STRING_LENGTH, stdin);

		removeNewLineChar(deleteName);

		deletePet(&headMainPetPtr, deleteName);

		printPet(headMainPetPtr);

		puts("Continue deleting pets?");
		userContinue = yesOrNo();
		puts("");
	} while (userContinue == 'y');

	puts("Outputting list to file pets.txt...");
}

void removeNewLineChar(char* string) {
	// If the end of string is a new line char, replace with null char
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

void insertPet(Pet** headPtr, char name[STRING_LENGTH], int age) {
	Pet* newPetPtr = malloc(sizeof(Pet));
	char lowerCurrentName[STRING_LENGTH] = "";
	char lowerInputName[STRING_LENGTH] = "";

	if (newPetPtr != NULL) {
		strncpy(newPetPtr->petName, name, STRING_LENGTH);
		newPetPtr->petAge = age;

		Pet* previousPtr = NULL;
		Pet* currentPtr = *headPtr;

		// If previous value was entered, make a lowercase copy
		if (currentPtr != NULL) {
			strncpy(lowerCurrentName, currentPtr->petName, STRING_LENGTH);
			lowerString(lowerCurrentName);
		}
		
		// Make lowercase copy of current name
		strncpy(lowerInputName, newPetPtr->petName, STRING_LENGTH);
		lowerString(lowerInputName);

		// Make the comparison between new and old pet name
		int comparison = strcmp(lowerCurrentName, lowerInputName);

		// Iterate through if current pointer exists and if the name is
		// still appears earlier in the alphabet
		while (currentPtr != NULL && comparison <= 0) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPetPtr;
			
			// Make a lowercase copy of current name
			if (currentPtr != NULL) {
				strncpy(lowerCurrentName, currentPtr->petName, STRING_LENGTH);
				lowerString(lowerCurrentName);
			}
			// Make comparison again
			comparison = strcmp(lowerCurrentName, lowerInputName);
		}
		// If the name is appears earlier alphabetically, make it first
		if (previousPtr == NULL) {
			*headPtr = newPetPtr;
		}
		// If not, then make previous pointer point to new name
		else {
			previousPtr->nextPetPtr = newPetPtr;
		}
		// Set new pointer to current pointer
		newPetPtr->nextPetPtr = currentPtr;
	}
	// If no memory, print error message
	else {
		printf("No memory to create a space for %s\n", name);
	}
}

void printPet(Pet* headPtr) {
	if (headPtr != NULL) {
		puts("Pets: ");

		Pet* currentPtr = headPtr;
		while (currentPtr != NULL) {
			printf("%s is %d years old\n", currentPtr->petName, currentPtr->petAge);
			currentPtr = currentPtr->nextPetPtr;
		}
	}
	else {
		puts("No pets");
	}
}

char yesOrNo() {
	char validResponse = '\0';

	while (validResponse != 'y' && validResponse != 'n') {
		puts("Enter (y)es or (n)o:");
		validResponse = getchar();
		while (getchar() != '\n');
		validResponse = tolower(validResponse);
	}

	return validResponse;
}

void deletePet(Pet** headPtr, char deleteName[STRING_LENGTH]) {
	Pet* previousPtr = NULL;
	Pet* currentPtr = *headPtr;

	if (*headPtr != NULL) {
		if (strcmp((*headPtr)->petName, deleteName) == 0) {
			*headPtr = (*headPtr)->nextPetPtr;
			free(currentPtr);
			currentPtr = NULL;
		}
		else {
			while (currentPtr != NULL && strcmp(currentPtr->petName, deleteName) != 0) {
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPetPtr;
			}
			if (currentPtr != NULL) {
				previousPtr->nextPetPtr = currentPtr->nextPetPtr;
				free(currentPtr);
				currentPtr = NULL;
			}
			else {
				printf("%s is not in this list!", deleteName);
			}
		}
	}
}

void lowerString(char string[]) {
	for (size_t stringChar = 0; stringChar < strlen(string); stringChar++) {
		string[stringChar] = tolower(string[stringChar]);
	}
}

void printPetToFile(Pet* headPtr) {
	FILE* pfPtr = NULL;
	if ((pfPtr = fopen("C:\\GithubRepos\\CSC2060ClassCode\\CS2060ClassCodeFall2023-main\\examples\\Homework\\pets.txt", "a")) == NULL) {
		puts("File could not be opened");
	}
	else {
		if (headPtr != NULL) {
			Pet* currentPtr = headPtr;

			while (currentPtr != NULL) {
				fprintf(pfPtr, "Name: %s\n", currentPtr->petName);
				fprintf(pfPtr, "Age: %d\n", currentPtr->petAge);
				fputs("",pfPtr);
				currentPtr = currentPtr->nextPetPtr;
			}
		}
		else {
			puts("No pets");
		}
	}
	fclose(pfPtr);
}