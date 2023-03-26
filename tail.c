/***************************************************************
* File Name: tail.c
* Description: riesnie IJC-DU2, priklad a)
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.03.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/
// TODO komenty, hlavicka

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
    char line[MAX_LINE_SIZE];

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

args_t parse_args(int argc, char **argv);

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
    strcpy(cb->elements[++cb->end].line,line);
    cb->end %= cb->size; // If end reaches size of the buffer, it will be set to position 0.
    if (cb->end== cb->start) { // If end reaches start, start is moved and the old data are overwritten by new data.
        cb->start++;           
        cb->start %= cb->size; // If start reaches size of the buffer, it will be set to position 0.
    }
}

char* cb_get(cb_t *cb)
{
    char *line = cb->elements[cb->start++].line; 
    cb->start %= cb->size; // If start reaches size of the buffer, it will be set to position 0.
    return line;
}

int print_last_n_lines(cb_t *cb, FILE *file, unsigned int n)
{
    int number_of_lines = 0;
    cb->start = 0;
    cb->end = 0;

    char line[MAX_LINE_SIZE];
    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        cb_put(cb,line);
        number_of_lines++;
    }

    for (int i = 0; i < DEFAULT_LAST_N_LINES; i++)
    {
        printf("%s", cb_get(cb));
    }

    return number_of_lines; // Returns number of lines read
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
    long last_n_lines = DEFAULT_LAST_N_LINES;

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
            last_n_lines = atol(argv[2]);
            if (last_n_lines < 0)
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

    // Create empty circular buffer
    cb_t *cb = cb_create(DEFAULT_LAST_N_LINES);
    
    // Prints last n lines (default )
    print_last_n_lines(cb, args.fp, args.number_of_lines);
    // TODO kontrola DEFAULT_LAST_N_LINES <= lines in file?
    // ? mozno nie, lebo tail POSSIX funguje

    fclose(args.fp);
    
    cb_free(cb);
}


//=============================== End of file tail.c ===============================//
