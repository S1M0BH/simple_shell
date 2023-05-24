#include "shell.h"


/**
 * _list_to_str =>returns an array of strings of the list=>str.
 * @head: pointer to first node.
 * Return : array of strings.
 */

char **_list_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = _list_len(head), j;
	char **strs;
	char *str;
	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _str_cp(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list =>prints all elements of a list_t linked list.
 * @h: pointer to first node.
 * Return : size of list.
 */

size_t print_list(const list_t *h)
{
	size_t i = 0;
	while (h)
	{
		_putee(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_putee(h->str ? h->str : "(nil)");
		_putee("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _node_starts =>returns node whose string starts with prefix.
 * @node: pointer to list head.
 * @pfix: string to match.
 * @c: the next character after prefix to match.
 * Return : match node or null.
 */

list_t *_node_starts(list_t *node, char *pfix, char c)
{
	char *p = NULL;
	while (node)
	{
		p = _starts_with(node->str, pfix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}



/**
 * dupl_chart =>duplicates characters.
 * @pathstr: the PATH string.
 * @start: starting index.
 * @stop: stopping index.
 * Return : pointer to new buffer.
 */

char *dupl_chart(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _find_path =>finds this cmd in the PATH string.
 * @info: the info struct.
 * @pathstr: the PATH string.
 * @cmd: the cmd to find.
 * Return : full path of cmd if found or NULL.
 */

char *_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;
	if (!pathstr)
		return (NULL);
	if ((_str_len(cmd) > 2) && _starts_with(cmd, "./"))
	{
		if (my_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupl_chart(pathstr, curr_pos, i);
			if (!*path)
				_str_cat(path, cmd);
			else
			{
				_str_cat(path, "/");
				_str_cat(path, cmd);
			}
			if (my_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	} return (NULL);
}
