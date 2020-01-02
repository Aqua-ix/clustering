#!/bin/bash/

cd output
rm -f unite_miss.pdf
pdfunite *.pdf unite_miss.pdf
cd ..
