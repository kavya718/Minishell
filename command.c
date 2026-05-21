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

kavyap@DESKTOP-MV1Q62J:~/minishell$ cat command.c
#include "header.h"

char buffer[20];              // buffer to store command
int ext_cmd_count = 0;        // external command count

// extract first word from input
char *get_command(char *input_string)
{
    int i = 0, j = 0;

    // skip leading spaces
    while (input_string[i] == ' ')
        i++;

    // copy command till space
    while (input_string[i] && input_string[i] != ' ')
        buffer[j++] = input_string[i++];

    buffer[j] = '\0';
    return buffer;
}

// load external commands from file
void extract_external_commands(char **external_commands)
{
    int fd = open("ext_cmd.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("external file not opened\n");
        return;
    }

    char temp[100], ch;
    int idx = 0, pos = 0;

    // read file character by character
    while (read(fd, &ch, 1))
    {
        if (ch == '\n')
        {
            temp[pos] = '\0';
            external_commands[idx] = malloc(strlen(temp) + 1);
            strcpy(external_commands[idx++], temp);
            pos = 0;
        }
        else
            temp[pos++] = ch;
    }

    // store last command
    if (pos)
    {
        temp[pos] = '\0';
        external_commands[idx] = malloc(strlen(temp) + 1);
        strcpy(external_commands[idx++], temp);
    }

    external_commands[idx] = NULL;
    close(fd);
}

// identify command type
int check_command_type(char *commands, char **external_commands)
{
    // check builtin commands
    for (int i = 0; builtins[i]; i++)
        if (!strcmp(commands, builtins[i]))
            return BUILTIN;

    // check external commands
    for (int i = 0; external_commands[i]; i++)
        if (!strcmp(commands, external_commands[i]))
            return EXTERNAL;

    return NO_COMMAND;
}

// execute internal shell commands
void execute_internal_commands(char *input_string)
{
    char buff[100];

    // exit shell
    if (!strcmp(input_string, "exit"))
        exit(0);

    // print current directory
    else if (!strcmp(input_string, "pwd"))
    {
        getcwd(buff, sizeof(buff));
        printf("%s\n", buff);
    }

    // change directory
    else if (!strncmp(input_string, "cd ", 3))
    {
        chdir(input_string + 3);
        getcwd(buff, sizeof(buff));
        printf("%s\n", buff);
    }

    // print process id
    else if (!strcmp(input_string, "echo $$"))
        printf("%d\n", getpid());

    // print last command status
    else if (!strcmp(input_string, "echo $?"))
        printf("%d\n", WEXITSTATUS(last_status));

    // print shell path
    else if (!strcmp(input_string, "echo $SHELL"))
        printf("%s\n", getenv("SHELL"));

    // display background jobs
    else if (!strcmp(input_string, "jobs"))
        print_jobs();

    // foreground job
    else if (!strcmp(input_string, "fg") && job_list)
    {
        kill(job_list->pid, SIGCONT);
        waitpid(job_list->pid, &last_status, WUNTRACED);
        delete_first();
    }

    // background job
    else if (!strcmp(input_string, "bg") && job_list)
    {
        kill(job_list->pid, SIGCONT);
        delete_first();
    }
}

// execute external commands
void execute_external_commands(char *input_string, char *argv[])
{
    int i = 0, j = 0;
    char temp[100];

    // split input into arguments
    while (input_string[i])
    {
        while (input_string[i] == ' ')
            i++;

        if (!input_string[i])
            break;

        int k = 0;
        while (input_string[i] && input_string[i] != ' ')
            temp[k++] = input_string[i++];

        temp[k] = '\0';
        argv[j] = malloc(strlen(temp) + 1);
        strcpy(argv[j++], temp);
    }

    argv[j] = NULL;

    // execute command
    execvp(argv[0], argv);
    perror("execvp");
    exit(1);
}

// print job list
void print_jobs(void)
{
    if (!job_list)
    {
        printf("NO JOBS TO DO !!\n");
        return;
    }

    job *temp = job_list;
    while (temp)
    {
        printf("%s\n", temp->cmd);
        temp = temp->next;
    }
}

// delete completed job
void delete_first(void)
{
    if (job_list)
    {
        job *temp = job_list;
        job_list = job_list->next;
        free(temp);
    }
}