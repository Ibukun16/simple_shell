#include "main.h"

/* The array of names of aliases that have been expanded */
static char **aliases_expanded;
/* The length of the array of alias names */
static int n;
/* The expansion been created by the alias sub
