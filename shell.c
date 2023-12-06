#include "main.h"

int command_count = 0;
/**
 * print_error - prints errno msg to stderr
 * @cmd: the failed command
 * @msg: error message
 */
void print_error(char *cmd, char *msg)
{
	char *cc = num_to_str(command_count);

	write(2, "./hsh", 5);
	write(2, ": ", 2);
	write(2, cc, _strlen(cc));
	write(2, ": ", 2);
	write(2, cmd, _strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, _strlen(msg));
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
	char *c_path;

	while (1)
	{
		char *line_buffer = NULL;
		char **buff_arr;
		char *c_path;
		size_t buff_size = 0;
		int status = 0;
		pid_t child_pid;

		print_prompt();
		buff_size = getline(&line_buffer, &buff_size, stdin);
		line_buffer[buff_size - 1] = '\0';
		buff_arr = _strtok(line_buffer, " \t");
		if ((int) buff_size == -1 || !_strcmp(buff_arr[0], "exit"))
		exit_program(buff_arr, buff_size);
		++command_count;
		if ((c_path = get_path(buff_arr[0])) != NULL)
			child_pid = fork();
		else
		{
			print_error(buff_arr[0], "not found\n");
			continue;
		}
		if (child_pid == -1)
		{
			print_error(buff_arr[0], "process failed\n");
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(c_path, buff_arr, ev) == -1)
				print_error(buff_arr[0], "not found\n");
		}
		else
			wait(&status);
		free(line_buffer);
		free_arr(buff_arr);
	}
	return (0);
}

/**
 * exec_command - excutes built-in and system commands
 * @args: array containing command and args
 *
 * Return: status
 */
/**
int exec_command(char **args)
{
	char **paths;
	char *c_path;
	pid_t child_pid;

	if (args[0][0] != '/')
	{
		if (built_in(args[0]))
			return (execute_builtin(args));
		c_path = get_Path(args[0]);
		if (c_paths != NULL)
			child_pid = fork();
	}
}
**/
