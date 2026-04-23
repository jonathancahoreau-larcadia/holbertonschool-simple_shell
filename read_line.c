#include "main.h"

/**
 * read_line - read a line from stdin
 *
 * Return: pointer to allocated line or NULL
 */
char *read_line(void)
{
	char *line = NULL;
	size_t size = 0;
	
	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
