#include "shell.h"


/**
 **_mem_set =>fills memory with a constant byte.
 *@s: the pointer to the memory area.
 *@b: the byte to fill *s with.
 *@n: the amount of bytes to be filled.
 *Return : (s) a pointer to the memory area s.
 */

char *_mem_set(char *s, char b, unsigned int n)
{
	unsigned int i;
	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _starts_with =>checks if needle starts with haystack.
 * @kach: string to search.
 * @needle: the substring to find.
 * Return : address of next char of haystack or NULL.
 */

char *_starts_with(const char *kach, const char *needle)
{
	while (*needle)
		if (*needle++ != *kach++)
			return (NULL);
	return ((char *)kach);
}

/**
 * my_chain =>test if current char in buffer is a chain delimeter.
 * @info: the parameter struct.
 * @buf: the char buffer.
 * @p: address of current position in buf.
 * Return : 1 if chain delimeter, 0 otherwise.
 */

int my_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->_cmd_buff_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->_cmd_buff_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->_cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _check_chain =>checks we should continue chaining based on last stat.
 * @info: the parameter struct.
 * @buf: the char buffer.
 * @p: address of current position in buf.
 * @i: starting position in buf.
 * @len: length of buf.
 * Return : Void.
 */

void _check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;
	if (info->_cmd_buff_type == CMD_AND)
	{
		if (info->stat)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->_cmd_buff_type == CMD_OR)
	{
		if (!info->stat)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * _replace_vars =>replaces vars in the tokenized string.
 * @info: the parameter struct.
 * Return : 1 if replaced, 0 otherwise.
 */

int _replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;
	for (i = 0; info->args[i]; i++)
	{
		if (info->args[i][0] != '$' || !info->args[i][1])
			continue;

		if (!_str_cmp(info->args[i], "$?"))
		{
			_replace_str(&(info->args[i]),
				_str_dup(conv_num(info->stat, 10, 0)));
			continue;
		}
		if (!_str_cmp(info->args[i], "$$"))
		{
			_replace_str(&(info->args[i]),
				_str_dup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts(info->env, &info->args[i][1], '=');
		if (node)
		{
			_replace_str(&(info->args[i]),
				_str_dup(_str_chr(node->str, '=') + 1));
			continue;
		}
		_replace_str(&info->args[i], _str_dup(""));
	}
	return (0);
}
