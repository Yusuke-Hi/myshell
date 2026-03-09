cmake_minimum_required(VERSION 3.22)

project(myshell C)

add_executable(myshell
  src/main.c
  src/builtin.c
  src/executor.c
  src/mysignal.c
  src/parser.c
)

target_include_directories(myshell PRIVATE include)

install(TARGETS myshell DESTINATION bin)
