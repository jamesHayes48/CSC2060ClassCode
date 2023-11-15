#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void printPetToFile();

int main(void) {
	printPetToFile();
}

void printPetToFile() {

	// Intialize file pointer and open file
	FILE* pfPtr = NULL;
	if ((pfPtr = fopen("C:\\GithubRepos\\CSC2060ClassCode\\CS2060ClassCodeFall2023-main\\examples\\Homework\\pets.txt", "r")) == NULL) {
		puts("File could not be opened");
	}
	// Add pets to file if file does exist
	else {
		char name[80];
		int age;
		while (!feof(pfPtr)) {
			fscanf(pfPtr, "%s\n", name);
			fscanf(pfPtr, "%d\n", &age);

			printf("Name: %s Age: %d\n", name, age);
		}
		// If none were found, print mes
	}
	fclose(pfPtr);
}