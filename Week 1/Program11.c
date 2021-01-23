//11.Write a program in C to copy a file in another name.
#include <stdio.h>
#include <stdlib.h>

void main()
{
	FILE *fptr1, *fptr2;
	char ch, fname1[20], fname2[20];

	printf(" Input the source file name : ");
	scanf("%s",fname1);

	fptr1=fopen(fname1, "r");
	if(fptr1==NULL)
	{
		printf(" File does not found or error in opening.!!");
		exit(1);
	}
	printf(" Input the new file name : ");
	scanf("%s",fname2);
	fptr2=fopen(fname2, "w");
	if(fptr2==NULL)
	{
		printf(" File does not found or error in opening.!!");
		fclose(fptr1);
		exit(2);
	}
	while(1)
	{
		ch=fgetc(fptr1);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fptr2);
		}
	}
	printf(" The file %s  copied successfully in the file %s. \n\n",fname1,fname2);
	fclose(fptr1);
	fclose(fptr2);
	getchar();
}
