#include "main.h"
/**
void print_prompt(void)
{
	char *prompt = "shell:";
	char *env_var = malloc(sizeof(char) * 6), *full_prompt;
	char *pwd;
	int i = 0, j, k;

	while (environ != NULL && environ[i] != NULL)
	{
		for (j = 0; j < 5; j++)
		{
			env_var[j] = environ[i][j];
		}
		env_var[j] = '\0';
		if (!_strcmp(env_var, "PWD=/"))
		{
			pwd = &environ[i][4];
			printf("pwd = %s\n", pwd);
		}
		if (!_strcmp(env_var, "SHLVL"))
			k = i;
		i++;
	}
	printf("shlvl = %s\n", environ[k]);
	free(env_var);
	if (!_strcmp(environ[k], "SHLVL=1"))
	{
		full_prompt = malloc(sizeof(char) *
				     (_strlen(prompt) + _strlen(pwd) + 2));
		if (full_prompt != NULL)
		{
			for (i = 0; i < _strlen(prompt); i++)
			{
				full_prompt[i] = prompt[i];
			}
			for (j = 0; j < _strlen(pwd); j++)
			{
				full_prompt[i] = pwd[j];
				i++;
			}
			full_prompt[i++] = '$';
			full_prompt[i] = ' ';
		}
		j = write(1, full_prompt, _strlen(prompt) + _strlen(pwd) + 2);
		free(full_prompt);
	}
}
**/
void print_prompt(void)
{
	int i = 0;
	char *shlvl, *pwd, *prompt = "simple_shell:";

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
		i = write(1, prompt, _strlen(prompt));
		i = write(1, pwd, _strlen(pwd));
		i = write(1, "$ ", 2);
	}
}
