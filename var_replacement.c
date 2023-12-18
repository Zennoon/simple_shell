#include "main.h"

/**
 * replace_variables - Replace variables given as arguments/commands
 * @args: The arguments given
 * @status: Exit status of the last executed command
 *
 * Return: void
 */
char **replace_variables(char **args, int status)
{
	int i = 0;

	args = replace_aliases(args);
	while (args[i] != NULL)
	{
		if (args[i][0] == '$')
		{
			if (!_strcmp(args[i], "$$"))
			{
				pid_t process_id = getpid();

				free(args[i]);
				args[i] = _strcat(1, num_to_str(process_id));
			}
			else if (!_strcmp(args[i], "$?"))
			{
				free(args[i]);
				args[i] = _strcat(1, num_to_str(status));
			}
			else
			{
				char *env_var = get_env_var(&args[i][1]);
				size_t len = _strlen(args[i]);

				if (env_var != NULL)
				{
					free(args[i]);
					args[i] = _strcat(1,
							  &env_var[len]);
				}
			}
		}
		i++;
	}
	return (args);
}

/**
 * check_pwd - Checks if the pwd is simple_shell
 *
 * Return: 1 if pwd is simple_shell, 0 otherwise
 */
int check_pwd(void)
{
	char *pwd = get_env_var("PWD");
	char **pwd_arr = _strtok(pwd, "/");
	int i = 0;

	while (pwd_arr[i])
		i++;
	if (!_strcmp(pwd_arr[i - 1], "simple_shell"))
	{
		free_arr(pwd_arr);
		return (1);
	}
	free_arr(pwd_arr);
	return (0);
}

/**
 * replace_aliases - Replace aliases with their value
 * @args: An array of the command and its given arguments
 *
 * Return: An array with all the aliases replaced with their value
 */
char **replace_aliases(char **args)
{
	size_t bytes;
	int i = 0;

	if (check_pwd())
	{
		char *aliases = read_file_content("./aliases", &bytes, NULL);
		char **alias_arr = _strtok(aliases, "\n");

		while (args[i] && _strcmp(args[0], "alias"))
		{
			char *alias_arr_entry = get_alias(alias_arr, args[i]);

			if (alias_arr_entry != NULL)
			{
				size_t j = 0, k = 0;
				char **name_val = _strtok(alias_arr_entry, "=");
				char *comm = malloc(sizeof(char) *
						    (_strlen(name_val[1]) - 1));

				for (k = 0; k <= _strlen(name_val[1]); k++)
				{
					if (name_val[1][k] != 39)
					{
						comm[j] = name_val[1][k];
						j++;
					}
				}
				free(args[i]);
				args[i] = _strcat(1, comm);
				free_arr(name_val);
				free(comm);
			}
			i++;
		}
		free(aliases);
		free_arr(alias_arr);
	}
	return (args);
}

/**
 * clear_aliases - Clears the alias list when exiting
 *
 * Return: void
 */
void clear_aliases(void)
{
	if (check_pwd())
	{
		int fd = open("./aliases", O_RDWR | O_TRUNC);

		close(fd);
	}
}
