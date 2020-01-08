#! /usr/bin/env python
import csv
import os

mp = '4'
ots = ['0.200000',
       '0.400000',
       '0.600000',
       '0.800000',
       '1.000000',]

datasets = ['book', 'movie', 'libimseti', 'jester', 'epinions', 'sushi']
methods = ['BFCS', 'EFCS', 'QFCS', 'BPCS', 'EPCS', 'QPCS']
results = [0] * len(methods)

for ot in ots:
    for data in datasets:
        inputDir = data + '/' + data + '_MP' + mp + '_overlap_threshold' + ot + '/'
        outputDir = data + '_MP' + mp + '_overlap/'
        for index, method in enumerate(methods):
            inputFileName = inputDir + method + '_OVERLAP_averageMAE.txt'
            inputFile = open(inputFileName, 'r')
            tsv = csv.reader(inputFile, delimiter = '\t')
            for row in tsv:
                missing = row[0]
                param = row[1]
                
                
            inputFile.close()

        outputPath = outputDir + str(missing) + '/'
        if not os.path.exists(outputPath):
            os.makedirs(outputPath)
        outputFileName = outputPath + method + '.txt'
        outputFile = open(outputFileName, 'a')
        outputFile.write(ot + '\t' + row[1] + '\t' + row[2] + '\n')
        outputFile.close()
