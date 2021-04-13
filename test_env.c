#include <stdio.h>

extern char **environ;
void env(char **);
void print(char *);

int main() {
    char **token = {"env", NULL};
    env(token);
    return 0;
}

void env(char **tokenized_command __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		print(environ[i]);
	    	print("\n");
	}
}

void print(char *string)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
		write(1, &string[i], 1);
}
