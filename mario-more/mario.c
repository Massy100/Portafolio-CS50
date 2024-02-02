#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int height;

    do {
        height = get_int("Enter the height (number between 1 and 8): ");
    } while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++) {
        // Prints left ladder
        for (int j = 1; j <= height - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= i; k++) {
            printf("#");
        }

        // Space between ladders
        printf("  ");

        // Prints second ladder
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }
}