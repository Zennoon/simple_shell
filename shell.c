#include "main.h"

int exec_command(char **, char *, char **);
int command_count = 0;
/**
 * print_error - prints errno msg to stderr
 * @shl_name: Current name of the executable (shell)
 * @cmd: the failed command
 * @msg: error message
 */
void print_error(char *shl_name, char *cmd, char *msg)
{
	char *cc = num_to_str(command_count);
	char *err;

	err = _strcat(7, shl_name, ": ", cc, ": ", cmd, ": ", msg);
	write(2, err, _strlen(err));
	free(err);
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

	if (!_strchr(command, '/'))
	{
		c_path = command_path(paths, command);
		if (c_path == NULL)
			return (NULL);
	}
	else
		c_path = command;
	/**for ( ; paths[i]; i++)
	   free(paths[i]);**/
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
	while (1)
	{
		char *line_buffer = NULL, **buff_arr;
		size_t buff_size = 0;
		int status = 0, line_size = 0;

		print_prompt();
		line_size = getline(&line_buffer, &buff_size, stdin);
		if (line_size <= 1)
		{
			free(line_buffer);
			continue;
		}
		line_buffer[line_size - 1] = '\0';
		//buff_arr = _strtok(line_buffer, " \t");
		//if ((int) buff_size == -1 || !_strcmp(buff_arr[0], "exit"))
		//	exit_program(buff_arr, buff_size);
		++command_count;
		/**if ((c_path = get_path(buff_arr[0])) != NULL)
			child_pid = fork();
		else
		{
			print_error(av[0], buff_arr[0], "not found\n");
			continue;
		}
		if (child_pid == -1)
		{
			print_error(av[0], buff_arr[0], "process failed\n");
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(c_path, buff_arr, ev) == -1)
				print_error(av[0], buff_arr[0], "not found\n");
		}
		else
			wait(&status);**/
		status = exec_command(av, line_buffer, ev);
		status = status;
		//free(line_buffer);
		//free_arr(buff_arr);
		if (!is_interactive())
			break;
	}
	return (0);
}

/**
 * exec_command - excutes built-in and system commands
 * @args: array containing command and args
 * @ev: environment
 *
 * Return: status - 0 -> success, 1-> command not found
 * 2 -> command excution failed
 */

int exec_command(char **av, char *line, char **ev)
{
	int i = 0, j;
	char *c_path;
	pid_t child_pid;
	char **commands;

	commands = _strtok(line, ";");
	for (j = 0; commands[j]; j++)
		;
	while (i < j)
	{
		char **args = _strtok(commands[i], " /t");

		if (_strchr(args[0], '/') == NULL)
		{
			if (is_builtin(args[0]) == 1)
			   	return (execute_builtin(args));
			c_path = get_path(args[0]);
		}
		else
			c_path = args[0];

		if (c_path != NULL)
			child_pid = fork();
		else
		{
			print_error(av[0], args[0], "not found\n");
			i++;
			continue;
		}
		if (child_pid == -1)
			return (2);
		if (child_pid == 0)
		{
			if (execve(c_path, args, ev) == -1)
			{
				print_error(av[0], args[0], "excution failed\n");
				return (2);
			}
		}
		else
			wait(NULL);
		free(args);
		i++;
	}
	free(commands);
	return (0);
}
