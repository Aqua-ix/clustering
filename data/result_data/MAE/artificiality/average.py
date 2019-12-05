#! /usr/bin/env python
import csv
import os
from decimal import *

dataname = 'artificiality'
mp = '19'
ots = ['0.000000',
       '0.100000',
       '0.200000',
       '0.300000',
       '0.400000',
       '0.500000',
       '0.600000',
       '0.700000',
       '0.800000',
       '0.900000',
       '1.000000']

methods = ['BFCS', 'EFCS', 'QFCS', 'BPCS', 'EPCS', 'QPCS']

minimal = 1.0
minimal_str = ''

for ot in ots:
    inputDir = dataname + '_MP' + mp + '_overlap_threshold' + ot + '/'
    outputDir = dataname + '_MP' + mp + '_average/'
    if not os.path.exists(outputDir):
        os.makedirs(outputDir)
    outputFileName = outputDir + ot + '.txt'
    outputFile = open(outputFileName, 'a')
    for method in methods:
        inputFileName = inputDir + method + '_OVERLAP_averageMAE.txt'
        inputFile = open(inputFileName, 'r')
        tsv = csv.reader(inputFile, delimiter = '\t')
        summation = 0
        
        for index,row in enumerate(tsv):
            missing = row[0]
            summation = summation + float(row[2])

        average = summation/(index+1)

        if average<=minimal:
            minimal = average
            minimal_str = 'min: ' + method + ', ' + str(ot) + ': ' + str(minimal)
		
        result = Decimal(str(average)).quantize(Decimal('0.000001'), rounding=ROUND_HALF_UP)
        outputFile.write(method + '\t' + str(result) + '\n')
    outputFile.close()
        
    inputFile.close()
print(minimal_str)
