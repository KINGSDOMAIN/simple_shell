#include "shell.h"

/**
 * interactive - checks  if shell is interactive mode
 * @data: the address of the struct function
 *
 * Retur: if interactive return 1 else return 0
 */
int interactive(list_str *data)
{
	return (isatty(STDIN_FILENO) && data->read_fd <= 2);
}

/**
 * check_delim - is delimeter?
 * @ca: the character to be checked
 * @delimeter: the delimeter string 
 * Return: 1 on success 0 on failure
 */
int check_delim(char ca, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ca)
			return (1);
	return (0);
}

/**
 *check_alpha - determine alphabetic character
 *@ca: entered character
 *Return: if ca is alpa return 1 else return 0
 */

int check_alpha(int ca)
{
	if ((ca >= 'a' && ca <= 'z') || (ca >= 'A' && ca <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strtoint - function that converts a string to an int
 *@str: string to convert
 *Return: if numbers are in string return 0 else return string
 */

int strtoint(char *str)
{
	int a, mysign = 1, myflag = 0, myoutput;
	unsigned int myresult = 0;

	for (a = 0;  str[a] != '\0' && myflag != 2; a++)
	{
		if (str[a] == '-')
			mysign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			myflag = 1;
			myresult *= 10;
			myresult += (str[a] - '0');
		}
		else if (myflag == 1)
			myflag = 2;
	}

	if (mysign == -1)
		myoutput = -myresult;
	else
		myoutput =myresult;

	return (myoutput);
}
