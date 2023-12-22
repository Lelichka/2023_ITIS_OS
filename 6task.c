#include <stdio.h>
#include <dirent.h>

int readDir(char *dirPath)
{
	DIR *dir = opendir(dirPath);
	if (dir == NULL)
	{
		printf("Error closing directory");
		return 1;
	}

	struct dirent *d;

	while ((d = readdir(dir)) != NULL)
	{
		printf("%s\n", d->d_name);
	}
	if (closedir(dir) != 0)
	{
		printf("Error closing directory");
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Enter directory path");
		return 1;
	}

	printf("Current directory:\n\n");

	int readCurrentDir = readDir(".");
	if (readCurrentDir != 0)
	{
		return readCurrentDir;
	}

	printf("Param directory:\n\n");
	char *path = argv[1];

	int readParamDir = readDir(path);
	if (readParamDir != 0)
	{
		return readParamDir;
	}
	return 0;
}
