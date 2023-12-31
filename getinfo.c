#include "shell.h"

/**
 * struct_clear - function to initialize list_str
 * @data: address of struct_clear 
 */
void struct_clear(list_str *data)
{
	data->ag = NULL;
	data->av = NULL;
	data->path = NULL;
	data->ac = 0;
}

/**
 * struct_set - function to initialize list_str
 * @data: address of list_str
 * @av: argument vector
 */
void struct_set(list_str *data, char **av)
{
	int i = 0;

	data->file_name = av[0];
	if (data->ag)
	{
		data->av = tok1(data->ag, " \t");
		if (!data->av)
		{

			data->av = malloc(sizeof(char *) * 2);
			if (data->av)
			{
				data->av[0] = duplicate_str(data->ag);
				data->av[1] = NULL;
			}
		}
		for (i = 0; data->av && data->av[i]; i++)
			;
		data->ac = i;

		alias_replace(data);
		var_replace(data);
	}
}

/**
 * struct_free - Function to free list_str
 * @data: address of list_str
 * @allfree: set to true if all field are to befreed
 */
void struct_free(list_str *data, int allfree)
{
	free_mem(data->av);
	data->av = NULL;
	data->path = NULL;
	if (allfree)
	{
		if (!data->buff_comd)
			free(data->ag);
		if (data->envcopy)
			list_free(&(data->envcopy));
		if (data->history)
			list_free(&(data->history));
		if (data->alias)
			list_free(&(data->alias));
		free_mem(data->envmodcopy);
			data->envmodcopy = NULL;
		freed((void **)data->buff_comd);
		if (data->read_fd > 2)
			close(data->read_fd);
		_putchar(BUF_FLUSH);
	}
}
