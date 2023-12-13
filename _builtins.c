#include "main.h"

/**
 * exit_cmd - Exits the shell with a given status,
 * and also handles EOF condition
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: void
 */

void exit_cmd(char **argv, char **env)
{
	long status = 0;
	char *endptr;

	(void)env;

	if (argv[1] != NULL)
	{
		errno = 0;
		status = strtol(argv[1], &endptr, 10);

		if (errno == ERANGE && (status == LONG_MAX || status == LONG_MIN))
		{
			perror("hsh");
			exit(EXIT_FAILURE);
		}
	}

	printf("Exiting shell with status %ld\n", status);

	exit(status);
}

/**
 * env_cmd - Prints the current environment
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: void
 */

void env_cmd(char **argv, char **env)
{
	int i = 0;

	(void)argv;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * cd_cmd - Changes the current working directory
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: void
 */

void cd_cmd(char **argv, char **env)
{
	char *cwd = NULL;
	char *oldpwd = NULL;
	char *home = NULL;
	char *path = NULL;
	char pwd_str[PATH_MAX];
	char oldpwd_str[PATH_MAX];

	(void)env;

	cwd = getcwd(cwd, 0);
	oldpwd = getcwd(oldpwd, 0);

	if (argv[1] == NULL)
	{
		home = getenv("HOME");
		chdir(home);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		chdir(path);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			perror("hsh");
			free(cwd);
			free(oldpwd);
			return;
		}
	}

	sprintf(pwd_str, "PWD=%s", cwd);
	sprintf(oldpwd_str, "OLDPWD=%s", oldpwd);
	putenv(pwd_str);
	putenv(oldpwd_str);

	free(cwd);
	free(oldpwd);
}

/**
 * help_cmd - Prints help information
 * @argv: Array of arguments
 * @env: Array of environment variables
 * Return: void
 */

void help_cmd(char **argv, char **env)
{
	(void)argv;
	(void)env;

	printf("This is a help message\n");
}

