#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

// command types
#define BUILTIN     1
#define EXTERNAL    2
#define NO_COMMAND  3

// job structure for background process
typedef struct job
{
    int pid;                // process id
    char cmd[100];          // command name
    struct job *next;       // link to next job
} job;

// global variables
extern char *builtins[];
extern int last_status;
extern job *job_list;

// function declarations
char *get_command(char *input_string);
void extract_external_commands(char **external_commands);
int check_command_type(char *commands, char **external_commands);

void execute_internal_commands(char *input_string);
void execute_external_commands(char *input_string, char *argv[]);

void scan_input(char *prompt, char *input_string);
void signal_handler(int signum);

void add_job(int pid, char *cmmd);
void print_jobs(void);
void delete_first(void);

#endif