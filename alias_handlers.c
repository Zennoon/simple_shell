#include "main.h"

/**
 * list_aliases - lista all aliases
 * @aliases: array of aliases
 *
 * Return: 1 Always
 */
int list_aliases(alias *aliases)
{
	int i;

	if (aliases == NULL)
		return (1);
	for (i = 0; aliases[i]; i++)
	{
		char *name = aliases[i]->name;
		char *cmd = aliases[i]->cmd;
		char *format = _strcat(5, name, "=", "'", cmd, "'\n");

		write(1, format, _strlen(format));
		free(format);
	}
	return (1);
}

/**
 * print_alias - prints a single alias with it's value
 * @aliases: array of aliases to search
 * @alias: name od alias to search for
 *
 * Return: 1 id alias found, -1 if not
 */
int print_alias(alias *aliases, char *n_alias)
{
	int i;
	char *msg;

	for (i = 0; aliases[i]; i++)
	{
		if (!_strcmp(aliases[i]->name, n_alias))
		{
			char *res = _strcat(5, n_alias, "=", "'", aliases[i]->cmd, "'\n");

			write(stdout, res, _strlen(res));
			free(res);
			return (1);
		}
	}
	msg = _strcat(3, "alias: ", n_alias, " not found\n");
	write(stderr, msg, _strlen(msg));
	free(msg);
	return (-1);
}

/**
 * set_alias - creates an alias for a command
 * @aliases: array of existing aliases
 * @new_alias: new_alias=command string
 *
 * REturn: 1 on success, -1 on fialure
 */
int set_alias(alias *aliases, char *new_alias)
{
	int i, j;
	char **key_value;
	alias ali;

	for (i = 0; aliases[i]; i++)
		;
	if (sizeof(aliases) == sizeof(alias) * i)
	{
		aliases = _realloc(aliases, sizeof(alias) * i, sizeof(alias) (i * 2));
		if (!aliases)
			return (-1);
	}
	key_value = _strtok(new_alias, "=");
	ali = {key_value[0], key_value[1] ? key_value[1] : NULL};
	aliases[i] = ali;
	free_arr(key_value);
	return (1);
}
