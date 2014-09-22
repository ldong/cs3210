README
======

Implementation Design
---------------------

1. A unique sequence of symbols (`.` for "dit" and `-` for "dah") that
represents a character (letter or numeral) are delimited by a single space ` `.

2. The letters of a word are separated by a vertical bar `|`.

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
     S          U          R            W           ?           K          G        O
   / \         / \        / \          / \         / \         / \        /\        /\
  H   V      F     ?     L    ?      P    J      B    X      C    Y     Z    Q     ?  ?
 /\   /\    /\    /\    /\    /\    /\    /\    /\    /\    /\    /\    /\   /\   /\  /\
5  4 ? 3   ?  ?  ?  2  ?  ?  ?  ?  ?  ?  ?  1  6  ?  ?  ?  ?  ?  ?  ?  7  ?  ? ? 8 ? 9  0
```

* There is a total number of 64 slots.
* An array with size 2^6 -1 = 63, indexing start from 1, array size will be 1.
* K, the index of the current node
  - Index of Left child of node K: 2k
  - Index of Right child of node K: 2k+1

Automated build
---------------

If a morse code sequence is given as an argument, it will be translated.
Otherwise a default string sequence `"- . ... - .. -. --.|... - .-. .. -. --."`
will be written to the procfs file which translate to `TESTING STRING` after
reading.

Usage
-----

`chmod +x runtest.sh cleanmod.sh`

`./runtest.sh`

or

`./runtest "-.-. ... ...-- ..--- .---- -----|.--. .----"`

Run `./cleanmod.sh` to unload the module and clean the directory if you want to
commit any changes.


