// Header files
#include <stdio.h>
#include <stdlib.h>

// Intialize and declare functions
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, 
	unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, 
	unsigned int interval2Nighs, double charges);
void printNightsCharges(unsigned int nights, double charges);

// Main function
int main(void) {
	// Constants used for calculation and input
	int const SENTINAL_NEG1 = -1;
	int unsigned const MIN_RENTAL_NIGHTS = 1;
	unsigned int const MAX_RENTAL_NIGHTS = 14;
	unsigned int const INTERVAL_1_NIGHTS = 3;
	unsigned int const INTERVAL_2_NIGHTS = 6;
	double const RENTAL_RATE = 400;
	double const DISCOUNT = 50;

	// User Inputs
	int userNights = 0;
	double usercharges = 0;
	//int scanfRef = 0;

	do {
		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, 
			INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
		scanf("%d", &userNights);
		while (getchar() != '\n');
		getValidInt();
	} while (!(userNights == SENTINAL_NEG1));
}


void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, 
	unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	printf("Rental Property can be rented for %d to %d nights.\n", 
		minNights, interval2Nights);
	printf("$%.2f rate a night for the first %d nights\n", 
		rate, interval1Nights);
	printf("$%.2f discount rate a night for nights %d to %d\n", 
		discount, interval1Nights, interval2Nights);
	printf("$%.2f discount rate for each remaining night over %d\n", 
		discount *2, interval2Nights);
}

int getValidInt(int min, int max) {

}

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nighs, double charges) {

}

void printNightsCharges(unsigned int nights, double charges) {

}
