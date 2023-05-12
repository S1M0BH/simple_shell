#include "shell.h"

/**
 * loop_shell -> Main Loop.
 * @info: Info Struct Pointer.
 * @av: Argument Vector.
 * Return: 0 Success, -1 Failure.
 */

int loop_shell(info_t *info, char **av)
{
	ssize_t r = 0;

	int buil_ret = 0;

	while (r != -1 && buil_ret != -2)
	{
		_clear_info(info);
		if (inter_active(info))
		_putee("$ ");
		_put_char(BUF_FLUSH);
		r = _get_input(info);
		if (r != -1)
		{
			_set_info(info, av);
			buil_ret = _find_builtin(info);
			if (buil_ret == -1)
				_find_cmd(info);
		}
		else if (inter_active(info))
			_putchar('\n');
		_free_info(info, 0);
	}
	write_hist(info);
	_free_info(info, 1);
	if (!inter_active(info) && info->stat)
		exit(info->stat);
	if (buil_ret == -2)
	{
		if (info->error_num == -1)
			exit(info->stat);
		exit(info->error_num);
	} return (buil_ret);
}
