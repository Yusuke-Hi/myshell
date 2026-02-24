# Design
1. Display a prompt.
2. Read one line.
3. Execute fork on parent process.
4. Execute exec on child process.
5. Execute wait on parent process.

## Input
### API
fgets was adopted.\
Because of the following reasons.
- scanf: not secure and prompt will be separeted by spaces.
- getline: suitable and modern api, but it is too usefull.
- fgets: suitable for studing.
### Buffer size
1024
### Line breaks
Remove line breaks with strchr.\
Execute as if even if there is no line break.
### Token
To split prompt with space as tokens, strtok was adopted.

