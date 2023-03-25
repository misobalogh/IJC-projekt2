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
#define DEFAULT_LAST_N 10

typedef struct
{
    long number_of_lines;
    FILE *fp;

} args_t;

typedef struct
{
    unsigned int size; // max size 4095
    char line[MAX_LINE_SIZE];

} cb_element;

typedef struct
{
    unsigned int start;
    unsigned int end;
    cb_element *element;
    unsigned int size;

} cb_t;

//=============================== Interface ===============================//

args_t parse_args(int argc, char **argv);

cb_t *cb_create(unsigned long n);

// void cb_put(cb,line);

// cb_element cb_get(cb);

void cb_free(cb_t *cb);

//=============================== Functions ===============================//

cb_t *cb_create(unsigned long n)
{
    cb_t *cb = malloc(sizeof(cb_t));
    cb->size = n;
    cb->start = 0;
    cb->end = 0;
    cb->element = malloc(sizeof(cb_element) * cb->size);
    return cb;
}

void cb_free(cb_t *cb)
{
    long size = cb->size;
    for(int i = 0; i < size; i++)
    {
        free(cb->element[i].line);
    }
    free(cb);
}

args_t parse_args(int argc, char **argv)
{
    args_t args;
    args.fp = stdin;                   // default input file
    const char *program_switch = "-n"; // program optional switch
    long last_n_lines = DEFAULT_LAST_N;

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

    return args;

error_exit1:
    fprintf(stderr, "tail: invalid number of lines\n");
    exit(EXIT_FAILURE);
}

//=============================== Main ===============================//

int main(int argc, char **argv)
{
    /*args_t args = parse_args(argc, argv);
    if (args.fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file\n");
        return -1;
    }

    char c;
    while ((c = fgetc(args.fp)) != EOF)
    {
        putchar(c);
    }
    putchar('\n');

    fclose(args.fp);*/

    cb_t *cbufik = cb_create(10);
    strcpy(cbufik->element->line,"string");

    printf("%s\n", cbufik->element->line);

    cb_free(cbufik);
}
