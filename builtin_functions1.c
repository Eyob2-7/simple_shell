#include "shell.h"

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

	if (!_strcmp(args[0], "exit"))
		shell_exit(args);
	else if (!_strcmp(args[0], "env"))
		shell_env();
	else if (!_strcmp(args[0], "setenv"))
		shell_setenv(args);
	else if (!_strcmp(args[0], "unsetenv"))
		shell_unsetenv(args);
	else if (!_strcmp(args[0], "help"))
		shell_help();
	else if (!_strcmp(args[0], "cd"))
		shell_cd(args);
	else if (!_strcmp(args[0], "clear"))
		shell_clear(args);
	else
		return (0);

	return (1);
}

/**
 * shell_cd - changes the current working directory of the shell
 * @args: array of arguments
 */
void shell_cd(char **args)
{
	char *dir = args[1];

	/* If no argument is provided, change to HOME directory */
	if (dir == NULL)
	{
		dir = __getenv("HOME");
		if (dir == NULL)
		{
			_puts("cd: No HOME directory found\n");
			return;
		}
	}

	if (chdir(dir) == -1)
	{
		perror("cd");
	}
}

/**
 * shell_exit - Exit the shell.
 * @args: Arguments.
 *
 * Return: Nothing.
 */
void shell_exit(char **args)
{
	int status = args[1] != NULL ? _atoi(args[1]) : 0;

	free_tokens(args);
	free_last_input();
	exit(status);
}

/**
 * shell_help - displays help information for built-in commands
 */
void shell_help(void)
{
	_puts("\nShell Version 1.0.0\n\n");
	_puts("Usage: ./hsh\n\n");
	_puts("Shell built-in commands:\n\n");
	_puts("help\t\tDisplay this help information\n\n");
	_puts("cd [dir]\tChange the current working directory\n\n");
	_puts("env\t\tDisplay the environment variables\n\n");
	_puts("setenv\t\tSet an environment variable\n\n");
	_puts("unsetenv\tUnset an environment variable\n\n");
	_puts("exit\t\tExit the shell\n\n");
}
