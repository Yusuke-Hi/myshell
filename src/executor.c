#include "executor.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mysignal.h"

void Execute(const ParseResult* parse_result, char* const* argv) {
  if (parse_result->pipe_index != -1) {
    ExecutePipe(parse_result);
  } else {
    ExecuteNormal(parse_result, argv);
  }
}

void ExecutePipe(const ParseResult* parse_result) {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("failed to pipe\n");
    return;
  }
  IgnoreSigint();
  pid_t pid1 = fork();
  switch (pid1) {
    case -1:
      perror("failed to fork\n");
      exit(EXIT_FAILURE);
    case 0:
      RestoreSigint();
      close(pipefd[0]);
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[1]);
      execvp(parse_result->left_argv[0], parse_result->left_argv);
    default:
      pid_t pid2 = fork();
      switch (pid2) {
        case -1:
          perror("failed to fork\n");
          exit(EXIT_FAILURE);
        case 0:
          RestoreSigint();
          close(pipefd[1]);
          dup2(pipefd[0], STDIN_FILENO);
          close(pipefd[0]);
          execvp(parse_result->right_argv[0], parse_result->right_argv);
        default:
          close(pipefd[0]);
          close(pipefd[1]);
          waitpid(pid1, NULL, 0);
          waitpid(pid2, NULL, 0);
      }
  }
}

void ExecuteNormal(const ParseResult* parse_result, char* const* argv) {
  IgnoreSigint();
  pid_t pid = fork();
  switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0:
      RestoreSigint();
      if (parse_result->redirect_index != -1) {
        int fd = open(argv[parse_result->redirect_index + 1],
                      O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
          perror("failed to fd");
          exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
          perror("failed to dup2");
          exit(EXIT_FAILURE);
        }
        close(fd);
      }
      if (execvp(argv[0], argv) == -1) {
        perror("execvp failed");
        exit(EXIT_FAILURE);
      }
    default:
      wait(NULL);
  }
}
