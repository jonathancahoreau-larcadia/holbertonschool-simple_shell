#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;

	while(1)
	{
		printf("$");
		nread = getline(&line, &size, stdin);
		if (nread == -1)
			break;
		printf("%s", line);
	}
	free(line);
	return 0;
}