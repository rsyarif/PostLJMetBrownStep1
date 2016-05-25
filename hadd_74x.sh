#!/bin/bash


#74x

echo "HADDING NOMINAL"

python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds nominal

echo "HADDING JECUP"

python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds JEC_up

echo "HADDING JECDOWN"
python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds JEC_down

echo "HADDING JERUP"

python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds JER_up

echo "HADDING JERDOWN"

python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds JER_down

echo "HADDING BTAGUP"

python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds BTag_up

echo "HADDING BTAGDOWN"

python -u haddoutput.py LJMet_3lep_122115_step1_v2 LJMet_3lep_122115_step1_v2hadds BTag_down

echo "DONE"
