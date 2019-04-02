#!/bin/sh
file=`date|sed 's/[\ :]/_/g'`
sed 's/\(\\contentsline\ {section}{\\numberline\ {\)\([0-9]\)}/\1第\2節}　/' ${1}.toc > $file
sed 's/\(\\contentsline\ {subsection}{\\numberline\ {\)\([0-9]\)}/\1第\2小節}　/' $file > ${1}.toc
rm $file
