#!/bin/sh

D=$1
OT='0.2 0.4 0.6 0.8 1.0'
PAT='0 1 2 3 4'

for O in $OT; do
	for P in $PAT; do
	    DIR=${D}/${D}_overlap_threshold${O}00000/missing_pattern${P}/
        cp plot.plt $DIR
        cd ${DIR}
        mkdir -p ../../graph
		gnuplot -e "data='$D'; ot='$O'; pt='$P'" -persist plot.plt
        cd ../../..
	done
done
