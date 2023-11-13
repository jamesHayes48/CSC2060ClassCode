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
void printPetToFile(Pet* headPtr);
void freeRemainingPets(Pet** headPtr);

int main(void) {
	// Intialize all variables
	Pet* headMainPetPtr = NULL;
	char name[STRING_LENGTH] = "";
	char deleteName[STRING_LENGTH] = "";
	int age = 0;
	char userContinue = ' ';

	// Prompt user for name and age of pet and store on
	// linked list as long as user wants to
	do {
		// Ask for name
		printPet(headMainPetPtr);
		printf("%s", "Enter name: ");
		fgets(name, STRING_LENGTH, stdin);
		removeNewLineChar(name);

		// Ask for age
		printf("%s", "Enter age: ");
		scanf("%d", &age);

		while (getchar() != '\n');

		// Insert into list
		insertPet(&headMainPetPtr, name, age);

		puts("");

		printPet(headMainPetPtr);

		// Ask to continue
		puts("Continue adding pets?");
		userContinue = yesOrNo();
		puts("");
	} while (userContinue == 'y');

	// Ask user which pet should be deleted as long as
	// user wants to
	do {
		// Ask for name of pet to delete
		puts("Enter name of pet to delete: ");
		fgets(deleteName, STRING_LENGTH, stdin);
		removeNewLineChar(deleteName);

		deletePet(&headMainPetPtr, deleteName);

		printPet(headMainPetPtr);
		
		// Prompt to continue deletion
		puts("Continue deleting pets?");
		userContinue = yesOrNo();
		puts("");
	} while (userContinue == 'y');

	// Print pets to file
	puts("Outputting list to file pets.txt...");
	printPet(headMainPetPtr);
	printPetToFile(headMainPetPtr);

	// Deallocate remaining pets and end program
	freeRemainingPets(&headMainPetPtr);
	return 0;
}

void removeNewLineChar(char* string) {
	// If the end of string is a new line char, replace with null char
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

void insertPet(Pet** headPtr, char name[STRING_LENGTH], int age) {

	// Place linked list onto heap
	Pet* newPetPtr = malloc(sizeof(Pet));

	// Initalize strings for comparison
	char lowerCurrentName[STRING_LENGTH] = "";
	char lowerInputName[STRING_LENGTH] = "";

	// Make comparison and insert into list if newPetPtr
	// exists
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
		// If the name is appears earlier alphabetically than other names, 
		// make it first
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
	// Print pets if there are any pets in list
	if (headPtr != NULL) {
		puts("Pets: ");

		Pet* currentPtr = headPtr;
		while (currentPtr != NULL) {
			printf("%s is %d years old\n", currentPtr->petName, currentPtr->petAge);
			currentPtr = currentPtr->nextPetPtr;
		}
	}
	// If not, then print message
	else {
		puts("No pets");
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

	// Intialize file pointer and open file
	FILE* pfPtr = NULL;
	if ((pfPtr = fopen("C:\\GithubRepos\\CSC2060ClassCode\\CS2060ClassCodeFall2023-main\\examples\\Homework\\pets.txt", "a")) == NULL) {
		puts("File could not be opened");
	}
	// Add pets to file if file does exist
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
		// If none were found, print message
		else {
			puts("No pets to print to file");
		}
	}
	fclose(pfPtr);
}

void freeRemainingPets(Pet** headPtr) {
	// Deallocate memory from pets if memory exists
	if (*headPtr != NULL) {
		// Intialize pointers
		Pet* currentPtr = *headPtr;
		Pet* nextFreePetPtr = NULL;

		// CurrentPtr is not null, deallocate memory
		while (currentPtr != NULL) {
			nextFreePetPtr = currentPtr->nextPetPtr;
			free(currentPtr);
			currentPtr = nextFreePetPtr;
		}
		*headPtr = NULL;
	}
	// If no pets were in the list, print message
	else {
		puts("No pets to deallocate memory");
	}
}