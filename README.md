# myshell

A simple Unix shell implementation written in C.
This project was created to learn process control and OS concepts.

## Features

- Execute commands
- Built-in command (cd)
- Output redirection (> )
- Pipe (| )
- Signal handling (Ctrl+C)

## Build

mkdir build
cd build
cmake ..
make

## Run

./myshell
myshell> ls
myshell> echo hello > file.txt
myshell> cat file.txt
myshell> ls | grep main

## Architecture

myshell is composed of the following modules.

### parser
Parse user input and detect operators (|, >)

### executor
Execute commands using fork, execvp, pipe, dup2

### builtin
Handle built-in commands like cd

### mysignal
Handle signal behavior (SIGINT)
