#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"
#include "directory.h"

// From http://spskhokhar.blogspot.com/2012/09/url-decode-http-query-string.html
int url_decode(char* str) {
  unsigned int i;
  char tmp[BUFSIZ];
  char* ptr = tmp;
  memset(tmp, 0, sizeof(tmp));

  for (i=0; i < strlen(str); i++) {
    if (str[i] != '%') {
      *ptr++ = str[i];
      continue;
    }

    if (!isdigit(str[i+1]) || !isdigit(str[i+2])) {
      *ptr++ = str[i];
      continue;
    }

    *ptr++ = ((str[i+1] - '0') << 4) | (str[i+2] - '0');
    i += 2;
  }

  *ptr = '\0';
  strcpy(str, tmp);
  return 0;
}

char* query_string_path() {
  char* path;
  char* query_string;
  int length;
  
  query_string = getenv("QUERY_STRING");

  if (NULL != query_string && 0 == strncmp("path=", query_string, 5)) {
    length = strlen(query_string);
    path = malloc(length);
    strncpy(path, query_string + 5, length - 5);
  }

  url_decode(path);

  return path;
}

int main() {
  char* path;
  Formatter formatter = EntryJSONFormatter;

  printf("Content-type: application/json\r\n\r\n");

  path = query_string_path();
  Directory.list(path, formatter);

  return 0;
}
