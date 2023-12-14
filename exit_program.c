#include "main.h"

/**
 * exit_program - Exits the running shell
 * @buff_arr: An array of the command and arguments
 * @buff_size: Number of characters in buff_arr
 *
 * Return: void
 */
void exit_program(char **buff_arr, size_t buff_size)
{
	if ((int) buff_size == -1)
	{
		free_arr(buff_arr);
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (buff_arr[1] != NULL)
	{
		int status = 0;
		char *ptr = buff_arr[1];

		while (*ptr)
		{
			status = (status * 10) + (*ptr - 48);
			ptr++;
		}
		free_arr(buff_arr);
		exit(status);
	}
	free_arr(buff_arr);
	exit(0);
}
