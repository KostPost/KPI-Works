#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#define MAX_FILES 100
#define MAX_ENTRIES 100
#define MAX_LINES 1000

struct rec {
    char name[40];
    int square;
    int nas;
};
char *tempFilePath = "/home/Works-KPI/Proga/Laba1.9/temp.txt";
char *path = "/home/Works-KPI/Proga/Laba1.9/data";

int compare_name_asc(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *) a;
    struct rec *rec2 = (struct rec *) b;
    return strcmp(rec1->name, rec2->name); // Сортування за назвою області у зростаючому порядку
}
int compare_name_desc(const void *a, const void *b) {
    return -compare_name_asc(a, b); // Сортування за назвою області у спадаючому порядку
}

int compare_square_asc(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *) a;
    struct rec *rec2 = (struct rec *) b;
    return rec1->square - rec2->square; // Сортування за площею у зростаючому порядку
}
int compare_square_desc(const void *a, const void *b) {
    return -compare_square_asc(a, b); // Сортування за площею у спадаючому порядку
}

int compare_nas_asc(const void *a, const void *b) {
    struct rec *rec1 = (struct rec *) a;
    struct rec *rec2 = (struct rec *) b;
    return rec1->nas - rec2->nas; // Сортування за кількістю населення у зростаючому порядку
}
int compare_nas_desc(const void *a, const void *b) {
    return -compare_nas_asc(a, b); // Сортування за кількістю населення у спадаючому порядку
}


int compareFiles(const char *file1, const char *file2) {
    FILE *fptr1, *fptr2;
    char c1, c2;

    fptr1 = fopen(file1, "r");
    fptr2 = fopen(file2, "r");

    if (fptr1 == NULL || fptr2 == NULL) {
        printf("Ошибка открытия файлов.\n");
        return -1; // Ошибка открытия файлов
    }

    do {
        c1 = fgetc(fptr1);
        c2 = fgetc(fptr2);

        if (c1 != c2) {
            fclose(fptr1);
            fclose(fptr2);
            return 0; // Файлы имеют различное содержимое
        }
    } while (c1 != EOF && c2 != EOF);

    fclose(fptr1);
    fclose(fptr2);

    if (c1 == EOF && c2 == EOF) {
        return 1; // Файлы имеют одинаковое содержимое
    } else {
        return 0; // Файлы имеют различное содержимое
    }
}
char* insertInFile(const char *sourceFile) {
    struct rec data[MAX_ENTRIES];

    //qsort(data, count, sizeof(struct rec), compare_name_asc);
    FILE *tempFile = fopen(tempFilePath, "r");
    int count = 0;
    while (fscanf(tempFile, "%39s %d %d", data[count].name, &data[count].square, &data[count].nas) == 3) {
        count++;
    }

    for (int i = 0; i < 6; i++) {
        int result = 0;
        char* methodSort;


        if(i == 0) {
            qsort(data, count, sizeof(struct rec), compare_square_asc);
            result = compareFiles(sourceFile, tempFilePath);
            methodSort = "площа зростання";
        }
        else if(i == 1) {
            qsort(data, count, sizeof(struct rec), compare_square_desc);
            result = compareFiles(sourceFile, tempFilePath);
            methodSort = "площа спадання";
        }

        else if(i == 2) {
            qsort(data, count, sizeof(struct rec), compare_nas_asc);
            result = compareFiles(sourceFile, tempFilePath);
            methodSort = "населення зростання";
        }
        else if(i == 3) {
            qsort(data, count, sizeof(struct rec), compare_nas_desc);
            result = compareFiles(sourceFile, tempFilePath);
            methodSort = "населення спадання";
        }

        else if(i == 4) {
            qsort(data, count, sizeof(struct rec), compare_name_asc);
            result = compareFiles(sourceFile, tempFilePath);
            methodSort = "назва зростання";
        }
        else if(i == 5) {
            qsort(data, count, sizeof(struct rec), compare_name_desc);
            result = compareFiles(sourceFile, tempFilePath);
            methodSort = "назва спадання";
        }


        if (result == 1) {
            return methodSort;
        } else {
            printf("Файлы имеют различное содержимое.\n");
        }
    }

    return "-";
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

                        char full_path[256];
                        char *txtFile = files[choiceFile - 1];

                        strcpy(full_path, path);
                        strcat(full_path, "/");
                        strcat(full_path, txtFile);

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
                                    } else {
                                        printf("Invalid line number.\n");
                                    }


                                    break;
                                }

                                case 4: {
                                    struct rec data[MAX_ENTRIES];
                                    count = 0;
                                    int choice;

                                    file = fopen(full_path, "r");

                                    while (fscanf(file, "%39s %d %d", data[count].name, &data[count].square,
                                                  &data[count].nas) == 3) {
                                        count++;
                                    }

                                    fclose(file);

                                    printf("Current data:\n");
                                    for (int i = 0; i < count; ++i) {
                                        printf("%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                    }

                                    printf("Choose a field for sorting:\n");
                                    printf("1. Name of the region\n");
                                    printf("2. Area\n");
                                    printf("3. Population\n");
                                    printf("Your choice: ");
                                    scanf("%d", &choice);

                                    switch (choice) {
                                        case 1: {
                                            int order;
                                            printf("Select the sorting order:\n");
                                            printf("1. Ascending\n");
                                            printf("2. Descending\n");
                                            printf("Your choice: ");
                                            scanf("%d", &order);

                                            switch (order) {
                                                case 1:
                                                    qsort(data, count, sizeof(struct rec), compare_name_asc);
                                                    break;
                                                case 2:
                                                    qsort(data, count, sizeof(struct rec), compare_name_desc);
                                                    break;
                                                default:
                                                    printf("Invalid sorting order choice.\n");
                                                    break;
                                            }
                                            break;
                                        }

                                        case 2: {
                                            int order;
                                            printf("Select the sorting order:\n");
                                            printf("1. Ascending\n");
                                            printf("2. Descending\n");
                                            printf("Your choice: ");
                                            scanf("%d", &order);

                                            switch (order) {
                                                case 1:
                                                    qsort(data, count, sizeof(struct rec), compare_square_asc);
                                                    break;
                                                case 2:
                                                    qsort(data, count, sizeof(struct rec), compare_square_desc);
                                                    break;
                                                default:
                                                    printf("Invalid sorting order choice.\n");
                                                    break;
                                            }

                                            break;
                                        }

                                        case 3: {
                                            int order;
                                            printf("Select the sorting order:\n");
                                            printf("1. Ascending\n");
                                            printf("2. Descending\n");
                                            printf("Your choice: ");
                                            scanf("%d", &order);

                                            switch (order) {
                                                case 1:
                                                    qsort(data, count, sizeof(struct rec), compare_nas_asc);
                                                    break;
                                                case 2:
                                                    qsort(data, count, sizeof(struct rec), compare_nas_desc);
                                                    break;
                                                default:
                                                    printf("Invalid sorting order choice.\n");
                                                    break;
                                            }

                                            break;
                                        }

                                        default:
                                            printf("Invalid choice.\n");
                                            return 1;
                                    }

                                    file = fopen(full_path, "w");

                                    if (file == NULL) {
                                        printf("Failed to open the file.\n");
                                        break;
                                    }

                                    for (int i = 0; i < count; ++i) {
                                        fprintf(file, "%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                    }

                                    fclose(file);

                                    printf("Data sorted and written back to the file successfully.\n");

                                    break;
                                }

                                case 5: {
                                    const char *sourceFile = full_path;
                                    const char *tempFile = "/home/Works-KPI/Proga/Laba1.9/temp.txt";

                                    FILE *source, *destination;
                                    char ch;

                                    source = fopen(sourceFile, "r");
                                    if (source == NULL) {
                                        printf("Error opening file %s\n", sourceFile);
                                        break;
                                    }

                                    destination = fopen(tempFile, "w");
                                    if (destination == NULL) {
                                        fclose(source);
                                        printf("Error opening file %s\n", tempFile);
                                        break;
                                    }


                                    while ((ch = fgetc(source)) != EOF) {
                                        fputc(ch, destination);
                                    }

                                    printf("Content from %s successfully copied to %s\n", sourceFile, tempFile);

                                    fclose(source);
                                    fclose(destination);

                                    char *methodSort = insertInFile(sourceFile);
                                    printf("\n\n%s\n\n", methodSort);

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

                                    struct rec data[MAX_ENTRIES];
                                    count = 0;

                                    while (fscanf(file, "%s %d %d", data[count].name, &data[count].square,
                                                  &data[count].nas) == 3) {
                                        count++;
                                    }

                                    file = fopen(full_path, "r");
                                    while (fscanf(file, "%39s %d %d", data[count].name, &data[count].square,
                                                  &data[count].nas) == 3) {
                                        count++;
                                    }
                                    fclose(file);

                                    if (strcmp(methodSort, "площа зростання") == 0) {
                                        qsort(data, count, sizeof(struct rec), compare_square_asc);
                                    } else if (strcmp(methodSort, "площа спадання") == 0) {
                                        qsort(data, count, sizeof(struct rec), compare_square_desc);
                                    } else if (strcmp(methodSort, "населення зростання") == 0) {
                                        qsort(data, count, sizeof(struct rec), compare_nas_asc);
                                    } else if (strcmp(methodSort, "населення спадання") == 0) {
                                        qsort(data, count, sizeof(struct rec), compare_nas_desc);
                                    } else if (strcmp(methodSort, "назва зростання") == 0) {
                                        qsort(data, count, sizeof(struct rec), compare_name_asc);
                                    } else if (strcmp(methodSort, "назва спадання\"") == 0) {
                                        qsort(data, count, sizeof(struct rec), compare_name_desc);
                                    }

                                    file = fopen(full_path, "w");

                                    if (file == NULL) {
                                        printf("Failed to open the file.\n");
                                        break;
                                    }
                                    for (int i = 0; i < count; ++i) {
                                        fprintf(file, "%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                    }

                                    fclose(file);
                                    printf("Data sorted and written back to the file successfully.\n");

                                    break;
                                }

                                case 6: {
                                    struct rec records[MAX_LINES];
                                    count = 0;
                                    int choice, i;

                                    file = fopen(full_path, "r");
                                    if (file == NULL) {
                                        printf("Failed to open the file.\n");
                                        break;
                                    }

                                    while (fscanf(file, "%39s %d %d", records[count].name, &records[count].square,
                                                  &records[count].nas) == 3) {
                                        count++;
                                    }

                                    fclose(file);

                                    printf("Available lines in the file:\n");
                                    for (i = 0; i < count; ++i) {
                                        printf("%d. %s %d %d\n", i + 1, records[i].name, records[i].square,
                                               records[i].nas);
                                    }

                                    printf("Select the line number to delete: ");
                                    scanf("%d", &choice);

                                    if (choice < 1 || choice > count) {
                                        printf("Invalid line number.\n");
                                        break;
                                    }

                                    for (i = choice - 1; i < count - 1; ++i) {
                                        records[i] = records[i + 1];
                                    }
                                    count--;

                                    file = fopen(full_path, "w");
                                    if (file == NULL) {
                                        printf("Failed to open the file for writing.\n");
                                        return 1;
                                    }
                                    for (i = 0; i < count; ++i) {
                                        fprintf(file, "%s %d %d\n", records[i].name, records[i].square, records[i].nas);
                                    }
                                    fclose(file);

                                    printf("The line has been successfully deleted.\n");

                                    break;
                                }

                            }

                        } while (actionFile != 7);


                    } else {
                        printf("Could not open directory.\n");
                    }

                }

                break;
            }

            case 3: {
                DIR *dir;
                int choice;

                dir = opendir(path);
                if (dir == NULL) {
                    perror("Не вдалося відкрити папку");
                    return EXIT_FAILURE;
                }

                printf("Доступні файли:\n");
                int file_count = 0;
                // Виведення усіх файлів у директорії з номерами
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_type == DT_REG) {  // Перевірка, що це файл
                        file_count++;
                        printf("%d. %s\n", file_count, entry->d_name);
                    }
                }
                closedir(dir);

                printf("Виберіть файл, який потрібно видалити (введіть номер): ");
                scanf("%d", &choice);

                // Повторне відкриття директорії
                dir = opendir(path);
                if (dir == NULL) {
                    perror("Не вдалося відкрити папку");
                    return EXIT_FAILURE;
                }

                file_count = 0;
                // Знаходження обраного файлу за номером
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_type == DT_REG) {
                        file_count++;
                        if (file_count == choice) {
                            char filepath[100];  // Шлях до файлу
                            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
                            // Видалення файлу
                            if (remove(filepath) != 0) {
                                perror("Помилка видалення файлу");
                                return EXIT_FAILURE;
                            }
                            printf("Файл \"%s\" був успішно видалений.\n", entry->d_name);
                            break;
                        }
                    }
                }
                closedir(dir);

                break;
            }


        }

    } while (fileChoice != 4);


    return 1;
}