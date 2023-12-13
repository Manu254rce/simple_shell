# include "main.h"

/**
 * handle_builtins - Handles builtin commands
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: 0 on success, 1 on failure
 */

int handle_builtins(char **argv, char **env)
{
	int i = 0;

	builtins_t builtins[] =	{
		{"exit", exit_cmd},
		{"env", env_cmd},
		{"cd", cd_cmd},
		{"help", help_cmd},
		{NULL, NULL}
	};

	while (builtins[i].cmd != NULL)
	{
		if (strcmp(argv[0], builtins[i].cmd) == 0)
		{
			builtins[i].func(argv, env);
			return (0);
		}

		i++;
	}

	fprintf(stderr, "Error: Command %s not found\n", argv[0]);
	return (1);
}

/**
 * main - Entry point for shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: 0 on success
 */

int main(int argc, char **argv, char **env)
{
	char *line = NULL, *eof_argv[] = {"exit", NULL};
	size_t len = 0;
	ssize_t read_line = 0;
	int i = 0;
	char *args[BUFSIZE];

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("$ --> ");
		read_line = getline(&line, &len, stdin);

		if (read_line == -1)
			exit_cmd(eof_argv, env);

		line[strcspn(line, "\n")] = '\0';

		i = 0;
		args[i] = strtok(line, DELIM);
		while (args[i] != NULL)
		{
			i++;
			if (i >= BUFSIZE)
			{
				fprintf(stderr, "Error: Too many arguments\n");
				break;
			}
			args[i] = strtok(NULL, DELIM);
		}
		args[i] = NULL;

		if (handle_builtins(args, env) != 0)
			execute_shell(args, env);
	}
	free(line);
	return (0);
}
