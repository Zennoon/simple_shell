#include "main.h"

int _cd(char **args)
{
	printf("built in called for: %s\n", args[0]);
	return (0);
}

int _env(char **args)
{
	printf("built in called for: %s\n", args[0]);
	return (0);
}
