#include "main.h"

/**
 * get_paths - returns list of env paths
 *
 * Return: list of paths
 */
char **get_paths(void)
{
	int i;
	char *path;
	char **paths;

	if (!environ)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		char **key = _strtok(environ[i], "=");

		if (_strcmp(key[0], "PATH") == 0)
		{
			path = key[1];
			if (path == NULL)
				return (NULL);
			paths = _strtok(path, ":");
			return (paths);
		}
		/**free(key[0]);
		   free(key[1]);**/
		free(key);
	}

	return (NULL);
}

/**
 * command_path - finds full path of a command
 * @dirs: directories to shearch in
 * @command: command name
 *
 * Return: full path of command if found,
 * NULL if not
 */
char *command_path(char **dirs, char *command)
{
	int i;
	char *path = NULL;

	for (i = 0; dirs[i]; i++)
	{
		DIR *dir = opendir(dirs[i]);
		struct dirent *file;

		while ((file = readdir(dir)) != NULL)
		{
			if (_strcmp(command, file->d_name) == 0)
			{
				path = dirs[i];
				break;
			}
		}
		closedir(dir);
		if (path != NULL)
		{
			path = _strcat(3, path, "/", command);
			return (path);
		}
	}
	return (NULL);
}
