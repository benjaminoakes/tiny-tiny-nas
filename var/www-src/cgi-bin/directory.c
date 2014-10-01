#include "directory.h"

#define MAX_PATH_LENGTH 1024

bool is_hidden(struct dirent* entry) {
  return (entry->d_name[0] != '.');
}

char* concat_path(char* base_path, char* name) {
  char full_path[MAX_PATH_LENGTH] = "";
  strcat(full_path, base_path);
  if ('/' != base_path[strlen(base_path) - 1]) {
    strcat(full_path, "/");
  }
  strcat(full_path, name);
}

bool is_directory(char* full_path) {
  struct stat st;
  lstat(full_path, &st);
  return !!S_ISDIR(st.st_mode);
}

void list(char* base_path, Formatter formatter) {
  struct dirent** entries;
  int i, entry_count;
  char* name;
  char* path;
  entry_t* entry;

  formatter.before();
  entry_count = scandir(base_path, &entries, 0, alphasort);

  if (entry_count < 0) {
    perror("Couldn't scan directory");
  } else {
    for (i = 0; i < entry_count; i++) {
      if (is_hidden(entries[i])) {
        name = entries[i]->d_name;
        path = concat_path(base_path, name);
        entry = Entry.init(is_directory(path), name, path);

        formatter.display(entry);

        Entry.free(entry);
        free(entries[i]);
      }
    }

    free(entries);
  }

  formatter.after();
}

_Directory const Directory = {
  list
};
