#ifndef SIMPLE_SHELL_HEADER_
#define SIMPLE_SHELL_HEADER_

#include <dirent.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifdef MAX_EXIT_CODE
#undef MAX_EXIT_CODE
#endif
/* The maximum value of an exit code */
#define MAX_EXIT_CODE 256
#ifdef HISTORY_FILE
#undef HISTORY_FILE
#endif
/* The file name used to store the shell history */
#define HISTORY_FILE "/.simple_shell_history"
/* The string representation of INT32_MAX */
#ifndef MAX_INT_STR
#define MAX_INT_ST "2147483647"
#endif

#include "main_types.h"

int sig(int c);

/************* Program (simple_shell.c) ************/

void init_shell(int ac, char **av, char **envp);
void print_node(cmd_t *node);
void handle_signal(int sig_num);
void *get_shell_prop(char prop_id);
void clean_shell(void);

/************* -------------------------- *************/
void manage_aliases(char op);
void add_alias(char *name, char *value);
char *get_alias_value(char *str);
alias_t **get_aliases(int *len);

/************ History Manager (history_manager.c) ************/
void manage_history(int op);
void add_to_history(char *str);
void save_history(void);
char **get_history(int *size)
int _strlen(char *str);

/********** Miscellenous ***********/
void print_prompt(void);
void clean_shell(void);
#endif /** SIMPLE_SHELL_HEADER_ **/
