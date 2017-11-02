#include <stdio.h>
#include <cs50.h>

int main(void) {
    int height = -1;
    printf("How big should Mario's pyramid be? Pick a number between 0 and 23.\n");
    height = get_int();
    while (height < 0 || height > 23) {
        printf("try again silly\n");
        height = get_int();    
    }
    for (int step=0; step < height; step++) {
    // print spaces
        for (int i=0; i<(height-step)-1; i++) {
            printf(" ");
        }
    // print block
        for (int i=0; i<step+1; i++) {
            printf("#");
        }
    // print space at center
        printf("  ");
    // print block at end
        for (int i=0; i<step+1; i++) {
            printf("#");
        }
        printf("\n");
    }
}