#ifndef MORSE_H
#define	MORSE_H

char alphabet_table[] = "abcdefghijklmnopqrstuvwqyz";
char *morse_table[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
    "....", "..", ".---", "-.-", ".-..", "--",
    "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."};

#define MORSE(x) (morse_table[(x) - ('a')])

#endif	/* MORSE_H */

