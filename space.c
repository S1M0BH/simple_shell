#include "shell.h"

/**
 * **_str_tow2 =>splits a string into words.
 * @str: the input string.
 * @d: the delimeter.
 * Return : a pointer to an array of strings, or NULL on failure.
 */

char **_str_tow2(char *str, char d)
{
	int i, j, k, m, num_w = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) || (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_w++;
	if (num_w == 0)
		return (NULL);
	s = malloc((1 + num_w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_w; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * *_str_dup =>Newly allocated space in memory.
 * @str: Input String.
 * Return: Depend Condition.
 */

char *_str_dup(const char *str)
{
	int i;
	int len;
	char *n;

	if (str == NULL)
		return (NULL);
	len = _str_len((char *)str);
	n = (char *) malloc(len + 1 * sizeof(char));
	if (n == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
	{
		n[i] = str[i];
	}
	n[i] = '\0';
	return (n);
}

/**
 * conv_str_int =>Convert string to integer.
 * @s: Input.
 * Return : Integer Converted.
 */

int conv_str_int(char *s)
{
	int i;
	int sn;
	unsigned int digt;

	i = 0;
	sn = 1;
	digt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sn *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			digt = (digt * 10) + (s[i] - '0');
		}
		else if (digt > 0)
			break;
		i++;
	}
	return (digt * sn);
}


/**
 * **_str_tow =>splits a string into words. Repeat delimiters are ignored.
 * @str: the input string.
 * @d: the delimeter string.
 * Return : a pointer to an array of strings, or NULL on failure.
 */

char **_str_tow(char *str, char *d)
{
	int i, j, k, m, num_w = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!my_delim(str[i], d) && (my_delim(str[i + 1], d) || !str[i + 1]))
			num_w++;

	if (num_w == 0)
		return (NULL);
	s = malloc((1 + num_w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_w; j++)
	{
		while (my_delim(str[i], d))
			i++;
		k = 0;
		while (!my_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
