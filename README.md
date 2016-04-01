# PostLJMetBrownStep1 - TpTp Multilepton

Code (step1.cc/.h) to slim LJMet trees. Built on ROOT's MakeClass.
Download the CSC & ECAL bad event files from CMS TWiki!

Set up runCondorSlimmerJobs.py to run over LJMet files stored on Fermilab's EOS.
Run with submitSlimmerJobs.sh
Hadd output files with hadd.sh after setting up haddoutput.py

NOTE: setup is current for CMSSW_7_4_X LJMet and files, changes will come with
CMSSW_7_6_X LJMet.
