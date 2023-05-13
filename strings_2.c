#include "shell.h"

/**
 * _putchar => Writes the character c to stdout.
 * @cpr: The character to print.
 * Return: On success 1.
*/

int _putchar(char cpr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cpr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (cpr != BUF_FLUSH)
		buf[i++] = cpr;
	return (1);
}

/**
 * _putee => Prints a string.
 * @st: Input.
 */

void _putee(char *st)
{
	int i;

	for (i = 0; st[i] != '\0'; i++)
	{
		_putchar(st[i]);
	}
}

/**
 * my_alpha => checks for a alphabetic character.
 * @ca: Character Of is alpha.
 * Return: 1 and 0 (Condition).
 */

int my_alpha(int ca)
{
	if (ca >= 'a' && ca <= 'z')
	{
		return (1);
	}
	else if (ca >= 'A' &&  ca <= 'Z')
	{
		return (1);
	}
	else
		return (0);
}

/**
 * *_strn_cp => Copy Number Of String From Source Into Destinse.
 * @de: Empty Input.
 * @src: Input Source.
 * @n: Input Number.
 * Return: Destinse String.
 */

char *_strn_cp(char *de, char *src, int n)
{
	int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		de[i] = src[i];
		i++;
	}
	while (i < n)
	{
		de[i] = '\0';
		i++;
	}
	return (de);
}

/**
 * *_strn_cat => Appends Selected Number Elements src string to the dest string.
 * @de: Destination Input.
 * @src: Source Input.
 * @n: Number Elements.
 * Return: Destination.
 */

char *_strn_cat(char *de, char *src, int n)
{
	int i;
	
	int j;

	i = _str_len(de);
	for (j = 0; de[j] != '\0' && j < n; j++)
	{
		de[i] = src[j];
		i++;
	}
	de[i] = '\0';
	return (de);
}
