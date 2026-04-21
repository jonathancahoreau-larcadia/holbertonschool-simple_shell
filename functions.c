#include "main.h"
/**
 * tokenizes - Split a line into tokens (one command, no arguments)
 * @line: The input string to tokenize (modified in-place)
 *
 * Return: A pointer to a static NULL-terminated array of tokens
 */
char **tokenizes(char *line)
{
	static char *argv[2];
	char *token;
	int i = 0;

	token = strtok(line, " \n");
	while (token)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	return (argv);
}
