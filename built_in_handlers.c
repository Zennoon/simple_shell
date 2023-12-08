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
		set_env_var("PWD", 4, buff);
		set_env_var("OLDPWD", 7, old_buff);
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
