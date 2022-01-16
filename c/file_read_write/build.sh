#!/bin/bash
gcc -fPIC aes.c -I ./ -c 
gcc -shared -o libaes.so *.o

gcc ./file_read.c ./crypt.c -o file_read -g -I./ -L. -laes -Wl,-rpath=./
gcc ./file_write.c  ./crypt.c -o file_write -g -I./ -L. -laes -Wl,-rpath=./
gcc ./aes_test.c  -o aes_test -g -I./ -L. -laes -Wl,-rpath=./ -DAES128
gcc ./aes_test2.c  -o aes_test2 -g -I./ -L. -laes -Wl,-rpath=./