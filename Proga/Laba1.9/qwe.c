//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <dirent.h>
//#include <time.h>
//
//#define MAX_FILES 100 // Maximum number of files in the directory
//#define MAX_NAME_LENGTH 40 // Maximum length of the name field in the structure
//
//struct rec {
//    char name[MAX_NAME_LENGTH];
//    int square;
//    int nas;
//};
//
//int main() {
//    char* directory = "/path/to/your/folder"; // Replace with the directory path
//    DIR *dir;
//    struct dirent *ent;
//    char* files[MAX_FILES];
//    int count = 0;
//
//    // Open the directory
//    if ((dir = opendir(directory)) != NULL) {
//        // Read all files in the directory
//        while ((ent = readdir(dir)) != NULL) {
//            if (ent->d_type == DT_REG) { // Check if it's a regular file
//                // Filter for text files
//                if (strstr(ent->d_name, ".txt") != NULL) {
//                    files[count] = malloc(strlen(ent->d_name) + 1);
//                    strcpy(files[count], ent->d_name);
//                    count++;
//                }
//            }
//        }
//        closedir(dir);
//
//        if (count > 0) {
//            srand(time(NULL)); // Seed for random number generation
//            int random_index = rand() % count; // Generate a random index
//            char* selected_file = files[random_index];
//            printf("Selected file: %s\n", selected_file);
//
//            // Read the contents of the selected file
//            char file_path[256]; // Adjust the size accordingly
//            snprintf(file_path, sizeof(file_path), "%s/%s", directory, selected_file);
//
//            FILE* file = fopen(file_path, "r");
//            if (file != NULL) {
//                struct rec record;
//                printf("Contents of '%s':\n", selected_file);
//                while (fread(&record, sizeof(struct rec), 1, file) == 1) {
//                    printf("Name: %s, Square: %d, Nas: %d\n", record.name, record.square, record.nas);
//                }
//                fclose(file);
//            } else {
//                printf("Error opening file '%s'\n", selected_file);
//            }
//        } else {
//            printf("No text files found in the directory.\n");
//        }
//
//        // Free allocated memory
//        for (int i = 0; i < count; ++i) {
//            free(files[i]);
//        }
//    } else {
//        printf("Could not open directory.\n");
//        return 1;
//    }
//
//    return 0;
//}
