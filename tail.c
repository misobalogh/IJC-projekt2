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
    unsigned int size; // max size 4095
    char line[MAX_LINE_SIZE];
} cb_element;

//=============================== Interface ===============================//

long parse_args(int argc, char **argv);

int invaild_number_of_lines();

// void cb_create(n);

// void cb_put(cb,line);

// cb_element cb_get(cb);

// void cb_free(cb);

//=============================== Functions ===============================//

/*if (fp == NULL)
                {
                    fprintf(stderr, "Error opening file %s\n", argv[2]);
                    exit(EXIT_FAILURE);
                */

long parse_args(int argc, char **argv)
{
    FILE *fp = stdin;                  // default input file
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
                fp = argv[3];
            }
        }
    }
    else if (argc > 1)
    {
        fp = argv[1];
    }
    printf("%s\n", fp);
    
    return last_n_lines;

error_exit1:
    fprintf(stderr, "tail: invalid number of lines\n");
    return -1;
}

//=============================== Main ===============================//

int main(int argc, char **argv)
{
    long last_n_lines = parse_args(argc, argv);
}
