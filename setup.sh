#!/bin/sh

ulimit -c unlimited
git pull
make clean clean.o
cd src
gtags -v
emacs . &

cd ../documents/
git pull
cd ./presentation/
make clean
cd ../thesisAbst/
make clean
cd ../thesis/
make clean
