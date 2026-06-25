# 🐚 Mini Shell in C

A simple Unix-like command-line shell built in C that supports command execution, job control, pipelines, input/output redirection, and signal handling, providing a Linux shell experience.

## ✨ Features

💻 Command Execution – Executes external commands using `fork()` and `execvp()`
⚙️ Built-in Commands – Supports `cd`, `pwd`, `exit`, `echo`, `jobs`, `fg`, and `bg`
🔀 Pipelines – Executes multiple commands connected using pipes (`|`)
📥 Input & Output Redirection – Supports `<`, `>`, and `>>` operators
⏳ Foreground & Background Execution – Runs background processes using `&`
📋 Job Control – Manage background and stopped jobs with `jobs`, `fg`, and `bg`
🔔 Signal Handling – Handles `SIGINT` (Ctrl+C), `SIGTSTP` (Ctrl+Z), and `SIGCHLD`
📝 Command Parsing – Parses user input into commands and arguments
🔗 Process Tracking – Maintains background jobs using a linked list
🧩 Modular Design – Separate modules for parsing, execution, signals, job control, and utilities

## 🛠️ Core Concepts Covered

Process Creation → `fork()`
Program Execution → `execvp()`
Process Synchronization → `waitpid()`
Inter-Process Communication → `pipe()`
Input/Output Redirection → `dup2()`
Signal Handling → `signal()`, `sigaction()`
Job Control
Linux System Calls
Linked Lists
Process Management

