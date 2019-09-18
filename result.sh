#!/bin/bash

DN=$1
MP=$3
echo "clusters number>"
read CN_VAL

METHOD_NAME="B E Q"
FCS_PCS="FCS PCS"
ROOT="data/result_data"

if [ $2 = "clisp" ]; then
     for MN in $METHOD_NAME ; do
        for FP in $FCS_PCS ; do
            METHOD="${MN}${FP}_CLISP"
            for CN in $CN_VAL ; do
                if [ $FP = "PCS" ]; then
                    CN="1"
                fi
                CLUSTERS="clusters_number${CN}"
                MISSING="missing_pattern${MP}"
                MAE="averageMAE.txt"
                FROM="${ROOT}/${METHOD}_${DN}/${CLUSTERS}/${MISSING}/${METHOD}_${MAE}"
                echo "FROM: ${FROM}"
                TO="${ROOT}/MAE/${DN}_MP${MP}/"
                echo "TO: ${TO}"
                mkdir -p ${TO}
                cp ${FROM} ${TO}
                echo ""
            done
        done
     done                
    exit 0
elif [ $2 = "overlap" ]; then
    ## echo "overlap threshold>"
    ## read OT_VAL
    OT_VAL="0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7"
    for MN in $METHOD_NAME ; do
        for FP in $FCS_PCS ; do
            METHOD="${MN}${FP}_OVERLAP"
            for CN in $CN_VAL ; do
                if [ $FP = "PCS" ]; then
                    CN="1"
                fi
                CLUSTERS="clusters_number${CN}"
                for OT in $OT_VAL ; do
                    OVERLAP="overlap_threshold${OT}00000"
                    MISSING="missing_pattern${MP}"
                    MAE="averageMAE.txt"
                    FROM="${ROOT}/${METHOD}_${DN}/${CLUSTERS}/${OVERLAP}/${MISSING}/${METHOD}_${MAE}"
                    echo "FROM: ${FROM}"
                    TO="${ROOT}/MAE/${DN}_MP${MP}_${OVERLAP}/"
                    echo "TO: ${TO}"
                    mkdir -p ${TO}
                    cp ${FROM} ${TO}
                    echo ""
                done
            done
        done
    done                
    exit 0
else
    echo "Please specify the method type."
    exit 1
fi
