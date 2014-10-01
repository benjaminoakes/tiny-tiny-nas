#ifndef __directory_h__
#define __directory_h__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // for `strcat`
#include <sys/stat.h>  // for `lstat`
#include <sys/types.h> // for `DIR`
#include <dirent.h>    // for `struct dirent`
#include "entry.h"
#include "formatter.h"

typedef struct {
  void (* const list)(char*, Formatter);
} _Directory;

extern _Directory const Directory;
#endif
