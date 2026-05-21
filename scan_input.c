#include "header.h"

char *external_commands[150];   // external commands list
char *argv[100];                // argument array

pid_t fg_pid = -1;              // foreground pid
int last_status;                // exit status
job *job_list = NULL;           // job list

// builtin commands list
char *builtins[] = {
    "exit", "pwd", "cd", "echo", "jobs", "fg", "bg", NULL
};

// read and process input
void scan_input(char *prompt, char *input_string)
{
    // register signals
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGCHLD, signal_handler);

    // load external commands
    extract_external_commands(external_commands);

    while (1)
    {
        // display prompt
        printf("%s ", prompt);

        // read input
        fgets(input_string, 100, stdin);
        input_string[strcspn(input_string, "\n")] = 0;

        // change prompt
        if (!strncmp(input_string, "PS1=", 4))
        {
            strcpy(prompt, input_string + 4);
            continue;
        }

        // get command
        char *cmd = get_command(input_string);
        int type = check_command_type(cmd, external_commands);

        // builtin command
        if (type == BUILTIN)
        {
            execute_internal_commands(input_string);
        }
        // external command
        else if (type == EXTERNAL)
        {
            int pid = fork();

            if (pid > 0)
            {
                fg_pid = pid;
                waitpid(pid, &last_status, WUNTRACED);
                fg_pid = -1;

                if (WIFSTOPPED(last_status))
                    add_job(pid, input_string);
            }
            else if (pid == 0)
            {
                signal(SIGINT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);
                execute_external_commands(input_string, argv);
            }
        }
        else
            printf("given command is invalid\n");
    }
}

// signal handler
void signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTSTP)
    {
        if (fg_pid > 0)
            return;

        write(1, "\n", 1);
        fflush(stdout);
    }
    else if (signum == SIGCHLD)
    {
        waitpid(-1, &last_status, WNOHANG);
    }
}

// add stopped job
void add_job(int pid, char *cmmd)
{
    job *new = malloc(sizeof(job));
    new->pid = pid;
    strcpy(new->cmd, cmmd);
    new->next = job_list;
    job_list = new;
}