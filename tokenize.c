#include "main.h"
/**
 * tokenize - Split an input string into an array of tokens
 * @line: The input string to split (not modified)
 *
 * Return: A NULL-terminated array of dynamically allocated strings.
 *         Each element is a token extracted from the input.
 *         Returns NULL on allocation failure.
 */
char **tokenize(const char *line)
{
	char **args, **tmp, *token, *copy;
	size_t count = 0, capacity = 4, new_capacity;

	args = malloc(capacity * sizeof(char *));
	if (!args)
		return (NULL);
	copy = strdup(line);
	if (!copy)
	{
		free(args);
		return (NULL);
	}
	token = strtok(copy, " \t\n");
	while (token)
	{
		if (count == capacity)
		{
			new_capacity = capacity * 2;
			tmp = realloc(args, new_capacity * sizeof(char *));
			if (!tmp)
			{
				free(copy);
				free_tokens(args);
				return (NULL);
			}
			args = tmp;
			capacity = new_capacity;
		}
		args[count] = strdup(token);
		count++;
		token = strtok(NULL, " \t\n");
	}
	args[count] = NULL;
	free(copy);
	if (count == 0)
	{
		free(args);
		return (NULL);
	}
return (args);
}
/**
 * free_tokens - Free a NULL-terminated array of strings
 * @args: The array of strings to free
 */
void free_tokens(char **args)
{
	size_t count = 0;

	if (!args)
		return;
	while (args[count])
	{
		free(args[count]);
		count++;
	}
	free(args);
}
