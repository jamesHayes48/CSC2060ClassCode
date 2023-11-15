#include <stdio.h>
#include <stdlib.h>

#define MAX_EMPLOYEE 5

struct employee {
	int age;
	int id;
};

void enterEmployee(struct employee* employeeArr);
void sortEmployee(struct employee* employeeArr);

int main(void) {
	struct employee employeeArrMain[MAX_EMPLOYEE];
	enterEmployee(employeeArrMain);
	sortEmployee(employeeArrMain);

	for (size_t i = 0; i < MAX_EMPLOYEE; i++) {
		printf("Age: %d Id: %d\n", employeeArrMain[i].age, employeeArrMain[i].id);
	}

}

void enterEmployee(struct employee* employeeArr) {
	for (size_t i = 0; i < MAX_EMPLOYEE; i++) {
		puts("Enter Age: ");
		scanf("%d", &employeeArr[i].age);

		while (getchar() != '\n');

		puts("Enter id");
		scanf("%d", &employeeArr[i].id);

		while (getchar() != '\n');
	}
}

void sortEmployee(struct employee* employeeArr) {
	for (int pass = 1; pass < MAX_EMPLOYEE; ++pass) {
		for (size_t i = 0; i < MAX_EMPLOYEE - 1; i++) {
			if (employeeArr[i].age < employeeArr[i + 1].age) {
				struct employee temp = employeeArr[i + 1];
				employeeArr[i + 1] = employeeArr[i];
				employeeArr[i] = temp;
			}
		}
	}
	
}