#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

int main(int ac, char *av[])
{
	struct stat my_status;
	char *PATH = getenv("PATH");
	char *next_path = strtok(PATH, ":");
	DIR *next_dir = NULL;
	int dir_fd;

	if (ac != 2)
	{
		printf("Usage: %s filename\n", av[0]);
		return (1);
	}
	while (next_path != NULL)
	{
		next_dir = opendir(next_path);
		dir_fd = dirfd(next_dir);
		if (fstatat(dir_fd, av[ac-1], &my_status, 0) == 0)
		{
			printf("Found in %s\n", next_path);
		}
		else
		{
			printf("Not found in %s\n", next_path);
		}
		next_path = strtok(NULL, ":");
		closedir(next_dir);
	}
	return (0);
}
