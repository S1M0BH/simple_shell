#include "shell.h"

/**
 * *_str_chr => Locate character in string.
 * @s: String.
 * @c: Character.
 * Return: Depend Condition
 */

char *_str_chr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (s + i);
	}
	return ('\0');
}

/**
 * *_str_cp => Copy String From Source Into Destinse.
 * @de: Empty Input.
 * @src: Input Source.
 * Return: Destinse String.
 */

char *_str_cp(char *de, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		de[i] = src[i];
		i++;
	}
	de[i] = '\0';
	return (de);
}

/**
 * _str_len => The length of a string.
 * @l: Input.
 * Return: i String Length
 */

int _str_len(char *l)
{
	int i;

	for (i = 0; l[i] != '\0'; i++)
	{
		continue;
	}
	return (i);
}

/**
 * *_str_cat => Appends the src string to the (de) string.
 * @de: Destination Input.
 * @src: Source Input.
 * Return: Destination.
 */

char *_str_cat(char *de, char *src)
{
	int i;
	int j;

	i = _str_len(de);
	for (j = 0; src[j] != '\0'; j++)
	{
		de[i] = src[j];
		i++;
	}
	de[i] = '\0';
	return (de);
}

/**
 * _str_cmp =>  Compares two strings.
 * @str1: First Input.
 * @str2: Second Input.
 * Return: 0 Or Different (Condition).
 */

int _str_cmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
