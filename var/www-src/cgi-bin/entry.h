#ifndef __entry_h__
#define __entry_h__

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  bool  is_directory;
  char* name;
  char* path;
} entry_t;

typedef struct {
  entry_t* (*alloc)();
  entry_t* (*init)(bool, char*, char*);
  void     (*free)(entry_t*);
} _Entry;

extern _Entry const Entry;
#endif
