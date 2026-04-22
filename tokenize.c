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
	char **args = NULL, **tmp, *token, *copy;
	size_t count = 0, capacity = 4, new_capacity, i;

	if (!line)
		return (NULL);
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
			tmp = realloc(args, new_capacity * sizeof(char *));
			if (!tmp)
			{
				free(copy);
				for (i = 0; i < count; i++)
					free(args[i]);
				return (NULL);
			}
			args = tmp;
			new_capacity = capacity * 2;
		}
		args[count] = strdup(token);
		if (!args[count])
		{
			free(copy);
			for (i = 0; i < count; i++)
				free(args[i]);
			free(args);
			return (NULL);
		}
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(copy);
	if (count == 0)
	{
		free(args);
		return (NULL);
	}
	args[count] = NULL;
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
