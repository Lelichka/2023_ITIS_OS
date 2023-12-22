#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

int searchFiles(char *dirName, char *outputPath, int minSize, int maxSize, time_t startDate, time_t endDate)
{
	FILE *outputFile = fopen(outputPath, "w");
	if ((outputFile == NULL))
	{
		printf("Error opening output file");
		return 1;
	}

	DIR *dir = opendir(dirName);
    	if (dir == NULL)
	{
		printf("Error opening directory");
        	return 1;
    	}
	
	struct dirent *d;
	struct stat fileStat;
	char path[512];

    	while ((d = readdir(dir)) != NULL)
	{
        	if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
		{
			continue;
		}

		snprintf(path, sizeof(path), "%s/%s", dirName, d->d_name);

          	if (stat(path, &fileStat) < 0)
		{
			printf("Error getting stat file");
			continue;
		}
                if S_ISDIR(fileStat.st_mode)
		{
                    	int res = searchFiles(path, outputPath, minSize, maxSize, startDate, endDate);
			if (res != 0)
			{
				printf("Error processing directory path");
			}
                } 
		else
		{
                    	if ((fileStat.st_size >= minSize && fileStat.st_size <= maxSize) &&
				      (fileStat.st_ctime >= startDate && fileStat.st_ctime <= endDate))
			{
                        	printf("%s\t%d\t%s", d->d_name, (int)fileStat.st_size, ctime(&fileStat.st_ctime));
                       		fprintf(outputFile, "%s\t%d\t%s", d->d_name, (int)fileStat.st_size, ctime(&fileStat.st_ctime));
                    	}
                }
        }
	if (closedir(dir) != 0)
	{
		printf("Error closing directory");
		return 1;
	}
	if (fclose(outputFile) == EOF)
	{
		printf("Error closing file");
		return 1;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 7)
	{
        	printf("Enter output file, min and max size, start and end date");
        	return 1;
    	}

	char *dirPath = argv[1];
	char *outputPath = argv[2];
    	int minSize = atoi(argv[3]);
    	int maxSize = atoi(argv[4]);
    	time_t startDate = atoi(argv[5]);
   	time_t endDate = atoi(argv[6]);

   	int res = searchFiles(dirPath,outputPath, minSize, maxSize, startDate, endDate);
    	
	if (res != 0)
	{
		return res;
	}
    	return 0;
}
