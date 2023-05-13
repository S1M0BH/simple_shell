#include "shell.h"


/**
 * my_delim =>checks if character is a delimeter.
 * @c: the char to check.
 * @dlm: the delimeter string.
 * Return : 1 if true, 0 if false.
 */

int my_delim(char c, char *dlm)
{
	while (*dlm)
		if (*dlm++ == c)
			return (1);
	return (0);
}
/**
 * _get_env =>gets the value of an environ variable.
 * @info: Structure containing potential arguments. Used to maintain.
 * @name: env var name.
 * Return : the value.
 */

char *_get_env(info_t *info, const char *name)
{
	list_t *node = info->env;

	char *p;

	while (node)
	{
		p = _starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _set_env =>Initialize a new environment variable,or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *  Return : Always 0.
 */

int _set_env(info_t *info)
{
	if (info->arg_count != 3)
	{
		_put_str(" Incorrect number of arguements : \n");
		return (1);
	}
	if (set_env(info, info->args[1], info->args[2]))
		return (0);
	return (1);
}

/**
 * is_unset_env =>Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *  Return : Always 0.
 */

int is_unset_env(info_t *info)
{
	int i;

	if (info->arg_count == 1)
	{
		_put_str(" Too few arguements : \n");
		return (1);
	}
	for (i = 1; i <= info->arg_count; i++)
		unset_env(info, info->args[i]);

	return (0);
}

/**
 * _env =>prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return : Always 0.
 */

int _env(info_t *info)
{
	_print_list_str(info->env);
	return (0);
}
