#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void recursive_dir_list(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Cannot open directory: %s\n", path);
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullPath[1024];
        sprintf(fullPath, "%s/%s", path, entry->d_name);
        printf("%s\n", fullPath);

        if (entry->d_type == DT_DIR) {
            recursive_dir_list(fullPath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    recursive_dir_list(argv[1]);
    return 0;
}

