#!/usr/bin/bash
platex thesisAbst2018
platex thesisAbst2018
dvipdfmx -f texfonts.map thesisAbst2018.dvi
