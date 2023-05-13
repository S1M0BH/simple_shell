#include "shell.h"

/**
 * read_hist =>Reads history file into a linked list.
 * @info: Pointer.
 * Return: Depend Condition.
 */

int read_hist(info_t *info)
{
	int i, last = 0, l_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _get_hist(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			_build_hist_list(info, buf + last, l_count++);
			last = i + 1;
		}
	if (last != i)
		_build_hist_list(info, buf + last, l_count++);
	free(buf);
	info->hist_count = l_count;
	while (info->hist_count-- >= HIST_MAX)
		_delete_node(&(info->history), 0);
	_renumber_hist(info);
	return (info->hist_count);

	
}
