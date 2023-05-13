#include "shell.h"

/**
 * chang_dir =>Changes the current working directory.
 * @info: Parameter.
 * Return : Depend Condition.
 */

int chang_dir(info_t *info)
{
	char *s, *dir, buffer[1024];

	int chdir_ret;
	s = getcwd(buffer, 1024);
	if (!s)
		_putee("TODO: >>getcwd failure emsg here<<\n");
	if (!info->args[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_str_cmp(info->args[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_putee(s);
			_putchar('\n');

			return (1);
		}
		_putee(_get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->args[1]);
	if (chdir_ret == -1)
	{
		print_error_msg(info, "can't cd to ");
		_put_str(info->args[1]), _put_char('\n');
	}
	else
	{
		set_env(info, "OLDPWD", _get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	} return (0);
}

/**
 * my_cmd =>checks if a path is a command.
 * @info: Parameter.
 * @path: Parameter.
 * Return: Depend Condition.
 */

int my_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _find_builtin =>Finds a builtin command.
 * @info: Parameter.
 * Return: Depend Condition.
 */

int _find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _set_env},
		{"unsetenv", is_unset_env},
		{"cd", chang_dir},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_cmp(info->args[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].funct(info);

			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd =>Finds a command in the path.
 * @info: Parameter.
 */

void _find_cmd(info_t *info)
{
	char *path = NULL;

	int i, k;

	info->path = info->args[0];
	if (info->line_count_flag == 1)
	{
		info->line_count++;
		info->line_count_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!my_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _find_path(info, _get_env(info, "PATH="), info->args[0]);
	if (path)
	{
		info->path = path;
		_run_cmd(info);
	}
	else
	{
		if ((inter_active(info) || _get_env(info, "PATH=")
			|| info->args[0][0] == '/') && my_cmd(info, info->args[0]))
			_run_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->stat = 127;
			print_error_msg(info, "not found\n");
		}
	}
}

/**
 * _run_cmd =>Runs a command.
 * @info: Parameter.
 */

void _run_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->args, _get_as_env(info)) == -1)
		{
			_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->stat));
		if (WIFEXITED(info->stat))
		{
			info->stat = WEXITSTATUS(info->stat);
			if (info->stat == 126)
				print_error_msg(info, "Permission denied\n");
		}
	}
}
