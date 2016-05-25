#!/bin/bash


#76x

echo "HADDING NOMINAL"

python -u haddoutput.py LJMet_3lepTT_051316_step1_preliminary LJMet_3lepTT_051316_step1_preliminary_hadds nominal

echo "HADDING JECUP"

python -u haddoutput.py LJMet_3lepTT_051316_step1_preliminary LJMet_3lepTT_051316_step1_preliminary_hadds JECup

echo "HADDING JECDOWN"
python -u haddoutput.py LJMet_3lepTT_051316_step1_preliminary LJMet_3lepTT_051316_step1_preliminary_hadds JECdown

echo "HADDING JERUP"

python -u haddoutput.py LJMet_3lepTT_051316_step1_preliminary LJMet_3lepTT_051316_step1_preliminary_hadds JERup

echo "HADDING JERDOWN"

python -u haddoutput.py LJMet_3lepTT_051316_step1_preliminary LJMet_3lepTT_051316_step1_preliminary_hadds JERdown

echo "DONE"
