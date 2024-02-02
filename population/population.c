#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size, end_size;

    do {
        start_size = get_int("Enter the starting population size (must be greater or equal than 9):");
    } while (start_size < 9);

    do {
        end_size = get_int("Enter the ending population size (must be greater or equal than starting size): ");
    } while (end_size < start_size);

    int years = 0;
    while (start_size < end_size) {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        years++;
    }

    printf("Years: %d\n", years);

    return 0;
}
