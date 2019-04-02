#!/usr/bin/bash
chmod 755 listofcontents.sh
platex thesisAbst2018
platex thesisAbst2018
platex thesisAbst2018
sh ./listofcontents.sh
dvipdfmx -f texfonts.map thesisAbst2018.dvi
