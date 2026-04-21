#include "main.h"

/**
 * find_path - searches for the full path of a command in PATH
 * @command: name of the command to search for
 *
 * Return: full path if found, NULL otherwise
 */
char *find_path(char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[1024];

	if (access(command, X_OK) == 0)
		return (strdup(command));

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
    dir = strtok (NULL, ':');
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
	}

	free(path_copy);
	return (NULL);
}
