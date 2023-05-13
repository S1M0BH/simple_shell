#include "shell.h"


/**
 * _put_fd =>writes the character c to given fd.
 * @c: The character to print.
 * @fd: The filedescriptor to write to.
 * Return : On success 1,On error, -1 is returned, and errno is set appropriately.
 */

int _put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_put_sfd =>prints an input string.
 * @str: the string to be printed.
 * @fd: the filedescriptor to write to.
 * Return : the number of chars put.
 */

int _put_strfd(char *str, int fd)
{
	int i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i += _put_fd(*str++, fd);
	}
	return (i);
}




/**
 * remove_comments =>function replaces first instance of # with \0.
 * @buf: address of the string to modify.
 * Return : Always 0.
 */

void rm_cmd(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * input_buf =>buffers chained commands.
 * @info: parameter struct.
 * @buf: address of buffer.
 * @len: address of len var.
 * Return : bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, siginal_h);
#if USE_GETLINE
	r = getline(buf, &len_p, stdin);
#else
		r = _get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->line_count_flag = 1;
			rm_cmd(*buf);
			_build_hist_list(info, *buf, info->hist_count++);
			{
				*len = r;
				info->_cmd_buff = buf;
			}
		}
	} return (r);
}
/**
 * read_buf =>reads a buffer.
 * @info: parameter struct.
 * @buf: buffer.
 * @i: size.
 * Return : r.
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;
	if (*i)
		return (0);
	r = read(info->read_fd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}