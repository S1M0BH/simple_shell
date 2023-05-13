#include "shell.h"




/**
 * _help =>changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *  Return : Always 0.
 */

int _help(info_t *info)
{
	char **_arg_array;

	_arg_array = info->args;
	_putee(" help call works. Function not yet implemented : \n");
	if (0)
		_putee(*_arg_array);
	return (0);
}

/**
 * _history =>displays the history list, one command by line, preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *  Return : Always 0.
 */

int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}



/**
 *_eputs =>prints an input string.
 * @str: the string to be printed.
 * Return : Nothing.
 */

void _put_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_put_char(str[i]);
		i++;
	}
}

/**
 * _eputchar =>writes the character c to stderr.
 * @c: The character to print.
 * Return : On success 1,On error, -1 is returned, and errno is set appropriately.
 */

int _put_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * conv_num =>converter function, a clone of itoa.
 * @num: number.
 * @base: base.
 * @flg: argument flags.
 * Return : string.
 */

char *conv_num(long int num, int base, int flg)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flg & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}