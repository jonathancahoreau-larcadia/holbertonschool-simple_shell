#include "main.h"

/**
 * split_line - split a line into tokens
 * @line: input line
 *
 * Return: array of tokens
 */
char **split_line(char *line)
{
	int buf = 64, pos = 0;
	char **tokens = malloc(sizeof(char *) * buf);
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		tokens[pos] = strdup(token);
		pos++;

		if (pos >= buf - 1)
		{
		buf *= 2;
		tokens = realloc(tokens, sizeof(char *) * buf);
		if (!tokens)
			return (NULL);
		}
		token = strtok(NULL, " \t\n");
	}
	tokens[pos] = NULL;
	return (tokens);
}
