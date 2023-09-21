#include "shell.h"

/**
 * main - main method
 *
 * Return: void.
 */
int main(void)
{
char *shell_prompt = "$ ";
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars;
int from_terminal = 1;

while (from_terminal != 0)
{
/* Check if STDIN is not from terminal */
if (!isatty(STDIN_FILENO))
{
from_terminal = 0;
}

/* Print the prompt */
_printf(shell_prompt);

/* Get a line of input from user */
chars = getline(&buffer, &bufsize, stdin);

/* check for EOF or error */
if (chars == -1)
{
perror("Error (getline)");
free(buffer);
exit(EXIT_FAILURE);
}

/* remove trailing newline character */
buffer[chars - 1] = '\0';

execute(buffer);
}

free(buffer);
return (0);
}



