#!/bin/sh

git pull
make clean clean.o

cd ./documents/
git pull
cd ./presentation/
make clean
cd ../thesisAbst/
make clean
cd ../thesis/
make clean
