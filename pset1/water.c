#include <stdio.h>
#include <cs50.h>

int main(void) {
    printf("How long is a typical shower for you (in minutes)?\n");
    int minutes = get_int();
    // min * 192 oz / min * 1 bottle / 16oz
    int num_bottles = minutes * 192 / 16;
    printf("That's like, %i x 16oz water bottles! Yowzas!\n", num_bottles);
}