#include "shell.h"
/**
 * inter_active =>returns true if shell is interactive mode.
 * @info: struct address.
 * Return : 1 if interactive mode, 0 otherwise.
 */

int inter_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}
/**
 * _exitt =>exits the shell.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *  Return : exits with a given exit stat(0) if info.args[0] != "exit".
 */

int _exitt(info_t *info)
{
	int exitcheck;
	if (info->args[1])
	{
		exitcheck = conv_error(info->args[1]);
		if (exitcheck == -1)
		{
			info->stat = 2;
			print_error_msg(info, " Illegal number : ");
			_put_str(info->args[1]);
			_put_char('\n');
			return (1);
		}
		info->error_num = conv_error(info->args[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}
/**
 * conv_error =>converts a string to an integer.
 * @s: the string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise -1 on error.
 */

int conv_error(char *s)
{
	int i = 0;
	unsigned long int rest = 0;
	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			rest *= 10;
			rest += (s[i] - '0');
			if (rest > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rest);
}

/**
 * print_error_msg =>prints an error message.
 * @info: the parameter & return info struct.
 * @estr: string containing specified error type.
 * Return : 0 if no numbers in string, converted number otherwise -1 on error.
 */

void print_error_msg(info_t *info, char *estr)
{
	_put_str(info->file_name);
	_put_str(": ");
	print_base10(info->line_count, STDERR_FILENO);
	_put_str(": ");
	_put_str(info->args[0]);
	_put_str(": ");
	_put_str(estr);
}

/**
 * print_base10 =>function prints a decimal integer number base 10.
 * @input: the input.
 * @fd: the filedescriptor to write to.
 * Return : number of characters printed.
 */

int print_base10(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;
	if (fd == STDERR_FILENO)
		__putchar = _put_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}
