# README

## Idea

Write a program that automatically sort pictures in order and sync up with
dropbox.

## Installation

On **Ubuntu**:

1. Download and extract
    ```
    sudo apt-get install pkg-config
    wget http://hivelocity.dl.sourceforge.net/project/fuse/fuse-2.X/2.9.3/fuse-2.9.3.tar.gz
    tar -xzf fuse-2.9.3.tar.gz
    ```

2. configure and install
    ```
    ./configure
    make
    make install
    ```

3. Try one example
    ```
    mkdir /tmp/fuse
    cd ~/fuse-2.9.3/example
    ./hello /tmp/fuse -d
    ```

4. Compile and download *helloworld* [here](http://fuse.sourceforge.net/helloworld.html)
    ```
    gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
    mkdir /tmp/fuse
    ./hello /tmp/fuse
    ls -l /tmp/fuse
    cat /tmp/fuse/hello
    fusermount -u /tmp/fuse
    ```

# Examples

[Hello world example]
(http://fuse.sourceforge.net/helloworld.html)

[FUSE Main]
(http://fuse.sourceforge.net)

# Reference
[Fuse python]
(https://pypi.python.org/pypi/fuse-python)

[llfuse]
(https://code.google.com/p/python-llfuse/)

[FUSE]
(http://sourceforge.net/projects/fuse/)

[Filesystem in Userspace]
(http://sourceforge.net/p/fuse/wiki/Main_Page/)

[FUSE api]
(http://fuse.sourceforge.net/doxygen/)

[The libexif C EXIF library]
(http://libexif.sourceforge.net)

[Dropbox API]
(https://www.dropbox.com/developers/core)

[Dropbox API for C]
(https://github.com/Dwii/Dropbox-C)

