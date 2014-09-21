#include <stdio.h>
#include <string.h>

#include "morse_code.h"

#define BUFFSIZE 5

int main(int argc, char **argv){

    /* char array[BUFFSIZE] = {'-','.','-'}; */
    /* printf("Test case: %s\n", array); */
    /* int c = translate(array); */
    /* char c = translate(array); */
    /* printf("Output: %c\n", c); */

  char *buffer;
  int length = strlen(argv[1]);
  buffer = malloc(length*sizeof(char));
  buffer = argv[1];

  printf("morse code: %s\nmorse length: %d\n", buffer, length);
  int bytes_read = 0;
  printf("translation: ");

  // parse for single characters (delimeted by a space)
  char charbuf[5];
  char c;
  int i = 0; int r = 0;
  while (length)
  {
    if (buffer[i] == '-' || buffer[i] == '.')
    {
      ++r;
    }
    else if (buffer[i] == ' ')
    {
      memcpy(charbuf, buffer+i-r, r);
      c = translate(charbuf);
      length -= (++r);
      ++bytes_read;
      /* write c to buffer */
      printf("%c", c);

      memset(charbuf, 0, 5);
      r = 0;
    }
    else if (buffer[i] == '|')
    {
      memcpy(charbuf, buffer+i-r, r);
      c = translate(charbuf);
      length -= (++r);
      bytes_read += 2;
      /* write c+<space> to buffer */
      printf("%c ", c);

      memset(charbuf, 0, 5);
      r = 0;
    }
    else if (buffer[i] == '\0')
    {
      memcpy(charbuf, buffer+i-r, r);
      c = translate(charbuf);
      length -= (++r);
      bytes_read += 2;
      /* write c+\0 to buffer */
      printf("%c\n", c);

      /* could break here... */
      break;
    }
    else /* error */ printf("error\n");
    ++i;
  }
  printf("bytes_read: %d\n", bytes_read);

    return 0;
}

