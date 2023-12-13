#include "main.h"

/**
 * print_prompt - Prints the prompt for the shell
 *
 * Return: void
 */
void print_prompt(void)
{
	char *prompt = "#cisfun$ ";

	if (is_interactive())
	{
		/**if (pwd == NULL)
		 *	prompt = _strcat(2, prompt, "$ ");
		 *else
		 *	prompt = _strcat(3, prompt, pwd, "$ ");
		 */
		write(1, prompt, _strlen(prompt));
		/**free(prompt);**/
	}
}
