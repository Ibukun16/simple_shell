#include "main.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * print_rev_string - A function that prints string in reverse.
 * @str: The string to print.
 *
 * Description: The method used for printing the string is recursion.
 *
 * Return: void.
 */
void print_rev_string(char *str)
{
	if (*str != '\0')
	{
		print_rev_string(str + 1);
		putchar(*str);
	}
}
