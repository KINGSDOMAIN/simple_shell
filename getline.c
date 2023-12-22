#include "shell.h"


/**
 * handler_signal - handles ctr c
 * @num_sig: signal value
 *
 * Return: on success void
 */
void handler_signal(__attribute__((unused))int num_sig)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}

/**
 * input_stream -  chain commands
 * @data: information about teh struct
 * @mybuf:the  address of the input_stream
 * @mylen: the address of the lenght variable
 *
 * Return: size of bytes read
 */
ssize_t input_stream(list_str *data, char **mybuf, size_t *mylen)
{
	ssize_t rr = 0;
	size_t lenn = 0;

	if (!*mylen)
	{
		free(*mybuf);
		*mybuf = NULL;
		signal(SIGINT, handler_signal);
#if USE_GETLINE
		rr = getline(mybuf, &lenn, stdin);
#else
		rr = _getline(data, mybuf, &lenn);
#endif
		if (rr > 0)
		{
			if ((*mybuf)[rr - 1] == '\n')
			{
				(*mybuf)[rr - 1] = '\0';
				rr--;
			}
			data->err_count_flag = 1;
			comment_rem(*mybuf);
			list_hist(data, *mybuf, data->history_count++);
			
			{
				*mylen = rr;
				data->buff_comd = mybuf;
			}
		}
	}
	return (rr);
}

/**
 * get_input_stream - gets a line minus the newline
 * @data: this is a struct
 *
 * Return: number of bytes read
 */
ssize_t get_input_stream(list_str *data)
{
	static char *mybuf;
	static size_t a, b, mylen;
	ssize_t rr = 0;
	char **buffer = &(data->ag), *p;

	_putchar(BUF_FLUSH);
	rr = input_stream(data, &mybuf, &mylen);
	if (rr == -1)
		return (-1);
	if (mylen)
	{
		b = b;
		p = mybuf + a;

		cmd_chain_check(data, mybuf, &b, a, mylen);
		while (b < mylen)
		{
			if (chain_check(data, mybuf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= mylen)
		{
			a = mylen = 0;
			data->cmd_operator = COMD_NORMAL;
		}

		*buffer = p;
		return (str_len(p));
	}

	*buffer = mybuf;
	return (rr);
}

/**
 * read_input_buf - reads the input stream buffer
 * @data: the parameter struct
 * @mybuf: stream buffer
 * @a: buffer size
 *
 * Return: on sucess return rr
 */
ssize_t read_input_buf(list_str *data, char *mybuf, size_t *a)
{
	ssize_t rr = 0;

	if (*a)
		return (0);
	rr = read(data->read_fd, mybuf, READ_BUF_SIZE);
	if (rr >= 0)
		*a = rr;
	return (rr);
}

/**
 * _getline - enter input from STDIN
 * @data: struct informations
 * @ptr: address of struct buff
 * @length: the size of buffer
 *
 * Return: on success return bb
 */
int _getline(list_str *data, char **ptr, size_t *length)
{
	static char mybuf[READ_BUF_SIZE];
	static size_t a, mylen;
	size_t gg;
	ssize_t rr = 0, bb = 0;
	char *pp = NULL, *pp_new = NULL, *cc;

	pp = *ptr;
	if (pp && length)
		bb = *length;
	if (a == mylen)
		a = mylen = 0;

	rr = read_input_buf(data, mybuf, &mylen);
	if (rr == -1 || (rr == 0 && mylen == 0))
		return (-1);

	cc = char_str(mybuf + a, '\n');
	gg = cc ? 1 + (unsigned int)(cc - mybuf) : mylen;
	pp_new = realloc(pp, bb ? bb + gg : gg + 1);
	if (!pp_new) /* No success on Malloc process */
		return (pp ? free(pp), -1 : -1);

	if (bb)
		catstr(pp_new,  mybuf + a, gg - a);
	else
		copystr(pp_new, mybuf + a, gg - a + 1);

	bb += gg - a;
	a = gg;
	pp = pp_new;

	if (length)
		*length = bb;
	*ptr = pp;
	return (bb);
}
