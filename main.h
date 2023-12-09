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
#include <stdarg.h>

/** Global vars **/
extern char **environ;

/** Utility functions **/
char *_strchr(char *, char);
int _strcmp(char *, char *);
size_t _strlen(char *);
char **_strtok(char *, char *);
char *_strcat(int, ...);
char *_strcpy(char *, char *);
char *num_to_str(unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void free_arr(char **);
void free_strs(int, ...);
char **get_paths(void);
char *command_path(char **, char *);
void print_prompt(void);
void print_error(char *, char *, char *, int);
void exit_program(char **, size_t);
int is_interactive(void);
char *get_env_var(char *);
int set_env_var(char *, char *);
/** built-in funcstions **/
int is_builtin(char *);
int execute_builtin(char **, char **, int);
int _cd(char **, char **, int);
int _env(char **, char **, int);
int _setenv(char **, char **, int);
int _unsetenv(char **, char **, int);
/** structs **/

/**
 * struct built_in - A struct for assigning a function to special commands
 * @name: The name of the command
 * @func: The function to handle the command
 */
typedef struct built_in
{
	char *name;
	int (*func)(char **, char **, int);
} built_in;
#endif
