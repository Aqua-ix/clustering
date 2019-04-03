#!/usr/bin/bash
chmod 755 listofcontents.sh
platex thesis2018
platex thesis2018
platex thesis2018
sh ./listofcontents.sh thesis2018
dvipdfmx -f texfonts.map thesis2018
