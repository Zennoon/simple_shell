#include "main.h"

/**
 * print_prompt - Prints the prompt for the shell
 *
 * Return: void
 */
void print_prompt(void)
{
	int i = 0;
	char *pwd = NULL, *prompt = "simple_shell:";

	pwd = &get_env_var("PWD")[4];
	/**while (environ && environ[i])
	{
		char **env_var = _strtok(environ[i], "=");

		if (!_strcmp(env_var[0], "PWD"))
			pwd = &environ[i][4];
		i++;
		free_arr(env_var);
	}
	**/
	if (is_interactive())
	{
		if (pwd == NULL)
			prompt = _strcat(2, prompt, "$ ");
		else
			prompt = _strcat(3, prompt, pwd, "$ ");
		i = write(1, prompt, _strlen(prompt));
		free(prompt);
	}
	i = i;
}
