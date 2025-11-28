#include<stdlib.h> 
#include<stdio.h>

const char* read_file(char fileName[]) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(fp);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, fp);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(fp);

    return buffer;
}
