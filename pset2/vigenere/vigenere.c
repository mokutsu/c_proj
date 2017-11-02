#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    if(argc != 2) {
        printf("incorrect number of arguments. womp womp.\n");
        return 1;
    }
    
    // get numerical value of each character
    // char input[20];
    int key_length = strlen(argv[1]);
    char key_letters[key_length];
    strcpy(key_letters, argv[1]);
    int key_nums[key_length];
    for (int a=0; a<key_length; a++) {
        int encr = toupper(key_letters[a]);
        int diff = encr - 'A';
        if (encr >= 'A' && encr <= 'Z'){
            encr = encr - 'A';
        } else {
            printf("ERROR: Non-alphanumeric input");
            return 1;
        }
        key_nums[a] = diff;
    }

    // get string to be cyphered
    printf("plaintext: ");
    string plaintext = get_string();
    int string_length = strlen(plaintext);
    int encrypted[string_length];
    int val = -1;
    for (int i=0; i<string_length; i++) {

        int char_int = (int) plaintext[i];
        int encr = 0;
        // If the plaintext character is not alphabetical
        if ((char_int < 'A') || (char_int > 'Z' && char_int < 'a') || (char_int > 'z')) {
            encr = char_int;
        } else {
        // if plaintext character is alphabetical increment cipher key position by 1
            val += 1;
            if (val > key_length-1) {
                val = val % key_length;
            }
        // Check if the word is upper case. If it wraps over into lower case, pull back into upper case
            if (plaintext[i]<= 'Z') {
                encr = char_int + key_nums[val];
                if (encr >'Z') {
                    encr -= 26;
                }
            }
            // Check if the word is lower case. If it wraps over past z, pull back into lower case range
            if (plaintext[i]>='a') {
                encr = char_int + key_nums[val];
                if (encr >'z') {
                    encr -= 26;
                }
            }
        }
        encrypted[i] = encr;
        
    }
    char str_encrypted[string_length];
    for (int j=0; j < string_length; j++) {
        str_encrypted[j] = (char) encrypted[j];
    }

    // output ciphertext
    str_encrypted[string_length] = '\0';
    printf("ciphertext: %s", str_encrypted);
    printf("\n");
    return 0;
}
