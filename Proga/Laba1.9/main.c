#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

struct rec {
    char name[40];
    int square;
    int nas;
};

//char folderPath[256] = "/home/KPI-Works/Proga/Laba1.9/data";
char *path = "/home/KPI-Works/Proga/Laba1.9/data";

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

    seeAllFiles();
    int choice, fileChoice, recordsChoice;

    do {
        printf("1 - Files\n2 - Records\n3 - Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                FILE *file;
                DIR *directory = opendir(path);
                struct dirent *entry;

                printf("1 - Create\n2 - Read\n3 - Delete\n");
                scanf("%d", &fileChoice);

                switch (fileChoice) {

                    case 1: {
                        bool isExist = false;

                        char filename[100];
                        printf("Enter a file name to create");
                        scanf("%99s",filename);

                        while ((entry = readdir(directory)) != NULL) {
                            if (strcmp(entry->d_name, filename) == 0) {
                                printf("File '%s' found in directory '%s'\n", filename, path);
                                isExist = true;
                                closedir(directory);
                                break;
                            }
                        }

                        if (!isExist) {
                            char filepath[100];
                            snprintf(filepath, sizeof(filepath), "%s/%s", path, filename);

                            // Create the file
                            file = fopen(filepath, "w");

                            if (file == NULL) {
                                perror("Unable to create the file");
                                return 1;
                            }

                            fflush(file); // Flush the content to the file immediately

                            fclose(file);
                            printf("File created: %s\n", filepath);
                        } else {
                            printf("File already exist");
                        }


                        break;
                    }

                }


                break;
            }

            case 2: {


                break;
            }

            default: {
                if (choice != 3) {

                }
                break;
            }
        }


    } while (choice != 3);

    return 1;
}



