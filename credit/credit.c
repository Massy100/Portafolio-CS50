#include <cs50.h>
#include <stdio.h>

int main() {
    long long card_number;

    card_number = get_long("Enter the credit card number: ");

    if (card_number < 1000000000000 || card_number >= 10000000000000000) {
        printf("INVALID\n");
    } else {
        int sum = 0;
        int is_second_digit = 0;
        int num_digits = 0;
        long long temp_number = card_number;

        while (temp_number > 0) {
            temp_number /= 10;
            num_digits++;
        }

        temp_number = card_number;

        while (temp_number > 0) {
            int digit = temp_number % 10;

            if (is_second_digit) {
                digit *= 2;
                while (digit > 0) {
                    sum += digit % 10;
                    digit /= 10;
                }
            } else {
                sum += digit;
            }

            is_second_digit = !is_second_digit;
            temp_number /= 10;
        }

        if (sum % 10 == 0) {
            if (num_digits == 15 && (card_number / 10000000000000 == 34 || card_number / 10000000000000 == 37)) {
                printf("AMEX\n");
            } else if (num_digits == 16 && (card_number / 100000000000000 == 51 || card_number / 100000000000000 == 52 || card_number / 100000000000000 == 53 || card_number / 100000000000000 == 54 || card_number / 100000000000000 == 55)) {
                printf("MASTERCARD\n");
            } else if (num_digits == 13 || (num_digits == 16 && card_number / 1000000000000000 == 4)) {
                printf("VISA\n");
            } else {
                printf("INVALID\n");
            }
        } else {
            printf("INVALID\n");
        }
    }
}