#include "shell.h"

/**
 * _get_as_env =>Get the environment as an array of strings.
 * @info: Pointer.
 * Return : Depend Condition.
 */

char **_get_as_env(info_t *info)
{
	if (!info->environ || info->env_chang)
	{
		info->environ = _list_to_str(info->env);
		info->env_chang = 0;
	}

	return (info->environ);
}

/**
 * unset_env =>Remove an environment variable.
 * @info: Pointer.
 * @var: Pointer.
 * Return : Depend Condition.
 */

int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_chang = _delete_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_chang);
}

/**
 * set_env =>Set an environment variable.
 * @info: Pointer.
 * @var: Pointer.
 * @val: Pointer.
 * Return : Depend Condition.
 */

int set_env(info_t *info, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_str_len(var) + _str_len(val) + 2);
	if (!buf)
		return (1);
	_str_cp(buf, var);
	_str_cat(buf, "=");
	_str_cat(buf, val);
	node = info->env;
	while (node)
	{
		p = _starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_chang = 1;
			return (0);
		}
		node = node->next;
	}
	_add_end_node(&(info->env), buf, 0);
	free(buf);
	info->env_chang = 1;
	return (0);
}


/**
 * _env_list =>Creates a linked list of the environment.
 * @info: Pointer.
 * Return : Depend Condition.
 */

int _env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_end_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * _replace_str =>Replace a string with another.
 * @old: Pointer.
 * @new: Pointer.
 * Return : Depend Condition.
 */

int _replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
