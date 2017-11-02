#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    // printf("Please provide your name");
    string name = get_string();
    int name_length = strlen(name);
    // printf("name is %u chars", name_length);
    
    // int i=0;
    // char first_char = " ";
    // char space = " ";
// check for first initial
    int position = 0;
    for(int i=position; i<name_length-1; i++) {
        position = i;
        char letter = name[i];
        if (letter != ' ') {
            printf("%c", toupper(letter));
            break;
        }
    }

// check for all remaining initials
    for(int i=position; i<name_length-1; i++) {
        char letter = name[i];
        if (letter == ' ') {
            char next = name[i+1];
            if (next != ' ') {
            letter = name[i+1];
            printf("%c", toupper(letter));                
            }
        }
    }
    printf("\n");
}