#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
/**
 * main - Entry point
 *
 * Return: (0), if sucess
 */
int main(void)
{
	pid_t my_ppid;	/*variable de type pid_t*/

	my_ppid = getppid();	/*fonction pour récupérer le ppid du programme*/
	printf("%d\n", my_ppid);

	return (0);
}
