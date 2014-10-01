#include <assert.h>
#include <string.h>
#include "entry.h"

void entry_test() {
  entry_t* entry = Entry.init(true, "Music", "/home/username/Music");

  assert(entry->is_directory);
  assert(0 == strcmp(entry->name, "Music"));
  assert(0 == strcmp(entry->path, "/home/username/Music"));

  Entry.free(entry);
}

int main() {
  entry_test();
  return 0;
}
