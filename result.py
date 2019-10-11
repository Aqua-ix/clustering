#! /usr/bin/env python

import pandas as pd

data_dir="data/result_data/"
dataname = 'artificiality'
clusters = '5'
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
ems = ['1.100000',
       '1.300000',
       '1.500000',
       '1.700000',
       '1.900000',
       '2.100000',
       '2.300000',
       '2.500000',
       '2.700000',
       '2.900000']
lms = ['2.000000',
       '4.000000',
       '8.000000',
       '16.000000',
       '32.000000',
       '64.000000',
       '128.000000',
       '256.000000',
       '512.000000',
       '1024.000000']
method1 = ['B', 'E', 'Q']
method2 = ['FCS', 'PCS']
saved_mae = [1000]*13
saved_auc = [0]*13
saved_mae_em = [0]*13
saved_mae_lm = [0]*13
saved_auc_em = [0]*13
saved_auc_lm = [0]*13

for m1 in method1:
    for m2 in method2:
        m_dir =  m1 + m2 + 'OVERLAP_' + dataname
        for c in clulsters:
            c_dir = 'clusters_number' + c
            for ot in ots:
                ot_dir = 'overlap_threshold' + ot
                for em in ems:
                    for lm in lms:
                        if m1 == 'B':
                            param_dir = 'params_' + em
                            lms.clear()
                        elif m1 == 'E':
                            param_dir = 'params_' + lm
                            ems.clear()
                        elif m1 == 'Q':
                            param_dir = 'params_' + em + '_' + lm
                        mp_dir = 'missing_pattern' + mp
                        mae_dn = m1 + m2 + '_OVERLAP_' + averageMAE + '.txt'
                        auc_dn = m1 + m2 + '_OVERLAP_' + averageAUC + '.txt'
                        mae = m_dir + '/' + c_dir + '/' + ot_dir + '/' + param_dir + '/' + mae_dn
                        auc = m_dir + '/' + c_dir + '/' + ot_dir + '/' + param_dir + '/' + auc_dn
                        result_mae = pd.read_table(mae, header=None, usecols=[2])
                        leng = len(result_mae)
                        for n in range(leng):
                            if result_mae[n] < saved_mae[n]:
                                saved_mae[n] = result_mae[n]
                                if m1 == 'B':
                                    saved_mae_em[n] = em
                                elif m1 == 'E':
                                    saved_mae_lm[n] = lm
                                elif m1 == 'Q':
                                    saved_mae_em[n] = em
                                    saved_mae_lm[n] = lm
                        result_auc = pd.read_table(auc, header=None, usecols=[2])
                        leng = len(result_mae)
                        for n in range(leng):
                            if result_auc[n] > saved_auc[n]:
                                saved_auc[n] = result_auc[n]
                                if m1 == 'B':
                                    saved_auc_em[n] = em
                                elif m1 == 'E':
                                    saved_auc_lm[n] = lm
                                elif m1 == 'Q':
                                    saved_auc_em[n] = em
                                    saved_auc_lm[n] = lm
