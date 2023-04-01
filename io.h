/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * Reads a word from a file and stores it in a character array.
 *
 * @param s The character array to store the word in.
 * @param max The maximum number of characters to read.
 * @param f The file to read from.
 *
 * @returns The number of characters read.
 */
int read_word(char *s, int max, FILE *f);
