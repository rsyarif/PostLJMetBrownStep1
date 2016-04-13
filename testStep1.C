#include "step1.cc"

void makeSingleStep1(){
  
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet_1lepTT_022916/nominal//TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns_1.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet_3lep_122115/nominal/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns_1.root";
  TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet_3lep_122115/nominal/DoubleMuon_PRD_25ns/DoubleMuon_PRD_25ns_2.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet_3lep_122115/nominal/TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8_25ns/TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8_25ns_1.root";
  
  TString outputFile="test.root";
  
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
}


