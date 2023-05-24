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
 * _get_hist =>gets the history file.
 * @info: parameter struct
 *
 * Return : allocated string containg history file
 */

char *_get_hist(info_t *info)
{
	char *buf, *dir;
	dir = _get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_str_len(dir) + _str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_str_cp(buf, dir);
	_str_cat(buf, "/");
	_str_cat(buf, HIST_FILE);
	return (buf);
}
/**
 * _get_node_index =>gets the index of a node.
 * @head: pointer to list head.
 * @node: pointer to the node.
 * Return : index of node or -1.
 */

ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;
	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}