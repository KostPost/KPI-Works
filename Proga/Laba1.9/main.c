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

struct sort {
    char sortingMethod[40];
    char sortingWay[40];
};

char *path = "/home/kostpost/KPI-Works/Proga/Laba1.9/data";

int compare_name_asc(const void *a, const void *b) {
    return strcmp(((struct rec *) a)->name, ((struct rec *) b)->name);
}

int compare_name_desc(const void *a, const void *b) {
    return strcmp(((struct rec *) b)->name, ((struct rec *) a)->name); // Reverse order
}

int compare_square_desc(const void *a, const void *b) {
    return ((struct rec *) b)->square - ((struct rec *) a)->square; // descending order
}

int compare_square_asc(const void *a, const void *b) {
    return ((struct rec *) a)->square - ((struct rec *) b)->square;
}

int compare_nas_desc(const void *a, const void *b) {
    return ((struct rec *) b)->nas - ((struct rec *) a)->nas;
}

int compare_nas_asc(const void *a, const void *b) {
    return ((struct rec *) a)->nas - ((struct rec *) b)->nas; // ascending order (reverse)
}

void printAllData(char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct sort sorting;
    fscanf(file, "%39s %39s", sorting.sortingMethod, sorting.sortingWay);
    printf("Sorting Method: %s, Sorting Way: %s\n", sorting.sortingMethod, sorting.sortingWay);

    int max_records = 100;
    struct rec records[max_records];
    int count = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) && count < max_records) {
        if (sscanf(line, "%s %d %d", records[count].name, &records[count].square, &records[count].nas) == 3) {
            count++;
        }
    }

    fclose(file);

    for (int i = 0; i < count; i++) {
        printf("Name: %s\tSquare: %d\tNas: %d\n", records[i].name, records[i].square, records[i].nas);
    }
}

void displayRecords(struct rec data[], int count) {
    printf("Records:\n");
    for (int i = 0; i < count; ++i) {
        printf("%d. %s %d %d\n", i + 1, data[i].name, data[i].square, data[i].nas);
    }
}

void changeDataSort(char *file_path, struct sort newData) {
    FILE *inputFile, *tempFile;
    char line[100];

    inputFile = fopen(file_path, "r");
    if (inputFile == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    tempFile = fopen("temp_file.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(inputFile);
        return;
    }

    fprintf(tempFile, "%s %s\n", newData.sortingMethod, newData.sortingWay);

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        fprintf(tempFile, "%s", line);
    }

    fclose(inputFile);
    fclose(tempFile);

    remove(file_path);
    rename("temp_file.txt", file_path);

    printf("Sorting information updated successfully.\n");

    FILE *outputFile;
    int lineNumber = 0;

    inputFile = fopen(file_path, "r");
    if (inputFile == NULL) {
        printf("Error opening the file for reading.\n");
        return;
    }

    outputFile = fopen("temp_file.txt", "w");
    if (outputFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(inputFile);
        return;
    }

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        lineNumber++;
        if (lineNumber != 2) {
            fprintf(outputFile, "%s", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    remove(file_path);
    rename("temp_file.txt", file_path);

    printf("Second line deleted successfully.\n");
}

void sortDataRec(char *file_path) {
    FILE *file;
    struct sort sorting;
    file = fopen(file_path, "r");
    fscanf(file, "%39s %39s", sorting.sortingMethod, sorting.sortingWay);
    fclose(file);


    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        return;
    }

    int max_records = 100;
    struct rec records[max_records];
    int count = 0;
    char line[100];

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && count < max_records) {
        sscanf(line, "%s %d %d", records[count].name, &records[count].square, &records[count].nas);
        count++;
    }

    fclose(file);

    if (strcmp(sorting.sortingMethod, "name") == 0) {
        if (strcmp(sorting.sortingWay, "asc") == 0) {
            qsort(records, count, sizeof(struct rec), compare_name_asc);
        } else if (strcmp(sorting.sortingWay, "desc") == 0) {
            qsort(records, count, sizeof(struct rec), compare_name_desc);
        }
    } else if (strcmp(sorting.sortingMethod, "square") == 0) {
        if (strcmp(sorting.sortingWay, "asc") == 0) {
            qsort(records, count, sizeof(struct rec), compare_square_asc);
        } else if (strcmp(sorting.sortingWay, "desc") == 0) {
            qsort(records, count, sizeof(struct rec), compare_square_desc);
        }
    } else if (strcmp(sorting.sortingMethod, "nas") == 0) {
        if (strcmp(sorting.sortingWay, "asc") == 0) {
            qsort(records, count, sizeof(struct rec), compare_nas_asc);
        } else if (strcmp(sorting.sortingWay, "desc") == 0) {
            qsort(records, count, sizeof(struct rec), compare_nas_desc);
        }
    } else {
        printf("Invalid records method or way.\n");
        return;
    }

    FILE *temp_file = fopen("temp_file.txt", "w");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        return;
    }

    fprintf(temp_file, "%s %s\n", sorting.sortingMethod, sorting.sortingWay);
    for (int i = 0; i < count; i++) {
        fprintf(temp_file, "%s %d %d\n", records[i].name, records[i].square, records[i].nas);
    }
    fclose(temp_file);

    remove(file_path);
    rename("temp_file.txt", file_path);
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

                    file = fopen(filepath, "w");
                    struct sort data;
                    strcpy(data.sortingMethod, "-");
                    strcpy(data.sortingWay, "-");

                    fprintf(file, "%s %s\n", data.sortingMethod, data.sortingWay);

                    fclose(file);
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
                        int i = 0;
                        for (; i < count; ++i) {
                            printf("%d. %s\n", i + 1, files[i]);
                        }
                        int choiceFile;
                        do {
                            printf("Enter the file number you want to select: ");
                            scanf("%d", &choiceFile);
                        } while (choiceFile < 1 || choiceFile > i);

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

                                   printAllData(full_path);

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
                                            sscanf(line, "%39s %d %d", data[count].name, &data[count].square,
                                                   &data[count].nas);
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
                                    printAllData(full_path);

                                    int choice;
                                    printf("Choose a field for sorting:\n");
                                    printf("1. Name of the region\n");
                                    printf("2. Square\n");
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
                                    changeDataSort(full_path, sorting);

                                    fclose(file);

                                    sortDataRec(full_path);

                                    break;
                                }

                                case 5: {
                                    struct sort sorting;
                                    file = fopen(full_path, "r");
                                    fscanf(file, "%39s %39s", sorting.sortingMethod, sorting.sortingWay);
                                    fclose(file);

                                    if (strcmp(sorting.sortingMethod, "-") == 0) {
                                        printf("\nSorting Method is an empty string.\nPlease sort file before insert data\n");
                                        break;
                                    }

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

                                    sortDataRec(full_path);


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
                    perror("Failed to open directory");
                    return EXIT_FAILURE;
                }

                printf("Available files:\n");
                int file_count = 0;
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_type == DT_REG) {  // Check if it's a file
                        file_count++;
                        printf("%d. %s\n", file_count, entry->d_name);
                    }
                }
                closedir(dir);

                printf("Select the file to delete (enter the number): ");
                scanf("%d", &choice);

                dir = opendir(path);
                if (dir == NULL) {
                    perror("Failed to open directory");
                    return EXIT_FAILURE;
                }

                file_count = 0;
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_type == DT_REG) {
                        file_count++;
                        if (file_count == choice) {
                            char filepath[100];
                            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
                            if (remove(filepath) != 0) {
                                perror("Error deleting the file");
                                return EXIT_FAILURE;
                            }
                            printf("The file \"%s\" has been successfully deleted.\n", entry->d_name);
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