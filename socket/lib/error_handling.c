#include "error_handling.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_handling(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}
