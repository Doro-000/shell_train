#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void clean_input(char *);

int main()
{
	char *command = NULL;
	size_t size = 0;
	pid_t child;
	int error_num;
	char *argv[] = {NULL, NULL};

	while(1)
	{
		printf("> ");
		getline(&command, &size, stdin);
		clean_input(command);
		argv[0] = command;

		if ((child = fork()) == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				error_num = errno;
				printf("%s\n", strerror(error_num));
			}
		}
		else
		{
			wait(NULL);
			command = NULL;
		}
	}
	free(command);
	return (0);
}

void clean_input(char *str)
{
	int i = 0;

	while(str[i] != '\n')
	{
		i++;
	}
	str[i] = '\0';
}
