#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <intrin.h>

char** generateRandomStrings(char** list,int n_str, int str_size) {


    if (list == NULL) {
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < n_str; i++) {
        list[i] = (char*)malloc((str_size + 1) * sizeof(char));

        if (list[i] == NULL) {
            return NULL; // Memory allocation failed
        }

        for (int j = 0; j < str_size; j++) {
            // Generate a random character (both uppercase and lowercase)
            char randomChar = (rand() % 2 == 0) ? ('A' + rand() % 26) : ('a' + rand() % 26);
            list[i][j] = randomChar;
        }
        list[i][str_size] = '\0'; // Null-terminate the string
    }

    return list;
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int n_str, str_size;

    // Get the number of strings and string size from the user
    printf("Enter the number of strings: ");
    scanf_s("%d", &n_str);

    printf("Enter the size of each string: ");
    scanf_s("%d", &str_size);

    // Create an array of pointers to char arrays
    char** list = (char**)malloc(n_str * sizeof(char*));

    char *addr = (char*)malloc(n_str * sizeof(char*));


    list = generateRandomStrings(list,n_str,str_size);

    printf("Before sorting:\n");
    for (int i = 0; i < n_str; i++) {
        printf("String %d: %s\n", i + 1, list[i]);
    }

    qsort(list, n_str, sizeof(char*), compareStrings);


    printf("\nSorted strings:\n");
    for (int i = 0; i < n_str; i++) {
        printf("String %d: %s\n", i + 1, list[i]);
    }

    for (int i = 0; i < n_str; i++) {
        free(list[i]);
    }
    free(list);
    return 0;
}
