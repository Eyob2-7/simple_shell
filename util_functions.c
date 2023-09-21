#include "shell.h"

/**
 * _puts - Prints a string to the standard output stream
 * @str: The string to print
 *
 * Description: This function prints the given string to the standard output
 * stream. It calculates the length of the string and uses the write system
 * call to output the string.
 *
 * Return: None
 */
void _printf(char *str)
{
	size_t len = _strlen(str); /* Calculate the length of the string */
	ssize_t num_written; /* Number of characters written */

	/* Write the string to the standard output stream */
	num_written = write(STDOUT_FILENO, str, len);

	/* Check for write error */
	if (num_written == -1)
	{
		perror("write");
	}
}

/**
 * free_tokens - frees memory allocated dynamically by tokenize()
 * @ptr: pointer to allocated memory
 *
 * Return: void.
 */
void free_tokens(char **ptr)
{
	int i;

	for (i = 0; ptr[i]; i++)
		free((ptr[i]));
	free(ptr);
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

