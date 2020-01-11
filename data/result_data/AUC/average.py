#! /usr/bin/env python
import csv
import os
import numpy as np
from decimal import *
 
mp = '4'
ots = ['0.200000',
       '0.400000',
       '0.600000',
       '0.800000',
       '1.000000']

datasets = ['book', 'movie', 'libimseti', 'jester', 'epinions', 'sushi']
methods = ['BFCS', 'EFCS', 'QFCS', 'BPCS', 'EPCS', 'QPCS']

results = np.empty((len(datasets), len(methods), len(ots)))

for oi, ot in enumerate(ots):
    for di, data in enumerate(datasets):
        inputDir = data + '/' + data + '_MP' + mp + '_overlap/'
        inputFileName = inputDir + 'average_table.txt'
        inputFile = open(inputFileName, 'r')
        tsv = csv.reader(inputFile, delimiter = '\t')
        for ri, row in enumerate(tsv):
            if ri == 0:
                continue
            del row[0]
            row.remove('')
            results[di, ri-1] = row
                
        inputFile.close()
        
average = np.empty((len(methods), len(ots)))
summation = np.zeros((len(methods), len(ots)))
for oi, ot in enumerate(ots):
    for di, data in enumerate(datasets):
        for mi, method in enumerate(methods):
            summation[mi, oi] += results[di, mi, oi]

average = summation/len(datasets)

outputFileName = 'result_average.txt'    
outputFile = open(outputFileName, 'w')

for mi, method in enumerate(methods):
    outputFile.write(methods[mi])
    for oi, ot in enumerate(ots):
        a = Decimal(float(average[mi, oi])).quantize(Decimal("0.000001"), rounding=ROUND_HALF_UP)
        outputFile.write('\t' + str(a))
    outputFile.write('\n')
outputFile.close()
