#include "main.h"

/**
 * _strcpy - Copies the string in the second argument to the first argument
 * @dest: The string being copied into
 * @src: The string being copied
 *
 * Return: The pointer to the resulting string
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * pow_ten - caluculate ten raised to a number
 * @n: number input
 *
 * Return: result
 */
unsigned int pow_ten(unsigned int n)
{
	int res = 1;

	while (n > 0)
	{
		res *= 10;
		n--;
	}
	return (res);
}
/**
 * num_to_str - converts unsigned int to string
 * @num: number to be converted
 *
 * Return: string output
 */
char *num_to_str(unsigned int num)
{
	unsigned int len = 1, i = 0;
	unsigned int tmp = num;
	char *str;

	while (tmp / 10)
	{
		len++;
		tmp /= 10;
	}
	str = malloc(len + 1);
	len--;
	while (len > 1)
	{
		int n = num / pow_ten(len);

		str[i] = n + '0';
		num -= n * pow_ten(len);
		i++;
		len--;
	}
	str[i] = (num % 10) + '0';
	str[i + 1] = '\0';
	return (str);
}

/**
 * _memcpy - memcpy implementation
 * @dest: destination
 * @src: source
 * @n: number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		*(dest + i) = src[i];
	}
	return (dest);
}
