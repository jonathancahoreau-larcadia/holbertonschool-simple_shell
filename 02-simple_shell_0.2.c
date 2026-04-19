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
int main(void)
{
	char *line = NULL, **args;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = isatty(STDIN_FILENO);
	pid_t pid;

	while (1)
	{
		if (interactive)
			printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

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
			execve(args[0], args, environ);
			perror("execve");
			exit(1);
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
