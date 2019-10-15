#! /usr/bin/env python

import glob
import os
import pathlib
import pandas as pd

data_dir="data/result_data/"
b_e_q = ['B', 'E', 'Q']
f_p = ['FCS', 'PCS']
m_a = ['MAE', 'AUC']
overlap = '_OVERLAP_'
data_name = 'artificiality'
mp = 19

for m1 in b_e_q:
    for m2 in f_p:
        method_name = m1 + m2 + overlap
        method_dir = data_dir + method_name + data_name
        for m3 in m_a:
            miss = '/**/**/**/missing_pattern' + str(mp)
            file_name = 'average'+ m3 +'.txt'
            input_name = method_dir + miss  + '/' + method_name + file_name
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
                param = p_file.parents[1]
            
                #print(threshold.name + ', ' + param.name + ': ' + p_file.name)
            
                if threshold.name != prev_tname:
                    tname_array.append(threshold.name)
                    if 'result' in locals():
                        out.append(result)
                        del result
                prev_tname = threshold.name
            
                table = (pd.read_table(str(p_file), names=('miss', param.name)))
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
                    index = o.idxmin(axis='columns')
                    res = o.min(axis='columns')
                    i_r = pd.concat([index, res], axis = 'columns')
                    output = pd.concat([misses, i_r], axis = 'columns')
                    output.to_csv(out_path + method_name + file_name, sep = '\t', index = False)
                    #print(output)
                else:
                    res = o.max(axis='columns')
                    index = o.idxmax(axis='columns')
                    i_r = pd.concat([index, res], axis = 'columns')
                    output = pd.concat([misses, i_r], axis = 'columns')
                    output.to_csv(out_path + method_name + file_name, sep = '\t', index = False)
                    #print(output)
