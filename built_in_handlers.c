#include "main.h"

int _cd(char **args)
{
	char *buff = malloc(1024), *old_buff = "";
	char *pwd = NULL, *old_pwd, *home, *dir;
	/**int i = 0;**/

	pwd = &get_env_var("PWD")[4];
	old_pwd = &get_env_var("OLDPWD")[7];
	home = &get_env_var("HOME")[5];
	/**while (environ && environ[i])
	{
		char **env_var = _strtok(environ[i], "=");

		if (!_strcmp(env_var[0], "PWD"))
			pwd = &environ[i][4];
		else if (!_strcmp(env_var[0], "OLDPWD"))
			old_pwd = &environ[i][7];
		else if (!_strcmp(env_var[0], "HOME"))
			home = &environ[i][5];
		i++;
		free_arr(env_var);
	}
	**/
	old_buff = _strcat(2, old_buff, pwd);
	dir = args[1];
	if (args[1] == NULL)
		dir = home;
	else if (!_strcmp(args[1], "-"))
	{
		dir = old_pwd;
		write(1, dir, _strlen(dir));
		write(1, "\n", 1);
	}
	if (chdir(dir) == 0)
	{
		buff = getcwd(buff, 1024);
		set_env_var("PWD", buff);
		set_env_var("OLDPWD", old_buff);
	}
	else
		perror("");
	free(buff);
	free(old_buff);
	return (0);
}

int _env(__attribute__((unused)) char **args)
{
	/**printf("built in called for: %s\n", args[0]);**/
	char **ptr, *str;

	ptr = environ;
	while (ptr != NULL && *ptr != NULL)
	{
		str = _strcat(2, *ptr, "\n");
		write(1, str, _strlen(str));
		free(str);
		ptr++;
	}
	return (0);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * args: An array of the given arguments as strings
 *
 * Return: 0 if successful, -1 otherwise
 */
int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
		printf("Error\n");
	if (set_env_var(args[1], args[2]) == -1)
	{
		printf("Error");
		return (-1);
	}
	return (0);
}
/**
 * _unsetenv - Remove an environment variable
 * @args: An array of the given arguments as strings
 *
 * Return: 0 if successful, -1 otherwise
 */
int _unsetenv(char **args)
{
	int i = 0;

	if (args[1] == NULL)
		return (-1);
	while (environ[i])
	{
		char **str_arr = _strtok(environ[i], "=");

		if (!_strcmp(str_arr[0], args[1]))
		{
			free_arr(str_arr);
			break;
		i++;
		free_arr(str_arr);
	}
	if (environ[i] == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	return (0);
}
