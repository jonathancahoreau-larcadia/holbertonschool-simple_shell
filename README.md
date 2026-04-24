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

<img src="https://github.com/jonathancahoreau-larcadia/holbertonschool-simple_shell/raw/main/images/mon_image.svg" style="max-width: 100%;">

