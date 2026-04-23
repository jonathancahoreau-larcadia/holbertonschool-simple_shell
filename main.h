#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
extern char **environ;
char **tokenize(const char *line);
void free_tokens(char **args);
int execute(char **args, char **av, int countline);
char *on_path(char *command);
#endif
