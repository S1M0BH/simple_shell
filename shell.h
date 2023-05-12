#ifndef _SHELL_PLUS
#define _SHELL_PLUS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple__SHELL_PLUSistory"
#define HIST_MAX	4096
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

extern char **environ;

/**
 * struct liststr - singly linked list.
 * @num: the number field.
 * @str: a string.
 * @next: points to the next node.
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct.
 *@arg: a string generated from getline containing arguements.
 *@args: an array of strings generated from arg.
 *@path: a string path for the current command.
 *@arg_count: the argument count.
 *@line_count: the error count.
 *@error_num: the error code for exit()s.
 *@line_count_flag: if on count this line of input.
 *@file_name: the program filename.
 *@env: linked list local copy of environ.
 *@environ: custom modified copy of environ from LL env.
 *@history: the history node.
 *@alias: the alias node.
 *@env_chang: on if environ was changed.
 *@stat: the return status of the last exec'd command.
 *@_cmd_buff: address of pointer to _cmd_buff, on if chaining.
 *@_cmd_buff_type: CMD_type ||, &&, ;
 *@read_fd: the fd from which to read line input.
 *@hist_count: the history line number count.
 */

typedef struct passinfo
{
	char *arg;
	char **args;
	char *path;
	int arg_count;
	unsigned int line_count;
	int error_num;
	int line_count_flag;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_chang;
	int stat;
	char **_cmd_buff;
	int _cmd_buff_type;
	int read_fd;
	int hist_count;
} info_t;

/**
 *struct builtin - contains a builtin string and related function.
 *@type: the builtin command flag.
 *@funct: the function.
 */

typedef struct builtin
{
	char *type;
	int (*funct)(info_t *);
} builtin_table;

int loop_shell(info_t *, char **);
int _find_builtin(info_t *);
void _find_cmd(info_t *);
void _run_cmd(info_t *info);
int my_cmd(info_t *, char *);
char *dupl_chart(char *, int, int);
char *_find_path(info_t *, char *, char *);
/*int loop_hsh(char **);*/
void _put_str(char *);
int _put_char(char);
int _put_fd(char c, int fd);
int _put_strfd(char *str, int fd);
int _str_len(char *);
int _str_cmp(char *, char *);
char *_starts_with(const char *, const char *);
char *_str_cat(char *, char *);
char *_str_cp(char *, char *);
char *_str_dup(const char *);
void _putee(char *);
int _putchar(char);
char *_strn_cp(char *, char *, int);
char *_strn_cat(char *, char *, int);
char *_str_chr(char *, char);
char **_str_tow(char *, char *);
char *_mem_set(char *, char, unsigned int);
void _free_str(char **);
void *_realloct(void *, unsigned int, unsigned int);
int _free_ptr(void **);
int inter_active(info_t *);
int my_delim(char, char *);
int my_alpha(int);
int conv_str_int(char *);
int conv_error(char *);
void print_error_msg(info_t *, char *);
int print_base10(int, int);
char *conv_num(long int, int, int);
void rm_cmd(char *);
int _exit(info_t *);
int chang_dir(info_t *info);
int _help(info_t *);
int _history(info_t *);
int _alias(info_t *);
char **_str_tow(char *str, char d);
ssize_t _get_input(info_t *);
int _get_line(info_t *, char **, size_t *);
void siginal_h(int);
void _clear_info(info_t *);
void _set_info(info_t *, char **);
void _free_info(info_t *, int);
char *_get_env(info_t *, const char *);
int _env(info_t *);
int _set_env(info_t *);
int is_unset_env(info_t *);
int _env_list(info_t *);
char **_get_as_env(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);
char *_get_hist(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int _build_hist_list(info_t *info, char *buf, int linecount);
int _renumber_hist(info_t *info);
list_t *_add_node(list_t **, const char *, int);
list_t *_add_end_node(list_t **, const char *, int);
int _delete_node(list_t **, unsigned int);
size_t _print_list_str(const list_t *);
void _free_list(list_t **);
size_t _list_len(const list_t *);
char **_list_to_str(list_t *);
size_t print_list(const list_t *);
int _replace_alias(info_t *);
int _replace_vars(info_t *);
int _replace_str(char **, char *);
list_t *_node_starts(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);
int my_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);



#endif
