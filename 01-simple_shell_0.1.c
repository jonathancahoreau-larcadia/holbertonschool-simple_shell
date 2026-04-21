#include "main.h"
/**
 * main - Entry point
 *@ac: int argument
 *@av: double pointer on char
 * Return: (0), if sucess
 */

int main(int ac, char **av)
{
	char *line = NULL, **argv;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = isatty(STDIN_FILENO);
	pid_t pid;
	(void) ac;

	while (1)
	{
		if (interactive)
			printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			free(line);
			exit(0);
		}
		argv = tokenizes(line);

		if (argv[0] == NULL)
			continue;

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{

				perror(av[0]);
				free(line);
				exit(127);
			}
		}
		if (pid > 0)
			wait(NULL);
	}
	free(line);
	return (0);
}
