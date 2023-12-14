#include <stdio.h>

/**
 * printmsg - a simple shell program
 * Discription: this function displays a message to the standard output
 */
void printmsg(void)
{
	char *message = "This message to the output stream of the computer \n";

	while (*message != '\0')
	{
		putchar(*message);
		message++;
	}
}

/**
 *  main - entry point
 * Return: 0 on success Always
 */
int main(void)
{
	printmsg();
	return (0);
}
