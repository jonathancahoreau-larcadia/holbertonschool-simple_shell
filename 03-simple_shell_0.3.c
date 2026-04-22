#include "main.h"
/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: (0), if sucess
 */
int main(int ac, char **av)
{
	char *line = NULL, **args;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = isatty(STDIN_FILENO), countline = 0;
	(void) ac;

	while (1)
	{
		if (interactive)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		countline++;
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			free(line);
			exit(0);
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		args = tokenize(line);
		if (!args)
			continue;
		execute(args, av, countline);
		free_tokens(args);
	}
	free(line);
	return (0);
}
