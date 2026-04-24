-- Project --

C - Simple Shell | Holberton School

-- Global Description --

"hsh" is a simple shell that reads commands from standard input, interprets them, and executes them. It supports both interactive and non-interactive modes.

-- Requirements --

All files will be compiled on Ubuntu 20.04 LTS using gcc

All files should end with a new line

A README.md file, at the root of the folder of the project is mandatory

Code should use the Betty style

Shell should not have any memory leaks

No more than 5 functions per file

All header files should be include guarded

Use system calls only when we need to

-- Compilation --

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh


-- Usage --

Interactive mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

Non-interactive mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$
```

image.png

-- Features --

Display a prompt and wait for user input

Execute commands with their full path (e.g. `/bin/ls`)

Search for commands using the `PATH` environment variable

Handle end-of-file (EOF / Ctrl+D)

Handle errors the same way as `/bin/sh`

-- Authors --

adib-commits | jonathancahoreau-larcadia