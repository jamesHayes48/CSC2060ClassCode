#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 80

typedef struct {
	int interval1;
	int interval2;
	int rentalRate;
	int discount;
	
	char propertyName[MAX_SIZE];
	char propertyLocation[MAX_SIZE];
}Property;

void setUpProperty(Property* propertyPtr);
void displayOrganization(Property* propertyPtr);

int main(void) {
	Property property1;
	setUpProperty(&property1);
	displayOrganization(&property1);
}

void setUpProperty(Property* propertyPtr) {
	puts("Please enter first interval");
	scanf("%d", &(propertyPtr->interval1));

	while ((getchar()) != '\n');

	puts("Please enter second interval");
	scanf("%d", &(propertyPtr->interval2));

	while ((getchar()) != '\n');

	puts("Please enter rate");
	scanf("%d", &(propertyPtr->rentalRate));

	while ((getchar()) != '\n');

	puts("Please enter discount");
	scanf("%d", &(propertyPtr->discount));

	while ((getchar()) != '\n');

	puts("Please enter property name");
	fgets(propertyPtr->propertyName,MAX_SIZE,stdin);

	puts("Please enter property location");
	fgets(propertyPtr->propertyLocation, MAX_SIZE, stdin);
}

void displayOrganization(Property* propertyPtr) {
	printf("The first interval is %d, the second is %d\n", (propertyPtr->interval1), (propertyPtr->interval2));
	printf("The rental rate is %d and the discount is %d\n", (propertyPtr->rentalRate), (propertyPtr->discount));
	printf("The name of the property is %s, the location is %s\n", (propertyPtr->propertyName), (propertyPtr->propertyLocation));
}