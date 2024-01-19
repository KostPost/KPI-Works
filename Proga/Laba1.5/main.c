#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


char **generateRandomStrings(char **list, int n_str, int str_size) {
    if (list == NULL) {
        return NULL;
    }

    for (int i = 0; i < n_str; i++) {
        list[i] = (char *) malloc((str_size + 1) * sizeof(char));

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

char **enterData(char **list, int n_str, int str_size) {
    for (int i = 0; i < n_str; ++i) {
        int validInput = 0;

        do {
            printf("Enter string %d (%d characters): ", i + 1, str_size);

            list[i] = (char *) malloc((str_size + 1) * sizeof(char));

            if (fgets(list[i], str_size + 2, stdin) == NULL) {
                perror("Error reading input");
                exit(EXIT_FAILURE);
            }

            size_t len = strlen(list[i]);

            if (len > 0 && list[i][len - 1] == '\n') {
                if (len - 1 == str_size) {
                    list[i][len - 1] = '\0';
                    validInput = 1;
                } else {
                    printf("Entered string does not have the required length. Please try again.\n");
                }
            } else {
                printf("Entered string exceeds the allowed length. Please try again.\n");

                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        } while (!validInput);
    }

    return list;
}

int sortArrAsc(const void *a, const void *b) {
    return strcmp(*(const char **) a, *(const char **) b);
}

int sortArrDesc(const void *a, const void *b) {
    return strcmp(*(const char **) b, *(const char **) a);
}


int main() {
    int choice;

    do {

        printf("1 - Sorting chars\n2 - Exit\n");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
                int n_str;
                do {
                    printf("Enter the amount of strings: ");
                    scanf("%d", &n_str);
                } while (n_str < 1 || n_str >= 50);


                int str_size;
                do {
                    printf("Enter the size of each string: ");
                    scanf("%d", &str_size);
                } while (str_size < 0 || str_size >= 50);

                char **list = (char **) malloc(n_str * sizeof(char *));

                int choiceFileAction;
                while (1) {
                    printf("1 - Enter data in arr\n2 - Random data in file\n");
                    scanf("%d", &choiceFileAction);

                    if (choiceFileAction == 1) {
                        getchar();
                        list = enterData(list, n_str, str_size);
                        break;
                    } else if (choiceFileAction == 2) {
                        getchar();
                        list = generateRandomStrings(list, n_str, str_size);
                        break;
                    } else {
                        printf("Invalid choice. Exiting the loop.\n");
                        break;
                    }
                }

                printf("Before sorting:\n");
                for (int i = 0; i < n_str; i++) {
                    printf("String %d: %s\n", i + 1, list[i]);
                }

                int choiceSort;
                while (1) {
                    printf("Choose sorting order:\n");
                    printf("1 - Ascending\n");
                    printf("2 - Descending\n");
                    scanf("%d", &choiceSort);
                    getchar();

                    if(choiceFileAction == 1) {
                        qsort(list, n_str, sizeof(char *), sortArrAsc);
                        break;
                    }
                    else if(choiceFileAction == 2){
                        qsort(list, n_str, sizeof(char *), sortArrDesc);
                        break;
                    }
                }


                printf("\nSorted strings:\n");
                for (int i = 0; i < n_str; i++) {
                    printf("String %d: %s\n", i + 1, list[i]);
                }

                for (int i = 0; i < n_str; i++) {
                    free(list[i]);
                }
                free(list);
                break;
            }
        }

    } while (choice != 2);

    return 0;
}
