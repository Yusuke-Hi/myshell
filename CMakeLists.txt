cmake_minimum_required(VERSION 3.22)
project(myshell C)

# Specify the directory for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Generate executable file (for all .c files in src)
# file(GLOB SOURCES "src/*.c");
add_executable(${PROJECT_NAME} 
  src/main.c
  src/parser.c
)

# Installation Settings
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES
  include/parser.h
  DESTINATION include/myshell
)
