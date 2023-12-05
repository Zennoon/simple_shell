#include "main.h"

/**
 * print_error - prints errno msg to stderr
 * @cmd: the failed command
 * @msg: error message
 */
void print_error(char *cmd, char *msg)
{
	write(2, cmd, _strlen(cmd));
	write(2, ":", 2);
	perror(msg);
}
/**
 * get_path - gets full path of a command if it is not a path
 * itself
 * @command: input command string
 * 
 * Return: command to excute
 */
char *get_path(char *command)
{
	char **paths = get_paths();
	char *c_path;
	
	if (command[0] != '/')
	{
		c_path = command_path(paths, command);
		if (c_path == NULL)
			return (NULL);
	}
	else
		c_path = command;
	free(paths);
	return (c_path);
}

/**
 * main - Displays prompt, accepts user command + arguments, parses, executes
 * @ac: Argument Count
 * @av: Argument Vector
 * @ev: Environment Vector
 *
 * Return: Always 0 (Success)
 */
int main(__attribute__((unused)) int ac, char **av,
	 char **ev)
{
	int i;
	char *prompt = "shell$ ";
	char **ptr, *ptr2 = malloc(sizeof(char) * 6);

	ptr = ev;
	while (*ptr)
	{
		for (i = 0; i < 5; i++)
		{
			ptr2[i] = (*ptr)[i];
		}
		ptr2[i] = '\0';
		if (!_strcmp(ptr2, "SHLVL"))
		{
			break;
		}
		ptr++;
	}
	char **paths = get_paths();
	char *c_path;
	
	while (1)
	{
		char *line_buffer = NULL;
		char **buff_arr;
		char *c_path;
		size_t buff_size = 0;
		int status;
		pid_t child_pid;

		if (!_strcmp("SHLVL=1", *ptr))
		{
			write(1, prompt, _strlen(prompt));
		}
		status = 0;
		buff_size = getline(&line_buffer, &buff_size, stdin);
		line_buffer[buff_size - 1] = '\0';
		buff_arr = _strtok(line_buffer, " \t");
		if ((int) buff_size == -1 || !_strcmp(buff_arr[0], "exit"))
			exit(98);
		if ((c_path = get_path(buff_arr[0])) != NULL)
			child_pid = fork();
		else
		{
			print_error(av[0], "command not found");
			continue;
		}
		if (child_pid == -1)
		{
			print_error(av[0], "");
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(c_path, buff_arr, ev) == -1)
				print_error(av[0],"");
		}
		else
			wait(&status);
		free(line_buffer);
		free_arr(buff_arr);
	}
	free(ptr2);
	return (0);
}
