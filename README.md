# 🐚 Simple Shell — C Project

A minimalist command-line interpreter written in C, reproducing the basic behavior of a Unix shell.
This project was developed as part of the **Holberton School** curriculum to explore system calls, process management, environment handling, and the implementation of a simple interactive and non-interactive shell.

---

## 📑 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Project Architecture](#-project-architecture)
- [Compilation](#-compilation)
- [Usage](#-usage)
- [Examples](#-examples)
- [Internal Workflow](#-internal-workflow)
- [Error Handling](#-error-handling)
- [Author](#-author)

---

## 📘 About

This shell implements:

- An interactive and non-interactive loop
- Line reading and tokenization (`getline`, `strtok`)
- Executable lookup through the `PATH` environment variable
- Process creation and execution using `fork`, `execve`, `wait`
- Built-in commands: `exit` and `env`
- Error handling aligned with Holberton requirements

The behavior aims to mimic a minimal POSIX shell.

---

<img width="568" height="1096" alt="Flowchart Simple Shell 2 drawio" src="https://github.com/user-attachments/assets/0d7f7eb4-4522-427b-8b70-9054c1c5289c" />

---

## ✨ Features

- Executes simple commands (e.g., `ls`, `pwd`, `echo`)
- Automatic `PATH` resolution
- Supports absolute and relative paths
- Built-in commands:
  - `exit` — exits the shell
  - `env` — prints the environment
- Error handling for:
  - Command not found
  - Permission denied
  - Nonexistent files
  - Attempting to execute a directory
- Interactive and non-interactive modes
- Proper memory cleanup

---

## 🧱 Project Architecture
├── main.c               # Main shell loop
├── read_line.c          # User input handling
├── split_line.c         # Tokenization logic
├── free_tokens.c        # Memory cleanup for tokens
├── path.c               # PATH resolution and command lookup
├── execute.c            # Command execution logic
├── run_child_process.c  # fork + execve + status handling
├── print_exec_error.c   # Holberton-style error messages
├── print_env.c          # Implementation of the env built-in
├── main.h               # Header file
└── README.md            # Documentation

---

## 🛠 Compilation

Compile using `gcc`:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

▶️ Usage
Interactive Mode
bash
./hsh
($) ls -l
($) echo "Hello"
($) exit
Non-Interactive Mode
bash
echo "ls -l" | ./hsh
📌 Examples
bash
($) ls
main.c  hsh  README.md

($) /bin/echo "Hello"
Hello

($) env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/root
...
⚙️ Internal Workflow
🔹 1. Reading Input
read_line() uses getline() to capture user input.

🔹 2. Tokenization
split_line() splits the input into tokens using strtok.

🔹 3. Built-in Commands
Handled directly in main.c:

exit → clean exit

env → prints environment variables

🔹 4. PATH Resolution
find_path():

Checks if the command contains /

Otherwise iterates through each directory in PATH

Builds a full path and checks it with access()

🔹 5. Execution
run_child_process():

Creates a child process with fork()

Executes the command with execve()

Handles exit status and error codes (126, 127, etc.)

❗ Error Handling
The shell prints errors following Holberton formatting:

Code
./hsh: 3: ls: not found
./hsh: 5: ./folder: Is a directory
./hsh: 7: script.sh: Permission denied
Handled by: print_exec_error().

👤 Author
Jonathan
github :jonathancahoreau-larcadia
Developer — Holberton Simple Shell Project
Adib
github :adib-commits
Developer — Holberton Simple Shell Project

--------------------------------------------------------------------------

### MAN SIMPLE SHELL

.TH HSH 1 "Simple Shell Manual" "Holberton School" "User Commands"

.SH NAME
hsh \- a simple UNIX command line interpreter

.SH SYNOPSIS
.B hsh
.RI [ no\ options ]

.SH DESCRIPTION
.B hsh
is a minimalist UNIX command line interpreter designed to execute simple commands
in both interactive and non-interactive modes. It replicates the core behavior
of traditional shells such as
.BR sh (1)
while focusing on process creation, environment handling, and PATH resolution.

In
.B interactive mode,
the shell displays a prompt and waits for user input. After each command is
executed, the prompt is displayed again.

In
.B non-interactive mode,
the shell reads commands from standard input (stdin) without displaying a prompt.
This mode is typically used when commands are piped or redirected into the shell.

.SH USAGE
.TP
Interactive mode:
.EX
$ ./hsh
($) /bin/ls
($) exit
.EE

.TP
Non-interactive mode:
.EX
$ echo "/bin/ls" | ./hsh
.EE

.TP
.B exit
Terminate the shell. The exit status is the status of the last executed command.

.TP
.B env
Print the current environment, one variable per line, in the format:
.IR NAME = value .

.SH COMMAND EXECUTION
When a command is entered, the shell performs the following steps:

.IP 1.
Read the input line using
.BR getline (3).

.IP 2.
Tokenize the input using
.BR strtok (3)
to extract the command and its arguments.

.IP 3.
Check whether the command is a builtin. If so, execute it internally.

.IP 4.
If not a builtin, search for the executable in the directories listed in the
.B PATH
environment variable using
.BR access (2).

.IP 5.
If a valid executable is found, create a child process using
.BR fork (2)
and execute the command using
.BR execve (2).

.IP 6.
The parent process waits for the child to terminate using
.BR wait (2),
then retrieves and returns its exit status.

.SH PATH
The shell searches for commands in the directories listed in the
.B PATH
environment variable.

If the command contains a slash (e.g.
.IR /bin/ls
or
.IR ./script ),
the PATH lookup is bypassed and the command is executed directly.

If the command cannot be located in any PATH directory, the shell prints an
error message and does not spawn a child process.

.SH ERROR HANDLING
If a command cannot be executed, the shell prints an error message to standard
error in the following format:

.RS
.B argv[0]: LINE_NUMBER: COMMAND: error_message
.RE

Examples:
.RS
.B ./hsh: 1: qwerty: not found
.br
.B ./hsh: 2: ./dir: Is a directory
.br
.B ./hsh: 3: script.sh: Permission denied
.RE

Exit codes follow standard shell conventions:
.TP
.B 127
Command not found.
.TP
.B 126
Command found but not executable (permission denied or directory).

.SH SIGNALS
.TP
.B Ctrl+C
(SIGINT) is ignored by the main shell process. The shell does not terminate.

.TP
.B Ctrl+D
Signals end-of-file (EOF). The shell exits cleanly.

.SH COMPILATION
To compile the shell, use:

.EX
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
.EE

.SH EXAMPLES
.TP
Run a command with arguments:
.EX
($) ls -la /tmp
.EE

.TP
Use an absolute path:
.EX
($) /bin/echo "Hello World"
.EE

.TP
Display environment variables:
.EX
($) env
.EE

.TP
Exit the shell:
.EX
($) exit
.EE

.TP
Non-interactive mode with a file:
.EX
$ cat commands.txt | ./hsh
.EE

.SH SEE ALSO
.BR sh (1),
.BR bash (1),
.BR execve (2),
.BR fork (2),
.BR wait (2),
.BR access (2),
.BR getline (3),
.BR strtok (3)

.SH AUTHORS
Written by the contributors listed in the AUTHORS file at the root of the repository.
