#include "shell.h"

/**
 * hsh - this is the main  loop
 * @data: this is the  parameter & return list_str struct
 * @av: is the argument vector of main.c
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(list_str *data, char **av)
{
	ssize_t rr = 0;
	int return_builtin = 0;

	while (rr != -1 && return_builtin != -2)
	{
		data_free(data, 0);
		if (interactive(data))
			_puts("$ ");
		txtchar(BUF_FLUSH);
		rr = input_string(data);
		if (rr != -1)
		{
			data_set(data, av);
			return_builtin = builtin_check(data);
			if (return_builtin == -1)
				cmd_check(data);
		}
		else if (interactive(data))
			_putchar('\n');
		data_free(data, 0);
	}
	hist_write(data);
	data_free(data, 1);
	if (!interactive(data) && data->cmd_status)
		exit(data->cmd_status);
	if (return_builtin == -2)
	{
		if (data->err_code == -1)
			exit(data->cmd_status);
		exit(data->err_code);
	}
	return return_builtin;
}

/**
 * builtin_check - checks for a builtin comand
 * @data: this is the parameter and return data of list_str
 *
 * Return: -1 if builtin command is not found
 *          0 if builtin is found and successfull executed,
 *          1 if builtin command is found but not successfully exec'd
 *         -2 if builtin command have an exit signal
 */
int builtin_check(list_str *data)
{
	int a, return_builtin = -1;
	builtin_cmd_table builtintbl[] = {
		{"exit", exit_me},
		{"env", env_me},
		{"help", help_me},
		{"history", history_me},
		{"setenv", env_set},
		{"unsetenv", env_unset},
		{"cd", cd_me},
		{"alias", alias_me},
		{NULL, NULL}};

	for (a = 0; builtintbl[a].built_type; a++)
		if (str_compare(data->av[0], builtintbl[a].built_type) == 0)
		{
			data->err_count++;
			return_builtin = builtintbl[a].built_func(data);
			break;
		}
	return return_builtin;
}

/**
 * cmd_check - this function checksfor  a command in PATH
 * @data: this is the parameter & return list_str struct
 *
 * Return: void on success
 */
void cmd_check(list_str *data)
{
	char *path = NULL;
	int a, b;

	data->path = data->av[0];
	if (data->err_count_flag == 1)
	{
		data->err_count++;
		data->err_count_flag = 0;
	}
	for (a = 0, b = 0; data->ag[a]; a++)
		if (!check_delim(data->ag[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = path_finder(data, env_get(data, "PATH="), data->av[0]);
	if (path)
	{
		data->path = path;
		cmd_fork(data);
	}
	else
	{
		if ((interactive(data) || env_get(data, "PATH=") || data->av[0][0] == '/') && cmd_validate(data, data->av[0]))
			cmd_fork(data);
		else if (*(data->ag) != '\n')
		{
			data->cmd_status = 127;
			display_error(data, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks process
 * @data: the list_str struct
 *
 * Return: void on success
 */
void cmd_fork(list_str *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->av, env_get(data)) == -1)
		{
			data_free(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(data->cmd_status));
		if (WIFEXITED(data->cmd_status))
		{
			data->cmd_status = WEXITSTATUS(data->cmd_status);
			if (data->cmd_status == 126)
				display_error(data, "Permission denied\n");
		}
	}
}

