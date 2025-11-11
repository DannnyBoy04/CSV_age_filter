/**
 * @file main.c
 * @author Dánjal Leitisstein Olsen (s255821@dtu.dk)
 * @brief I have only written the parts wrapped by 'MY CODE START' and 'MY CODE
 * END'.
 * @version 0.1
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 100
#define DELIM "," // CSV delimiter

// Strings representing the names of the input- and output files.
// E.g. `people-with-age.csv` and `output.csv`.
char *ifile, *ofile;
// The maximum age to filter the input file by.
unsigned filter_age_max;
// The file pointers used in `filter_stream()`.
FILE *istream, *ostream;

// Message to print of there was an error with the program arguments.
#define USAGE                                                                  \
  "Filters CSV rows, keeping only those with provided maximum age\n"           \
  "%s max-age [input-file] [output-file]\n\n"                                  \
  "Example:\n"                                                                 \
  "%s max-age input.csv output.csv\n"                                          \
  "%s max-age input.csv (output to stdout)\n"                                  \
  "%s max-age           (input from stdin, output to stdout)\n"

void filter_stream(FILE *istream, FILE *ostream) {
  // Holds the contents of a line and sets its max length to `LINE_MAX`.
  char line[LINE_MAX];
  char *fgets_return;
  // Make sure to allocate enough memory for the `name` and `age_str` strings.
  char *name = malloc(LINE_MAX);
  char *age_str = malloc(LINE_MAX);
  size_t line_no = 0;

  while (!feof(istream)) {
    ++line_no;

    // Read a line from `istream` and assign the return value to `fgets_return`
    // MY CODE START

    // Write the contents of the input stream to the `line` string.
    // fgets returns null if it fails to read from the input stream.
    fgets_return = fgets(line, LINE_MAX, istream);

    // MY CODE END

    // If fgets failed to read or if the line was empty (first character is a
    // newline), print an error message and skip it.
    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Assign `name` and `age_str` using `strtok`
        // MY CODE START

        // Tokenize `line` up to DELIM (",").
        char *token = strtok(line, DELIM);
        // If strtok failed to tokenize and find a name, print an error message
        // andskip the line.
        if (!token) {
          fprintf(stderr, "\nERROR: Row %zu was empty or failed to read.",
                  line_no);
          continue;
        }
        // Copy the token to `name` after successful tokenization.
        strcpy(name, token);

        // Tokenize `line` same as before, but also with newline and carriage
        // return.
        token = strtok(NULL, ",\n\r");
        // If strtok failed to tokenize and find an age, print an error message
        // and skip the line.
        if (!token) {
          fprintf(stderr, "\nERROR: No age on row %zu.", line_no);
          continue;
        }
        // Copy the token to `age_str` after successful tokenization.
        strcpy(age_str, token);

        // MY CODE END

        // Alternative to strtok:
        // sscanf(line, "%*[^,],%d", &age);

        // If the row doesn't have an age, print an error message and skip the
        // line.
        if (!age_str) {
          // Error message
          // MY CODE START

          fprintf(stderr, "\nERROR: No age on row %zu.", line_no);

          // MY CODE END
          continue;
        }
      }
    } else {
      // Error message
      // MY CODE START

      fprintf(stderr, "\nERROR: Row %zu was empty or failed to read.", line_no);

      // MY CODE END
      continue;
    }

    // Age processing
    unsigned age;
    // sscanf returns 0 if it doesn't find anything of the specified format to
    // write to `age`.
    int recognized_count = sscanf(age_str, "%d", &age);
    // If the age_str can't be converted to a number, print an error message.
    if (recognized_count == 1) {
      // If the age is greater than the filter age, don't write the line to the
      // ouput stream.
      if (age <= filter_age_max) {
        // Forward input line to `ostream`
        // MY CODE START

        fprintf(ostream, "\n%s, %d", name, age);

        // MY CODE END
      }
    } else {
      // Error message
      // MY CODE START

      fprintf(stderr,
              "\nERROR: Age not recognized (failed to convert to a number)");

      // MY CODE END
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  // If there are 4 arguments, the fourth one is always the output file.
  case 4:
    // max-age ifile ofile
    ofile = argv[3];
  // If there are 3 arguments, the third one is always the input file.
  case 3:
    // max-age ifile
    ifile = argv[2];
  // If there are 2 arguments, the second one is always the filter age.
  case 2:
    // max-age
    // If the second argument isn't a number,
    // print an error message and terminate.
    if (!sscanf(argv[1], "%d", &filter_age_max)) {
      puts("\nERROR: First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  // If no arguments are provided, print the usage.
  default:
    printf(USAGE, argv[0], argv[0], argv[0], argv[0]);
    return EXIT_SUCCESS;
  }

  // If there is an input file, set the input stream to it.
  // Otherwise, the input stream is stdin (the keyboard).
  if (ifile) {
    // Open `ifile` and assign it to `istream`
    // MY CODE START

    istream = fopen(ifile, "r");

    // MY CODE END

    // Exit program with an error message if file cannot be opened
    // MY CODE START

    if (istream == NULL) {
      fprintf(stderr, "\nERROR: Not able to open input file.");
    }

    // MY CODE END
  } else {
    // Set `istream` if no file provided
    // MY CODE START

    istream = stdin;

    // MY CODE END
  }

  // If there is an ouput file, set the output stream to it.
  // Otherwise, the output stream is stdout (the terminal).
  if (ofile) {
    // Open `ofile` and assign it to `ostream`
    // MY CODE START

    ostream = fopen(ofile, "w");

    // MY CODE END

    // Exit program with an error message if file cannot be opened
    // MY CODE START

    if (ostream == NULL) {
      fprintf(stderr, "\nERROR: Not able to open output file.");
    }

    // MY CODE END
  } else {
    // Set `ostream` if no file provided
    // MY CODE START

    ostream = stdout;

    // MY CODE END
  }

  // MY CODE START

  // Start the output stream with a short text block
  // explaining the arguments used.
  switch (argc) {
  case 4:
    fprintf(ostream,
            "Arguments used for this output:\nMax-age filter, %s"
            "\nInput-stream, %s\nOutput-stream, %s\n",
            argv[1], argv[2], argv[3]);
    break;
  case 3:
    fprintf(ostream,
            "Arguments used for this output:\nMax-age filter, %s"
            "\nInput-stream, %s\nOutput-stream, stdout\n",
            argv[1], argv[2]);
    break;
  case 2:
    fprintf(ostream,
            "Arguments used for this output:\nMax-age filter, %s"
            "\nInput-stream, stdin\nOutput-stream, stdout\n",
            argv[1]);
    break;
  }

  // MY CODE END

  // Read the input stream and write the filtered result to the output stream.
  filter_stream(istream, ostream);

  // MY CODE START

  // Close the opened files.
  fclose(istream);
  fclose(ostream);

  // MY CODE END
}