#include <stdio.h>
#include "morse_code.h"

int translate(char* arr){
    int size = 0; // size of arr
    int index = 1;
    char const *ptr = arr;
    while(*ptr){
        if(*ptr == '.'){
            index = 2 * index;
        } else if(*ptr == '-'){
            index = 2 * index + 1;
        }
        ++size;
        ++ptr;
    }
    return lookup(index);
}

char lookup(int index){
    // index from 1
    char morse[MORSE_SIZE]  = {
       '?'
      ,'?'
      ,'E' ,'T'
      ,'I' ,'A' ,'N' ,'M'
      ,'S' ,'U' ,'R' ,'W' ,'?' ,'K' , 'G', 'O'
      ,'H' ,'V' ,'F' ,'?' ,'L' ,'?' , 'P', 'J'
      ,'B' ,'X' ,'C' ,'Y' ,'Z' ,'Q' , '?', '?'
      ,'5' ,'4' ,'?' ,'3'
      ,'?' ,'?' ,'?' ,'2'
      ,'?' ,'?' ,'?' ,'?'
      ,'?' ,'?' ,'?' ,'1'
      ,'6' ,'?' ,'?' ,'?'
      ,'?' ,'?' ,'?' ,'?'
      ,'7' ,'?' ,'?' ,'?'
      ,'8' ,'?' ,'9' ,'0'
    };
    return morse[index];
}
