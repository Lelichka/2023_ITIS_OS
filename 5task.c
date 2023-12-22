#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Enter file1 and file2");
		return 1;
	}

	char *path1 = argv[1];
	char *path2 = argv[2];

	FILE *file1;
	FILE *file2;

	if ((file1 = fopen(path1,"r")) == NULL)
	{
		printf("Error opening file 1");
		return 1;
	}
	if ((file2 = fopen(path2, "w")) == NULL)
	{
		printf("Error opening file 2");
		return 1;
	}

	char ch;

	while ((ch = getc(file1)) != EOF)
	{
		if (putc(ch, file2) == EOF)
		{
			printf("Error writing");
			fclose(file2);
		}
	}

	printf("Content Copied\n");

	if (fclose(file1) == EOF)
	{
		printf("Error closing file1");
		return 1;
	}
	if (fclose(file2) == EOF)
	{
		printf("Error closing file2");
		return 1;
	}
	
	struct stat s;
	if (stat(path1, &s) == 0 && chmod(path2, s.st_mode) == 0)
	{
		printf("Permissions copied");
		return 0;
	}
	printf("Error copying the permissions");
}
