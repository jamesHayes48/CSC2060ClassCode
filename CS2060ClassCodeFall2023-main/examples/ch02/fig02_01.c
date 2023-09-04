// fig02_01.c
// A first program in C.
#include <stdio.h>
#include <stdbool.h>

// function main begins program execution 
int main(void) {
   // Initialize variables
   int length = 0;
   int width = 0;
   int area = 0;
   double averageValue = 0;
   int scanfRef = 0;
   bool checkScan = false;

   // Print welcome
   printf("Welcome to C!\n");

   // Prompt user for length
   puts("Enter the length:");

   // Loop each time user inputs invalid value
   do {
	   // Allow user to input
	   scanfRef = scanf("%d", &length);
	   
	   // Referesh input buffer
	   while ((getchar()) != '\n');

		// Check if it is valid user input
	    // Can leave loop
		if (scanfRef != 0) {
			checkScan = true;
		}
		// Print error message then loop again
		else {
			puts("Not a valid input, enter again:");
		}
   } while(!checkScan);

   // Reset checking values
   checkScan = false;
   scanfRef = 0;

   // Prompt user for width
   puts("Enter the width:");

  // Loop each time user inputs invalid value
   do {
	   // Allow user to input
	   scanfRef = scanf("%d", &width);

	   // Referesh input buffer
	   while ((getchar()) != '\n');

	   // Check if it is valid user input
	   // Can leave loop
	   if (scanfRef != 0) {
		   checkScan = true;
	   }
	   // Print error message then loop again
	   else {
		   puts("Not a valid input, enter again:");
	   }
   } while (!checkScan);

   // Calculate area and average value
   area = length * width;

   // Print out inputs and area
   printf("Length: %d Width: %d Area: %d", length, width, area);

   // Calculate average value
   averageValue = (double) (length + width) / 2;

   // Print average value
   printf(" Average value: %.1f", averageValue);

   // End main function
   return 0;
} // end function main 



/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
