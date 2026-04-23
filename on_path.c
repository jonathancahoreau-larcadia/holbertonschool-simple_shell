#include "main.h"

/**
 * on_path - Search for command in PATH and return allocated full path
 * @command: command name (e.g., "ls")
 * @perm_denied: set to 1 if command found but not executable, else 0
 *
 * Return: allocated full path if found and executable (caller must free),
 *         or NULL if not found or permission denied.
 */
char *on_path(char *command, int *perm_denied)
{
	char *path_env, *path_copy, *dir, *path_complete;
	size_t len;

	*perm_denied = 0;
	if (!command || command[0] == '\0')
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) != 0)
			return (NULL);
		if (access(command, X_OK) != 0)
		{
			*perm_denied = 1;
			return (NULL);
		}
		return (strdup(command));
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
		path_complete = malloc(len);
		if (!path_complete)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(path_complete, "%s/%s", dir, command);
		if (access(path_complete, F_OK) == 0)
		{
			if (access(path_complete, X_OK) != 0)
			{
				*perm_denied = 1;
				free(path_complete);
				free(path_copy);
				return (NULL);
			}
			free(path_copy);
			return (path_complete);
		}
		free(path_complete);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}