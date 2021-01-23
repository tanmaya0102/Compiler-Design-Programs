//12.Write a program in C to merge two files and write it in a new file
#include <stdio.h>
#include <stdlib.h>

void main()
{
	FILE *fold1, *fold2, *fnew;
	char ch, fname1[20], fname2[20], fname3[30];
	printf(" Input the 1st file name : ");
	scanf("%s",fname1);
	printf(" Input the 2nd file name : ");
	scanf("%s",fname2);
	printf(" Input the new file name where to merge the above two files : ");
	scanf("%s",fname3);
	fold1=fopen(fname1, "r");
	fold2=fopen(fname2, "r");
	if(fold1==NULL || fold2==NULL)
	{
//		perror("Error Message ");
		printf(" File does not exist or error in opening...!!\n");
		exit(EXIT_FAILURE);
	}
	fnew=fopen(fname3, "w");
	if(fnew==NULL)
	{
//		perror("Error Message ");
		printf(" File does not exist or error in opening...!!\n");
		exit(EXIT_FAILURE);
	}
	while((ch=fgetc(fold1))!=EOF)
	{
		fputc(ch, fnew);
	}
	while((ch=fgetc(fold2))!=EOF)
	{
		fputc(ch, fnew);
	}
	printf(" The two files merged into %s file successfully..!!\n\n", fname3);
	fclose(fold1);
	fclose(fold2);
	fclose(fnew);
}
