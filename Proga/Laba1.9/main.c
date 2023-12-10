#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

struct rec
{
    char name[40];
    int square;
    int nas;
};

char folderPath[256] = "D:\\Proga\\LabaKPI\\Laba1.9\\data";

int listTxtFiles(char (*file_list)[100], int file_count) {
    DIR *dir = opendir(folderPath);

    if (dir == NULL) {
        perror("opendir");
    }

    struct dirent *entry;


    // List .txt files and add their names to the array
    while ((entry = readdir(dir)) != NULL) {
        long DT_REG = 0;
        if (entry->d_ino == DT_REG && strstr(entry->d_name, ".txt") != NULL) {
            snprintf(file_list[file_count], sizeof(file_list[file_count]), "%s", entry->d_name);
            file_count++;
        }
    }

    closedir(dir);
    return file_count;
}

int main(){

    long action = 0, fileAction = 0;
    int working = 1;




    char filename[256];


    do {
        printf("\n1 - File\n2 - Records\n3 - Exit\nAction:");
        scanf("%ld", &action);


        switch (action) {


            case 1: {

                do {
                    working = 1;
                    printf("\n1 - Create\n2 - Read\n3 - Delete\n4 - go Back\nAction:");
                    scanf("%ld", &fileAction);

                    switch (fileAction) {

                        case 1: {

                            printf("\nEnter the name of the text file (e.g., yourfile.txt): ");
                            if (scanf("%255s", filename) != 1) {
                                printf("Invalid input.\n");
                                return 1;
                            }

                            char fullFilePath[512];
                            snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", folderPath, filename);
                            FILE *file;
                            file = fopen(fullFilePath, "w");


//                        if (file == NULL) {
//                            printf("Error creating the file!\n");
//                            return 1;
//                        }
//
//                        struct rec data;
//
//                        printf("Enter data:\n");
//                        printf("Name:");
//                        scanf("%39s", data.name);
//                        printf("Square:");
//                        scanf("%d", &data.square);
//                        printf("Nas:");
//                        scanf("%d", &data.nas);
//
//                        fprintf(file, "%s %d %d\n", data.name, data.square, data.nas);
                            fclose(file);

                            break;
                        }

                        case 2: {

                            printf("Text files in the directory:\n");

                            char file_list[100][100];
                            int file_count = 0;
                            file_count = listTxtFiles(file_list, file_count);


                            for (int i = 0; i < file_count; i++) {
                                printf("\n");
                                printf("%d - %s", i + 1, file_list[i]);
                            }

                            //printf("\n%d\n",file_count);

                            int choice;
                            printf("\nEnter the number of the file to read data (1-%d):", file_count);
                            scanf("%d", &choice);

                            if (choice < 1 || choice > file_count) {
                                printf("Invalid choice.\n");
                                break;
                            }

                            // printf("\n%s",file_list[choice - 1]);

                            FILE *file;

                            struct rec data;
                            char file_to_read[100];
                            char line[100];


                            snprintf(file_to_read, sizeof(file_to_read), "%s/%s", folderPath, file_list[choice - 1]);

                            //printf("%s",file_to_read);


                            file = fopen(file_to_read, "r");

                            printf("\n");

                            if (file == NULL) {
                                perror("fopen");
                                return 1;
                            }

                            while (fscanf(file, "%39s %d %d", data.name, &data.square, &data.nas) == 3) {
                                printf("Name: %s, Square: %d, Nas: %d\n", data.name, data.square, data.nas);
                            }

                            fclose(file);

                            break;
                        }

                        case 3: {

                            printf("Text files in the directory:\n");


                            struct dirent *entry;
                            int file_count = 0;
                            char file_list[100][100];

                            DIR *dir = opendir(folderPath);
                            while ((entry = readdir(dir)) != NULL) {
                                char file_path[256];
                                snprintf(file_path, sizeof(file_path), "%s/%s", folderPath, entry->d_name);

                                struct stat file_stat;
                                if (stat(file_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode) &&
                                    strstr(entry->d_name, ".txt")) {
                                    printf("%d. %s\n", ++file_count, entry->d_name);
                                    strcpy(file_list[file_count - 1], entry->d_name);
                                }
                            }

                            if (file_count == 0) {
                                printf("No text files found in the directory.\n");
                                break;
                            }

                            int choice;
                            printf("Enter the number of the file to delete (1-%d): ", file_count);
                            scanf("%d", &choice);

                            if (choice < 1 || choice > file_count) {
                                printf("Invalid choice.\n");
                                break;
                            }

                            char file_to_delete[100];
                            snprintf(file_to_delete, sizeof(file_to_delete), "%s/%s", folderPath,
                                     file_list[choice - 1]);

                            // Attempt to delete the chosen file
                            if (remove(file_to_delete) == 0) {
                                printf("File '%s' has been deleted successfully.\n", file_to_delete);
                            } else {
                                printf("Unable to delete file '%s'.\n", file_to_delete);
                            }
                            closedir(dir);

                            break;
                        }

                        case 4:
                            action = 3;
                            break;
                    }
                } while (fileAction != 4);
            }

                break;


            case 2:{

                int action2 = 0;
                do {
                    printf("1 - Create records\n2 - Read data\n3 - Change data\n4 - Sort\n5 - ??\n6 - Delete data\n7 - Back\nAction:");
                    scanf("%d", &action2);

                    switch (action2) {

                        case 1:{
                            char file_list[100][100];
                            int file_count = 0;
                            file_count = listTxtFiles(file_list,file_count);

                            for(int i = 0; i < file_count; i++){
                                printf("\n");
                                printf("%s",file_list[i]);
                            }

                            int choice;
                            printf("\nEnter the number of the file to add data (1-%d):", file_count);
                            scanf("%d", &choice);

                            if (choice < 1 || choice > file_count) {
                                printf("Invalid choice.\n");
                                break;
                            }

                            char file_add_data[100];
                            snprintf(file_add_data, sizeof(file_add_data), "%s/%s", folderPath, file_list[choice - 1]);

                            FILE *file;
                            file = fopen(file_add_data, "w");

                            struct rec data;

                            printf("Enter data:\n");
                            printf("Name:");
                            scanf("%39s", data.name);
                            printf("Square:");
                            scanf("%d", &data.square);
                            printf("Nas:");
                            scanf("%d", &data.nas);

                            fprintf(file, "%s %d %d\n", data.name, data.square, data.nas);
                            fclose(file);
                        }



                    }
                } while (action2 != 7);


            }

            case 3:{
                return 0;
            }



        }

    } while (1);


   // fclose(file);
    return 1;

}







//int main() {
//    char directory_path[] = "D:\\Proga\\LabaKPI\\Laba1.9\\data";
//    char files[100][100];
//    int file_count;
//
//    listTextFiles(directory_path, files, &file_count);
//
//    if (file_count == 0) {
//        printf("No text files found in the directory.\n");
//        return 1;
//    }
//
//    int choice;
//    printf("Enter the number of the file to read (1-%d): ", file_count);
//    scanf("%d", &choice);
//
//    if (choice < 1 || choice > file_count) {
//        printf("Invalid choice.\n");
//        return 1;
//    }
//
//    readDataFromFile(directory_path, files[choice - 1]);
//
//
//
//    return 0;
//}



