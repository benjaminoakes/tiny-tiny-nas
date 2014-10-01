#include "formatter.h"
#include "directory.h"

int main(int argument_count, char** arguments) {
  Formatter formatter = EntryPrettyJSONFormatter;
  char* path;

  if (2 == argument_count) {
    path = arguments[1];
  } else {
    path = ".";
  }

  Directory.list(path, formatter);

  return 0;
}
