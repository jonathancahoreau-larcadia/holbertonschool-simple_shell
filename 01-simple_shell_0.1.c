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
	char *line = NULL, *argv[2];
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = isatty(STDIN_FILENO);
	pid_t pid;
	(void) ac;


	while (1)
	{
		if (interactive)
			printf("#cisfun$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (line[0] == '\0')
			continue;
		argv[0] = line;
		argv[1] = NULL;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			execve(argv[0], argv, environ);
			perror(av[0]);
			exit(1);
		}
		if (pid > 0)
			wait(NULL);
	}
	free(line);
	return (0);
}
