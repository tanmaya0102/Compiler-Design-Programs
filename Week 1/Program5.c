//5.Write a program in C to Find the Number of Lines in a Text File.
#include <stdio.h>

#define FSIZE 100
 
int main()
{
    FILE *fptr;
    int ctr = 0;  
    char fname[FSIZE];
    char c; 
	printf(" Input the file name to be opened : ");
	scanf("%s",fname);

    fptr = fopen(fname, "r");
    if (fptr == NULL)
    {
        printf("Could not open file %s", fname);
        return 0;
    }
    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n')
            ctr = ctr + 1;
    fclose(fptr);
    printf(" The lines in the file %s are : %d \n \n", fname, ctr-1);
    return 0;
}