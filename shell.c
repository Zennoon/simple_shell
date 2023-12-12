#include "main.h"

int command_count = 0;
void execute_fork(char *, char **, char **, char **, int, int *);
/**
 * print_error - prints errno msg to stderr
 * @shl_name: Current name of the executable (shell)
 * @cmd: the failed command
 * @msg: error message
 * @command_count: The current command number
 *
 * Return: void
 */
void print_error(char *shl_name, char *cmd, char *msg, int command_count)
{
	char *cc = n_to_s(command_count);
	char *err;

	err = _strcat(7, shl_name, ": ", cc, ": ", cmd, ": ", msg);
	write(2, err, _strlen(err));
	free(err);
	free(cc);
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
		{
			free_arr(paths);
			return (NULL);
		}
	}
	else
		c_path = command;
	free_arr(paths);
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
	int command_count = 0, stat = 0;

	while (1)
	{
		char *line_buffer = NULL;
		size_t buff_size = 0;
		int status = 0, line_size = 0;

		if (av[1])
			return (execute_from_file(av, ev));
		print_prompt();
		line_size = getline(&line_buffer, &buff_size, stdin);
		if (line_size <= 1)
		{
			if (line_size == -1)
			{
				write(1, "\n", 1);
				break;
			}
			free(line_buffer);
			continue;
		}
		line_buffer[line_size - 1] = '\0';
		/**buff_arr = _strtok(line_buffer, " \t");**/
		if ((int) line_size == -1)
			exit_program(&line_buffer, line_size);
		++command_count;
		status = exec_command(av, line_buffer, ev, command_count, &stat);
		free(line_buffer);
		status = status;
		if (!is_interactive())
			break;
	}
	return (0);
}

/**
 * exec_command - excutes built-in and system commands
 * @av: array containing command and args
 * @line: Buffer containing the data read from stdin
 * @ev: environment
 * @cmd_cnt: The current command number
 *
 * Return: status - 0 -> success, 1-> command not found
 * 2 -> command excution failed
 */

int exec_command(char **av, char *line, char **ev, int cmd_cnt, int *status)
{
	int i = 0, j;
	char *c_path, **uncommented, **commands;

	if (line[0] == '#')
		return (0);
	uncommented = _strtok(line, "#");
	commands = _strtok(uncommented[0], ";");
	for (j = 0; commands[j]; j++)
		;
	while (i < j)
	{
		char **args = _strtok(commands[i], " \t");

		args = replace_variables(args, *status);
		if (args[0] == NULL)
		{
			i++;
			continue;
		}
		if (!_strcmp(args[0], "exit"))
			exit_program(args, i);
		if (_strchr(args[0], '/') == NULL)
		{
			if (is_builtin(args[0]) == 1)
			{
				execute_builtin(args, av, cmd_cnt);
				i++;
				continue;
			}
			c_path = get_path(args[0]);
		}
		else
			c_path = args[0];
		if (c_path == NULL)
		{
			*status = 127;
			print_error(av[0], args[0], "not found\n", cmd_cnt);
			i++;
			free_arr(args);
			continue;
		}
		execute_fork(c_path, args, av, ev, cmd_cnt, status);
		free_if_malloced(c_path, args[0]);
		free_arr(args);
		i++;
	}
	free_arr(commands);
	free_arr(uncommented);
	return (0);
}

/**
 * execute_fork - Create a child process to execute a command
 * @c_path: The command to execute
 * @args: The arguments along with the command to be executed
 * @av: 1d array of the command line arguments given when the program is run
 * @ev: Environment variables
 * @cmd_cnt: The current command number
 *
 * Return: void
 */
void execute_fork(char *c_path, char **args, char **av, char **ev, int cmd_cnt,
	int *status)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		*status = 2;
		exit(2);
	}
	if (child_pid == 0)
	{
		if (execve(c_path, args, ev) == -1)
		{
			*status = 2;
			print_error(av[0], args[0], "execution failed\n",
				    cmd_cnt);
			exit(2);
		}
	}
	else
	{
		*status = 0;
		wait(NULL);
	}
}
