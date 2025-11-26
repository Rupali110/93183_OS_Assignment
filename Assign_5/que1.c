#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    char *dirPath = argv[1];

    DIR *dir = opendir(dirPath);
    if (dir == NULL) {
        perror("opendir");  
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
   
        if (entry->d_name[0] != '.')
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}

