#include "formatter.h"

static bool first;
void noop() { }

char* inspect_bool(bool b) {
  return b ? "true" : "false";
}

void html_before() {
  printf("<ul>\n");
}

void html_display(entry_t* entry) {
  // TODO: handle directories differently
  printf("<li><a href=\"%s\">%s</a></li>\n",
         entry->name,
         entry->name);
}

void html_after() {
  printf("</ul>\n");
}

Formatter const EntryHTMLFormatter = {
  html_before,
  html_display,
  html_after
};

void json_before() {
  first = true;
  printf("[");
}

void json_display(entry_t* entry) {
  if (first) {
    first = false;
  } else {
    printf(",");
  }

  printf("{\"isDirectory\":%s,"
          "\"name\":\"%s\","
          "\"path\":\"%s\"}",
          inspect_bool(entry->is_directory),
          entry->name,
          entry->path);
}

void json_after() {
  printf("]\n");
}

Formatter const EntryJSONFormatter = {
  json_before,
  json_display,
  json_after
};

void p_json_before() {
  first = true;
  printf("[\n");
}

void p_json_display(entry_t* entry) {
  char* spacer;

  if (first) {
    first = false;
  } else {
    printf(",\n");
  }

  spacer = (entry->is_directory) ? " " : "";

  printf("  { \"isDirectory\": %s,%s"
            " \"name\": \"%s\","
            " \"path\": \"%s\" }",
         inspect_bool(entry->is_directory),
         spacer,
         entry->name,
         entry->path);
}

void p_json_after() {
  printf("\n]\n");
}

Formatter const EntryPrettyJSONFormatter = {
  p_json_before,
  p_json_display,
  p_json_after
};

void text_display(entry_t* entry) {
  printf("%s\n", entry->name);
}

Formatter const EntryTextFormatter = {
  noop,
  text_display,
  noop
};
