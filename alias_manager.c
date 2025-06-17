#include "main.h"

/* Array of the aliases in the shell program */
static alias_t **alias_list;
/* Number of aliases in the shell program */
static int count_alias;

/**
 * manage_aliases - Function that perform aliases management operations
 * @ev: The operation to perform
 *
 * Return: Nothing
 */
void manage_aliases(char ev)
{
	int i;

	if (ev == MO_INIT)
	{
		count_alias = 0;
		alias_list = NULL;
	}
	else if (ev == MO_FREE)
	{
		if (alias_list)
		{
			for (i = 0; i < count_alias; i++)
			{
				if (alias_list[i])
				{
					if (alias_list[i]->name)
						free(alias_list[i]->name);
					if (alias_list[i]->value)
						free(alias_list[i]->value);
					free(alias_list[i]);
				}
			}
			if (alias_list)
				free(alias_list);
			alias_list = NULL;
			count_alias = 0;
		}
	}
}

/**
 * add_alias - A function that adds an alias to the list of aliases or
 * replaces the value if it exists
 * @name: The name of the alias
 * @value: The value of the alias
 */
void add_alias(char *name, char *value)
{
	int i;
	alias_t **new;

	if (!name || !value)
		return;
	if (is_alias(name))
	{
		for (i = 0; i < count_alias; i++)
		{
			if (str_equal(name, alias_list[i]->name))
			{
				if (alias_list[i]->value)
					free(alias_list[i]->value);
				alias_list[i]->value = str_copy(value);
			}

		}
	}
	else
	{
		new = _realloc(alias_list, sizeof(alias_t *) * count_alias,
				sizeof(alias_t *) * (count_alias + 1));
		if (!new)
			return;
		alias_list = new;
		alias_list[count_alias] = malloc(sizeof(alias_t));
		if (!alias_list[count_alias])
			return;
		alias_list[count_alias]->name = str_copy(name);
		alias_list[count_alias]->value = str_copy(value);
		count_alias++;
	}
}

/**
 * get_alias_value - A function that retrieves the value of an alias
 * @aliase: The name of the alias to retrieve
 *
 * Return: The value of the alias else NULL.
 */
char *get_alias_value(char *aliase)
{
	int i;

	if (!alias_list == NULL)
		return (NULL);
	for (i = 0; i < count_alias; i++)
		if (str_eql(aliase, alias_list[i]->name))
			return (alias_list[i]->value);
	return (NULL);
}

/**
 * get_aliases - A function that retrieves all available aliases and store
 * the length in a given parameter.
 * @length: Pointer to the variable that contains the number of aliase
 * available.
 *
 * Return: The list of the aliases
 */
alias_t **get_aliases(int *length)
{
	*len = count_alias;
	return (alias_list);
}
