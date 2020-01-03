#! /usr/bin/env python

import sys
import glob
import os
import re
import pathlib
import pandas as pd
import shutil

args = sys.argv

data_dir="data/result_data/"
b_e_q = ['B', 'E', 'Q']
f_p = ['FCS', 'PCS']
m_a = ['MAE', 'AUC']
overlap = '_OVERLAP_'
mp = 4
data_name = args[1]
clusters = [args[2], args[3], args[4]]

regex = re.compile('[0-9]+[._]?[0-9]*')

for m1_index, m1 in enumerate(b_e_q):
    for m2 in f_p:
        if m2 == 'PCS':
            cluster = 1
        else:
            cluster = clusters[m1_index]

        cn = '/clusters_number' + str(cluster)
        
        method_name = m1 + m2 + overlap
        method_dir = data_dir + method_name + data_name
        
        for m3 in m_a:
            miss = '/**/**/missing_pattern' + str(mp)
            file_name = 'average'+ m3 +'.txt'
            input_name = method_dir + cn + miss  + '/' + method_name + file_name
            print('========== ' + m3 + ' in ' + method_dir + ' ==========')
            files = sorted(glob.glob(input_name))
            out = []
            prev_tname = ''
            tname_array = []
            if 'result' in locals():
                del result
            
            for file in files:
                p_file = pathlib.Path(file)
                threshold = p_file.parents[2]
                param = "_".join(regex.findall(p_file.parents[1].name))
            
                #print(threshold.name + ', ' + param + ': ' + str(p_file))
            
                if threshold.name != prev_tname:
                    tname_array.append(threshold.name)
                    if 'result' in locals():
                        out.append(result)
                        del result
                prev_tname = threshold.name
            
                table = (pd.read_table(str(p_file), names=('miss', param)))
                if 'result' not in locals():
                    result = table
                else:
                    result = pd.merge(result, table)
            if not result.equals(table):
                out.append(result)
                
            for index, o in enumerate(out):
                misses = o['miss']
                del o['miss']
                print(tname_array[index])
                out_dir = data_name + '_MP' + str(mp) + '_' + str(tname_array[index])
                out_path = data_dir + m3 + '/'  + data_name + '/' + out_dir + '/'
                if not os.path.exists(out_path):
                    os.makedirs(out_path)
                #print(out_path)
                if(m3 == 'MAE'):
                    idx = o.idxmin(axis='columns')
                    res = o.min(axis='columns')
                    i_r = pd.concat([idx, res], axis = 'columns')
                    output = pd.concat([misses, i_r], axis = 'columns')
                    output.to_csv(out_path + method_name + file_name, sep = '\t', mode='a', header=False, index = False)
                else:
                    idx = o.idxmax(axis='columns')
                    res = o.max(axis='columns')
                    i_r = pd.concat([idx, res], axis = 'columns')
                    output = pd.concat([misses, i_r], axis = 'columns')
                    output.to_csv(out_path + method_name + file_name, sep = '\t', mode='a', header=False, index = False)

                    parr = regex.findall(str(idx))
                    parr.remove('0')
                    params = "_".join(parr)
                    root_dir = method_dir + cn + '/' + tname_array[index]
                    for mp_i in range(mp+1):
                        roc_dir =  root_dir + '/' + 'params_' + str(params) + '/missing_pattern' + str(mp_i) + '/ROC/choice/'
                        roc_file = roc_dir + method_name + 'ROC_' + str(misses[0]) + '_sort.txt'
                        roc_out_dir = data_dir + 'ROC/' + data_name + '/' + data_name + '_' + str(tname_array[index]) + '/missing_pattern' + str(mp_i) + '/'
                        roc_out_file = roc_out_dir + method_name + 'ROC_' + str(mp_i) + '.txt'
                        if not os.path.exists(roc_out_dir):
                            os.makedirs(roc_out_dir)
                        shutil.copy(roc_file, roc_out_file)
                    
