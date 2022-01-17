#/bin/sh

gcc cc2.c -o cc2
./cc2 > test.s
gcc test.s -o test
./test
echo $?
