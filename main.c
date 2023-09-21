#include "shell.h"

extern char **environ;
static char *last_input;

/**
 * free_last_input - Frees the most recent input entered by the user.
 *
 * This function frees the memory allocated for the most recent input string
 * entered by the user. It should be called after the input string is no longer
 * needed.
 */
void free_last_input(void)
{
    free(last_input);
    last_input = NULL;
}

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
    while (token) {
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

    for (i = 0; environ[i] != NULL; i++) {
        if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=') {
            value = environ[i] + len + 1;
            break;
        }
    }

    if (value == NULL) {
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
    return _getenv("PATH");
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
    if (!dir){
        return (NULL);

    }
        for (i = 0; dir[i]; i++) {
            _memset(buf, 0, PATH_MAX_LENGTH);
            _strcpy(buf, dir[i]);
            _strcat(buf, "/");
            _strcat(buf, command);
            stat_ret = stat(buf, &st);
            if (stat_ret == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
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

    id = fork();
    if (id < 0) {
        perror("fork");
        return (1);
    }
    if (id == 0) {
        envp[0] = get_path();
        envp[1] = NULL;
        cmd_path = NULL;
        if (args[0][0] != '/')
            cmd_path = find_in_path(args[0]);
        if (cmd_path == NULL)
            cmd_path = args[0];
        if (execve(cmd_path, args, envp) == -1) {
            perror(args[0] ), perror("\n"), free_tokens(args), free_last_input();
            exit(EXIT_FAILURE);
        }
    } else {
        do {
            waitpid(id, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (status);
}

/**
 * main - main method
 *
 * Return: void.
 */
int main()
{
    char *shell_prompt = "$ ";
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t chars;
    int from_terminal = 1;

    while(from_terminal != 0)
    {
        /* Check if STDIN is not from terminal */
        if(!isatty(STDIN_FILENO)) {
            from_terminal = 0;
        }

        /* Print the prompt */
        write(STDOUT_FILENO, shell_prompt, _strlen(shell_prompt));

        /* Get a line of input from user */
        chars = getline(&buffer, &bufsize, stdin);

        /* check for EOF or error */
        if (chars == -1) {
            perror("Error getline");
            free(buffer);
            exit(EXIT_FAILURE);
        }

        /* remove trailing newline character */
        buffer[chars - 1] = '\0';

        /* update last_input to point to the new input */
        last_input = (char *) chars;

        
        execute(buffer);
    }

    free(buffer);
    return (0);
}



