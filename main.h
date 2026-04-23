#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

char *read_line(void);
char **split_line(char *line);
void free_tokens(char **tokens);
char *find_path(char *cmd);
char *get_path_env(void);
int execute(char **args, char *prog, int line);
void print_exec_error(char *prog, int line, char *cmd);
int run_child_process(char *full, char **args, char *prog, int line);
void print_env(void);

#endif
