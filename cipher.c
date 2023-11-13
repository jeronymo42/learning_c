#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define EXT ".c"
#define EXT_H ".h"
#define ELEN 2

void read_file(char* file_path, FILE **ptr);
void cipher_file(FILE **ptr, int shift);

int main(void) {
    int errors = 0;
    char dir_path[500];
    if (scanf("%s", &dir_path) !=1) {
        errors = 1;
    } else {
        DIR * dp = opendir(dir_path);
        if (!dp) {
            errors = 1;
        } else {
    
            struct dirent * de;
            while ((de = readdir(dp))) {
                size_t nlen = strlen(de->d_name);
                if (nlen > ELEN && (strcmp((de->d_name) + nlen - ELEN, EXT) == 0 || strcmp((de->d_name) + nlen - ELEN, EXT_H) == 0)){
                    FILE* file;
                    read_file(de->d_name, &file);
                    cipher_file(&file, 3);
                    fclose(file);
            }
        }
        closedir(dp);
    }
    }
    return errors;
}

void read_file(char* file_path, FILE **ptr) {
    printf("%s", file_path);
    FILE *file = fopen(file_path, "r+");
    if (file && getc(file) != EOF) {
        *ptr = file;
        printf("File opened");
    }
    else {
        printf("n/a\n");
    }
}

void cipher_file(FILE **ptr, int shift) {
    char ch;
    while((ch = fgetc(*ptr)) != EOF) {
        printf("%c", ch);
        fputc((ch-shift) % 126, *ptr);
    }
}
