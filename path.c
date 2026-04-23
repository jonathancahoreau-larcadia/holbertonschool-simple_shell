#include "main.h"

/**
 * get_path_env - return PATH value
 *
 * Return: pointer to PATH string
 */
char *get_path_env(void)
	{
	int i;

	for (i = 0; environ[i]; i++)
	{
		printf("%s", environ[3]);
		if (strncmp(environ[i], "PATH=", 5) == 0)
		return (environ[i] + 5);
	}
	return (NULL);
	}

/**
 * find_path - search command in PATH
 * @cmd: command name
 *
 * Return: malloc'd full path or NULL
 */
char *find_path(char *cmd)
{
	char *path, *copy, *dir, *full;
	size_t len1, len2;

	if (strchr(cmd, '/'))
		return (strdup(cmd));
	path = get_path_env();
	if (!path)
		return (NULL);
	copy = strdup(path);
	if (!copy)
		return (NULL);
	dir = strtok(copy, ":");
	while (dir)
	{
		len1 = strlen(dir);
		len2 = strlen(cmd);
		full = malloc(len1 + len2 + 2);
		if (!full)
		{
			free(copy);
			return (NULL);
		}
		strcpy(full, dir);
		full[len1] = '/';
		strcpy(full + len1 + 1, cmd);
		if (access(full, F_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}
