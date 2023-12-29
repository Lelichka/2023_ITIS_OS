#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("Enter the file and N");
		return 1;
	}

	FILE *file;
	char *path = argv[1];
	int N = atoi(argv[2]);
	if ((file = fopen(path, "r")) == NULL)
	{
		printf("Error opening file");
		return 1;
	}

	char ch;
	int lines = 0;
	while((ch = getc(file)) != EOF)
	{
		if (putc(ch,stdout) == EOF)
		{
			printf("Error writing");
			fclose(file);
			return 1;
		}
		if (ch == '\n')
		{
			lines++;
			if (N > 0 && lines % N == 0)
			{
				printf("Press any key");
				getc(stdin);
			}
		}
	}
	if (fclose(file) == EOF)
	{
		printf("Error closing file");
		return 1;
	}
	return 0;
}


