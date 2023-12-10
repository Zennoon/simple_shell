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
