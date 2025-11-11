#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 100
#define DELIM "," // CSV delimiter

char *ifile, *ofile;
unsigned filter_age_max;
FILE *istream, *ostream;

#define USAGE \
"Filters CSV rows, keeping only those with provided maximum age\n" \
"%s max-age [input-file] [output-file]\n\n" \
"Example:\n" \
"%s max-age input.csv output.csv\n" \
"%s max-age input.csv (output to stdout)\n" \
"%s max-age           (input from stdin, output to stdout)\n"

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;

  while (!feof(istream)) {
    ++line_no;

    // Read a line from `istream` and assign the return value to `fgets_return`
    // YOUR CODE HERE

    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Assign `name` and `age_str` using `strtok`
        // YOUR CODE HERE

        // Alternative to strtok:
        // sscanf(line, "%*[^,],%d", &age);

        if (!age_str) {
          // Error message
          // YOUR CODE HERE
          continue;
        }
      }
    } else {
      // Error message
      // YOUR CODE HERE
      continue;
    }

    // Age processing
    unsigned age;
    int recognized_count = sscanf(age_str, "%d", &age);
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        // Forward input line to `ostream`
        // YOUR CODE HERE
      }
    } else {
      // Error message
      // YOUR CODE HERE
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    // max-age ifile ofile
    ofile = argv[3];
  case 3:
    // max-age ifile
    ifile = argv[2];
  case 2:
    // max-age
    if (!sscanf(argv[1], "%d", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0], argv[0], argv[0], argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    // Open `ifile` and assign it to `istream`
    // YOUR CODE HERE

    // Exit program with an error message if file cannot be opened
    // YOUR CODE HERE
  } else {
    // Set `ostream` if no file provided
    // YOUR CODE HERE
  }

  if (ofile) {
    // Open `ofile` and assign it to `ostream`
    // YOUR CODE HERE

    // Exit program with an error message if file cannot be opened
    // YOUR CODE HERE
  } else {
    // Set `ostream` if no file provided
    // YOUR CODE HERE
  }

  filter_stream(istream, ostream);
}