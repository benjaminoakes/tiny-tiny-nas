#include "entry.h"

entry_t* alloc() {
  return malloc(sizeof(entry_t));
}

entry_t* init(bool is_directory, char* name, char* path) {
  entry_t* entry = alloc();
  entry->is_directory = is_directory;
  entry->name = name;
  entry->path = path;
  return entry;
}

void free_(entry_t* entry) {
  free(entry);
}

_Entry const Entry = {
  alloc,
  init,
  free_
};
