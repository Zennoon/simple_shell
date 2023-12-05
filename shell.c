#include "main.h"

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
		child_pid = fork();
		if (child_pid == -1)
		{
			write(2, av[0], _strlen(av[0]));
			write(2, ": ", 2);
			perror("");
			return (1);
		}
		if (child_pid == 0)
		{
			c_path = command_path(paths, buff_arr[0]);
			if (execve(c_path, buff_arr, ev) == -1)
			{
				write(2, av[0], _strlen(av[0]));
				write(2, ": ", 2);
				perror("");
			}
		}
		else
			wait(&status);
		free(line_buffer);
		free_arr(buff_arr);
	}
	free(ptr2);
	return (0);
}
