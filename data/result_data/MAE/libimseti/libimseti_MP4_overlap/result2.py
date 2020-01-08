#! /usr/bin/env python
import csv
import os
from decimal import *
import numpy as np

mRange = range(300000,300001)
tRange = np.arange(0.2, 1.1, 0.2)

methods = ['BFCS', 'EFCS', 'QFCS', 'BPCS', 'EPCS', 'QPCS']

meSize = 0
for meIndex, method in enumerate(methods):
    meSize = meIndex
meSize += 1

mrSize = 0
for mrIndex, miss in enumerate(mRange):
    mrSize = mrIndex
mrSize += 1

otSize = 0
for otIndex, threshold in enumerate(tRange):
    otSize = otIndex
otSize += 1

otSum = [[0] * otSize for i in range(meSize)]

for miIndex, miss in enumerate(mRange):
    inputDir = str(miss) + '/'
    outputFileName = str(miss) + '_table.txt'
    outputFile = open(outputFileName, 'a')

    outputFile.write('\t')
    
    for threshold in tRange:
        ts = Decimal(threshold).quantize(Decimal('0.1'),
                                              rounding=ROUND_HALF_UP)
        outputFile.write(str(ts) + '\t')
        
    outputFile.write('\n')
    
    for meIndex, method in enumerate(methods):
        inputFileName = inputDir + method + '.txt'
        inputFile = open(inputFileName, 'r')
        outputFile.write(method + '\t')
        tsv = csv.reader(inputFile, delimiter = '\t')
        
        for otIndex, row in enumerate(tsv):
            otSum[meIndex][otIndex] += float(row[2])
            mae = Decimal(row[2]).quantize(Decimal('0.000001'),
                                              rounding=ROUND_HALF_UP)
            outputFile.write(str(mae) + '\t')

        outputFile.write('\n')
        inputFile.close()
        
    outputFile.close()


outputFileName = 'average_table.txt'
outputFile = open(outputFileName, 'a')

outputFile.write('\t')
for threshold in tRange:
    ts = Decimal(threshold).quantize(Decimal('0.1'),
                                              rounding=ROUND_HALF_UP)
    outputFile.write(str(ts) + '\t')
outputFile.write('\n')

for meIndex, method in enumerate(methods):
    outputFile.write(method + '\t')
    for otIndex, miss in enumerate(tRange):
        otAve = otSum[meIndex][otIndex]/mrSize
        ave = Decimal(otAve).quantize(Decimal('0.000001'),
                                      rounding=ROUND_HALF_UP)
        outputFile.write(str(ave) + '\t')
    outputFile.write('\n')
outputFile.close()
