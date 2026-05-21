/*
NAME: KAVYA P
DESCRIPTION:MiniShell is a simple command-line shell developed in C on Linux. It provides a user-defined prompt 
and allows users to execute both internal and external commands. Internal commands such as pwd, cd, echo, 
and exit are handled within the shell itself,while external commands are executed using system calls like fork() 
and execvp().
DATE: 04/02/2026
SAMPLE I/O:
input: minishell$ pwd
output:/home/kavyap/minishell

*/

#include <stdio.h>
#include "header.h"

int main(void)
{
    // clear terminal screen
    system("clear");

    // shell prompt
    char prompt[25] = "minishell$";

    // input buffer
    char input_string[100];

    // start minishell
    scan_input(prompt, input_string);

    return 0;
}