#include "main.h"

int _cd(char **args)
{
	printf("built in called for: %s\n", args[0]);
	return (0);
}

int _env(__attribute__((unused)) char **args)
{
	/**printf("built in called for: %s\n", args[0]);**/
	char **ptr, *str;

	ptr = environ;
	while (ptr != NULL && *ptr != NULL)
	{
		str = _strcat(2, *ptr, "\n");
		write(1, str, _strlen(str));
		free(str);
		ptr++;
	}
	return (0);
}
