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

/* string_functions.c */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);

#endif

