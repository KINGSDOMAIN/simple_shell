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
_eputchar(BUF_FLUSH);
rr = get_input(data);
if (rr != -1)
{
set_data(data, av);
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
if (!interactive(data) && data->status)
exit(data->status);
if (return_builtin == -2)
{
if (data->err_count == -1)
exit(data->status);
exit(data->err_count);
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

for (a = 0; builtintbl[a].type; a++)
if (string_compare(data->av[0], builtintbl[a].type) == 0)
{
data->err_count++;
return_builtin = builtintbl[a].func(data);
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
if (!is_delim(data->ag[a], " \t\n"))
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
if ((interactive(data) || env_get(data, "PATH=") || data->av[0][0] == '/') && is_cmd(data, data->av[0]))
cmd_fork(data);
else if (*(data->ag) != '\n')
{
data->status = 127;
err_print(data, "not found\n");
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
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(data->status));
if (WIFEXITED(data->status))
{
data->status = WEXITSTATUS(data->status);
if (data->status == 126)
err_print(data, "Permission denied\n");
}
}
}

