#!/bin/sh

# clustering/ setup
ulimit -c unlimited
echo ===========================
echo git pull start
echo ===========================
git pull
echo ===========================
echo git pull end
echo ===========================
mkdir -p .o
make clean clean.o
rm -rf core
emacs . &
cd src
echo ===========================
echo gtags setup start
echo ===========================
gtags -v
echo ===========================
echo gtags setup end
echo ===========================
# clustering/documents setup
cd ../documents/
echo ===========================
echo documents git pull start
echo ===========================
git pull
echo ===========================
echo documents git pull end
echo ===========================
cd ./presentation/
make clean
cd ../thesisAbst/
make clean
cd ../thesis/
make clean
