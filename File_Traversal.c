#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_CMD 1024
#define MENU "\nSelect an option:\n" \
             "1. List all files and directories (-ls)\n" \
             "2. Count all files (-fc)\n" \
             "3. Count all directories (-dc)\n" \
             "4. Calculate total size (-fs)\n" \
             "5. Delete files of specific extension (-del)\n" \
             "6. Copy directory (-cp)\n" \
             "7. Move directory (-mv)\n" \
             "8. Exit\n" \
             "Enter your choice: "

// these are the global variables for counting files, directories, and total size
int file_count = 0, dir_count = 0;
long total_size = 0;
const char *del_extension = NULL;  // this is an extension for files to delete

// this is a function that is created to give files and directories
int list_files(const char *file_path, const struct stat *file_stat, int file_type, struct FTW *file_info) {
    printf("%s\n", file_path);  // this will print each file and directory path present in the user mentioned location
    return 0;
}

// this is a function that is created to count files in a user mentioned directory
int count_files(const char *file_path, const struct stat *file_stat, int file_type, struct FTW *file_info) {
    if (file_type == FTW_F) file_count++;  // Increment file_count if the current locator is at file
    return 0;
}

// this is function that is created to count directories in a user mentioned directory
int count_dirs(const char *file_path, const struct stat *file_stat, int file_type, struct FTW *file_info) {
    if (file_type == FTW_D) dir_count++;  // Increment dir_count if the current locator is at directory
    return 0;
}

// this is function that is created to calculate the total size of files present in a user mentioned directory
int calculate_size(const char *file_path, const struct stat *file_stat, int file_type, struct FTW *file_info) {
    if (file_type == FTW_F) total_size += file_stat->st_size;  // to get the file size simply points the file_stat to st_size
    return 0;
}

// this function is created to delete files with a user mentioned extension
int delete_files(const char *file_path, const struct stat *file_stat, int file_type, struct FTW *file_info) {
    if (file_type == FTW_F && del_extension && strstr(file_path, del_extension)) {
        remove(file_path);  // It only deletes the file that matches the extension
        printf("Deleted: %s\n", file_path);  // This prints the file that was deleted in the earlier opearation
    }
    return 0;
}

// this function is created to copy a directory even if the user wants to exclude files with a specific extension
void copy_dir(const char *src_dir, const char *dst_dir, const char *exclude_ext) {
    char command[MAX_CMD];
    if (exclude_ext) {
        snprintf(command, sizeof(command), "rsync -av --exclude='*%s' %s/ %s/", exclude_ext, src_dir, dst_dir);
    } else {
        snprintf(command, sizeof(command), "cp -r %s %s", src_dir, dst_dir);
    }
    system(command);  // this is used for the execution of the copy command
}

// this function is created that is used to move a directory from source to destination
void move_dir(const char *src_dir, const char *dst_dir) {
    char command[MAX_CMD];
    snprintf(command, sizeof(command), "mv %s %s", src_dir, dst_dir);
    system(command);  // this is used for the execution of the move command
}

int main() {
    int user_choice;
    char source_dir[256], destination_dir[256], file_extension[10];

    while (1) {
        printf(MENU);  // Prints the menu for the user
        scanf("%d", &user_choice);  // this is used to store the choice of a user
        switch (user_choice) {
            case 1:  // case 1 is when a user enters 1 to call list all files and directories function
                printf("Enter directory: ");
                scanf("%s", source_dir);
                nftw(source_dir, list_files, 10, FTW_PHYS);
                break;
            case 2:  // case 2 is when user enters 2 to call count all files function
                file_count = 0;
                printf("Enter directory: ");
                scanf("%s", source_dir);
                nftw(source_dir, count_files, 10, FTW_PHYS);
                printf("Total files: %d\n", file_count);
                break;
            case 3:  // case 3 is when user enters 3 to call count all directories function
                dir_count = 0;
                printf("Enter directory: ");
                scanf("%s", source_dir);
                nftw(source_dir, count_dirs, 10, FTW_PHYS);
                printf("Total directories: %d\n", dir_count);
                break;
            case 4:  // case 4 is when user enters 4 to call a calculate total file function
                total_size = 0;
                printf("Enter directory: ");
                scanf("%s", source_dir);
                nftw(source_dir, calculate_size, 10, FTW_PHYS);
                printf("Total size: %ld bytes\n", total_size);
                break;
            case 5:  // case 5 is when user enters 5 to call a delete file function
                printf("Enter directory: ");
                scanf("%s", source_dir);
                printf("Enter file extension: ");
                scanf("%s", file_extension);
                del_extension = file_extension;
                nftw(source_dir, delete_files, 10, FTW_PHYS);
                break;
            case 6:  // case 6 is when user enters 6 to call a copy directory function
                printf("Enter source directory: ");
                scanf("%s", source_dir);
                printf("Enter destination directory: ");
                scanf("%s", destination_dir);
                printf("Enter file extension to exclude (or press enter for none): ");
                while (getchar() != '\n'); // Clear the input buffer
                fgets(file_extension, sizeof(file_extension), stdin);
                file_extension[strcspn(file_extension, "\n")] = 0;  // Remove newline character
                copy_dir(source_dir, destination_dir, strlen(file_extension) > 0 ? file_extension : NULL);
                break;
            case 7:  // Case 7 is when user enters 7 to call a move directory function
                printf("Enter source directory: ");
                scanf("%s", source_dir);
                printf("Enter destination directory: ");
                scanf("%s", destination_dir);
                move_dir(source_dir, destination_dir);
                break;
            case 8:  // when user enters 8 to exit from the program
                exit(0);
            default:
                printf("Invalid choice.\n");  // Handle invalid input
        }
    }
    return 0;
}
