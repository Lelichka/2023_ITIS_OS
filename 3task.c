#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("Enter the file");
		return 1;
	}
	FILE *file;
	if ((file = fopen(argv[1], "w")) == NULL)
	{
		printf("Error opening file");
		return 1;
	}
	char ch = getc(stdin);
	while(ch != 6)
	{
		if (putc(ch,file) == EOF)
		{
			printf("Error writing");
			fclose(file);
			return 1;
		}
		ch = getc(stdin);
	}
	if (fclose(file) == EOF)
	{
		printf("Error closing file");
		return 1;
	}
	return 0;
}

