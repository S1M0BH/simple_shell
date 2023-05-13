#include "shell.h"

/**
 * _free_str =>Free string.
 * @pi: Pointer.
 */

void _free_str(char **pi)
{
	char **a = pi;

	if (!pi)
		return;
	while (*pi)
		free(*pi++);
	free(a);
}

/**
 * _free_ptr =>Frees a pointer.
 * @ptr: Pointer.
 * Return : Depend Condition.
 */

int _free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _free_list =>Free list.
 * @hed_ptr: Pointer.
 */

void _free_list(list_t **hed_ptr)
{
	list_t *node, *next_node, *head;

	if (!hed_ptr || !*hed_ptr)
		return;
	head = *hed_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*hed_ptr = NULL;
}

/**
 * _free_info =>Free info.
 * @info: Pointer.
 * @all: Depend Condition.
 */

void _free_info(info_t *info, int all)
{
	_free_str(info->args);
	info->args = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->_cmd_buff)
			free(info->arg);
		if (info->env)
			_free_list(&(info->env));
		if (info->history)
			_free_list(&(info->history));
		if (info->alias)
			_free_list(&(info->alias));
		_free_str(info->environ);
			info->environ = NULL;
		_free_ptr((void **)info->_cmd_buff);
		if (info->read_fd > 2)
			close(info->read_fd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * _realloct =>reallocates a block of memory.
 * @ptr: pointer to previous malloc'ated block.
 * @old_s: byte size of previous block.
 * @new_s: byte size of new block
 * Return : pointer to da ol'block nameen.
 */

void *_realloct(void *ptr, unsigned int old_s, unsigned int new_s)
{
	char *p;

	if (!ptr)
		return (malloc(new_s));
	if (!new_s)
		return (free(ptr), NULL);
	if (new_s == old_s)
		return (ptr);

	p = malloc(new_s);
	if (!p)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		p[old_s] = ((char *)ptr)[old_s];
	free(ptr);
	return (p);
}
