#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Macro definitions for Read and Write Buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Chain Commands constants */
#define COMD_NORMAL	0
#define COMD_OR		1
#define COMD_AND		2
#define COMD_CHAIN	3

/*number_converter() macros */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*  getline() macros */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".shell_history"
#define HIST_MAX	4096

extern char **envcopy;


/**
 * struct liststring - define singly linked list
 * @mynum: number input
 * @mystr: string input
 * @next_node: pointer to next node in the list
 */
typedef struct liststring
{
	int mynum;
	char *mystr;
	struct liststring *next_node;
} data_str;

/**
 *struct infodata - pass pseudo-arguments to functions
 *@ag: string generated from getline function
 *@av: array of string arguments
 *@path: command path
 *@ac: arguments counter
 *@err_count: error counter
 *@err_code: error code for the exits function
 *@err_count_flag: if ON, then coun the number of lines
 *@file_name: file name of the program 
 *@envcopy: copy of environment var 
 *@envmodcopy: modified copy of envir1
 *@history: the history of nodes
 *@alias: node alias
 *@env_state_changed: is ON?, the change state
 *@cmd_status: status of executed command that is returned
 *@buff_comd: ON if state changed
 *@cmd_operator: cmd operators ||, &&, ;
 *@read_fd: read line input from file discriptor
 *@history_count: count the line number of the history
 */
typedef struct infodata
{
	char *ag;
	char **av;
	char *path;
	int ac;
	unsigned int err_count;
	int err_code;
	int err_count_flag;
	char *file_name;
	data_str *envcopy;
	data_str *history;
	data_str *alias;
	char **envmodcopy;
	int env_state_changed;
	int cmd_status;
	char **buff_comd;
	int cmd_operator;
	int read_fd;
	int history_count;
} list_str;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 *struct builtin - function for built in string commands
 *@built_type: flag variable
 *@built_func: function pointer
 */
typedef struct builtin
{
	char *built_type;
	int (*built_func)(list_str *);
} builtin_cmd_table;


/* shloop.c function prototype */
void cmd_check(list_str *);
void cmd_fork(list_str *);
int hsh(list_str *, char **);
int builtin_check(list_str *);

/* parser.c function prototype */
char *path_finder(list_str *, char *, char *);
int cmd_validate(list_str *, char *);
char *char_duplicate(char *, int, int);

/* loophsh.c function prototype */
int hshloop(char **);

/* errors.c function prototype */
void txt(char *);
int txtchar(char);
int txtfd(char c, int fd);
int etxtfd(char *str, int fd);

/* string.c prototype function */
int str_len(char *);
int str_compare(char *, char *);
char *str_start(const char *, const char *);
char *cat_str(char *, char *);

/* string1.c function prototype */
char *copy_str(char *, char *);
char *duplicate_str(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c prototype */
char *copystr(char *, char *, int);
char *catstr(char *, char *, int);
char *char_str(char *, char);

/* tokenizer.c function prototype */
char **tok1(char *, char *);
char **tok2(char *, char);

/* realloc.c  function prototype*/
char *set_mem(char *, char, unsigned int);
void free_mem(char **);
void *realloc_mem(void *, unsigned int, unsigned int);

/* memory.c function prototype */
int freed(void **);

/* _atoi.c function prototype */
int interactive(list_str *);
int check_delim(char, char *);
int check_alpha(int);
int strtoint(char *);

/* errors1.c function prototype */
int err1(char *);
void display_error(list_str *, char *);
int err_print(int, int);
char *conv_num(long int, int, int);
void comment_rem(char *);

/* builtin.c function prototype */
int exit_me(list_str *);
int cd_me(list_str *);
int help_me(list_str *);

/* builtin1.c function prototype */
int history_me(list_str *);
int alias_me(list_str *);

/*_getline.c function prototype */
ssize_t input_string(list_str *);
int _getline(list_str *, char **, size_t *);
void handler_signal(int);

/* getinfo.c function prototype */
void data_clear(list_str *);
void data_set(list_str *, char **);
void data_free(list_str *, int);

/* environ.c function prototype */
char *env_get(list_str *, const char *);
int env_me(list_str *);
int env_set(list_str *);
int env_unset(list_str *);
int env_populate(list_str *);

/* getenv.c function prototype */
char **env2_get(list_str *);
int env_unset2(list_str *, char *);
int env_set2(list_str *, char *, char *);

/* history.c function prototype */
char *file_hist(list_str *data);
int hist_write(list_str *data);
int hist_read(list_str *data);
int list_hist(list_str *data, char *buf, int linecount);
int hist_relist(list_str *data);

/* lists.c function prototype */
data_str *node_add(data_str **, const char *, int);
data_str *close_node_add(data_str **, const char *, int);
size_t print_data_list(const data_str *);
int node_index_del(data_str **, unsigned int);
void list_free(data_str **);

/* lists1.c function prototype */
size_t len_data(const data_str *);
char **list_string(data_str *);
size_t list_print(const data_str *);
data_str *start_node_(data_str *, char *, char);
ssize_t get_index_of_node(data_str *, data_str *);

/* vars.c function prototype */
int chain_check(list_str *, char *, size_t *);
void cmd_chain_check(list_str *, char *, size_t *, size_t, size_t);
int alias_replace(list_str *);
int var_replace(list_str *);
int str_replace(char **, char *);

#endif
