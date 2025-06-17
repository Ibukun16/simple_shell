#include "main.h"

/* The modified environment variable for the simple shell program */
static char **e_pas;

/* The number of environment variable in the simple shell program */
static int env_count;

/* The current line in the shell program */
static int line_num;

/* The name of the current instance of the simple shell program */
static char *exec_name;

/* The process ID of the current instance of the simple shell program */
static int shell_PID;

/* The exit code of the last executed process in the shell program */
static uchar_t node_exit_code;

/* Indicator of the interactiveness of the simple shell program */
static char is_interactive;

/* The lines of the files passed to the simple shell program */
static char **f_lines;

/* The number of lines in the file passed to the simple shell program */
static int count_cmd_lines;

/* The current line of command to be executed */
static char *cmd_line;

/* The current nodes of command list of to be executed */
static cmd_t *cmd_list;

/**
 * main - Entry point into the simple shell program
 * @ac: The count of the number of argument passed to the program
 * @av: Double pointer to the argument vector array
 * @env: The environment variables passed to the program
 *
 * Return: The exit code of the last command executed
 */
int main(int ac, char **av, char **env)
{
	int input = 0;

	init_shell(ac, av, env);
	while (input < count_cmd_lines)
	{
		print_prompt();
		cmd_line = (is_interactive == TRUE ? get_cmd_line() : f_lines[input]);
		add_to_history(cmd_line);
		line_num++;
		cmd_list = parse_cmd_line(cmd_line);
		execute_cmds_list(&cmd_list, &node_exit_code);
		if (cmd_list != NULL)
			free_cmd_t(&cmd_list);
		if ((is_interactive == TRUE) && (cmd_line != NULL))
		{
			free(cmd_line);
			cmd_line = NULL;
		}
		input += (is_interactive ? 0 : 1);
	}
	clean_shell();
	return (node_exit_code);
}

/**
 * init_shell - Function that initializes the simple shell program
 * @ac: The count of the number of argument passed to the command line
 * @av: Double pointer  to the arguments vector array
 * @env: The environment variables passed
 *
 * Return: Nothing
 */
void init_shell(int ac, char **av, char **env)
{
	int fd, i;

	is_interactive = ((ac < 2) && isatty(STDIN_FILENO) ? TRUE : FALSE);
	if (check_arguments(ac, av))
	{
		fd = open(av[1], O_RDONLY);
		if (fd >= 0)
		{
			f_lines = read_lines(fd, &count_cmd_lines);
			close(fd);
		}
		else
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		count_cmd_lines = 1;
		f_lines = NULL;
		if (!isatty(STDIN_FILENO))
			f_lines = read_lines(STDIN_FILENO, &count_cmd_lines);
	}
	e_pas = NULL;
	for (i = 0; env != NULL && env[i] != NULL; i++)
	{
		e_pas = _realloc(e_pas, sizeof(void *) * i, sizeof(void *) * (i + 1));
		e_pas[i] = str_copy(env[i]);
	}
	env_count = i;
	e_pas[i] = NULL;
	line_num = 0;
	exec_name = str_copy(av[0]);
	shell_PID = getpid();
	signal(SIGINT, handle_signal);
	node_exit_code = 0;
	manage_aliases(MO_INIT);
	manage_history(MO_INIT);
}

/**
 * get_shell_prop - Retrieve the address of a shell prop based on its id
 * @p_id: The identity of the prop to retrieve
 *
 * Return: Pointer to the prop, else NULL
 */
void *get_shell_prop(char p_id)
{
	switch (p_id)
	{
	case ENVP_ID:
		return (&e_pas);
	case ENVP_COUNT_ID:
		return (&env_count);
	case LINE_NUMBER_ID:
		return (&line_num);
	case EXEC_NAME_ID:
		return (&exec_name);
	case SHELL_PID_ID:
		return (&shell_PID);
	case NODE_EXIT_CODE_ID:
		return (&node_exit_code);
	case IS_INTERACTIVE_ID:
		return (&is_interactive);
	default:
		break;
	}
	return (NULL);
}

/**
 * clean_shell - Function that free up resources used by shell instance
 *
 * return: Nothing
 */
void clean_shell(void)
{
	save_history();
	manage_aliases(MO_FREE);
	manage_history(MO_FREE);
	if (f_line && cmd_line)
		free(cmd_line);
	if (cmd_list)
		free_cmd_t(&cmd_list);
	if (f_lines)
		free_array(f_lines, count_cmd_lines);
	if (e_pas)
		free_array(e_pas, env_count);
	if (exec_name)
		free(exec_name);
}
