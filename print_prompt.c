#include "main.h"

/**
 * print_prompt - Prints the prompt for the shell
 *
 * Return: void
 */
void print_prompt(void)
{
	int i = 0;
	char *shlvl, *pwd = NULL, *prompt = "simple_shell:";

	while (environ && environ[i])
	{
		char **env_var = _strtok(environ[i], "=");

		if (!_strcmp(env_var[0], "SHLVL"))
			shlvl = &environ[i][6];
		else if (!_strcmp(env_var[0], "PWD"))
			pwd = &environ[i][4];
		i++;
		free_arr(env_var);
	}
	if (!_strcmp(shlvl, "1"))
	{
		if (pwd == NULL)
			prompt = _strcat(2, prompt, "$ ");
		else
			prompt = _strcat(3, prompt, pwd, "$ ");
		i = write(1, prompt, _strlen(prompt));
		free(prompt);
	}
}
