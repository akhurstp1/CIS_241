#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>

#include "fileTree/fileTree.h"
#include "sha1/sha1.h"

#define MAX_FILENAME_LEN 100

#define FILE_DOC "file_names.txt"

int populateString(char* filename, char* string); 

int main () {
    FILE *fp1;
    char fileStr[FILE_LEN];
    char filename[MAX_FILENAME_LEN];
    char fsha[SHA_LEN];
    int offset;
    int counterA = 0;
    int counterB = 0;

    nListInit();

    fp1 = fopen(FILE_DOC, "r");

    while(fscanf(fp1, "%s", filename) == 1) {
        //printf("%s\n", filename);
        if(populateString(filename, fileStr)) {
            SHA1(fsha, fileStr, strlen(fileStr));

            initialNodeListadd(fsha);

            counterA++;
        }

        counterB++;
    }

    printf("Files used: %d\n", counterA);
    printf("Files given: %d\n", counterB);

    parseTree();
}

/*
 *  @brief:  This function takes an entire files and puts
 *           it into a single string
 *
 *  @params: filename - the file to be inputted
 *           string - the resulting string
 *
 *  @return: 
 *
 */

int populateString(char* filename, char* string) {
    FILE *fp1;
    char tempString[FILE_LEN];
    int count = 0;

    fp1 = fopen(filename, "r");

    if(fp1 == NULL) {
        printf("Cannot open file: %s\n", filename);
        return 0;
    }

    string[0] = '\0';

    while(count < 285 && fscanf(fp1, "%s", tempString) == 1) {
        strcat(string, tempString);
        count++;
    }

    fclose(fp1);

    return 1;
}