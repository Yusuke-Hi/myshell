#include <signal.h>

void IgnoreSigint(void) { signal(SIGINT, SIG_IGN); }
void RestoreSigint(void) { signal(SIGINT, SIG_DFL); }
