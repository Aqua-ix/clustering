#!/usr/bin/bash
chmod 755 listofcontents.sh
platex thesis2018
platex thesis2018
platex thesis2018
sh ./listofcontents.sh
dvipdfmx thesis2018
