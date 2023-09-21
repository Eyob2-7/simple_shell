#ifndef _SHELL_H_
#define _SHELL_H_


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define PATH_MAX_LENGTH 4096
#define PATH_SEPARATOR ":"

extern char **environ;

/* string_functions.c */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);

/* shell_functions.c */
char *_getenv(char *name);
char *get_path(void);
void shell_exit(char **args);
int shell_env(void);
int check_for_builtin(char **args);

/* util_function.c */
void _printf(char *str);
void free_tokens(char **ptr);
char *_memset(char *s, char b, unsigned int n);

/* more_shell_functions.c */
char **split_cmd(char *str, const char *delim);
char *find_in_path(char *command);
int execute(char *argv);




#endif

