// Header Files
#include <stdio.h>

// Constants for array sizes
#define RENTER_SURVEY_CATEGORIES 3
#define MAX_RENTER 5

// Function prototypes
void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories);
void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);
int getValidInt(int minRating, int maxRating);
void printSurveyResults(const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);
void calculateCategoryAverages(int averages[], int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Main function
int main(void) {
	// Constant variables for iterations 
	const int MAX_RATING = 5;
	const int MIN_RATING = 1;

	// Intialize and declare both arrays
	const char *surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };
	int rentalSurvey[MAX_RENTER][RENTER_SURVEY_CATEGORIES] = {0};
	int averageCategories[RENTER_SURVEY_CATEGORIES] = {0};

	printSurveyInformation(MIN_RATING, MAX_RATING, surveyCategories, RENTER_SURVEY_CATEGORIES);
	getRatings(MIN_RATING, MAX_RATING, rentalSurvey, MAX_RENTER, RENTER_SURVEY_CATEGORIES);
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
	printSurveyResults(rentalSurvey, MAX_RENTER, RENTER_SURVEY_CATEGORIES);
	calculateCategoryAverages(averageCategories, rentalSurvey, MAX_RENTER, RENTER_SURVEY_CATEGORIES);
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

void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	int const errorScan = 0;
	for (size_t i = 0; i < totalUsers; ++i) {
		printf("Survey %zu\n", i+1);
		for (size_t j = 0; j < totalCategories; ++j) {
			int scanRef = 0;
			while (scanRef == 0) {
				survey[i][j] = getValidInt(minRating, maxRating);
				while ((getchar() != '\n'));
				scanRef = survey[i][j];
				if (scanRef == errorScan) {
					printf("Please enter a number rating between %d and %d\n", minRating, maxRating);
				}
			}
			
		}
	}
}

int getValidInt(int minRating, int maxRating) {
	int input = 0;
	int errorReturn = 0;

	// Scan for user input, place into input
	scanf("%d", &input);

	// Return the user input if it is within the range or
	if (minRating <= input && input <= maxRating) {
		return input;
	}
	// Return an error value to print error message
	else {
		return errorReturn;
	}
}

void printSurveyResults(const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	for (size_t i = 0; i < totalUsers; ++i) {
		printf("Survey %zu:", i + 1);
		for (size_t j = 0; j < totalCategories; ++j) {
			printf("%30u", survey[i][j]);
		}
		printf("\n");
	}
}

void calculateCategoryAverages(int averages[], int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {

}