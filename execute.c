#include "main.h"

/**
 * execute - Fork and execute a command
 * @args: NULL-terminated array of arguments
 * @av: argument vector from main (shell name for error messages)
 * @countline: current line number for error messages
 *
 * Return: exit status of command, or -1 on fork failure
 */
int execute(char **args, char **av, int countline)
{
	pid_t pid;
	int status, perm_denied;
	char *path_complete;

	if (!args || !args[0])
		return (-1);
	path_complete = on_path(args[0], &perm_denied);
	if (path_complete == NULL)
	{
		if (perm_denied)
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
				av[0], countline, args[0]);
		else
			fprintf(stderr, "%s: %d: %s: not found\n",
				av[0], countline, args[0]);
		return (perm_denied ? 126 : 127);
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
		execve(path_complete, args, environ);
		if (errno == EACCES)
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
				av[0], countline, args[0]);
		else if (errno == ENOENT)
			fprintf(stderr, "%s: %d: %s: not found\n",
				av[0], countline, args[0]);
		else
			fprintf(stderr, "%s: %d: %s: %s\n",
				av[0], countline, args[0], strerror(errno));
		free(path_complete);
		exit(127);
	}
	waitpid(pid, &status, 0);
	free(path_complete);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
