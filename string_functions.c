#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */

int _strlen(const char *s)
{
int count = 0;

while (*s != '\0')
{
count++;
s++;
}
return (count);
}

/**
 * _strcpy - copies a string
 * @dest: the destination string
 * @src: the source string
 *
 * Return: copied string
 */
char *_strcpy(char *dest, const char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * _strncmp - copies a string
 * @s1: first string
 * @s2: second string
 * @n: the length to be compared
 *
 * Return: returns 0 if strings are equal
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
while (n > 0)
{
if (*s1 != *s2)
{
return (*s1 - *s2);
}

/* Break if one of the strings terminates or n characters have been compared */
if (*s1 == '\0' || n == 0)
{
break;
}

s1++;
s2++;
n--;
}

return (0);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, const char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}



