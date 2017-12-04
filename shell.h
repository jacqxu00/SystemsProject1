#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int count_chars(char *, char *);
void trim(char *);
char ** parse_args(char *, char *);
void fork_and_run(char **);
void exit_shell();
void cd(char *);
void simple_pipe(char **);
void simple_redirect(char **, int);
void get_and_run(char *);
