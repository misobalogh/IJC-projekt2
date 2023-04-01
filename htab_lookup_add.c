/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/


#include <stdlib.h> // size_t
#include <stdint.h> // uint32_t

/**
 * Computes the hash value of a given string using the djb2 algorithm.
 *
 * @param str The input string to be hashed.
 *
 * @returns The hash value of the input string.
 */
size_t htab_hash_function(const char *str)
{
    uint32_t h = 0; // 32-bit value
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

