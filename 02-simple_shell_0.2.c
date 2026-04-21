#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"
/**
 * main - Entry point
 *
 * Return: (0), if sucess
 */
int main(int ac, char **av)
{
	char *line = NULL, **args;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = isatty(STDIN_FILENO), countline = 0;
	pid_t pid;
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
		if(!args)
			continue;

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				fprintf(stderr, "%s: %d: %s: not found\n", av[0], countline, args[0]);
				free(line);
				exit(127);
			}
		}
		if (pid > 0)
		{
			wait(NULL);
			free_tokens(args);
		}
	}
	free(line);
	return (0);
}
