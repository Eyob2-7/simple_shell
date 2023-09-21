#include "shell.h"

/**
 * _getenv - function that gets an environment variable.
 * @name: name of the environment variable.
 *
 * Return: pointer to the value of the environment variable,
 *         or NULL if not found.
 */
char *_getenv(char *name)
{
	char *value = NULL;
	int i, len;

	if (name == NULL)
		return (NULL);

	len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			value = environ[i] + len + 1;
			break;
		}
	}

	if (value == NULL)
	{
		perror("getenv: environment variable not found: ");
		perror(name);
		perror("\n");
	}

	return (value);
}

/**
 * get_path - Returns the value of the PATH environment variable.
 *
 * Return: Pointer to the value of $PATH.
 */
char *get_path(void)
{
	return (_getenv("PATH"));
}

/**
 * shell_exit - Exit the shell.
 * @args: Arguments.
 *
 * Return: Nothing.
 */
void shell_exit(char **args)
{
	int status = args[1] != NULL ? atoi(args[1]) : 0;

	exit(status);
}

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
		_printf(environ[i]);
		_printf("\n");
	}

	return (0);
}

/**
 * check_for_builtin - checks if the command is a builtin
 * @args: the arguments array
 *
 * Return: 1 if command is a builtin, 0 otherwise
 */
int check_for_builtin(char **args)
{
	if (!args[0])
		return (0);

	if (!_strncmp(args[0], "exit", 4))
		shell_exit(args);
	else if (!_strncmp(args[0], "env", 3))
		shell_env();
	else
		return (0);

	return (1);
}

