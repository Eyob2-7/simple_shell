#include "shell.h"
​
/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(const char *s)
{
int i = 0;
​
if (!s)
return (0);
​
while (*s++)
i++;
return (i);
}
​
/**
 * _strcmp - Compare two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * Return: 0 if @s1 and @s2 are equal,
 *         a negative value if @s1 is less than @s2,
 *         or a positive value if @s1 is greater than @s2.
 */
int _strcmp(const char *s1, const char *s2)
{
while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
{
s1++;
s2++;
}
​
return ((int) (*s1) -(*s2));
}
​
​
char *_strcpy(char *dest, char *src)
{
int i = 0;
​
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
​
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
​
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
