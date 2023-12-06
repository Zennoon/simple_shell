#ifndef MAIN_H
#define MAIN_H

/** Header files **/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>

/** Global vars **/
extern char **environ;

/** Utility functions **/
char *_strchr(char *, char);
int _strcmp(char *, char *);
size_t _strlen(char *);
char **_strtok(char *, char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *num_to_str(unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void free_arr(char **);
char **get_paths(void);
char *command_path(char **, char *);
void print_prompt(void);
void exit_program(char **, size_t);
#endif
