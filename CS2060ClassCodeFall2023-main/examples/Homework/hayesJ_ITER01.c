// Header files
#include <stdio.h>
#include <stdlib.h>

// Intialize and declare functions
// Print Rental Property info 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, 
	unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
// Return valid input 
int getValidInt(int min, int max, int sentinel);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, 
	unsigned int interval2Nighs, double rate, double charges);
void printNightsCharges(unsigned int nights, double charges);

// Main function
int main(void) {
	// Constants used for calculation and input
	int const SENTINEL_NEG1 = -1;
	int unsigned const MIN_RENTAL_NIGHTS = 1;
	unsigned int const MAX_RENTAL_NIGHTS = 14;
	unsigned int const INTERVAL_1_NIGHTS = 3;
	unsigned int const INTERVAL_2_NIGHTS = 6;
	double const RENTAL_RATE = 400;
	double const DISCOUNT = 50;

	// User Inputs
	int userNights = 0;
	double userCharges = 0;
	
	// Rental Property Owner Summary
	int totalNights = 0;
	double totalCharges = 0;

	do {
		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, 
			INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
		userNights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1);
		while ((getchar()) != '\n');
		if (userNights == 0) {
			printf("Please enter an integer between %d and %d\n", 
				MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
		}
		else if (userNights == SENTINEL_NEG1) {
			// End program
			puts("Rental property summary");
			printNightsCharges(totalNights, totalCharges);
		}
		else {
			userCharges = calculateCharges(userNights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, 
				RENTAL_RATE, DISCOUNT);
			totalNights += userNights;
			totalCharges += userCharges;
			printNightsCharges(userNights, userCharges);
		}
	} while (!(userNights == SENTINEL_NEG1));
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

int getValidInt(int min, int max, int sentinel) {
	int input = 0;
	scanf("%d", &input);
	if (min <= input <= max || input == sentinel) {
		return input;
	}
	else {
		return 0;
	}
}

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	int count = 1;
	double charges = 0;
	while (!(count > nights)) {
		charges += rate;
		if (count > interval1Nights) {
			charges -= discount;
			if (count > interval2Nights) {
				charges -= discount;
			}
		}
		count++;
	}
	return charges;
}

void printNightsCharges(unsigned int nights, double charges) {
	printf("Nights: %d Charge: $%.2f\n", nights, charges);
}
