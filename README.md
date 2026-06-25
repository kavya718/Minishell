# 🐚 Mini Shell in C

A simple Unix-like command-line shell built in C that supports command execution, job control, pipelines, input/output redirection, and signal handling, providing a Linux shell experience.

## ✨ Features

- 💻 **Command Execution** – Executes external commands using `fork()` and `execvp()`
- ⚙️ **Built-in Commands** – Supports `cd`, `pwd`, `exit`, `echo`, `jobs`, `fg`, and `bg`
- 🔀 **Pipelines** – Executes multiple commands connected using pipes (`|`)
- 📥 **Input & Output Redirection** – Supports `<`, `>`, and `>>`
- ⏳ **Foreground & Background Execution** – Runs background processes using `&`
- 📋 **Job Control** – Manage jobs using `jobs`, `fg`, and `bg`
- 🔔 **Signal Handling** – Handles `SIGINT`, `SIGTSTP`, and `SIGCHLD`
- 📝 **Command Parsing** – Parses user input into commands and arguments
- 🔗 **Process Tracking** – Maintains background jobs using linked lists
- 🧩 **Modular Design** – Organized into parsing, execution, signal handling, and job control modules

## 🛠️ Core Concepts Covered

- Process Creation → `fork()`
- Program Execution → `execvp()`
- Process Synchronization → `waitpid()`
- Inter-Process Communication → `pipe()`
- Input/Output Redirection → `dup2()`
- Signal Handling → `signal()`, `sigaction()`
- Linux System Calls
- Job Control
- Linked Lists
- Process Management
Process Management

