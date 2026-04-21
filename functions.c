#include "main.h"
/**
 * tokenize - Split an input string into an array of tokens
 * @input: The input string to split (not modified)
 *
 * Return: A NULL-terminated array of dynamically allocated strings.
 *         Each element is a token extracted from the input.
 *         Returns NULL on allocation failure.
 */
char **tokenize(const char *input)
{
	char **args, **tmp;
	size_t count = 0;
	size_t capacity = 4, new_capacity;
	char *token, *copy;

	args = malloc(capacity * sizeof(char *));
	if (!args)
		return (NULL);

	copy = strdup(input);
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
return (args);
}
/**
 * free_tokens - Free a NULL-terminated array of strings
 * @args: The array of strings to free
 */
void free_tokens(char **args)
{
	size_t count = 0;

	while (args[count])
	{
		free(args[count]);
		count++;
	}
	free(args);
}
/**
 * tokenizes - Split a line into tokens (one command, no arguments)
 * @line: The input string to tokenize (modified in-place)
 *
 * Return: A pointer to a static NULL-terminated array of tokens
 */
char **tokenizes (char *line)
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
