#include "main.h"

/**
 * get_alias - Given an alias name, retrieves the name='value' pair from array
 * @alias_arr: An array of the the currently defined aliases with their values
 * @alias_name: The name of the alias name-value pair that is searched for
 *
 * Return: A string of the form alias_name='value'
 */
char *get_alias(char **alias_arr, char *alias_name)
{
	int i = 0;

	while (alias_arr[i])
	{
		char **name_val = _strtok(alias_arr[i], "=");

		if (!_strcmp(name_val[0], alias_name))
		{
			free_arr(name_val);
			return (alias_arr[i]);
		}
		free_arr(name_val);
		i++;
	}
	return (NULL);
}

/**
 * extend_aliases - Inserts or updates the alias_arr with a new value
 * @alias_arr: An array of the currently defined aliases
 * @alias: The new value to insert
 *
 * Return: The new alias_arr
 */
char **extend_aliases(char **alias_arr, char *alias)
{
	int i = 0, j;
	char **new_alias_name_val = _strtok(alias, "="), **nw_alias_arr;
	char **alias_split = _strtok(alias, "=");

	while (alias_arr[i])
	{
		char **name_val = _strtok(alias_arr[i], "=");

		if (!_strcmp(name_val[0], new_alias_name_val[0]))
		{
			char *new_alias = _strcat(4, alias_split[0], "='",
						  alias_split[1], "'");
			free(alias_arr[i]);
			alias_arr[i] = new_alias;
			free_arr(name_val);
			free_arr(alias_split);
			free_arr(new_alias_name_val);
			return (alias_arr);
		}
		free_arr(name_val);
		i++;
	}
	while (alias_arr[i])
		i++;
	nw_alias_arr = malloc(sizeof(char *) * (i + 2));
	for (j = 0; nw_alias_arr && j < i; j++)
	{
		nw_alias_arr[j] = alias_arr[j];
	}
	nw_alias_arr[j] = _strcat(4, alias_split[0], "='", alias_split[1], "'");
	nw_alias_arr[j + 1] = NULL;
	free(alias_arr);
	free_arr(new_alias_name_val);
	alias_arr = nw_alias_arr;
	free_arr(alias_split);
	return (alias_arr);
}

/**
 * concat_aliases - Concatenates all aliases to be written to the aliases file
 * @alias_arr: An array of the currently defined aliases
 *
 * Return: The concatenated string
 */
char *concat_aliases(char **alias_arr)
{
	char *cat = _strcat(2, alias_arr[0], "\n");
	int i = 1;

	while (alias_arr[i])
	{
		char *tmp = cat;

		cat = _strcat(3, cat, alias_arr[i], "\n");
		free(tmp);
		i++;
	}
	return (cat);
}

/**
 * print_aliases - Prints the name='value' pair of given alias names
 * @args: An array containing the alias names
 * @alias_arr: An array of the currently defined aliases
 *
 * Return: void
 */
void print_aliases(char **args, char **alias_arr)
{
	int i = 1;

	while (args[i])
	{
		char *alias = get_alias(alias_arr, args[i]);

		if (alias != NULL)
		{
			char *alias_per_line = _strcat(2, alias, "\n");

			write(1, alias_per_line, _strlen(alias_per_line));
			free(alias_per_line);
		}
		i++;
	}
}

/**
 * print_all_aliases - Prints the name='value' pair of all the defined aliases
 * @alias_arr: An array of the currently defined aliases
 *
 * Return: void
 */
void print_all_aliases(char **alias_arr)
{
	int i = 0;

	while (alias_arr[i])
	{
		char *alias_per_line = _strcat(2, alias_arr[i], "\n");

		write(1, alias_per_line, _strlen(alias_per_line));
		free(alias_per_line);
		i++;
	}
}
