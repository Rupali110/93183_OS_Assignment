#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void listRecursive(const char *path) {
    DIR *DP = opendir(path);
    if (DP == NULL) {
        perror(path);
        return;
    }

    printf("\n%s:\n", path);

    struct dirent *ent;
    struct stat point;

    // Change directory into current path
    if (chdir(path) != 0) {
        perror("chdir");
        closedir(DP);
        return;
    }

    // First pass: list all entries
    while ((ent = readdir(DP)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        if (stat(ent->d_name, &point) == 0) {
            printf("%-20s | mode: %d | links: %ld | uid: %d | gid: %d | size: %ld bytes\n",
                   ent->d_name, point.st_mode, point.st_nlink,
                   point.st_uid, point.st_gid, point.st_size);
        } else {
            perror(ent->d_name);
        }
    }

    rewinddir(DP); // Reset for recursion

    // Second pass: recurse into subdirectories
    while ((ent = readdir(DP)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        if (stat(ent->d_name, &point) == 0 && S_ISDIR(point.st_mode)) {
            listRecursive(ent->d_name); // Recurse into subdir
        }
    }

    chdir(".."); // Go back to parent directory
    closedir(DP);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    listRecursive(argv[1]);
    return 0;
}

