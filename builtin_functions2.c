#include "shell.h"

/**
 * shell_env - Prints all the environment variables.
 *
 * Return: 0 on success.
 */
int shell_env(void)
{
	int i;
	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}

	return (0);
}

/**
 * shell_clear - Clears the terminal screen.
 * @args: An array of arguments.
 *
 * Return: 1 to continue executing,
 *         or 0 to exit.
 */
int shell_clear(char **args)
{
	(void) args; /* Avoid "unused parameter" warning */
	_puts("\033[2J\033[H");
	return (1);
}

/**
 * shell_setenv - Set the value of an environment variable.
 * @args: Arguments (name and value of the environment variable).
 *
 * Return: 0 on success, -1 on error.
 */
int shell_setenv(char **args)
{
	char *name, *value;

	if (args[1] == NULL || args[2] == NULL)
	{
		_puterror("Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	name = args[1];
	value = args[2];

	if (setenv(name, value, 1) != 0)
	{
		_puterror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * shell_unsetenv - Unset an environment variable.
 * @args: Arguments (name of the environment variable).
 *
 * Return: 0 on success, -1 on error.
 */
int shell_unsetenv(char **args)
{
	char *name;

	if (args[1] == NULL)
	{
		_puterror("Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	name = args[1];

	if (unsetenv(name) != 0)
	{
		_puterror("unsetenv");
		return (-1);
	}
	return (0);
}
