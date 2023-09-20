/*
Name: James Hayes
Class: CSC 2060
Project Name: UCCS Air
OS: Windows 10 and Windows 11
Description: This program first prints the prompt for how much the user will be charged and what intervals
apply the appropriate discount. The program prompts the user for the number of nights and then calculates the charge
based on the discounts. When the sentinel value is entered by the property owner, then the total amount of nights
and charges will be displayed.
*/

// Header files
#include <stdio.h>
#include <stdlib.h>

// Intialize and declare functions
// Print Rental Property info 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, 
	unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);

// Return valid input based on range of nights 
int getValidInt(int min, int max, int sentinel);

// Calculate and return the charge based on number of nights, interval, and 
// discount
double calculateCharges(unsigned int nights, unsigned int interval1Nights, 
	unsigned int interval2Nighs, double rate, double charges);

// Print number of nights and its charge and if there were any rentals made
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
	int const ERROR_USER = 0;

	// User Inputs
	int userNights = 0;
	double userCharges = 0;
	
	// Rental Property Owner Summary
	int totalNights = 0;
	double totalCharges = 0;

	do {
		// Print rental information everytime
		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, 
			INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

		// Get user input
		userNights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1);

		// Cleaer input buffer
		while ((getchar()) != '\n');

		// Print error message
		if (userNights == ERROR_USER) {
			printf("Please enter a number between %d and %d\n", 
				MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
		}
		// End Program
		else if (userNights == SENTINEL_NEG1) {
			puts("Rental property summary:");
			printNightsCharges(totalNights, totalCharges);
		}
		// Calculate and print charges
		// Add to total nights and charges for summary
		else {
			userCharges = calculateCharges(userNights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, 
				RENTAL_RATE, DISCOUNT);
			totalNights += userNights;
			totalCharges += userCharges;
			printNightsCharges(userNights, userCharges);
		}

		// End Program
	} while (!(userNights == SENTINEL_NEG1));
}

/*
Print rental propery information everytime the user is prompted
Parameters: minimum nights, max nights, first interval, second interval, rate of charge, and discount
Return: Does not return value, only prints prompt for user
*/
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, 
	unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {

	// Print purpose of program and base charge in first interval
	printf("Rental Property can be rented for %d to %d nights.\n", 
		minNights, interval2Nights);
	printf("$%.2f rate a night for the first %d nights\n", 
		rate, interval1Nights);

	// Print information on discount value in first interval
	printf("$%.2f discount rate a night for nights %d to %d\n", 
		discount, interval1Nights, interval2Nights);

	// Print information on discount value is in second interval
	printf("$%.2f discount rate for each remaining night over %d\n", 
		discount *2, interval2Nights);
}

/*
Validate user input by returning the value of input or an error value of 0
Parameters: min nights, max nights, sentinel value
Return: Either the value for number of nights or the errorReturn to print an error message
*/
int getValidInt(int min, int max, int sentinel) {
	int input = 0;
	int errorReturn = 0;

	// Scan for user input, place into input
	scanf("%d", &input);

	// Return the user input if it is within the range or
	// if it is the sentinel value
	if ((min <= input && input <= max) || input == sentinel) {
		return input;
	}
	// Return an error value to print error message
	else {
		return errorReturn;
	}
}

/*
Calculate the charges using the discount
Parameters: int nights, 1st interval of nights, 2nd intervals of nights, charge rate, and discount
Return: the final charge after applying discount 
*/
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	// Intialize count
	int count = 1;

	// Intialize charges
	double charges = 0;

	// Loop until count is greater than number of nights
	while (!(count > nights)) {
		
		// Add charge each time
		charges += rate;

		// If count is greater than 1st interval apply discount
		if (count > interval1Nights) {
			charges -= discount;

			// If count is greatert than 2nd interval apply discount
			if (count > interval2Nights) {
				charges -= discount;
			}
		}

		// Iterate count
		count++;
	}
	return charges;
}

/*
Print the number of nights and the charges for those nights
Parameters: int nights (user input) and charges
Return: Does not return, prints out summary of nights and charges
*/
void printNightsCharges(unsigned int nights, double charges) {
	// If no rentals were made, then print then no rentals were made
	if (nights == charges) {
		puts("\nThere were no rentals\n");
	}
	//  If there were inputs, output the result
	else {
		printf("\nNights: %d Charge: $%.2f\n", nights, charges);
	}
}
