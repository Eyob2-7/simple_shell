#include "shell.h"

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
dir = tokenize(path, PATH_SEPARATOR);
if (!dir)
return (NULL);
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
strcpy(ret, buf);
return (ret);
}
}
if (stat_ret == -1)
free_tokens(dir);
return (NULL);
}


static char *last_input;

/**
 * get_input - Read the line of input from user.
 *
 * Return: Pointer to a buffer conatining the user's input.
*/
char *get_input(void)
{
char *input = NULL;
size_t input_size = 0;
ssize_t nread;

do {
/* print shell prompt */
prompt();

/* get a line of input from user */
nread = getline(&input, &input_size, stdin);

/* check for EOF or error */
if (nread == -1)
{
free(input);
_puts("\n");
return (NULL);
}

/* remove trailing newline character */
input[nread - 1] = '\0';

} while (input[0] == '\0' || isspace(input[0]));

/* update last_input to point to the new input */
last_input = input;
return (input);
}

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
 * prompt - Print shell prompt to stdin stream.
 *
 * Return: void.
 */
void prompt(void)
{
_puts(PROMPT);
fflush(stdout);
}


/**
 * execute - Execute a command with arguments.
 * @argv: An array of strings containing the command and its arguments.
 *
 * Return: The exit status of the executed command.
 */
int execute(char **argv)
{
pid_t id;
int status = 0;
char *cmd_path, *envp[2];

if (argv == NULL || *argv == NULL)
return (status);
if (check_for_builtin(argv))
return (status);

id = fork();
if (id < 0)
{
_puterror("fork");
return (1);
}
if (id == 0)
{
envp[0] = get_path();
envp[1] = NULL;
cmd_path = NULL;
if (argv[0][0] != '/')
cmd_path = find_in_path(argv[0]);
if (cmd_path == NULL)
cmd_path = argv[0];
if (execve(cmd_path, argv, envp) == -1)
{
perror(argv[0]), free_tokens(argv), free_last_input();
exit(EXIT_FAILURE);
}
}
else
{ do
{
waitpid(id, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (status);
}

