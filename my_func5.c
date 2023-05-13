#include "shell.h"


/**
 * _get_input =>gets a line minus the newline.
 * @info: parameter struct.
 * Return : bytes read.
 */

ssize_t _get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;
	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		_check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (my_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->_cmd_buff_type = CMD_NORM;
		}
		*buf_p = p;
		return (_str_len(p));
	}
	*buf_p = buf;
	return (r);
}



/**
 * _getline =>gets the next line of input from STDIN.
 * @info: parameter struct.
 * @ptr: address of pointer to buffer, preallocated or NULL.
 * @length: size of preallocated ptr buffer if not NULL.
 * Return : s.
 */

int _get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloct(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strn_cat(new_p, buf + i, k - i);
	else
		_strn_cp(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * _set_info =>initializes info_t struct.
 * @info: struct address.
 * @av: argument vector.
 */

void _set_info(info_t *info, char **av)
{
	int i = 0;
	info->file_name = av[0];
	if (info->arg)
	{
		info->args = _str_tow(info->arg, " \t");
		if (!info->args)
		{

			info->args = malloc(sizeof(char *) * 2);
			if (info->args)
			{
				info->args[0] = _str_dup(info->arg);
				info->args[1] = NULL;
			}
		}
		for (i = 0; info->args && info->args[i]; i++)
			;
		info->arg_count = i;

		_replace_alias(info);
		_replace_vars(info);
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