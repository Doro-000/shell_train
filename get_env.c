#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

char *_getenv(const char*);
int str_comp(char *, const char *);

int main(int ac, char **av)
{
	printf("builtin getenv -> %s\n", getenv(av[ac - 1]));
	printf("implemented getenv -> %s\n", _getenv(av[ac - 1]));
	return (0);
}

char *_getenv(const char *name)
{
	int pairs = 0, i = 0, flag = 0;
	char **keys = NULL;
	char **values = NULL;
	char *token = NULL;
	char *saveptr = NULL;

	for (; environ[pairs] != NULL; pairs++)
		;
	keys = malloc(sizeof(*keys) * pairs);
	values = malloc(sizeof(*values)  * pairs);
	for (; environ[i] != NULL; i++)
	{
		token = strtok_r(environ[i], "=", &saveptr);
		keys[i] = token;
		values[i] = saveptr;
	}
	for (i = 0; i < pairs; i++)
	{
		if (str_comp(keys[i], name) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
		return (values[i]);
	else
		return (NULL);
}

int str_comp(char *first, const char *second)
{
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}
	return (first[i] - second[i]);
}
