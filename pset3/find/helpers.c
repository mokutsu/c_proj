/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int left_bound = 0;
    int right_bound = n;
    int middle = n/2;

    while ((right_bound - left_bound) > 0) {
        // if the value is at the middle, exit with true
        if (value == values[middle]) {
            return true;
        } else if (value > values[middle]) {
            left_bound = middle+1;
            middle = (middle + right_bound) / 2;
        } else {
            right_bound = middle;
            middle = (middle + left_bound) / 2;
        }        
    }
    return false;
}

    
    // if the value is greater than the middle, toss out the left
    
    // if the value is less than the middle, toss out the right
    
    // if (n < 0) {
    //     return false;
    // }
    // for (int i=0; i<n; i++) {
    //     if (value == values[i]) {
    //         return true;
    //     }
    // }
    // return false;
// }

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
  // start at 0
  int start_position = 0;
  int min = values[0];
  int position = 0;
  // go up the array to find min value
  while(start_position < n-1) {
    min = values[start_position];
    for (int i=start_position; i < n; i++) {
      if (values[i] < min) {
        min = values[i];
        position = i;
      } else if (values[i] == min) {
        position = i;
      }
    }
    // swap values
    values[position] = values[start_position];
    // console.log(values);
    values[start_position] = min;
    // console.log(values);
    start_position += 1;
  }

    return;
}

