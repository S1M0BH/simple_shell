#include "shell.h"

/**
 * unset_alias =>sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 * Return : Always 0 on success, 1 on error.
 */

int unset_alias(info_t *info, char *str)
{
	char *p, q;
	int ret;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	q = *p;
	*p = 0;
	ret = _delete_node(&(info->alias),
		_get_node_index(info->alias, _node_starts(info->alias, str, -1)));
	*p = q;
	return (ret);
}

/**
 * set_alias =>sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 * Return : Always 0 on success, 1 on error.
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (_add_end_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias =>prints an alias string.
 * @node: the alias node.
 * Return : Always 0 on success, 1 on error.
 */

int print_alias(list_t *node)
{
	char *p = NULL, *q = NULL;

	if (node)
	{
		p = _str_chr(node->str, '=');
		for (q = node->str; q <= p; q++)
		_putchar(*q);
		_putchar('\'');
		_putee(p + 1);
		_putee("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias =>mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain constant functtion prototype.
 *  Return : Always 0
 */

int _alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->arg_count == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->args[i]; i++)
	{
		p = _str_chr(info->args[i], '=');
		if (p)
			set_alias(info, info->args[i]);
		else
			print_alias(_node_starts(info->alias, info->args[i], '='));
	}

	return (0);
}

/**
 * _replace_alias =>replaces an aliases in the tokenized string.
 * @info: the parameter struct.
 * Return : 1 if replaced, 0 otherwise.
 */

int _replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _node_starts(info->alias, info->args[0], '=');
		if (!node)
			return (0);
		free(info->args[0]);
		p = _str_chr(node->str, '=');
		if (!p)
			return (0);
		p = _str_dup(p + 1);
		if (!p)
			return (0);
		info->args[0] = p;
	}
	return (1);
}
