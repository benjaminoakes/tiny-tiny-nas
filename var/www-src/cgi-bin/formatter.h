#ifndef __formatter_h__
#define __formatter_h__

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "entry.h"

typedef struct {
  void (*before)();
  void (*display)(entry_t* entry);
  void (*after)();
} Formatter;

extern Formatter const EntryHTMLFormatter;
extern Formatter const EntryJSONFormatter;
extern Formatter const EntryPrettyJSONFormatter;
extern Formatter const EntryTextFormatter;
#endif
