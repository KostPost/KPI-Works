#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_ENTRIES 100

struct rec {
    char name[40];
    int square;
    int nas;
};

int compare(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *)a;
    struct rec *rec2 = (struct rec *)b;

    // Змініть цей блок відповідно до вибору сортування
    // Наприклад, для сортування за назвою області (у зростаючому порядку):
    return strcmp(rec1->name, rec2->name);
}

int compare_name_asc(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *)a;
    struct rec *rec2 = (struct rec *)b;
    return strcmp(rec1->name, rec2->name); // Сортування за назвою області у зростаючому порядку
}
int compare_name_desc(const void *a, const void *b) {
    return -compare_name_asc(a, b); // Сортування за назвою області у спадаючому порядку
}

int compare_square_asc(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *)a;
    struct rec *rec2 = (struct rec *)b;
    return rec1->square - rec2->square; // Сортування за площею у зростаючому порядку
}
int compare_square_desc(const void *a, const void *b) {
    return -compare_square_asc(a, b); // Сортування за площею у спадаючому порядку
}

int compare_nas_asc(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *)a;
    struct rec *rec2 = (struct rec *)b;
    return rec1->nas - rec2->nas; // Сортування за кількістю населення у зростаючому порядку
}

int compare_nas_desc(const void *a, const void *b) {
    return -compare_nas_asc(a, b); // Сортування за кількістю населення у спадаючому порядку
}

//char folderPath[256] = "/home/KPI-Works/Proga/Laba1.9/data";
char *path = "/home/Works-KPI/Proga/Laba1.9/data";

void seeAllFiles() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);

    if (dir != NULL) {


        while ((entry = readdir(dir)) != NULL) {

            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%s\n", entry->d_name);
            }
        }
    } else {
        perror("Unable to open directory");
    }

    closedir(dir);
}

int main() {
    int fileChoice, actionFile;


    FILE *file;
    DIR *directory = opendir(path);
    struct dirent *entry;

    do {
        printf("\n1 - Create\n2 - Choice file\n3 - Delete\n4 - Exit\n");
        scanf("%d", &fileChoice);

        switch (fileChoice) {

            case 1: {
                bool isExist = false;

                char filename[100];
                printf("Enter a file name to create\t");
                scanf("%99s", filename);

                while ((entry = readdir(directory)) != NULL) {
                    if (strcmp(entry->d_name, filename) == 0) {
                        isExist = true;
                        closedir(directory);
                        break;
                    }
                }

                if (!isExist) {
                    char filepath[100];
                    snprintf(filepath, sizeof(filepath), "%s/%s", path, filename);

                    file = fopen(filepath, "w");

                    if (file == NULL) {
                        perror("Unable to create the file");
                        return 1;
                    }

                    fflush(file);

                    fclose(file);
                    printf("File created: %s\n", filepath);
                } else {
                    printf("File already exist");
                }

                break;
            }

            case 2: {

                DIR *dir;
                struct dirent *ent;
                char *files[MAX_FILES];
                int count = 0;

                if ((dir = opendir(path)) != NULL) {
                    while ((ent = readdir(dir)) != NULL) {
                        if (ent->d_type == DT_REG) {
                            if (strstr(ent->d_name, ".txt") != NULL) {
                                files[count] = malloc(strlen(ent->d_name) + 1);
                                strcpy(files[count], ent->d_name);
                                count++;
                            }
                        }
                    }
                    closedir(dir);


                    if (count > 0) {

                        printf("Available text files:\n");
                        for (int i = 0; i < count; ++i) {
                            printf("%d. %s\n", i + 1, files[i]);
                        }

                        int choiceFile;
                        printf("Enter the file number you want to select: ");
                        scanf("%d", &choiceFile);

                        FILE *file;
                        char full_path[256];
                        char *txtFile = files[choiceFile - 1];

                        strcpy(full_path, path);
                        strcat(full_path, "/");
                        strcat(full_path, txtFile);

//                        printf("\nfull path = %s\n", full_path);
//                        printf("choose file = %s\n\n", txtFile);

                        do {
                            printf("\n1 - Add data to file\n"
                                   "2 - Read data from file\n"
                                   "3 - Change data in file\n"
                                   "4 - Sorting data in file\n"
                                   "5 - Insert into file\n"
                                   "6 - Delete data in file\n"
                                   "7 - Back\n");
                            scanf("%d", &actionFile);

                            struct rec data_to_write;


                            switch (actionFile) {

                                case 1: {
                                    file = fopen(full_path, "a");

                                    printf("Enter name: ");
                                    scanf("%s", data_to_write.name);

                                    printf("Enter square: ");
                                    scanf("%d", &data_to_write.square);

                                    printf("Enter nas: ");
                                    scanf("%d", &data_to_write.nas);

                                    fprintf(file, "%s %d %d\n", data_to_write.name, data_to_write.square,
                                            data_to_write.nas);

                                    fclose(file);

                                    break;
                                }

                                case 2: {
                                    file = fopen(full_path, "r");
                                    struct rec data[MAX_ENTRIES];
                                    count = 0;

                                    while (fscanf(file, "%39s %d %d", data[count].name, &data[count].square,
                                                  &data[count].nas) == 3) {
                                        count++;
                                    }

                                    printf("Data read from the file:\n");
                                    for (int i = 0; i < count; ++i) {
                                        printf("Name: %s, Square: %d, Nas: %d\n", data[i].name, data[i].square,
                                               data[i].nas);
                                    }

                                    fclose(file);

                                    break;
                                }

                                case 3: {
                                    file = fopen(full_path, "r");
                                    int line_number, choice;
                                    count = 0;
                                    char new_name[40];
                                    struct rec data[MAX_ENTRIES];

                                    while (fscanf(file, "%39s %d %d", data[count].name, &data[count].square,
                                                  &data[count].nas) == 3) {
                                        count++;
                                    }

                                    fclose(file);

                                    printf("Current data:\n");
                                    for (int i = 0; i < count; ++i) {
                                        printf("%d. Name: %s, Square: %d, Nas: %d\n", i + 1, data[i].name,
                                               data[i].square, data[i].nas);
                                    }

                                    printf("Enter the line number to modify: ");
                                    scanf("%d", &line_number);

                                    if (line_number >= 1 && line_number <= count) {
                                        printf("What do you want to change?\n");
                                        printf("1. Name\n");
                                        printf("2. Square\n");
                                        printf("3. Nas\n");
                                        printf("Enter your choice: ");
                                        scanf("%d", &choice);

                                        // Apply changes based on user input
                                        switch (choice) {
                                            case 1:
                                                printf("Enter the new name: ");
                                                scanf("%s", new_name);
                                                strcpy(data[line_number - 1].name, new_name);
                                                break;
                                            case 2:
                                                printf("Enter the new square: ");
                                                scanf("%d", &data[line_number - 1].square);
                                                break;
                                            case 3:
                                                printf("Enter the new nas: ");
                                                scanf("%d", &data[line_number - 1].nas);
                                                break;
                                            default:
                                                printf("Invalid choice.\n");
                                                return 1;
                                        }


                                        file = fopen(full_path, "w");

                                        for (int i = 0; i < count; ++i) {
                                            fprintf(file, "%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                        }

                                        fclose(file);

                                        printf("Data modified and written back to the file successfully.\n");
                                    }else {
                                        printf("Invalid line number.\n");
                                    }


                                    break;
                                }

                                case 4: {
                                    struct rec data[MAX_ENTRIES]; // Масив для даних
                                    count = 0;
                                    int choice;

                                    // Відкрити файл у режимі читання
                                    file = fopen(full_path, "r");

                                    if (file == NULL) {
                                        printf("Не вдалося відкрити файл.\n");
                                        return 1;
                                    }

                                    while (fscanf(file, "%39s %d %d", data[count].name, &data[count].square, &data[count].nas) == 3) {
                                        count++;
                                    }

                                    fclose(file);

                                    printf("Поточні дані:\n");
                                    for (int i = 0; i < count; ++i) {
                                        printf("%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                    }

                                    printf("Виберіть поле для сортування:\n");
                                    printf("1. Назва області\n");
                                    printf("2. Площа\n");
                                    printf("3. Кількість населення\n");
                                    printf("Ваш вибір: ");
                                    scanf("%d", &choice);

                                    switch (choice) {
                                        case 1: {
                                            int order;
                                            printf("Виберіть напрямок сортування:\n");
                                            printf("1. Зростання\n");
                                            printf("2. Спадання\n");
                                            printf("Ваш вибір: ");
                                            scanf("%d", &order);

                                            switch (order) {
                                                case 1:
                                                    qsort(data, count, sizeof(struct rec), compare_name_asc);
                                                    break;
                                                case 2:
                                                    qsort(data, count, sizeof(struct rec), compare_name_desc);
                                                    break;
                                                default:
                                                    printf("Невірний вибір напрямку сортування.\n");
                                                    return 1;
                                            }
                                            break;
                                        }

                                        case 2: {
                                            int order;
                                            printf("Виберіть напрямок сортування:\n");
                                            printf("1. Зростання\n");
                                            printf("2. Спадання\n");
                                            printf("Ваш вибір: ");
                                            scanf("%d", &order);

                                            switch (order) {
                                                case 1:
                                                    qsort(data, count, sizeof(struct rec), compare_square_asc);
                                                    break;
                                                case 2:
                                                    qsort(data, count, sizeof(struct rec), compare_square_asc);
                                                    break;
                                                default:
                                                    printf("Невірний вибір напрямку сортування.\n");
                                                    return 1;
                                            }

                                            break;
                                        }

                                        case 3: {
                                            int order;
                                            printf("Виберіть напрямок сортування:\n");
                                            printf("1. Зростання\n");
                                            printf("2. Спадання\n");
                                            printf("Ваш вибір: ");
                                            scanf("%d", &order);

                                            switch (order) {
                                                case 1:
                                                    qsort(data, count, sizeof(struct rec), compare_nas_asc);
                                                    break;
                                                case 2:
                                                    qsort(data, count, sizeof(struct rec), compare_nas_desc);
                                                    break;
                                                default:
                                                    printf("Невірний вибір напрямку сортування.\n");
                                                    return 1;
                                            }

                                            break;
                                        }

                                        default:
                                            printf("Невірний вибір.\n");
                                            return 1;
                                    }

                                    // Відкрити файл у режимі запису, щоб записати впорядковані дані
                                    file = fopen(full_path, "w");

                                    if (file == NULL) {
                                        printf("Не вдалося відкрити файл.\n");
                                        return 1;
                                    }

                                    // Запис впорядкованих даних у файл
                                    for (int i = 0; i < count; ++i) {
                                        fprintf(file, "%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                    }

                                    // Закрити файл
                                    fclose(file);

                                    printf("Дані впорядковано і записано назад у файл успішно.\n");


                                    break;
                                }

                            }

                            for (int i = 0; i < count; ++i) {
                                free(files[i]);
                            }


                        } while (actionFile != 7);


                    } else {
                        printf("Could not open directory.\n");
                    }

                }

                break;
            }


        }

    } while (fileChoice != 4);

    return 1;
}