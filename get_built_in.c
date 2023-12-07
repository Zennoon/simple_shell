#include "main.h"

/**
 * is_builtin - checks if a command is a builtin
 * @cmd: command to be checked
 *
 * Return: 1 if cmd is builtin, 0 otherwise
 */
int is_builtin(char *cmd)
{
	int i = 0;
	char *commands[] = {"env", "cd"};

	while (i < 2)
	{
		if (_strcmp(cmd, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * excute_builtin - finds built-in handdle and excutes it
 * @args: arguments (args[0] is the command)
 *
 * Return: 0 on success
 */
int execute_builtin(char **args)
{
	int i = 0;
	char *command = args[0];
	int (*func)(char **args);
	built_in built_ins[] = {
		{"env", _env},
		{"cd", _cd}
	};

	while (i < 2)
	{
		if (_strcmp(command, built_ins[i].name) == 0)
		{
				func = built_ins[i].func;
				break;
		}
		i++;
	}
	if (!func)
		return (1);
	return ((*func)(args));
}
