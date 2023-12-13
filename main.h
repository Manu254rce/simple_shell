#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

# define BUFSIZE 10
# define DELIM " "

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

/**
 * struct builtins - Struct for builtins
 * @cmd: Command
 * @func: Function
 */
typedef struct 
{
    char *cmd;
    void (*func)(char **argv, char **env);
} builtins_t;

/**
 * struct vars - Struct for PATH, HOME, USER and HOSTNAME
 * @var: Variable
 * @function: Function
 */
typedef struct
{
    char *var;
    int (*function)(char **argv, char **env);
} vars_t;

extern char **environ;

void exit_cmd(char **argv, char **env);
void env_cmd(char **argv, char **env);
void cd_cmd(char **argv, char **env);
void help_cmd(char **argv, char **env);

int handle_builtins(char **argv, char **env);
void execute_shell(char **argv, char **env);

#endif /* MAIN_H */
