#include <stdio.h>

int main() {
  int PROMPTSIZE = 1024;
  char buf[PROMPTSIZE];
  fgets(buf, sizeof(buf), stdin);
}
