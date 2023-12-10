#include "main.h"

/**
 * read_file_content - reads files content in to a buffer
 * @filename: name of file
 * @bytes-read: pointer to a variable to store total bytes
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
		return (NULL);
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
	while (total_bytes_read < filestat.st_size)
	{
		size_t new_read_bytes = read(fd, buffer + total_bytes_read,
				filestat.st_size - total_bytes_read);

		if (new_read_bytes == -1)
		{
			free(buffer);
			close(fd);
			return (NULL);
		}
		total_bytes_read += new_read_bytes;
	}
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
char **parse_lines(char *buffer, size_t bytes_read, size_t *line_count)
{
	size_t initial_line_capacity = 16;
	char **lines = malloc(sizeof(char *) * initial_line_capacity);
	size_t *line_lengths = malloc(sizeof(size_t) * initial_line_capacity);
	size_t i = 0;

	if (!lines || !line_lengths)
	{
		free(buffer);
		return (NULL);
	}
	*line_count = 0;
	for (i = 0; i < bytes_read; i++)
	{
		if (buffer[i] == '\n')
		{
			lines[*line_count] = malloc(line_lengths[*line_count] + 1);
			if (!lines[*line_count])
			{
				size_t j;

				for (j = 0; j < *line_count; j++)
					free(lines[j]);
				free(lines);
				free(line_lengths);
				free(buffer);
				return (NULL);
			}
			_memcpy(lines[*line_count], buffer, line_lengths[*line_count]);
			lines[*line_count][line_lengths[*line_count]] = '\0';
			(*line_count)++;
			line_lengths[*line_count] = 0;
			if (*line_count >= initial_line_capacity)
			{
				initial_line_capacity *= 2;
				lines = _realloc(lines, sizeof(lines), sizeof(char *) + initial_line_capacity);
				line_lengths = _realloc(line_lengths, sizeof(line_lengths), sizeof(size_t) * initial_line_capacity);
				if (!lines || !line_lengths)
				{
					free(buffer);
					return (NULL);
				}
			}
		}
		else
			line_lengths[*line_count]++;
	}
	buffer = _realloc(buffer, sizeof(buffer), bytes_read);
	return (lines);
}
/**
 * exexute_from_file - executes command from file line by line
 * @av: argument vector
 * @ev: env
 *
 * Return: execution statis
 */
int execute_from_file(char **av, char ** ev)
{
	size_t bytes_read;
	size_t line_count;
	char *buffer;
	char **lines;
	int i = 0;

	buffer = read_file_content(av[1], &bytes_read);
	if (!buffer)
	{
		printf("file not found");
		return (1);
	}
	lines = parse_lines(buffer, bytes_read, &line_count);
	for ( ; lines[i]; i++)
	{
		exec_command(av, lines[i], ev);
	}
	return (0);
}

