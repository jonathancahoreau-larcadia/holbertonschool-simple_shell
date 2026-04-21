#ifndef MAIN_H
#define MAIN_H
extern char **environ;
char **tokenize(const char *line);
void free_tokens(char **args);
#endif
