/*Purpose: Lab 7: Organizing IKEA Products in Aisles by Serial Numbers 
 * Author: Abdullah Faisal
 * Date: Oct 29th 2023
 * References:
 * Lab Instructions
 * String Concatenation (strcat) referenced from https://www.geeksforgeeks.org/strcat-in-c/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int numAisles;
    if (scanf("%d", &numAisles) != 1) {
        fprintf(stderr, "Failed to read the number of aisles.\n");
        return 1;
    }

    int *arrayLen = (int *)malloc(numAisles * sizeof(int)); // Initialize arrayLen
    char **aisles = (char **)malloc(numAisles * sizeof(char *)); // Initialize 2D array aisles

    if (arrayLen == NULL || aisles == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numAisles; i++) {
        arrayLen[i] = 0;
        aisles[i] = (char *)malloc(1); // Start with an empty aisle
        aisles[i][0] = '\0'; // Null-terminate the string
    }

    int number;
    char label[10]; // Assuming a maximum label length of 9 characters

    while (1) {
        int result = scanf("%d", &number);
        if (result == EOF) {
            break; // Exit the loop if end of input is reached
        } else if (result != 1) {
            fprintf(stderr, "Failed to read the number.\n");
            return 1;
        }

        int labelRead = scanf(" %9[^\n]", label); // Read the label, up to 9 characters
        if (labelRead != 1 && labelRead != EOF) {
            fprintf(stderr, "Failed to read the label.\n");
            return 1;
        }

        if (number == 0) {
            int printIndex = atoi(label);
            printf("%s\n", aisles[printIndex]);
        } else {
            int aisleIndex = number % numAisles;
            int labelLength = strlen(aisles[aisleIndex]);
            char *newAisle = (char *)realloc(aisles[aisleIndex], (labelLength + strlen(label) + 1) * sizeof(char));

            if (newAisle == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                return 1;
            }

            aisles[aisleIndex] = newAisle;
            strcat(aisles[aisleIndex], label);
            arrayLen[aisleIndex]++;
        }
    }

    for (int i = 0; i < numAisles; i++) {
        free(aisles[i]);
    }
    free(aisles);
    free(arrayLen);

    return 0;
}
