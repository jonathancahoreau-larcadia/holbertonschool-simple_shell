#include "main.h"

/**
 * main - entry point of the shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	char *line = NULL, **args = NULL;
	int interactive = isatty(STDIN_FILENO);
	int line_count = 0, status = 0;

	(void)ac;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);
		line = read_line();
		if (!line)
		{
			if (interactive)
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		line_count++;
		args = split_line(line);
		if (args && args[0])
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_tokens(args);
				free(line);
				exit(status);
			}
			if (strcmp(args[0], "env") == 0)
			{
				print_env();
				free_tokens(args);
				free(line);
				continue;
			}
			status = execute(args, av[0], line_count);
		}
		free_tokens(args);
		free(line);
	}
	return (status);
}
