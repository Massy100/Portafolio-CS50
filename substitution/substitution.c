#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// function to encrypt substitution
void encryptSubstitution(string key, string plaintext) {
    string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alphabetLower = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; plaintext[i]; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int index = islower(plaintext[i]) ? plaintext[i] - 'a' : plaintext[i] - 'A';
            char substitute = islower(plaintext[i]) ? tolower(key[index]) : toupper(key[index]);

            plaintext[i] = (plaintext[i] - base == substitute - base) ? plaintext[i] : substitute;
        }
    }
}

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int keyLength = strlen(key);

    if (keyLength != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < keyLength; i++) {
        if (!isalpha(key[i])) {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        for (int j = i + 1; j < keyLength; j++) {
            if (key[i] == key[j]) {
                printf("Key must not contain duplicate characters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    encryptSubstitution(key, plaintext);

    printf("ciphertext: %s\n", plaintext);

    return 0;
}
