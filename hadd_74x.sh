#!/bin/bash


#76x

echo "HADDING NOMINAL"

python -u haddoutput.py LJMet76In74_3lepTT_052716_step1_DEBUG_fixLooseEl LJMet76In74_3lepTT_052716_step1_DEBUG_fixLooseEl_hadds nominal

# echo "HADDING JECUP"
# 
# python -u haddoutput.py LJMet76In74_3lepTT_052716_step1 LJMet76In74_3lepTT_052716_step1_hadds JECup
# 
# echo "HADDING JECDOWN"
# python -u haddoutput.py LJMet76In74_3lepTT_052716_step1 LJMet76In74_3lepTT_052716_step1_hadds JECdown
# 
# echo "HADDING JERUP"
# 
# python -u haddoutput.py LJMet76In74_3lepTT_052716_step1 LJMet76In74_3lepTT_052716_step1_hadds JERup
# 
# echo "HADDING JERDOWN"
# 
# python -u haddoutput.py LJMet76In74_3lepTT_052716_step1 LJMet76In74_3lepTT_052716_step1_hadds JERdown

echo "DONE"
