#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void encryptCaesar(string message, int key) {
    for (int i = 0; message[i]; i++) {
        if (isalpha(message[i])) {
            char base = islower(message[i]) ? 'a' : 'A';
            message[i] = (message[i] - base + key) % 26 + base;
        }
    }
}

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    int keyLength = strlen(argv[1]);

    for (int i = 0; i < keyLength; i++) {
        if (!isdigit(argv[1][i])) {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    encryptCaesar(plaintext, key);
    printf("%s\n", plaintext);

    return 0;
}
