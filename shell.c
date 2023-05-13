#include "shell.h"

/**
 * main -> Entry point.
 * @ac: Argument Count.
 * @av: Argument Vector.
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 *
*/

int main(int ac, char **av)
{
	info_t inf[] = {INFO_INIT};
	int fd;
	fd = 2;
	asm ("mov %1, %0\n\t"
		 "add $3, %0" : "=r" (fd) : "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_put_str(av[0]);
				_put_str(": 0: Can't open ");
				_put_str(av[1]);
				_put_char('\n');
				_put_char(BUF_FLUSH);
				exit(127);
			} return (EXIT_FAILURE);
		}
		inf->read_fd = fd;
	}

	_env_list(inf);

	read_hist(inf);

	loop_shell(inf, av);
	
	return (EXIT_SUCCESS);
}
