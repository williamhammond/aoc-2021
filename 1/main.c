#if WIN32
    #define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 1024

int main(int argc, char** argv)
{
    char* path = "input.txt";
    char line[MAX_LINE_LENGTH] = { 0 };
    unsigned int line_count = 0;

    FILE* file = fopen(path, "r");

    if (!file) {
        perror(path);
        return EXIT_FAILURE;
    }

    int prev = NULL;
    int result = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        int current = atoi(line);
        if (!prev) {
            prev = current;
            continue;
        }
        if (current > prev) {
            result += 1;
        }
        prev = current;
    }

    if (fclose(file)) {
        return EXIT_FAILURE;
        perror(path);
    }
    printf("result :%d", result);
    return EXIT_SUCCESS;
}