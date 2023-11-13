#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define EXT ".c"
#define EXT_H ".h"
#define ELEN 2

void read_file(char* file_path, FILE **ptr);
void cipher_file(FILE **ptr, int shift, char* buffer);
void buffer_file(char* buffer, FILE **ptr);
void write_file(char* file_path, FILE **ptr);

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
                    char buffer[5000];
                    read_file(de->d_name, &file);
                    buffer_file(buffer, &file);
                    fclose(file);
                    printf("%s", buffer);
                    write_file(de->d_name, &file);
                    cipher_file(&file, 3, buffer);
                    fclose(file);
            }
        }
        closedir(dp);
    }
    }
    return errors;
}

void read_file(char* file_path, FILE **ptr) {
    FILE *file = fopen(file_path, "r");
    if (file && getc(file) != EOF) {
        *ptr = file;
        printf("File opened");
    }
    else {
        printf("n/a\n");
    }
}

void write_file(char* file_path, FILE **ptr) {
    FILE *file = fopen(file_path, "w+");
    printf("Opened for writing");
    *ptr = file;
}

void buffer_file(char* buffer, FILE **ptr) {
    char ch;
    int counter = 0;
    while((ch = fgetc(*ptr)) != EOF) {
        buffer[counter++] = ch;
    }
}


void cipher_file(FILE **ptr, int shift, char* buffer) {
    int counter = 0;
    while(buffer[counter++] != '\0') {
        fputc((buffer[counter]+shift) % 126, *ptr);
    }
}
