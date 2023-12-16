#include "shell.h"

/**
 * main - entry point of program
 * @ac: argument count of input string
 * @av: argument vector of string
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	String_input string[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				txt(av[0]);
				txt(": 0: This file Can't be opened ");
				txt(av[1]);
				txtchar('\n');
				txtchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	env_populate(string);
	hist_read(string);
	hsh(string, av);
	return (EXIT_SUCCESS);
}
