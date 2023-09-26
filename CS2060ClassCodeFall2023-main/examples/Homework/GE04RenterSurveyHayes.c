// Header Files
#include <stdio.h>

// Constants for array sizes
#define RENTER_SURVEY_CATEGORIES 3
#define MAX_RENTER 5

// Function prototypes
void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories);
void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int minRating, int maxRating, int maxRenter, int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Main function
int main(void) {
	// Constant variables for 
	const int MAX_RATING = 5;
	const int MIN_RATING = 1;
	int count = 0;

	const char *surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };
	const int rentalSurvey[MAX_RENTER][RENTER_SURVEY_CATEGORIES] = {0};

	printSurveyInformation(MAX_RATING, MIN_RATING, surveyCategories, RENTER_SURVEY_CATEGORIES);

	//do {

	//} while (!(count == MAX_RENTER));
}

void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories) {
	printf("We want your feed back, please enter your rating from %d to %d for each category.\n", 
		minRating, maxRating);
	printCategories(categories, totalCategories);
}

void printCategories(const char* categories[], size_t totalCategories)
{
    //loop to display each category horizontally
    printf("%s", "Rating Categories:\t");
    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
    {
        printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
    }
    puts(""); // start new line of output
}

void getRatings(int minRating, int maxRating, int maxRenter, int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	for (size_t i = 0; i < totalUsers; ++i) {
		for (size_t j = 0; j < totalCategories; ++j) {
			survey[i][j] = getValidInt(minRating, maxRating);
		}
	}
}

int getValidInt(int min, int max) {
	double input = 0;
	int errorReturn = 0;

	// Scan for user input, place into input
	scanf("%.1f", &input);

	// Return the user input if it is within the range or
	if (min <= input && input <= max) {
		return input;
	}
	// Return an error value to print error message
	else {
		return errorReturn;
	}
}


