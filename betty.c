#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int interactive = isatty(STDIN_FILENO);
	ssize_t nread;
	size_t len = 0;
	char **line;

	if (interactive)
		printf("$ ");

	nread = getline(&line, &len, stdin);
	if (!nread)
		return(0)
	while (1)


}