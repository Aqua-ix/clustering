#! /usr/bin/env python
import csv
import os

dataname = 'epinions'
mp = '4'
ots = ['0.200000',
       '0.400000',
       '0.600000',
       '0.800000',
       '1.000000',]

methods = ['BFCS', 'EFCS', 'QFCS', 'BPCS', 'EPCS', 'QPCS']

for ot in ots:
    inputDir = dataname + '_MP' + mp + '_overlap_threshold' + ot + '/'
    outputDir = dataname + '_MP' + mp + '_overlap/'
    for method in methods:
        inputFileName = inputDir + method + '_OVERLAP_averageAUC.txt'
        inputFile = open(inputFileName, 'r')
        tsv = csv.reader(inputFile, delimiter = '\t')
        for row in tsv:
            missing = row[0]
            outputPath = outputDir + str(missing) + '/'
            if not os.path.exists(outputPath):
                os.makedirs(outputPath)
            outputFileName = outputPath + method + '.txt'
            outputFile = open(outputFileName, 'a')
            outputFile.write(ot + '\t' + row[1] + '\t' + row[2] + '\n')
        outputFile.close()
    inputFile.close()
