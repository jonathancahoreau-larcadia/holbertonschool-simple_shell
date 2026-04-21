#include <stdio.h>
/**
 * main - Prints all arguments without using ac
 * @ac: argument count (unused)
 * @av: array of argument strings
 *
 * Return: Always 0 (Success)
 */
int main(int ac, char **av)
{
	int i = 0;

	while(av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}
	return (0);
}
