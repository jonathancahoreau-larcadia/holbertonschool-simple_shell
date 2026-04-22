#include "main.h"
/**
 * execute - Fork and execute a command using execve
 * @args: NULL-terminated array of arguments (args[0] is the command path)
 * @av: Argument vector from main, used to print the shell program name
 * @countline: Current line number, used for formatted error messages
 *
 * Return: 0 on success, or -1 if fork() fails.
 */
int execute(char **args, char **av, int countline)
{
	pid_t pid;
	int status;
	char *path_complete;

	if (!args || !args[0])
		return (-1);
	if (strcmp(args[0], "exit") == 0)
		exit(0);
	path_complete = on_path(args[0]);
	if (!path_complete)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", av[0], countline, args[0]);
			return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path_complete);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(path_complete, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
			av[0], countline, args[0]);
			free(path_complete);
			_exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free(path_complete);
	return (0);
}
