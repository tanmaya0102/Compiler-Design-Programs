//9.Write a program in C to replace a specific line with another text in a file.
#include <stdio.h>
#include <string.h>

#define MAX 256

  int main() 
  {
        FILE *fptr1, *fptr2;
        int lno, linectr = 0;
        char str[MAX],fname[MAX];        
        char newln[MAX], temp[] = "temp.txt";
		printf(" Input the file name to be opened : ");
        fgets(fname, MAX, stdin);
        fname[strlen(fname) - 1] = '\0';
        fptr1 = fopen(fname, "r");
        if (!fptr1) 
        {
                printf("Unable to open the input file!!\n");
                return 0;
        }
        fptr2 = fopen(temp, "w");
        if (!fptr2) 
        {
                printf("Unable to open a temporary file to write!!\n");
                fclose(fptr1);
                return 0;
        }
        /* get the new line from the user */
        printf(" Input the content of the new line : ");
        fgets(newln, MAX, stdin);
        /* get the line number to delete the specific line */
        printf(" Input the line no you want to replace : ");
        scanf("%d", &lno);
        lno++;
         // copy all contents to the temporary file other except specific line
        while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            if (!feof(fptr1)) 
            {
                linectr++;
                if (linectr != lno) 
                    {
                        fprintf(fptr2, "%s", str);
                    } 
                    else 
                    {
                        fprintf(fptr2, "%s", newln);
                    }
                }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove(fname);
        rename(temp, fname);
        printf(" Replacement did successfully..!! \n");
        return 0;
  }
