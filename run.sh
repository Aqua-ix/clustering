#!/bin/sh

mkdir -p .log

if [ $1 = "all" ]; then
    ./grouplens.out > ./.log/grouplens.log &
    ./bfcs_crisp.out > ./.log/bfcs_crisp.log &
    ./efcs_crisp.out > ./.log/efcs_crisp.log &
    ./qfcs_crisp.out > ./.log/qfcs_crisp.log &
    ./bpcs_crisp.out > ./.log/bpcs_crisp.log &
    ./epcs_crisp.out > ./.log/epcs_crisp.log &
    ./qpcs_crisp.out > ./.log/qpcs_crisp.log &
    ./bfcs_overlap.out > ./.log/bfcs_overlap.log &
    ./efcs_overlap.out > ./.log/efcs_overlap.log &
    ./qfcs_overlap.out > ./.log/qfcs_overlap.log &
    ./bpcs_overlap.out > ./.log/bpcs_overlap.log &
    ./epcs_overlap.out > ./.log/epcs_overlap.log &
    ./qpcs_overlap.out > ./.log/qpcs_overlap.log &
    exit 0
elif [ $1 = "grouplens" ]; then
    ./grouplens.out > ./.log/grouplens.log &
    exit 0
elif [ $1 = "crisp" ]; then
    ./bfcs_crisp.out > ./.log/bfcs_crisp.log &
    ./efcs_crisp.out > ./.log/efcs_crisp.log &
    ./qfcs_crisp.out > ./.log/qfcs_crisp.log &
    ./bpcs_crisp.out > ./.log/bpcs_crisp.log &
    ./epcs_crisp.out > ./.log/epcs_crisp.log &
    ./qpcs_crisp.out > ./.log/qpcs_crisp.log &
    exit 0
elif [ $1 = "overlap" ]; then
    ./bfcs_overlap.out > ./.log/bfcs_overlap.log &
    ./efcs_overlap.out > ./.log/efcs_overlap.log &
    ./qfcs_overlap.out > ./.log/qfcs_overlap.log &
    ./bpcs_overlap.out > ./.log/bpcs_overlap.log &
    ./epcs_overlap.out > ./.log/epcs_overlap.log &
    ./qpcs_overlap.out > ./.log/qpcs_overlap.log &
    exit 0
elif [ $1 = "fcs_crisp" ]; then
    ./bfcs_crisp.out > ./.log/bfcs_crisp.log &
    ./efcs_crisp.out > ./.log/efcs_crisp.log &
    ./qfcs_crisp.out > ./.log/qfcs_crisp.log &
    exit 0
elif [ $1 = "fcs_overlap" ]; then
    ./bfcs_overlap.out > ./.log/bfcs_overlap.log &
    ./efcs_overlap.out > ./.log/efcs_overlap.log &
    ./qfcs_overlap.out > ./.log/qfcs_overlap.log &
    exit 0
    elif [ $1 = "pcs_crisp" ]; then
    ./bpcs_crisp.out > ./.log/bpcs_crisp.log &
    ./epcs_crisp.out > ./.log/epcs_crisp.log &
    ./qpcs_crisp.out > ./.log/qpcs_crisp.log &
    exit 0
elif [ $1 = "pcs_overlap" ]; then
    ./bpcs_overlap.out > ./.log/bpcs_overlap.log &
    ./epcs_overlap.out > ./.log/epcs_overlap.log &
    ./qpcs_overlap.out > ./.log/qpcs_overlap.log &
    exit 0
else
    echo "Please specify the method type of program."
    exit 1
fi
