#include <stdio.h>
#include <stdbool.h>

#define STRING_LENGTH 80

typedef struct {
	char name[STRING_LENGTH];
	int age;

	struct Pet* nextPetPtr;
} Pet;

void insertPet(Pet** headPtr);
bool yesOrNo();

int main(void) {
	Pet* headMainPetPtr = NULL;

	do {

	} while ();
}

void insertPet(Pet** headPtr) {

}

bool yesOrNo() {

}