#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
 *_putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}


/**
 * _atoi - Converts a string to an integer.
 * @str: The string to convert.
 *
 * Return: The integer value of the string.
 */
int _atoi(const char *str)
{
int i, sign;
unsigned int num;

i = 0;
sign = 1;
num = 0;

while (str[i] != '\0')
{
if (str[i] == '-')
sign *= -1;
else if (str[i] >= '0' && str[i] <= '9')
num = (num * 10) + (str[i] - '0');
else
break;
i++;
}
return (num *sign);
}

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}
