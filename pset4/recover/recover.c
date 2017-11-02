/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Only needs 1 argument \n");
        return 1;
    }

    // open input file 
    FILE *file = fopen(argv[1], "r");
    if (*file == NULL)
    {
        fprintf(stderr, "Could not open file \n",);
        return 2;
    }

    // make array called buffer
    int buffer [512];
    fread(buffer, 512, 1, inptr);
    int file_count = 1;
    // read first 4 bytes from 512 byte block
    if (buffer[0] == 0xff &&
    buffer[1] == 0xd8 &&
    buffer[2] == 0xff &&
    (buffer[3] & 0xf0) == 0xe0) {
        // found star of jpeg!
        // open jpeg filename ###.jpg
        // keep track of jpegs foudn thusfar!
        if (file_count = 1) {
            sprintf(filename, "00%i.jpg", file_count);
            FILE *img = fopen(filename, "w");
            fwrite(buffer, 512, 1, *img);
        } else {
            file_count += 1;
            fclose(*img);
            sprintf(filename, "%03i.jpg", 2);
            FILE *img = fopen(filename, "w");
            fwrite(buffer, 512, 1, *img);
        }

    } else {

    }


    // close infile
    fclose(inptr);

    // close outfile


    // success
    return 0;
}
