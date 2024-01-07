#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#define MAX_FILES 100
#define MAX_ENTRIES 100
#define MAX_LINES 1000
#define MAX_RECORDS 100
#define MAX_NAME_LENGTH 40

struct rec {
    char name[40];
    int square;
    int nas;
};

struct sort {
    char sortingMethod[40];
    char sortingWay[40];
};
//char *tempFilePath = "/home/Works-KPI/Proga/Laba1.9/temp.txt";
//char *path = "/home/Works-KPI/Proga/Laba1.9/data";

char path[100] = "/home/Works-KPI/Proga/Laba1.9/data";

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

void printData(char full_path[100]){
    char line[100];
    struct rec records[MAX_RECORDS];
    struct sort sorting;
    int rec_count = 0;

    FILE *file = fopen(full_path, "r"); // Replace "your_file.txt" with your file path

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "|") != NULL) {
            sscanf(line, "%39[^|]|%39s", sorting.sortingMethod, sorting.sortingWay);
        } else {
            sscanf(line, "%39s %d %d", records[rec_count].name, &records[rec_count].square, &records[rec_count].nas);
            rec_count++;
        }
    }

    fclose(file);

    printf("Sorting method: %s\n", sorting.sortingMethod);
    printf("Sorting way: %s\n", sorting.sortingWay);

    printf("Rec records:\n");
    for (int i = 0; i < rec_count; ++i) {
        printf("%d. ", i + 1);
        printf("%s %d %d\n", records[i].name, records[i].square, records[i].nas);
    }
}
void displayRecords(struct rec data[], int count) {
    printf("Records:\n");
    for (int i = 0; i < count; ++i) {
        printf("%d. %s %d %d\n", i + 1, data[i].name, data[i].square, data[i].nas);
    }
}

void s(char full_path[100]) {
    FILE *file = fopen(full_path, "r+");

    struct sort sorting;
    char lineSort[100];
    if (fgets(lineSort, sizeof(lineSort), file) != NULL) {
        sscanf(lineSort, "%39[^|]|%39s", sorting.sortingMethod, sorting.sortingWay);
    } else {
        printf("Invalid format in the file.\n");
        fclose(file);
        return;
    }

    struct rec data[MAX_ENTRIES];
    int count = 0;

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "|") == NULL) {
            sscanf(line, "%39s %d %d", data[count].name, &data[count].square, &data[count].nas);
            count++;
        }
    }

    printf("\nSorting method: %s\n", sorting.sortingMethod);
    printf("Sorting way: %s\n", sorting.sortingWay);

    if (strcmp(sorting.sortingMethod, "name") == 0) {
        if (strcmp(sorting.sortingWay, "asc") == 0) {
            qsort(data, count, sizeof(struct rec), compare_name_asc);
        } else if (strcmp(sorting.sortingWay, "desc") == 0) {
            qsort(data, count, sizeof(struct rec), compare_name_desc);
        }
    } else if (strcmp(sorting.sortingMethod, "square") == 0) {
        if (strcmp(sorting.sortingWay, "asc") == 0) {
            qsort(data, count, sizeof(struct rec), compare_square_asc);
        } else if (strcmp(sorting.sortingWay, "desc") == 0) {
            qsort(data, count, sizeof(struct rec), compare_square_desc);
        }
    } else if (strcmp(sorting.sortingMethod, "nas") == 0) {
        if (strcmp(sorting.sortingWay, "asc") == 0) {
            qsort(data, count, sizeof(struct rec), compare_nas_asc);
        } else if (strcmp(sorting.sortingWay, "desc") == 0) {
            qsort(data, count, sizeof(struct rec), compare_nas_desc);
        }
    } else {
        printf("Invalid sorting method or way.\n");
        return;
    }

    rewind(file);
    fprintf(file, "%s|%s\n", sorting.sortingMethod, sorting.sortingWay);
    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s %d %d\n", data[i].name, data[i].square, data[i].nas);
    }

    fclose(file);
    printf("\nData sorted and written back to the file successfully.\n");
}

void SortDataByNas(char full_path[100]) {
    FILE *file = fopen(full_path, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    char lineSort[100];
    if (fgets(lineSort, sizeof(lineSort), file) == NULL) {
        printf("Invalid format in the file.\n");
        fclose(file);
        return;
    }

    struct rec data[MAX_ENTRIES];
    int count = 0;

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "|") == NULL) {
            sscanf(line, "%39s %d %d", data[count].name, &data[count].square, &data[count].nas);
            count++;
        }
    }

    printf("\nData read from the file successfully.\n");

    printf("\nSorting by nas ascending order:\n");
    qsort(data, count, sizeof(struct rec), compare_nas_asc);
    for (int i = 0; i < count; ++i) {
        printf("%s %d %d\n", data[i].name, data[i].square, data[i].nas);
    }

    fclose(file);
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

                    ///////////////////////////////////////////////////////////// Sorting

                    struct sort sorting;

                    strcpy(sorting.sortingMethod, "NULL");
                    strcpy(sorting.sortingWay, "NULL");

                    file = fopen(filepath, "a");
                    fprintf(file, "%s|%s\n", sorting.sortingMethod, sorting.sortingWay);


                    fclose(file);

                    printf("Data added to the file successfully.\n");

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

                        SortDataByNas(full_path);

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

                                    printData(full_path);

                                    break;
                                }

                                case 3: {
                                    file = fopen(full_path, "r+");

                                    struct rec data[MAX_ENTRIES];
                                    struct sort sorting;
                                    count = 0;

                                    char line[100];
                                    while (fgets(line, sizeof(line), file) != NULL) {
                                        if (strstr(line, "|") != NULL) {
                                            sscanf(line, "%39[^|]|%39s", sorting.sortingMethod, sorting.sortingWay);
                                        } else {
                                            sscanf(line, "%39s %d %d", data[count].name, &data[count].square, &data[count].nas);
                                            count++;
                                        }
                                    }

                                    fclose(file);

                                    printf("Current data:\n");
                                    displayRecords(data, count);

                                    int choice, recordNum;
                                    printf("\nEnter the record number to modify (1-%d): ", count);
                                    scanf("%d", &recordNum);

                                    if (recordNum >= 1 && recordNum <= count) {
                                        printf("Choose what to change for record %d:\n", recordNum);
                                        printf("1. Name\n");
                                        printf("2. Square\n");
                                        printf("3. Nas\n");
                                        printf("Enter your choice: ");
                                        scanf("%d", &choice);

                                        switch (choice) {
                                            case 1:
                                                printf("Enter new name: ");
                                                scanf("%s", data[recordNum - 1].name);
                                                break;
                                            case 2:
                                                printf("Enter new square: ");
                                                scanf("%d", &data[recordNum - 1].square);
                                                break;
                                            case 3:
                                                printf("Enter new nas: ");
                                                scanf("%d", &data[recordNum - 1].nas);
                                                break;
                                            default:
                                                printf("Invalid choice.\n");
                                                return 1;
                                        }

                                        file = fopen(full_path, "w");
                                        if (file == NULL) {
                                            printf("Failed to open the file.\n");
                                            return 1;
                                        }

                                        fprintf(file, "%s|%s\n", sorting.sortingMethod, sorting.sortingWay);
                                        for (int i = 0; i < count; ++i) {
                                            fprintf(file, "%s %d %d\n", data[i].name, data[i].square, data[i].nas);
                                        }

                                        fclose(file);

                                        printf("Data modified and written back to the file successfully.\n");
                                    } else {
                                        printf("Invalid record number.\n");
                                    }



                                    break;
                                }

                                case 4: {
                                    file = fopen(full_path, "r+");
                                    struct sort sorting;

                                    printf("Current data:\n");
                                    printData(full_path);

                                    int choice;
                                    printf("Choose a field for sorting:\n");
                                    printf("1. Name of the region\n");
                                    printf("2. Square\n");
                                    printf("3. Population\n");
                                    printf("Your choice: ");
                                    scanf("%d", &choice);

                                    char line[100];
                                    if (fgets(line, sizeof(line), file) != NULL) {
                                        sscanf(line, "%39[^|]|%39s", sorting.sortingMethod, sorting.sortingWay);

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
                                                        strcpy(sorting.sortingMethod, "name");
                                                        strcpy(sorting.sortingWay, "asc");
                                                        break;
                                                    case 2:
                                                        strcpy(sorting.sortingMethod, "name");
                                                        strcpy(sorting.sortingWay, "desc");
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
                                                        strcpy(sorting.sortingMethod, "square");
                                                        strcpy(sorting.sortingWay, "asc");
                                                        break;
                                                    case 2:
                                                        strcpy(sorting.sortingMethod, "square");
                                                        strcpy(sorting.sortingWay, "desc");
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
                                                        strcpy(sorting.sortingMethod, "nas");
                                                        strcpy(sorting.sortingWay, "asc");
                                                        break;
                                                    case 2:
                                                        strcpy(sorting.sortingMethod, "nas");
                                                        strcpy(sorting.sortingWay, "desc");
                                                        break;
                                                    default:
                                                        printf("Invalid sorting order choice.\n");
                                                        break;
                                                }

                                                break;
                                            }

                                            default:
                                                printf("Invalid choice.\n");
                                                break;
                                        }

                                        fseek(file, 0, SEEK_SET);

                                        fprintf(file, "%s|%s\n", sorting.sortingMethod, sorting.sortingWay);

                                        fclose(file);
                                    }



                                    s(full_path);



                                    break;
                                }

                                case 5: {
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