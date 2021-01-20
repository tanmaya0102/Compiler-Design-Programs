
//1. Write a program in C to create and store information in a text file.
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE  200
int main()
{
    FILE *fp = NULL;
    char buffer[MAX_SIZE] = {0};
    fp = fopen("text1.txt", "w");
    if(fp == NULL)
    {
        printf("Error in creating the file\n");
        exit(0);
    }
    
    printf("Enter data:");
    if(fgets(buffer,MAX_SIZE,stdin) == NULL)
    {
        printf("Error in reading the input data\n");
        
        fclose(fp);
        exit(0);
    }
   
    fwrite(buffer, sizeof(buffer[0]), MAX_SIZE, fp);
    fclose(fp);
    printf("File has been created and saved successfully\n");
    return 0;
}