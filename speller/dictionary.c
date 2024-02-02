#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose the number of buckets in the hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Hash function prototype
unsigned int hash(const char *word);

bool check(const char *word)
{
    // Convert the word to lowercase
    char lowercase_word[LENGTH + 1];
    for (int i = 0; i < LENGTH + 1 && word[i] != '\0'; i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }
    lowercase_word[LENGTH] = '\0'; // Ensure the string is terminated

    // Hash the lowercase word to get the bucket index
    unsigned int index = hash(lowercase_word);

    // Search for the word in the linked list at the index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lowercase_word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improved hash function using the djb2 algorithm
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer for reading words
    char word[LENGTH + 1];

    // Initialize current node pointer
    node *current_node = NULL;

    // Read words from dictionary and insert into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy the word to the new node
        strcpy(new_node->word, word);

        // Hash the word to get the bucket index
        unsigned int index = hash(word);

        // Insert the new node at the beginning of the linked list
        new_node->next = table[index];
        table[index] = new_node;

        // Update the current node pointer
        current_node = new_node;
    }

    // Set the next pointer of the last node to NULL
    if (current_node != NULL)
    {
        current_node->next = NULL;
    }

    // Close dictionary file
    fclose(file);

    return true;
}

// Returns the number of words in the dictionary
unsigned int size(void)
{
    unsigned int count = 0;

    // Iterate through each bucket
    for (int i = 0; i < N; i++)
    {
        // Iterate through each node in the linked list
        node *cursor = table[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through each bucket
    for (int i = 0; i < N; i++)
    {
        // Free each node in the linked list
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
