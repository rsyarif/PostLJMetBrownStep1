#!/bin/bash

echo "HADDING NOMINAL"

python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds nominal

echo "HADDING JECUP"

python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds JEC_up

echo "HADDING JECDOWN"
python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds JEC_down

echo "HADDING JERUP"

python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds JER_up

echo "HADDING JERDOWN"

python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds JER_down

echo "HADDING BTAGUP"

python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds BTag_up

echo "HADDING BTAGDOWN"

python -u haddoutput.py LJMet_3lep_122115_step1 LJMet_3lep_122115_step1hadds BTag_down

echo "DONE"
