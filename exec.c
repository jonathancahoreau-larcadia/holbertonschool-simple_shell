#include "main.h"

/**
 * execute - run a command with correct error messages
 * @args: arguments
 * @prog: program name
 * @line: line count
 *
 * Return: 1
 */
int execute(char **args, char *prog, int line)
{
	pid_t pid;
	char *full = find_path(args[0]);
	int status;
	if (!full)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
		prog, line, args[0]);
		return (1);
	}
	if (access(full, F_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
		prog, line, args[0]);
		free(full);
		return (1);
	}
	if (access(full, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
		prog, line, args[0]);
		free(full);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full);
		return (1);
	}
	if (pid == 0)
	{
		execve(full, args, environ);
		print_exec_error(prog, line, args[0]);
		_exit(126);
	}
	else
		waitpid(pid, &status, 0);
	free(full);
	return (status);
}
