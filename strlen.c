#include "main.h"

/**
 * _strlen - A function that returns length of a given string
 * @str: The string to find its length
 *
 * Return: The length of string in a integer value
 */
int _strlen(char *str)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str++)
		l++;
	return (l);
}
