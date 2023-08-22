#ifndef _SHELL_H_
#define _SHELL_H_
#define _GNU_SOURCE
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
#include <stdarg.h>
#include <ctype.h>
/*macros*/
#define PATH_MAX_LENGTH 4096
#define PATH_SEPARATOR ":"
#define PROMPT "$ "
/* Global Variables */
extern char **environ;
char *__getenv(char *name);
/* signals.c */
void handle_sigint(int sig);
void handle_sigquit(int sig);
void handle_sigstp(int sig);
/* printers.c */
void _puts(char *str);
void _puterror(char *err);
/* shell_functions.c */
int execute(char **args);
void prompt(void);
char *get_input(void);
void free_last_input(void);
char *find_in_path(char *command);
/* parsers.c */
char **tokenize(char *str, const char *delim);
char **tokenize_input(char *input);
char *get_path(void);
void free_tokens(char **ptr);
/* builtin_functions1.c */
int check_for_builtin(char **args);
void shell_help(void);
void shell_exit(char **args);
void shell_cd(char **args);
/* builtin_functions2.c */
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_env(void);
int shell_clear(char **args);
/* util_functions1.c */
int _strlen(const char *);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *, char *);
char *_strcat(char *, const char *);
/* util_functions2.c */
char *_strdup(const char *);
int _putchar(char);
int _atoi(const char *str);
char *_memset(char *, char, unsigned int);
#endif
