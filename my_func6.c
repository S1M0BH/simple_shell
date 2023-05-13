#include "shell.h"

/**
 * sigintHandler =>blocks ctrl+C.
 * @sig_num: the signal number.
 * Return: void.
 */

void siginal_h(__attribute__((unused))int sig_num)
{
	_putee("\n");
	_putee("$ ");
	_putchar(BUF_FLUSH);
}


/**
 * _clear_info =>initializes info_t struct.
 * @info: struct address.
 */

void _clear_info(info_t *info)
{
	info->arg = NULL;
	info->args = NULL;
	info->path = NULL;
	info->arg_count = 0;
}



/**
 * write_hist =>creates a file, or appends to an existing file.
 * @info: the parameter struct.
 * Return : 1 on success, else -1.
 */

int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = _get_hist(info);
	list_t *node = NULL;
	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_put_strfd(node->str, fd);
		_put_fd('\n', fd);
	}
	_put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _build_hist_list =>adds entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buf: buffer.
 * @linecount: the history linecount, hist_count.
 * Return : Always 0.
 */

int _build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;
	if (info->history)
		node = info->history;
	_add_end_node(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * _renumber_hist =>renumbers the history linked list after changes.
 * @info: Structure containing potential arguments. Used to maintain.
 * Return: the new hist_count.
 */

int _renumber_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;
	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_count = i);
}