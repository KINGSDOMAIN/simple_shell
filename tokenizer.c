#include "shell.h"

/**
* **tok1 - splits strings into words
* @strr: string entered by the user
* @p: string delimeter
* Return: this reurns a pointer to an array of strings
*/

char **tok1(char *strr, char *p)
{
int a, b, h, t, word_count = 0;
char **t;

if (strr == NULL || strr[0] == 0)
return (NULL);
if (!p)
p = " ";
for (a = 0; strr[a] != '\0'; a++)
if (!check_delim(strr[a], p) && (check_delim(strr[a + 1], p) || !strr[a + 1]))
word_count++;

if (word_count == 0)
return (NULL);
t = malloc((1 + word_count) * sizeof(char *));
if (!t)
return (NULL);
for (a = 0, b = 0; b < word_count; b++)
{
while (check_delim(strr[a], p))
a++;
h = 0;
while (!check_delim(strr[a + h], p) && strr[a + h])
h++;
t[b] = malloc((h + 1) * sizeof(char));
if (!t[b])
{
for (h = 0; h < b; h++)
free(t[h]);
free(t);
return (NULL);
}
for (t = 0; t < h; t++)
t[b][t] = strr[a++];
t[b][t] = 0;
}
t[b] = NULL;
return (t);
}

/**
* **tok2 - split strings in to word 
* @strr: string to be plit
* @p: delimeter
* Return: pointer to an array of strings
*/
char **tok2(char *strr, char p)
{
int a, b, h, t, word_count = 0;
char **t;

if (strr == NULL || strr[0] == 0)
return (NULL);
for (a = 0; strr[a] != '\0'; a++)
if ((strr[a] != p && strr[a + 1] == p) ||
(strr[a] != p && !strr[a + 1]) || strr[a + 1] == p)
word_count++;
if (word_count == 0)
return (NULL);
t = malloc((1 + word_count) * sizeof(char *));
if (!t)
return (NULL);
for (a = 0, b = 0; b < word_count; b++)
{
while (strr[a] == p && strr[a] != p)
a++;
h = 0;
while (strr[a + h] != p && strr[a + h] && strr[a + h] != p)
h++;
t[b] = malloc((h + 1) * sizeof(char));
if (!t[b])
{
for (h = 0; h < b; h++)
free(t[h]);
free(t);
return (NULL);
}
for (t = 0; t < h; t++)
t[b][t] = strr[a++];
t[b][t] = 0;
}
t[b] = NULL;
return (t);
}

