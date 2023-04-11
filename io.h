/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b) hlavickovy subor pre io.c
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 04.04.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * Reads a word from a file and stores it in a character array.
 *
 * @param s The character array in which the function store the word.
 * @param max The maximum length of the word to be read - the rest of the word will be skipped.
 * @param f The file stream to read from.
 *
 * @returns The length of the read word, or EOF if no word has been read.
 */
int read_word(char *s, int max, FILE *f);

//====================== End of file io.h ===============================//
