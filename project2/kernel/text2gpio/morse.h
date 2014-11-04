#ifndef MORSE_H
#define	MORSE_H

char alphabet[] = "abcdefghijklmnopqrstuvwqyz";
char *morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
    "....", "..", ".---", "-.-", ".-..", "--",
    "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."};

#define MORSE(x) (morse[(x) - ('a')])

#endif	/* MORSE_H */

