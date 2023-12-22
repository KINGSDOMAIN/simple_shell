#include "shell.h"

/**
 * env2_get - returns a copy of the environ string
 * @data: our struc controller 
 * Return: 0 on success
 */
char **env2_get(list_str *data)
{
	if (!data->envmodcopy || data->env_state_changed)
	{
		data->envmodcopy = list_string(data->envcopy);
		data->env_state_changed = 0;
	}

	return (data->envmodcopy);
}

/**
 * env_unset2 - Get rid of environment variable
 * @data: Struct controller
 * Return: 1 if removed else return 0
 * @strvar:  string variable
 */
int env_unset2(list_str *data, char *strvar)
{
	data_str *mynode = data->envcopy;
	size_t a = 0;
	char *y;

	if (!mynode || !strvar)
		return (0);

	while (mynode)
	{
		y = str_start(mynode->mystr, strvar);
		if (y && *y == '=')
		{
			data->env_state_changed = node_index_del(&(data->envcopy), a);
			a = 0;
			mynode = data->envcopy;
			continue;
		}
		mynode = mynode->next_node;
		a++;
	}
	return (data->env_state_changed);
}

/**
 * env_set2 - set new environment
 * @data: Struct controller
 * @strvar: string environment variable
 * @strvalue:string environment value
 *  Return: 0 on success
 */
int env_set2(list_str *data, char *strvar, char *strvalue)
{
	char *mybuf = NULL;
	data_str *mynode;
	char *y;

	if (!strvar || !strvalue)
		return (0);

	mybuf = malloc(str_len(strvar) + str_len(strvalue) + 2);
	if (!mybuf)
		return (1);
	copy_str(mybuf, strvar);
	cat_str(mybuf, "=");
	cat_str(mybuf, strvalue);
	mynode = data->envcopy;
	while (mynode)
	{
		y = str_start(mynode->mystr, strvar);
		if (y && *y == '=')
		{
			free(mynode->mystr);
			mynode->mystr = mybuf;
			data->env_state_changed = 1;
			return (0);
		}
		mynode = mynode->next_node;
	}
	close_node_add(&(data->envcopy), mybuf, 0);
	free(mybuf);
	data->env_state_changed = 1;
	return (0);
}
