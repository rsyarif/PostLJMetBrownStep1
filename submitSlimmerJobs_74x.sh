#!/bin/bash

date

echo "SUBMITTING nominal"

python -u runCondorSlimmerJobs.py nominal

sleep 5

echo "SUBMITTING JEC_up"

python -u runCondorSlimmerJobs.py JEC_up

sleep 5

echo "SUBMITTING JEC_down"

python -u runCondorSlimmerJobs.py JEC_down

sleep 5

echo "SUBMITTING JER_up"

python -u runCondorSlimmerJobs.py JER_up

sleep 5

echo "SUBMITTING JER_down"

python -u runCondorSlimmerJobs.py JER_down

sleep 5

echo "SUBMITTING BTag_up"

python -u runCondorSlimmerJobs.py BTag_up

sleep 5

echo "SUBMITTING BTag_down"

python -u runCondorSlimmerJobs.py BTag_down

sleep 5

echo "DONE"

date

