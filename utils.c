#include "main.h"

/**
 * free_tokens - free an array of tokens
 * @tokens: token array
 */
void free_tokens(char **tokens)
	{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);
}

/**
 * print_exec_error - print correct execve error
 * @prog: program name
 * @line: line count
 * @cmd: command
 */
void print_exec_error(char *prog, int line, char *cmd)
{
	if (errno == EACCES)
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
		prog, line, cmd);
	else if (errno == EISDIR)
		fprintf(stderr, "%s: %d: %s: Is a directory\n",
		prog, line, cmd);
	else
		fprintf(stderr, "%s: %d: %s: not found\n",
		prog, line, cmd);
}
