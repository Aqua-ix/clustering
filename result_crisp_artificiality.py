#! /usr/bin/env python

import sys
import glob
import os
import re
import pathlib
import pandas as pd
import shutil

args = sys.argv

data_dir = 'data/result_data/'
b_e_q = ['B', 'E', 'Q']
f_p = ['FCS', 'PCS']
m_a = ['MAE', 'AUC']
overlap = '_CRISP_'
mp = 4
data_name = 'artificiality'

regex = re.compile('[0-9]+[._]?[0-9]*')

for m1_index, m1 in enumerate(b_e_q):
    for m2 in f_p:
        if m2 == 'PCS':
            cluster = 1
        else:
            cluster = 5

        cn = '/clusters_number' + str(cluster)
        
        method_name = m1 + m2 + overlap
        method_dir = data_dir + method_name + data_name
        
        for m3 in m_a:
            miss = '/**/missing_pattern' + str(mp)
            file_name = 'average'+ m3 +'.txt'
            input_name = method_dir + cn + miss  + '/' + method_name + file_name
            print('========== ' + m3 + ' in ' + method_dir + ' ==========')
            files = sorted(glob.glob(input_name))
            out = []
            if 'result' in locals():
                del result
            
            for file in files:
                p_file = pathlib.Path(file)
                param = "_".join(regex.findall(p_file.parents[1].name))
            
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
                out_dir = data_name + '_MP' + str(mp) + '_crisp'
                out_path = data_dir + m3 + '/'  + data_name + '/' + out_dir + '/'
                if not os.path.exists(out_path):
                    os.makedirs(out_path)
                #print(out_path)
                if(m3 == 'MAE'):
                    idx = o.idxmin(axis='columns')
                    res = o.min(axis='columns')
                    i_r = pd.concat([idx, res], axis = 'columns')
                    output = pd.concat([misses, i_r], axis = 'columns')
                    output.to_csv(out_path + method_name + file_name, sep = '\t', header=False, index = False)
                else:
                    idx = o.idxmax(axis='columns')
                    res = o.max(axis='columns')
                    i_r = pd.concat([idx, res], axis = 'columns')
                    output = pd.concat([misses, i_r], axis = 'columns')
                    output.to_csv(out_path + method_name + file_name, sep = '\t', header=False, index = False)
