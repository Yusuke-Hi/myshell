# myshell Design

## Overview

myshell is a simple Unix shell written in C to learn:

- process creation
- pipes
- redirection
- signal handling

---

## Execution Flow

1. Display prompt
2. Read user input
3. Tokenize input
4. Parse operators
5. Check builtin commands
6. Execute command

---

## Process Model

Normal command execution:

parent
 └ fork
     └ child
         └ execvp()

---

## Pipe Implementation

cmd1 | cmd2

parent
 ├ fork -> child1 (cmd1)
 └ fork -> child2 (cmd2)

child1:
    dup2(pipefd[1], STDOUT_FILENO)

child2:
    dup2(pipefd[0], STDIN_FILENO)

---

## Redirection Implementation

cmd > file

child process:

open(file)
dup2(fd, STDOUT_FILENO)
execvp()

---

parser.c  
Tokenizes input and detects operators.

executor.c  
Handles fork, pipe, dup2, execvp.

builtin.c  
Implements built-in commands.

mysignal.c  
Handles SIGINT behavior.