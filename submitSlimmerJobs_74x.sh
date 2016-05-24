#!/bin/bash

date

echo "SUBMITTING nominal"

python -u runCondorSlimmerJobs.py nominal

sleep 5

echo "SUBMITTING JEC_up"

python -u runCondorSlimmerJobs.py JECup

sleep 5

echo "SUBMITTING JEC_down"

python -u runCondorSlimmerJobs.py JECdown

sleep 5

echo "SUBMITTING JER_up"

python -u runCondorSlimmerJobs.py JERup

sleep 5

echo "SUBMITTING JER_down"

python -u runCondorSlimmerJobs.py JERdown

sleep 5

echo "SUBMITTING BTag_up"

python -u runCondorSlimmerJobs.py BTagup

sleep 5

echo "SUBMITTING BTag_down"

python -u runCondorSlimmerJobs.py BTagdown

sleep 5

echo "DONE"

date

