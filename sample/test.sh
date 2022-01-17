#!/bin/sh
NAME=$1
gcc -S -masm=intel "$NAME".c -static
