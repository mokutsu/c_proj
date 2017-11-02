/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include <string.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "wrong arg count. Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER bi_new;
    BITMAPFILEHEADER bf_new;
    bf_new = bf;
    bi_new = bi;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0){
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    int n = atoi(argv[1]);
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;

    // determine padding for scanlines
    bi_new.biWidth = bi.biWidth * n;
    int new_padding = (4 - (bi_new.biWidth) * sizeof(RGBTRIPLE) % 4) % 4;
    bi_new.biHeight = bi.biHeight * n;
    bi_new.biSizeImage = (bi_new.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_new.biHeight);

    bf_new.bfSize = bi_new.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPF./resize 2 small.bmp small2.bmpFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        // iterate over pixels in scanline
        for (int z=1; z <=n; z++) {
            // RESIZE HORIZONTAL STARTS HERE 
            for (int j = 0; j < bi.biWidth; j++) {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // RGBTRIPLE temp = triple;
                // write RGB triple to outfile
                for (int l = 0; l < n; l++) {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }                    
            }
            fseek(inptr, old_padding, SEEK_CUR);
            for (int k = 0; k < new_padding; k++) {
                fputc(0x00, outptr);
            }

            // RESIZE HORIZONTAL ENDS HERE ^^
            if (z != n) {
                long shift_size = (bi.biWidth * sizeof(RGBTRIPLE) + old_padding);
                fseek(inptr, -shift_size, SEEK_CUR);
            }
        }
    }
    // close infile 
    fclose(inptr);
    // close outfile
    fclose(outptr);
    // success
    return 0;
}
