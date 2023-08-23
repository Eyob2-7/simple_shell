#include "shell.h"

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number
 *
 * Description: This function is called when the SIGINT signal is received,
 * indicating that the user pressed Ctrl+C. It prints a newline and prompts
 * for the next command.
 *
 * Return: None
 */
void handle_sigint(int sig)
{
(void) sig;  /* Unused parameter */

_putchar('\n'); /* Print a newline character */
prompt(); /* Display the shell prompt */
}

/**
 * handle_sigquit - Signal handler for SIGQUIT (Ctrl+\)
 * @sig: Signal number
 *
 * Description: This function is called when the SIGQUIT signal is received,
 * indicating that the user pressed Ctrl+\ (backslash). It prints an error
 * message and exits the shell with a success status.
 *
 * Return: None
 */
void handle_sigquit(int sig)
{
(void) sig;  /* Unused parameter */

_puterror("Quit (core dumped)\n"); /* Print error message */
exit(EXIT_SUCCESS); /* Exit the shell with success status */
}

/**
 * handle_sigstp - Signal handler for SIGTSTP (Ctrl+Z)
 * @sig: Signal number
 *
 * Description: This function is called when the SIGTSTP signal is received,
 * indicating that the user pressed Ctrl+Z. It prints a newline and prompts
 * for the next command.
 *
 * Return: None
 */
void handle_sigstp(int sig)
{
(void) sig;  /* Unused parameter */

_puts("\n"); /* Print a newline character */
prompt(); /* Display the shell prompt */
}
