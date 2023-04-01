/***************************************************************
* File Name: tail.c
* Description: riesnie IJC-DU2, priklad a)
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.03.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

/**
 * @file tail.c
 * @author Michal Balogh
 *
 * @brief riesnie IJC-DU2, priklad a)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//=============================== Types ===============================//

#define MAX_LINE_SIZE 4096
#define DEFAULT_LAST_N_LINES 10

/**
 * A struct that contains parsed arguments.
 *
 * @param number_of_lines  Last N number of lines to print from the file if the '-n' switch is enabled.
 * @param fp A pointer to the file to be read from.
 */
typedef struct
{
    long number_of_lines;
    FILE *fp;

} args_t;

/**
 * A struct representing an element in a circular buffer.
 *
 * @param line The content of the element.
 */
typedef struct
{
    char line[MAX_LINE_SIZE + 1];

} cb_element;

/**
 * A circular buffer data structure that stores a range of elements.
 *
 * @typedef cb_t
 * @struct cb_t
 *
 * @param start The starting index of the circular buffer.
 * @param end The ending index of the circular buffer.
 * @param elements A pointer to array of elements stored in the circular buffer.
 * @param size The size of the circular buffer.
 */
typedef struct
{
    unsigned int start;
    unsigned int end;
    cb_element *elements;
    unsigned int size;

} cb_t;

//=============================== Interface ===============================//

/**
 * Parses command line arguments.
 * If the first argument is "-n", the argument after that is expected to be a non-negative integer representing the number of lines to print from file.
 * If there is also third argument, it is expected to be the name of the file to read from.
 * If the first argument is not "-n", it is expected to be the name of the file to read from.
 * If no arguments are provided, the function will read from stdin.
 * If an error occurs during parsing, program will end with EXIT_FAILURE.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 *
 * @returns args_t struct containing the parsed arguments.
 *
 */
args_t parse_args(int argc, char **argv);

/**
 * Prints the last n lines of a file.
 *
 * The default number of lines is 10, and the function reads up to a maximum of 4095 characters per line.
 * To store lines from the file to the circular buffer, the function uses the 'cb_put' function,
 * and to retrieve the lines from the circular buffer, it uses the 'cb_get' function.
 *
 * @param cb A circular buffer used to store the last n lines of the file.
 * @param file A pointer to the file to read from.
 * @param n The number of lines to print.
 *
 * @return None
 */
void print_last_n_lines(cb_t *cb, FILE *file, unsigned int n);

/**
 * Creates a new circular buffer with a given capacity.
 *
 * @param n The capacity of the circular buffer.
 *
 * @returns A pointer to the new circular buffer.
 */
cb_t *cb_create(unsigned long n);

/**
 * Puts a string into the circular buffer.
 *
 * @param cb A pointer to the circular buffer.
 * @param line A pointer to the string to be put into the buffer.
 *
 * @returns None
 */
void cb_put(cb_t *cb, char *line);

/**
 * Retrieves the next element from the circular buffer.
 *
 * @param cb A pointer to the circular buffer.
 *
 * @returns A pointer to the next element in the buffer. Returns NULL if the buffer is empty.
 */
char *cb_get(cb_t *cb);

/**
 * Frees the memory allocated for a circular buffer and its elements.
 *
 * @param cb A pointer to the circular buffer to be freed.
 *
 * @returns None
 */
void cb_free(cb_t *cb);

//=============================== Functions ===============================//

void cb_put(cb_t *cb, char *line)
{
    // If end reaches start, start is moved and the old data are overwritten by new data.
    if (cb->end == cb->start)
    {
        cb->start++;
        cb->start %= cb->size; // If start reaches size of the buffer, it will be set to position 0.
    }
    strncpy(cb->elements[cb->end++].line, line, MAX_LINE_SIZE + 1);
    cb->end %= cb->size; // If end reaches size of the buffer, it will be set to position 0.
}

char *cb_get(cb_t *cb)
{
    char *line = cb->elements[cb->start++].line;
    cb->start %= cb->size; // If start reaches size of the buffer, it will be set to position 0.
    return line;
}

void print_last_n_lines(cb_t *cb, FILE *file, unsigned int n)
{

    cb->start = 0;
    cb->end = 0;

    int printed_warning = 0;

    char line[MAX_LINE_SIZE + 2];
    while (fgets(line, MAX_LINE_SIZE + 1, file) != NULL)
    {
        if (strlen(line) == MAX_LINE_SIZE && line[MAX_LINE_SIZE - 1] != '\n')
        {

            if (line[strlen(line)] == '\0')
            {
                line[strlen(line) - 1] = '\n';
            }
            if (!printed_warning)
            {
                fprintf(stderr, "Warning: line is longer than the max length of line.\n");
                printed_warning = 1;
            }
            int trash;
            while ((trash = fgetc(file)) != EOF && trash != '\n')
            {
                // Discard characters until the end of line or end of file is reached
            }
        }

        cb_put(cb, line);
    }

    for (unsigned int i = 0; i < n; i++)
    {
        printf("%s", cb_get(cb));
    }
}

cb_t *cb_create(unsigned long n)
{
    cb_t *cb = malloc(sizeof(cb_t));
    if (cb == NULL)
    {
        fprintf(stderr, "Error: memory allocation error");
        exit(EXIT_FAILURE);
    }
    cb->size = n;
    cb->start = 0;
    cb->end = 0;
    cb->elements = malloc(sizeof(cb_element) * cb->size);
    return cb;
}

void cb_free(cb_t *cb)
{
    free(cb->elements);
    free(cb);
}

args_t parse_args(int argc, char **argv)
{
    args_t args;
    args.fp = stdin;                   // default input file
    const char *program_switch = "-n"; // program optional switch
    args.number_of_lines = DEFAULT_LAST_N_LINES;

    if (argc > 1 && (strcmp(argv[1], program_switch) == 0)) // ./tail -n (program with switch)
    {
        if (argc < 3) // ./tail -n 'missing arg'
        {
            goto error_exit1;
        }
        else // ./tail -n last_n [file]
        {
            // checks if argument after -n is number
            // program will also accept for example 4a, but will only take the 4 as a number
            if (!isdigit(argv[2][0]))
            {
                goto error_exit1;
            }
            args.number_of_lines = strtol(argv[2], NULL, 10);
            if (args.number_of_lines < 0)
            {
                goto error_exit1;
            }

            if (argc > 3) // ./tail -n last_n file
            {
                args.fp = fopen(argv[3], "r");
            }
        }
    }
    else if (argc > 1)
    {
        args.fp = fopen(argv[1], "r");
    }

    if (args.fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    return args;

error_exit1:
    fprintf(stderr, "tail: invalid number of lines\n");
    exit(EXIT_FAILURE);
}

//=============================== Main ===============================//

int main(int argc, char **argv)
{
    // Parse arguments
    args_t args = parse_args(argc, argv);
    if (args.number_of_lines == 0)
    {
        return 0;
    }

    // Create empty circular buffer
    cb_t *cb = cb_create(args.number_of_lines);

    // Prints last n lines (default )
    print_last_n_lines(cb, args.fp, args.number_of_lines);

    // Cleanup

    // Close file
    fclose(args.fp);
    // Deallocate memmory from circular buffer
    cb_free(cb);
}

//=============================== End of file tail.c ===============================//
