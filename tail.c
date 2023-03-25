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
#define LAST_N_LINES 10

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
    cb_element *elements;
    unsigned int size;

} cb_t;

//=============================== Interface ===============================//

args_t parse_args(int argc, char **argv);

cb_t *cb_create(unsigned long n);
// TODO len doplnit z funkcie get_input
//  void cb_put(cb,line);

// TODO len ctrl+c ctrlc+v z getinput 
//  cb_element cb_get(cb);

void cb_free(cb_t *cb);

//=============================== Functions ===============================//
//  args_t args = parse_args(argc, argv);
int get_input(cb_t *cb, FILE *file)
{
    // TODO refaktorizacia
    int i = 0;
    cb->start = 0;
    cb->end = 0;

    while (fgets(cb->elements[cb->end++].line, MAX_LINE_SIZE, file) != NULL)
    {
        cb->start%=cb->size;
        cb->end %= cb->size;
        if(cb->start == cb->end) cb->start++;
        i++;
    }
    // TODO kontrola LAST_N_LINES <= lines in file? 
    // ? mozno nie, lebo tail POSSIX funguje
    for (int i = 0; i < LAST_N_LINES; i++)
    {
        printf("%s", cb->elements[cb->start++].line);
        cb->start %= cb->size;
    }

    return i; // Return the number of lines read
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
    long last_n_lines = LAST_N_LINES;

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
    args_t args = parse_args(argc, argv);

    /*char c;
    while ((c = fgets(args.fp)) != EOF)
    {
        putchar(c);
    }
    putchar('\n');

    */

    cb_t *cb = cb_create(LAST_N_LINES);

    printf("lines read: %d\n", get_input(cb, args.fp));

    

    fclose(args.fp);
    cb_free(cb);
}
