#include "shell.h"

/**
 * split_cmd - parsing user input into arguments
 *            by splits an array string into tokens using a delimiter.
 * @str: the string to be tokenized.
 * @delim: the delimiter used to split the string.
 *
 * Return: an array of pointers to the tokens,
 *         or NULL if an error occurs.
 */
char **split_cmd(char *str, const char *delim)
{
	char *token = NULL;
	char **ret = NULL;
	int i = 0;

	token = strtok(str, delim);
	while (token)
	{
		ret = realloc(ret, sizeof(char *) * (i + 1));
		if (ret == NULL)
			return (NULL);

		ret[i] = malloc(_strlen(token) + 1);
		if (!(ret[i]))
			return (NULL);

		_strcpy(ret[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	/*increase the size of the array*/
	ret = realloc(ret, (i + 1) * sizeof(char *));
	if (!ret)
		return (NULL);

	ret[i] = NULL;
	return (ret);
}

/**
 * find_in_path - Looks for a command in each directory specified in the PATH
 *                environment variable
 * @command: pointer to `command` string to look for.
 *
 * Return: pointer to string containing the full path (success) if it is found,
 *         or NULL if it is not found (failure).
*/
char *find_in_path(char *command)
{
	struct stat st;
	int stat_ret, i;
	char buf[PATH_MAX_LENGTH], *path, *ret, **dir;

	path = get_path();
	if (!path)
		return (NULL);
	dir = split_cmd(path, PATH_SEPARATOR);
	if (!dir)
	{
		return (NULL);
	}

	for (i = 0; dir[i]; i++)
	{
		_memset(buf, 0, PATH_MAX_LENGTH);
		_strcpy(buf, dir[i]);
		_strcat(buf, "/");
		_strcat(buf, command);
		stat_ret = stat(buf, &st);
		if (stat_ret == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			free_tokens(dir);
			ret = malloc(sizeof(char) * (strlen(buf) + 1));
			if (!ret)
				return (NULL);
			_strcpy(ret, buf);
			return (ret);
		}
	}

	if (stat_ret == -1)
		free_tokens(dir);
	return (NULL);
}

/**
 * execute - Execute a command with arguments.
 * @argv: An array of strings containing the command and its arguments.
 *
 * Return: The exit status of the executed command.
 */
int execute(char *argv)
{
	pid_t id;
	int status = 0;
	char *cmd_path;
	char *envp[2];
	char **args;

	if (argv == NULL || _strncmp(argv, " ", 1) == 0)
		return (status);
	args = split_cmd(argv, " ");

	if (check_for_builtin(args))
		return (status);

	id = fork();
	if (id < 0)
	{
		perror("fork");
		return (1);
	}
	if (id == 0)
	{
		envp[0] = get_path();
		envp[1] = NULL;
		cmd_path = NULL;
		if (args[0][0] != '/')
			cmd_path = find_in_path(args[0]);
		if (cmd_path == NULL)
			cmd_path = args[0];
		if (execve(cmd_path, args, envp) == -1)
		{
			perror(args[0]), perror("\n"), free_tokens(args);
			exit(EXIT_FAILURE);
		}
	} else
	{
		do {
			waitpid(id, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (status);
}

