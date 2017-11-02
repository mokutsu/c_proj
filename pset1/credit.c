#include <stdio.h>
#include <cs50.h>
#include <math.h>

double pow(double x, double y);
float powf(float x, float y);
long double powl(long double x, long double y);
 
int main(void) {
    printf("Please enter credit card number");
    long credit_num = get_long_long();
    while (credit_num < 0) {
        printf("Please enter credit card number");
        credit_num = get_long_long();
    }

    int power = 1;
    int sum_of_ones = 0;
    int sum_of_twos = 0;
    int digit_value = 0;
    
    while (credit_num/(pow(10, power)) >= 0.1) {

        long ten = 10;
        long remainder = pow(ten, power);
        remainder = credit_num % remainder;
        long remainder_less = (pow(10, (power-1)));
        remainder_less = remainder % remainder_less;
        digit_value = (remainder-remainder_less) / pow(10, (power-1));
            
        if ((power % 2) == 0) {

        // get digit value
            digit_value = digit_value * 2;
        // boil down to single digit value if greater than 10
            if (digit_value >= 10) {
                int tens = 1;
                int ones = digit_value-10;
                digit_value = tens + ones;

            }
        // add to total
            sum_of_twos += digit_value;

        } else {

            sum_of_ones += digit_value;

        }
        power += 1;
    };


    int total_sum = sum_of_ones + sum_of_twos;
    
    int num_digits = power-1;

    // get first digit which would equal last loop value
    long exp_10_dig = pow(10, power-1);
    long exp_10_p = pow(10, power-2);
    long exp_10_p1 = pow(10, (power-3));
    int first_digit = ((credit_num % exp_10_dig) - (credit_num % exp_10_p)) / exp_10_p;
    int first_two_digs = (credit_num % (exp_10_dig) - credit_num % exp_10_p1) / exp_10_p1;

    bool dig_valid = false;

    if (total_sum % 10 == 0) {
        dig_valid = true;
    }
    // amex = 15 digit, starts with 34 or 37
    // mastercard = 16 digits, starts with 51 - 55
    // visa = 13 or 16 digits, starts with 4

    if (dig_valid == true && num_digits == 15 && (first_two_digs == 34 || first_two_digs == 37)){
        printf("AMEX\n");
    } else if ((dig_valid == true && num_digits == 16) && ((first_two_digs > 50) && (first_two_digs < 58))) {
        printf("MASTERCARD\n");
    } else if (dig_valid == true && (num_digits == 15 || num_digits == 16) && first_digit == 4) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }
    
}
