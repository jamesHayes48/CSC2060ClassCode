#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEE 3

typedef struct {
	char name[20];
	int age;
	float zone;
	double heartRate;
}Member;

void sortMembers(Member membersArr[], int size);
void printMembers(Member membersArr[], int size);
void calculateHeartRate(Member membersArr[], int size);
void writePath(char path[]);
void printToFile(char path[], Member membersArr[], int size);
void scanFromFile(char path[], Member membersArr[], int size);

int main(void) {

	Member member1 = {"Static", 45, 3, 0};
	Member member2 = { "Dynamic", 23, 1, 0 };
	Member member3 = { "Queue", 19, 2, 0 };
	
	Member gymMembersArr[MAX_EMPLOYEE] = {member1, member2, member3};

	sortMembers(gymMembersArr, MAX_EMPLOYEE);
	printMembers(gymMembersArr, MAX_EMPLOYEE);
	calculateHeartRate(gymMembersArr, MAX_EMPLOYEE);

	puts("After calc");
	printMembers(gymMembersArr, MAX_EMPLOYEE);

	char path[200] = "C:\\Users\\jhpip\\Documents\\CSC2060ClassCode\\CS2060ClassCodeFall2023-main\\examples\\Homework\\";
	writePath(path);
	printf("%s\n", path);

	printToFile(path, gymMembersArr, MAX_EMPLOYEE);
	
	scanFromFile(path, gymMembersArr, MAX_EMPLOYEE);
	return 0;
}

void sortMembers(Member membersArr[], int size) {
	for (int pass = 1; pass < size; ++pass) {
		for (size_t i = 0; i < size - 1; i++) {
			if (membersArr[i].age > membersArr[i + 1].age) {
				Member temp = membersArr[i + 1];
				membersArr[i + 1] = membersArr[i];
				membersArr[i] = temp;
			}
		}
	}
}

void printMembers(Member membersArr[], int size) {
	for (size_t i = 0; i < size; i++) {
		printf("Name: %s Age: %d Zone: %.2f Heartrate: %.2lf\n", membersArr[i].name, membersArr[i].age, membersArr[i].zone, membersArr[i].heartRate);
	}
}

void calculateHeartRate(Member membersArr[], int size) {
	for (size_t i = 0; i < size; i++) {
		membersArr[i].heartRate = 220 - membersArr[i].age;
		if (membersArr[i].zone == 1) {
			membersArr[i].heartRate *= .6;
		}
		else if (membersArr[i].zone == 2) {
			membersArr[i].heartRate *= .7;
		}
		else if (membersArr[i].zone == 3) {
			membersArr[i].heartRate *= .8;
		}
	}
}

void writePath(char path[]) {
	char file[9] = "gym.txt";

	strcat(path, file);
}

void printToFile(char path[], Member membersArr[], int size) {

	FILE* pfPtr = NULL;
	if ( (pfPtr = fopen(path, "w") ) ==  NULL ) {
		puts("File cannot be found");
	}
	else {
		for (size_t i = 0; i < size; i++) {
			fprintf(pfPtr, "%s %d% .2f% .2lf\n", membersArr[i].name, membersArr[i].age, membersArr[i].zone, membersArr[i].heartRate);
		}
		fclose(pfPtr);
	}
}

void scanFromFile(char path[], Member membersArr[], int size) {
	FILE* pfPtr = NULL;
	if ((pfPtr = fopen(path, "r")) == NULL) {
		puts("File cannot be found");
	}
	else {
		char name[80] = "";
		int age = 0;
		float zone = 0.0;
		double heartRate = 0.0;
		while (!feof(pfPtr)) {
			fscanf(pfPtr, "%s%d%f%lf", name, &age, &zone, &heartRate);
			printf("Name: %s Age: %d Zone: %.2f HeartRate: %.2lf\n", name, age, zone, heartRate);
		}
		fclose(pfPtr);
	}
}