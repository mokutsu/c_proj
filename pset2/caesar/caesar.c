#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    if(argc != 2) {
        printf("incorrect number of arguments. womp womp.\n");
        return 1;
    }
    // for (int i=0; i<argc; i++) {
    //     printf("%s \n", argv[i]);        
    // }
    char input[20];
    string argument = argv[1];
    strcpy(input, argument);
    int val = atol(input);
    if (val > 26) {
        val = val % 26;
    }
    // printf("String value = %s, Long value = %i \n", input, val);

    // get string to be cyphered
    printf("plaintext: ");
    string plaintext = get_string();
    int string_length = strlen(plaintext);
    int encrypted[string_length];
    // printf("STRING LENGTH: %i", )
    for (int i=0; i<string_length; i++) {
        int char_int = (int) plaintext[i];
        int encr = 0;
        // printf("char is %c, int is %i", plaintext[i], char_int);
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z'){
            encr = char_int + val;
            if (encr >'Z') {
                encr -= 26;
            }
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            encr = char_int + val;
            if (encr >'z') {
                encr -= 26;
            }
        } else {
            encr = (int) plaintext[i];
        }
        // printf("after ecryption, int: %i", encr);   
        // printf("char: %c \n", (char)encr);
        encrypted[i] = encr;
    }
    char str_encrypted[string_length];
    for (int j=0; j < string_length; j++) {
        str_encrypted[j] = (char) encrypted[j];
    }
    str_encrypted[string_length]='\0';
    
    // output ciphertext
    printf("ciphertext: %s\n", str_encrypted);
    // for (int j=0; j<string_length; j++) {
    //     printf("%c", (char) encrypted[j]);
    // }
    // printf("\n");
    return 0;
}