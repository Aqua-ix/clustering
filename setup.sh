#!/bin/sh

git pull

make clean
make clean.o

cd ./documents/
git pull
