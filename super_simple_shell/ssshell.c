#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;

int main (void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread = 0;
	char *argv[10];
	char *token;
	int i = 0;
	pid_t pid;
	char path[1024];
	char *dir;
	char *path_copy;

	while (1)
	{
		/* lire la ligne*/
		printf("$");
		nread = getline(&line, &size, stdin);
		if (nread ==-1)
			break;

		/* tokenisation*/
		i= 0;
		token = strtok(line, " \n");
		while (token)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " \n");
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
			continue;

		/*executer un processus*/
		pid = fork();
		if (pid == 0)
		{
			path_copy = strdup(getenv("PATH"));
			if (path_copy == NULL)
			{
				fprintf(stderr, "%s: command not found\n", argv[0]);
				free(path_copy);
				exit(1);
			}
			dir = strtok(path_copy, ":");
			while (dir)
			{
				strcpy(path, dir);
				strcat(path, "/");
				strcat(path, argv[0]);
				if (access(path, X_OK) == 0)
				{
					execve(path, argv, environ);
					perror("execve");
					free(path_copy);
					exit(1);

				}

			dir = strtok(NULL, ":");
			}
			fprintf(stderr, "%s: command not found\n", argv[0]);
			free(path_copy);
			exit(1);
		}
		else if (pid > 0)
			wait(NULL);
	}
	free(line);
return (0);
}