#include "shell.h"

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
 * get_path - Returns the value of the PATH environment variable.
 *
 * Return: Pointer to the value of $PATH.
 */
char *get_path(void)
{
	return (__getenv("PATH"));
}
/**
 * _getenv - function that gets an environment variable.
 * @name: name of the environment variable.
 *
 * Return: pointer to the value of the environment variable,
 *         or NULL if not found.
 */
char *__getenv(char *name)
{
	char *value = NULL;
	int i, len;

	if (name == NULL)
		return (NULL);

	len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			value = environ[i] + len + 1;
			break;
		}
	}

	if (value == NULL)
	{
		_puterror("getenv: environment variable not found: ");
		_puterror(name);
		_puterror("\n");
	}

	return (value);
}

/**
 * tokenize - parsing user input into arguments
 *            by splits an array string into tokens using a delimiter.
 * @str: the string to be tokenized.
 * @delim: the delimiter used to split the string.
 *
 * Return: an array of pointers to the tokens,
 *         or NULL if an error occurs.
 */
char **tokenize(char *str, const char *delim)
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
 * tokenize_input - splits a user input string into tokens with tokenize().
 * @input: the user input string to be tokenized
 *
 * Return: an array of pointers to the tokens, or NULL if an error occurs
 */
char **tokenize_input(char *input)
{
	char **tokens = NULL;
	char *tmp = NULL;

	tmp = _strdup(input);
	if (tmp == NULL)
	{
		_puts("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	tokens = tokenize(tmp, " \t\r\n\a");
	free(tmp);

	return (tokens);
}
