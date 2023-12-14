#include "main.h"
#include <string.h>

/**
 * read_file_content - reads files content in to a buffer
 * @filename: name of file
 * @bytes_read: pointer to a variable to store total bytes
 * read
 *
 * Return: buffer containing file content
 */
char *read_file_content(char *filename, size_t *bytes_read)
{
	int fd = open(filename, O_RDONLY);
	struct stat filestat;
	char *buffer;
	size_t total_bytes_read = 0;

	if (fd == -1)
	{
		char *m = _strcat(3, "./hsh: 0: Can't open ", filename, "\n");

		write(STDERR_FILENO, m, _strlen(m));
		free(m);
		exit(127);
	}
	if (fstat(fd, &filestat) == -1)
	{
		close(fd);
		return (NULL);
	}
	buffer = malloc(filestat.st_size + 1);
	if (buffer == NULL)
	{
		close(fd);
		return (NULL);
	}
	while ((long int) total_bytes_read < filestat.st_size)
	{
		size_t new_read_bytes = read(fd, buffer + total_bytes_read,
				filestat.st_size - total_bytes_read);

		if ((int) new_read_bytes == -1)
		{
			free(buffer);
			close(fd);
			return (NULL);
		}
		total_bytes_read += new_read_bytes;
	}
	buffer[total_bytes_read] = '\0';
	close(fd);
	*bytes_read = total_bytes_read;
	return (buffer);
}

/**
 * parse_lines - parses buffer and returns array of lines
 * @buffer: buffer to parse
 * @bytes_read: size of bufer in bytes
 * @line_count: variable to store line count
 *
 * Return: array of lines
 */
char **parse_lines(char *buffer, size_t *line_count)
{
	char **lines = _strtok(buffer, "\n\0");
	int i = 0;

	while (lines[i])
	{
		(*line_count)++;
		i++;
	}
	free(buffer);
	return (lines);
}
/**
 * execute_from_file - executes command from file line by line
 * @av: argument vector
 * @ev: env
 *
 * Return: execution statis
 */
int execute_from_file(char **av, char **ev)
{
	size_t bytes_read;
	size_t line_count = 0;
	char *buffer;
	char **lines;
	int i, status = 0;

	buffer = read_file_content(av[1], &bytes_read);
	if (!buffer)
	{
		return (0);
	}
	lines = parse_lines(buffer, &line_count);
	for (i = 0; lines[i]; i++)
	{
		exec_command(av, lines[i], ev, 0, &status);
	}
	//for (i = 0; lines[i]; i++)
	//	free(lines[i]);
	free(lines);
	//free(lines);
	return (0);
}
