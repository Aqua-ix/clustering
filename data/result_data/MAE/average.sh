#!/bin/sh

MP=4

cd $1
python result1.py
cd ${1}_MP${MP}_overlap
python result2.py
