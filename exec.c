#include "main.h"

/**
 * run_child_process - fork, execve and return child's exit status
 * @full: full path to executable
 * @args: argument vector
 * @prog: program name
 * @line: line count
 *
 * Return: exit status of child
 */
int run_child_process(char *full, char **args, char *prog, int line)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(full, args, environ);
		print_exec_error(prog, line, args[0]);
		if (errno == EACCES)
			_exit(126);
		if (errno == EISDIR)
			_exit(127);
		_exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}
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
	char *full = find_path(args[0]);

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
	return (run_child_process(full, args, prog, line));
}
