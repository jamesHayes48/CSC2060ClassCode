// Header files
#include <stdio.h>

// Constants
# define const SENTINEL_NEG1 -1
# define int unsigned const MIN_RENTAL_NIGHTS 1
# define unsigned int const MAX_RENTAL_NIGHTS 14
# define unsigned int const INTERVAL_1_NIGHTS 3
# define unsigned int const INTERVAL_2_NIGHTS 6
# define double const RENTAL_RATE 400
# define double const DISCOUNT 50

// Intialize and declare functions
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, 
	unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, 
	unsigned int interval2Nighs, double);
void printNightsCharges(unsigned int nights, double charges);