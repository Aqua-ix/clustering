#!/bin/sh

mkdir -p .log
data=$2

if [ $1 = "all" ]; then
    ./grouplens.out > ./.log/grouplens_$data.log &
    ./bfcs_crisp.out > ./.log/bfcs_crisp_$data.log &
    ./efcs_crisp.out > ./.log/efcs_crisp_$data.log &
    ./qfcs_crisp.out > ./.log/qfcs_crisp_$data.log &
    ./bpcs_crisp.out > ./.log/bpcs_crisp_$data.log &
    ./epcs_crisp.out > ./.log/epcs_crisp_$data.log &
    ./qpcs_crisp.out > ./.log/qpcs_crisp_$data.log &
    ./bfcs_overlap.out > ./.log/bfcs_overlap_$data.log &
    ./efcs_overlap.out > ./.log/efcs_overlap_$data.log &
    ./qfcs_overlap.out > ./.log/qfcs_overlap_$data.log &
    ./bpcs_overlap.out > ./.log/bpcs_overlap_$data.log &
    ./epcs_overlap.out > ./.log/epcs_overlap_$data.log &
    ./qpcs_overlap.out > ./.log/qpcs_overlap_$data.log &
    exit 0
elif [ $1 = "grouplens" ]; then
    ./grouplens.out > ./.log/grouplens_$data.log &
    exit 0
elif [ $1 = "crisp" ]; then
    ./bfcs_crisp.out > ./.log/bfcs_crisp_$data.log &
    ./efcs_crisp.out > ./.log/efcs_crisp_$data.log &
    ./qfcs_crisp.out > ./.log/qfcs_crisp_$data.log &
    ./bpcs_crisp.out > ./.log/bpcs_crisp_$data.log &
    ./epcs_crisp.out > ./.log/epcs_crisp_$data.log &
    ./qpcs_crisp.out > ./.log/qpcs_crisp_$data.log &
    exit 0
elif [ $1 = "overlap" ]; then
    ./bfcs_overlap.out > ./.log/bfcs_overlap_$data.log &
    ./efcs_overlap.out > ./.log/efcs_overlap_$data.log &
    ./qfcs_overlap.out > ./.log/qfcs_overlap_$data.log &
    ./bpcs_overlap.out > ./.log/bpcs_overlap_$data.log &
    ./epcs_overlap.out > ./.log/epcs_overlap_$data.log &
    ./qpcs_overlap.out > ./.log/qpcs_overlap_$data.log &
    exit 0
elif [ $1 = "fcs_crisp" ]; then
    ./bfcs_crisp.out > ./.log/bfcs_crisp_$data.log &
    ./efcs_crisp.out > ./.log/efcs_crisp_$data.log &
    ./qfcs_crisp.out > ./.log/qfcs_crisp_$data.log &
    exit 0
elif [ $1 = "fcs_overlap" ]; then
    ./bfcs_overlap.out > ./.log/bfcs_overlap_$data.log &
    ./efcs_overlap.out > ./.log/efcs_overlap_$data.log &
    ./qfcs_overlap.out > ./.log/qfcs_overlap_$data.log &
    exit 0
    elif [ $1 = "pcs_crisp" ]; then
    ./bpcs_crisp.out > ./.log/bpcs_crisp_$data.log &
    ./epcs_crisp.out > ./.log/epcs_crisp_$data.log &
    ./qpcs_crisp.out > ./.log/qpcs_crisp_$data.log &
    exit 0
elif [ $1 = "pcs_overlap" ]; then
    ./bpcs_overlap.out > ./.log/bpcs_overlap_$data.log &
    ./epcs_overlap.out > ./.log/epcs_overlap_$data.log &
    ./qpcs_overlap.out > ./.log/qpcs_overlap_$data.log &
    exit 0
else
    echo "Please specify the method type of program."
    exit 1
fi
