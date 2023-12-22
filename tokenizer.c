#include "shell.h"

/**
 * **tok1 - splits strings into words
 * @strr: string entered by the user
 * @p: string delimiter
 * Return: this returns a pointer to an array of strings
 */

char **tok1(char *strr, char *p)
{
	int a, b, h, t, word_count = 0;
	char **y;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	if (!p)
		p = " ";
	for (a = 0; strr[a] != '\0'; a++)
		if (!check_delim(strr[a], p) && (check_delim(strr[a + 1], p) || !strr[a + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	y = malloc((1 + word_count) * sizeof(char *));
	if (!y)
		return (NULL);
	for (a = 0, b = 0; b < word_count; b++)
	{
		while (check_delim(strr[a], p))
			a++;
		h = 0;
		while (!check_delim(strr[a + h], p) && strr[a + h])
			h++;
		y[b] = malloc((h + 1) * sizeof(char));
		if (!y[b])
		{
			for (h = 0; h < b; h++)
				free(y[h]);
			free(y);
			return (NULL);
		}
		for (t = 0; t < h; t++)
			y[b][t] = strr[a++];
		y[b][t] = 0;
	}
	y[b] = NULL;
	return (y);
}

/**
 * **tok2 - split strings into word 
 * @strr: string to be split
 * @p: delimiter
 * Return: pointer to an array of strings
 */
char **tok2(char *strr, char p)
{
	int a, b, h, t, word_count = 0;
	char **y;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	for (a = 0; strr[a] != '\0'; a++)
		if ((strr[a] != p && strr[a + 1] == p) ||
				(strr[a] != p && !strr[a + 1]) || strr[a + 1] == p)
			word_count++;
	if (word_count == 0)
		return (NULL);
	y = malloc((1 + word_count) * sizeof(char *));
	if (!y)
		return (NULL);
	for (a = 0, b = 0; b < word_count; b++)
	{
		while (strr[a] == p && strr[a] != p)
			a++;
		h = 0;
		while (strr[a + h] != p && strr[a + h] && strr[a + h] != p)
			h++;
		y[b] = malloc((h + 1) * sizeof(char));
		if (!y[b])
		{
			for (h = 0; h < b; h++)
				free(y[h]);
			free(y);
			return (NULL);
		}
		for (t = 0; t < h; t++)
			y[b][t] = strr[a++];
		y[b][t] = 0;
	}
	y[b] = NULL;
	return (y);
}

