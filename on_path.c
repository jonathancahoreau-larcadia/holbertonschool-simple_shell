#include "main.h"
/**
 * on_path - Search for command in PATH and return allocated full path
 * @command: command name (e.g., "ls")
 *
 * Return: allocated string with full path (caller must free), or NULL
 */
char *on_path(char *command)
{
	char *path_env, *path_copy, *dir, *path_complete;
	size_t len;

	if (!command || command[0] == '\0')
		return (NULL);
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		if (dir[0] == '\0')
			dir = ".";
		len = strlen(dir) + 1 + strlen(command) + 1;
		path_complete = malloc(len * sizeof(char));
		if (!path_complete)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(path_complete, "%s/%s", dir, command);
		if (access(path_complete, X_OK) == 0)
		{
			free(path_copy);
			return (path_complete);
		}
		free(path_complete);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
