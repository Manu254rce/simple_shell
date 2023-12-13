# include "main.h"

/**
 * handle_path - Handles the PATH variable
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: 0 on success, 1 on failure
 */

char *handle_path(char **argv, char **env)
{
	char *path = NULL, *token = NULL, *path_argv[BUFSIZE], *path_copy = NULL;
	char *cmd_path = malloc(BUFSIZE);
	int i = 0;

	(void)env;

	path = getenv("PATH");

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH variable not found\n");
		return (NULL);
	}

	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		path_argv[i] = token;
		token = strtok(NULL, ":");
		i++;
	}

	path_argv[i] = NULL;

	for (i = 0; path_argv[i] != NULL; i++)
	{
		sprintf(cmd_path, "%s/%s", path_argv[i], argv[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free(path_copy);
			return (cmd_path);
		}
	}

	free(path_copy);
	return (NULL);
}

/**
 * execute_shell - Executes the shell
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: void
 */

void execute_shell(char **argv, char **env)
{
	pid_t pid;
	int status = 0;
	char *cmd_path = NULL;

	if (access(argv[0], F_OK) != 0)
	{
		cmd_path = handle_path(argv, env);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "Error: Command %s not found\n", argv[0]);
			return;
		}
	}

	else
		cmd_path = strdup(argv[0]);

	pid = fork();

	if (pid == -1)
	{
		perror("hsh");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			perror("hsh");
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	free(cmd_path);
}
