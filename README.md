# Overview

This is a basic C program that reads data line by line from an input CSV file or from standard input, filters the lines based on a maximum allowed age, and writes the valid lines to an output file or standard output.  
Each line in the input is expected to have a name and an age separated by a comma.  
Only entries with an age less than or equal to the user-provided limit are written to the output.
I have only written the parts wrapped by ``MY CODE START`` and ``MY CODE END``.

## Example output

An example output of the program can be senn in the ``output.csv`` file with its provided arguments.

## Flowchart

The flowchart and included mermaid code only represents the entire program logic.

# Files

## main.c

Explanations of the code blocks I have written:

### Inside ``filter_stream()``

This function is responsible for processing the input one line at a time.
It reads each line using ``fgets()``, splits it into two parts (a name and an age) using ``strtok()``, and converts the age text into a number with ``sscanf()``.
If a line is valid and the age is within the specified limit, the line is written to the output.
If a line is incomplete or contains invalid data, it is simply skipped.

In short:

- Reads a line from the input stream.
- Extracts the name and age fields.
- Checks if the age is within the allowed range.
- Writes valid lines to the output.

### Inside ``main()``

The main function handles program setup and teardown.
It reads the command-line arguments, checks that they are valid, and opens the input and output streams (or defaults to standard input/output if no files are given).
It then prints a short summary of the arguments being used and calls ``filter_stream()`` to process the data.
Finally, it closes any open files before the program ends.

In short:

- Reads arguments from the command line.
- Opens input and output files if given.
- Prints a short summary of settings.
- Calls ``filter_stream()`` to do the actual filtering.
- Closes files and exits.