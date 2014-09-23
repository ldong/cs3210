# README

## Implementation Design

1. Delimiter will be space

2. Vertical Bar will be separate the actual words

3. Construct the Morse code tree based on wiki international morse code

![](./resources/wiki.png)

```
                                 .                       -
                                Dit                     Dah

                                         START
                      /                                            \
                     E                                              T
            /                   \                         /                  \
           I                     A                       N                    M
      /        \            /         \             /         \            /      \
     S          U          R            W           D           K          G        O
   / \         / \        / \          / \         / \         / \        /\        /\
  H   V      F     ?     L    ?      P    J      B    X      C    Y     Z    Q     ?  ?
 /\   /\    /\    /\    /\    /\    /\    /\    /\    /\    /\    /\    /\   /\   /\  /\
5  4 ? 3   ?  ?  ?  2  ?  ?  ?  ?  ?  ?  ?  1  6  ?  ?  ?  ?  ?  ?  ?  7  ?  ? ? 8 ? 9  0
```

Total number of slots is 64

An array with size 2^6 -1 = 63, indexing start from 1, array size will be 1;

K, the index of the current node

index of Left child of node K: 2k

index of Right child of node K: 2k+1


## Test code

Run make using `make run` `make clean`

or manual

```
gcc -c morse_code.c
gcc -c main.c
gcc -o run main.o morse_code.o
```

