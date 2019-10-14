#! /usr/bin/env python

import glob
import pathlib
import pandas as pd

data_dir="data/result_data/"
#beq = ['B', 'E', 'Q']
beq = ['B']
fp = ['FCS', 'PCS']
ma = ['MAE', 'AUC']
overlap = '_OVERLAP_'
data_name = 'artificiality'
mp = 19

for m1 in beq:
    for m2 in fp:
        method_name = m1 + m2 + overlap
        method_dir = data_dir + method_name + data_name
        for m3 in ma:
            input_name = method_dir + '/**/**/**/missing_pattern' + str(mp) + '/' + method_name + 'average'+ m3 +'.txt'
            print('========== ' + m3 + ' in ' + method_dir + ' ==========')
            files = sorted(glob.glob(input_name))
            out = []
            prev_tname = ''
            if 'result' in locals():
                del result
            
            for file in files:
                p_file = pathlib.Path(file)
                threshold = p_file.parents[2]
                param = p_file.parents[1]
            
                print(threshold.name + ', ' + param.name + ': ' + p_file.name)
            
                if threshold.name != prev_tname:
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
            for o in out:
                if(m3 == 'MAE'):
                    print(o.min(axis='columns'))
                else:
                    print(o.max(axis='columns'))
