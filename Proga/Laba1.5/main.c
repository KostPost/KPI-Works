#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


char** generateRandomStrings(char** list,int n_str, int str_size) {


    if (list == NULL) {
        return NULL;
    }

    for (int i = 0; i < n_str; i++) {
        list[i] = (char*)malloc((str_size + 1) * sizeof(char));

        if (list[i] == NULL) {
            return NULL;
        }

        for (int j = 0; j < str_size; j++) {
            char randomChar = (rand() % 2 == 0) ? ('A' + rand() % 26) : ('a' + rand() % 26);
            list[i][j] = randomChar;
        }
        list[i][str_size] = '\0';
    }

    return list;
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int n_str, str_size;

    printf("Enter the number of strings: ");
    scanf("%d", &n_str);

    printf("Enter the size of each string: ");
    scanf("%d", &str_size);

    char** list = (char**)malloc(n_str * sizeof(char*));

    //char *addr = (char*)malloc(n_str * sizeof(char*));

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
