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
void _puts(char *str)
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
 * _puterror - Prints an error message to the standard error stream
 * @err: The error message to print
 *
 * Description: This function prints the given error message to the standard
 * error stream. It calculates the length of the error message and uses the
 * write system call to output the error message.
 *
 * Return: None
 */
void _puterror(char *err)
{
	size_t len = _strlen(err); /* Calculate the length of the error message */
	ssize_t num_written; /* Number of characters written */

	/* Write the error message to the standard error stream */
	num_written = write(STDERR_FILENO, err, len);

	/* Check for write error */
	if (num_written == -1)
	{
		perror("write");
	}
}
