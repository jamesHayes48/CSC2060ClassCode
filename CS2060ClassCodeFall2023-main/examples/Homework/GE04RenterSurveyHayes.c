/*
Name: James Hayes
Class: CSC 2060
Project Name: UCCS Air Survey
OS: Windows 10 and Windows 11
Description: This program first prints the information on what the maximum rating the user can
give the categories. Then, it prompts each number of users for a rating between 1 and 5 for
each of the three categories. After this, it displays each entry of rating from every user formatted
for each category. Finally, the program calculates and displays the 
averages of each category from each user.
*/

// Header Files
#include <stdio.h>

// Constants for array sizes
#define RENTER_SURVEY_CATEGORIES 3
#define MAX_RENTER 5

// Function prototypes
// Print survey information
void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories);

// Print categories for rating
void printCategories(const char* categories[], size_t totalCategories);

// Loop and add input into 2D array
void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], const char* categories[], size_t totalUsers, size_t totalCategories);

// Get valid input
int getValidInt(int minRating, int maxRating);

// Print the results of the survey
void printSurveyResults(const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Calculate the average for each category
void calculateCategoryAverages(double averages[], int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories);

// Print the averages for each category
void printCategoryData(const double averages[], size_t totalUsers, size_t totalCategories);

// Main function
int main(void) {
	// Constant variables for iterations 
	const int MAX_RATING = 5;
	const int MIN_RATING = 1;

	// Intialize and declare both arrays
	const char *surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };
	int rentalSurvey[MAX_RENTER][RENTER_SURVEY_CATEGORIES] = {0};
	double averageCategories[RENTER_SURVEY_CATEGORIES] = {0};

	// Print the intial information on what needs to be done
	printSurveyInformation(MIN_RATING, MAX_RATING, surveyCategories, RENTER_SURVEY_CATEGORIES);

	// Get user input and store into 2D array
	getRatings(MIN_RATING, MAX_RATING, rentalSurvey, surveyCategories, MAX_RENTER, RENTER_SURVEY_CATEGORIES);

	// Print the ratings from each user and for each category
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
	printSurveyResults(rentalSurvey, MAX_RENTER, RENTER_SURVEY_CATEGORIES);

	// Calculate the average for each category
	calculateCategoryAverages(averageCategories, rentalSurvey, MAX_RENTER, RENTER_SURVEY_CATEGORIES);

	// Print the averages of each category
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
	printCategoryData(averageCategories, MAX_RENTER, RENTER_SURVEY_CATEGORIES);
}

/*
Purpose: Print information on what the rating scale is and what categories they are writing on
Parameters: minimum rating, maximum rating, array of categories, and the number of categories
Return: Does not return a value but prints info for user
*/
void printSurveyInformation(int minRating, int maxRating, const char* categories[], size_t totalCategories) {
	printf("We want your feed back, please enter your rating from %d to %d for each category.\n", 
		minRating, maxRating);
	printCategories(categories, totalCategories);
}

/*
Purpose: Print the categories the user will be rating on
Parameters: array with categories and the number of categories
Return: Does not return anything, but prints out the categories horizontally
*/
void printCategories(const char* categories[], size_t totalCategories)
{
    // Loop to display each category horizontally
    printf("%s", "Rating Categories:\t");
    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
    {
        printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
    }
	// Start new line of output
	puts(""); 
}

/*
Purpose: Get and store user input for ratings
Parameters: minimum rating, maximum rating, array for survey data, array of categories, 
number of users and number of categories
Return: Does not return anything, modifies intialized array
*/
void getRatings(int minRating, int maxRating, int survey[][RENTER_SURVEY_CATEGORIES], const char* categories[], size_t totalUsers, size_t totalCategories) {
	// Initialize error value
	int const errorScan = 0;

	// Iterate through row (users)
	for (size_t i = 0; i < totalUsers; ++i) {
		// Print current survey
		printf("Survey %zu\n", i+1);

		// Iterate through column (categories)
		for (size_t j = 0; j < totalCategories; ++j) {

			// Print which category will be rated
			printf("Enter your rating for %s\n", categories[j]);

			// Intialize scan reference for input
			int scanRef = 0;

			// While the user input is invalid, keep prompting
			while (scanRef == 0) {

				// Store user input into array
				survey[i][j] = getValidInt(minRating, maxRating);

				// Clear input buffer
				while ((getchar() != '\n'));

				// Set the scan reference to check input
				scanRef = survey[i][j];

				// If user input is invalid, print error message
				if (scanRef == errorScan) {
					printf("Please enter a number rating between %d and %d\n", minRating, maxRating);
				}
			}
			
		}
	}
}

/*
Purpose: Validates user input to check if it is incorrect
Parameters: minimum rating and maximum rating
Return: Returns the user data if valid, if invalid, returns an error input
*/
int getValidInt(int minRating, int maxRating) {
	int input = 0;
	int errorReturn = 0;

	// Scan for user input, place into input
	scanf("%d", &input);

	// Return the user input if it is within the range of ratings
	if (minRating <= input && input <= maxRating) {
		return input;
	}
	// Return an error value to print error message
	else {
		return errorReturn;
	}
}

/*
Purpose: Print the survey's results
Parameters: array with survey data, number of users, and number of categories
Return: Does not return anything but prints results of survey formatted
*/
void printSurveyResults(const int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	// Iterate through rows (users)
	for (size_t i = 0; i < totalUsers; ++i) {
		// Print which survey
		printf("Survey %zu:", i + 1);

		// Iterate through columns (categories)
		for (size_t j = 0; j < totalCategories; ++j) {
			// Print the rating for the category formatted
			printf("%30u", survey[i][j]);
		}
		// Print new line
		printf("\n");
	}
}

/*
Purpose: Calculate the averages for each category and store in array
Parameters: array with averages, array with survey results, number of users and number of categories
Return: Does not return anything, but modifies initialized array with averages
*/
void calculateCategoryAverages(double averages[], int survey[][RENTER_SURVEY_CATEGORIES], size_t totalUsers, size_t totalCategories) {
	// Iterate through rows (users)
	for (size_t i = 0; i < totalUsers; ++i) {
		
		// Iterate through columns (categories)
		for (size_t j = 0; j < totalCategories; ++j ) {
			// Calculate the average for each category and store in array
			averages[j] += ((double) (survey[i][j]) / totalUsers);
		}
	}
}

/*
Purpose: Print the averages of categories 
Parameters: constant array with averages, number of users, and number of categories
Return: Does not return anything, but prints the averages for each category formatted
*/
void printCategoryData(const double averages[], size_t totalUsers, size_t totalCategories) {
	// Print the title
	printf("%s", "Rating Averages:\t");

	// Iterate through average category data
	for (size_t i = 0; i < totalCategories; ++i) {
		// Print the average for the category
		printf("%.1f\t", averages[i]);
	}
}