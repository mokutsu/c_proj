/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if wrong number of arguments are supplied, return instructions
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convert argument into int
    int n = atoi(argv[1]);

    // if a third argument is provided, initialize the random
    // number generator with srand using the 2nd number provided.
    // if no number is provided, initialize the random number
    // generator with a null value
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // print back the quantity of random numbers requested. Drand48
    // returns nonnegative double precision floating point values
    //between 0.0 and 1.0. Multiply by the max value to get
    //a value within the range of 0 to limit, and convert to integer.
    
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
