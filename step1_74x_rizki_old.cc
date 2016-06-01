#define step1_cxx
#include "step1.h"
#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>
// #include "fakerate_3lep_rizki.h" //added by rizki
#include "fakerate_3lep_ptEta_rizki.h" //added by rizki


using namespace std;

bool comparepair( const std::pair<double,int> a, const std::pair<double,int> b) { return a.first > b.first; }

TRandom * gRandom = new TRandom3();

void step1::Loop() 
{
//   In a ROOT session, you can do:
//      root> .L step1.C
//      root> step1 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (inputTree == 0) return;
   
   inputTree->SetBranchStatus("*",0);

   //Specify branches to keep
   
   //Event info
   inputTree->SetBranchStatus("event_CommonCalc",1);
   inputTree->SetBranchStatus("run_CommonCalc",1);
   inputTree->SetBranchStatus("lumi_CommonCalc",1);
   inputTree->SetBranchStatus("nPV_singleLepCalc",1);
   inputTree->SetBranchStatus("nTrueInteractions_singleLepCalc",1);
   inputTree->SetBranchStatus("MCWeight_singleLepCalc",1);

   inputTree->SetBranchStatus("isTHBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTHTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBWBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTZ_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTWTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBZ_TpTpCalc",1);
   inputTree->SetBranchStatus("NLeptonDecays_TpTpCalc",1);
   
   //triggers
   inputTree->SetBranchStatus("vsSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersMu_singleLepCalc",1);
   
   //electrons
   inputTree->SetBranchStatus("elPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elEta_singleLepCalc",1);
   inputTree->SetBranchStatus("elPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("elEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("elMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elRelIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elMVAValue_singleLepCalc",1);
   inputTree->SetBranchStatus("elDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("elDZ_singleLepCalc",1);
   inputTree->SetBranchStatus("elCharge_singleLepCalc",1);
   
   //muons
   inputTree->SetBranchStatus("muPt_singleLepCalc",1);
   inputTree->SetBranchStatus("muEta_singleLepCalc",1);
   inputTree->SetBranchStatus("muPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("muEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("muMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muRelIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsTight_singleLepCalc",1);
   inputTree->SetBranchStatus("muDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("muDz_singleLepCalc",1);
   inputTree->SetBranchStatus("muCharge_singleLepCalc",1);
   
   //missing et
   inputTree->SetBranchStatus("corr_met_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_met_phi_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_metnohf_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_metnohf_phi_singleLepCalc",1);

   // genParticles
   inputTree->SetBranchStatus("genPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("genStatus_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEnergy_singleLepCalc",1);
   
   //jets
   inputTree->SetBranchStatus("AK4JetFlav_singleLepCalc",1);
   inputTree->SetBranchStatus("theJetPt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetEta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetCSV_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_JetSubCalc",1);
// new format
//    inputTree->SetBranchStatus("theJetBTag_bSFup_JetSubCalc",1);
//    inputTree->SetBranchStatus("theJetBTag_bSFdn_JetSubCalc",1);
//    inputTree->SetBranchStatus("theJetBTag_lSFup_JetSubCalc",1);
//    inputTree->SetBranchStatus("theJetBTag_lSFdn_JetSubCalc",1);

   inputTree->SetBranchStatus("theJetAK8Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Mass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Energy_JetSubCalc",1);
//    inputTree->SetBranchStatus("WPt_JetSubCalc",1);
//    inputTree->SetBranchStatus("WEta_JetSubCalc",1);
//    inputTree->SetBranchStatus("WPhi_JetSubCalc",1);
//    inputTree->SetBranchStatus("WEnergy_JetSubCalc",1);
//    inputTree->SetBranchStatus("WdecayDR_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau1_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau2_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau3_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDropMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedTau21Tag_JetSubCalc",1);
//    inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVMSF_JetSubCalc",1); //UNCOMMENT LATER!
   inputTree->SetBranchStatus("theJetAK8SDSubjetPt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetEta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetCSV_JetSubCalc",1);
//    inputTree->SetBranchStatus("theJetAK8SDSubjetBTag_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetIndex_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetSize_JetSubCalc",1);
   
   //top
   inputTree->SetBranchStatus("ttbarMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEnergy_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEta_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPhi_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topID_TTbarMassCalc",1);
   
   //LHE weights
   inputTree->SetBranchStatus("LHEWeightids_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEWeights_singleLepCalc",1);
   
   // OUTPUT FILE
   outputFile->cd();
   TTree *outputTree = new TTree("ljmet","ljmet");

   int NJetsWtagged_0p6;
   bool isPassTrilepton;    	    
   int isEEE;
   int isEEM;
   int isEMM;
   int isMMM;
   float leadWJetPtak8;
   float topPtWeightPast400;
   float topPtWeightHighPt;
   float minDR_leadAK8otherAK8;
   std::vector<float> deltaR_lep1Jets;
   std::vector<float> deltaR_lep2Jets;
   std::vector<float> deltaR_lep3Jets;
   std::vector<float> deltaR_lepClosestJet;
   std::vector<float> PtRelLepClosestJet;
   
   float Mll_sameFlavorOS; //inv mass of opposite sign same flavor leps
   std::vector<float> Mll_allComb; // all permutation between 3 trileps

   float JetSF_pTNbwflat;
   float JetSFup_pTNbwflat;
   float JetSFdn_pTNbwflat;
   float JetSFupwide_pTNbwflat;
   float JetSFdnwide_pTNbwflat;
   std::vector<float> leadWJetPtak8_shifts;
   std::vector<float> pdfWeights;
   std::vector<float> theJetAK8SoftDropMass_JetSubCalc_PtOrdered;
   std::vector<float> theJetAK8NjettinessTau3_JetSubCalc_PtOrdered;
   std::vector<float> theJetAK8MaxSubCSV_JetSubCalc_PtOrdered;
   std::vector<float> AllLeptonPt_PtOrdered;
   std::vector<float> AllLeptonEta_PtOrdered;
   std::vector<float> AllLeptonPhi_PtOrdered;
   std::vector<float> AllLeptonEnergy_PtOrdered;
   std::vector<float> AllLeptonMiniIso_PtOrdered;
   std::vector<int> AllLeptonFlavor_PtOrdered;
   std::vector<int> AllLeptonIsTight_PtOrdered;
   std::vector<int> AllLeptonCharge_PtOrdered;
   std::vector<int> AllLeptonIdx_PtOrdered;

   std::vector<float> TightLeptonPt_PtOrdered;
   std::vector<float> TightLeptonEta_PtOrdered;
   std::vector<float> TightLeptonPhi_PtOrdered;
   std::vector<float> TightLeptonEnergy_PtOrdered;
   std::vector<float> TightLeptonMiniIso_PtOrdered;
   std::vector<int> TightLeptonFlavor_PtOrdered;
   std::vector<int> TightLeptonCharge_PtOrdered;
   std::vector<int> TightLeptonIdx_PtOrdered;
   
   std::vector<int> theJetBTagBuggy_JetSubCalc_PtOrdered;
   std::vector<int> theJetAK8Wmatch_JetSubCalc_PtOrdered;
   std::vector<int> NJetsWtagged_0p6_shifts;
   std::vector<float> ddBkgWeights;
   
   int MCPastTrigger_trilep;
   int DataPastTrigger_trilep;
   int MCPastTrigger_dilep;
   int DataPastTrigger_dilep;
   int MCPastTrigger_dilepHT;
   int DataPastTrigger_dilepHT;

   outputTree->Branch("event_CommonCalc",&event_CommonCalc,"event_CommonCalc/I");
   outputTree->Branch("run_CommonCalc",&run_CommonCalc,"run_CommonCalc/I");
   outputTree->Branch("lumi_CommonCalc",&lumi_CommonCalc,"lumi_CommonCalc/I");
   outputTree->Branch("isTHBW_TpTpCalc",&isTHBW_TpTpCalc,"isTHBW_TpTpCalc/O");
   outputTree->Branch("isTHTH_TpTpCalc",&isTHTH_TpTpCalc,"isTHTH_TpTpCalc/O");
   outputTree->Branch("isBWBW_TpTpCalc",&isBWBW_TpTpCalc,"isBWBW_TpTpCalc/O");
   outputTree->Branch("isTZBW_TpTpCalc",&isTZBW_TpTpCalc,"isTZBW_TpTpCalc/O");
   outputTree->Branch("isTZTH_TpTpCalc",&isTZTH_TpTpCalc,"isTZTH_TpTpCalc/O");
   outputTree->Branch("isTZTZ_TpTpCalc",&isTZTZ_TpTpCalc,"isTZTZ_TpTpCalc/O");
   outputTree->Branch("isBHTW_TpTpCalc",&isBHTW_TpTpCalc,"isBHTW_TpTpCalc/O");
   outputTree->Branch("isBHBH_TpTpCalc",&isBHBH_TpTpCalc,"isBHBH_TpTpCalc/O");
   outputTree->Branch("isTWTW_TpTpCalc",&isTWTW_TpTpCalc,"isTWTW_TpTpCalc/O");
   outputTree->Branch("isBZTW_TpTpCalc",&isBZTW_TpTpCalc,"isBZTW_TpTpCalc/O");
   outputTree->Branch("isBZBH_TpTpCalc",&isBZBH_TpTpCalc,"isBZBH_TpTpCalc/O");
   outputTree->Branch("isBZBZ_TpTpCalc",&isBZBZ_TpTpCalc,"isBZBZ_TpTpCalc/O");
   outputTree->Branch("ttbarMass_TTbarMassCalc",&ttbarMass_TTbarMassCalc,"ttbarMass_TTbarMassCalc/D");

   outputTree->Branch("nPV_singleLepCalc",&nPV_singleLepCalc,"nPV_singleLepCalc/I");
   outputTree->Branch("nTrueInteractions_singleLepCalc",&nTrueInteractions_singleLepCalc,"nTrueInteractions_singleLepCalc/I");
   outputTree->Branch("MCWeight_singleLepCalc",&MCWeight_singleLepCalc,"MCWeight_singleLepCalc/D");
   outputTree->Branch("NLeptonDecays_TpTpCalc",&NLeptonDecays_TpTpCalc,"NLeptonDecays_TpTpCalc/I");
   outputTree->Branch("isPassTrilepton",&isPassTrilepton,"isPassTrilepton/O");
   outputTree->Branch("isEEE",&isEEE,"isEEE/I");
   outputTree->Branch("isEEM",&isEEM,"isEEM/I");
   outputTree->Branch("isEMM",&isEMM,"isEMM/I");
   outputTree->Branch("isMMM",&isMMM,"isMMM/I");
   
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("MCPastTriggerAlt",&MCPastTriggerAlt,"MCPastTriggerAlt/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");
   outputTree->Branch("DataPastTriggerAlt",&DataPastTriggerAlt,"DataPastTriggerAlt/I");

   outputTree->Branch("MCPastTrigger_dilep",&MCPastTrigger_dilep,"MCPastTrigger_dilep/I");
   outputTree->Branch("DataPastTrigger_dilep",&DataPastTrigger_dilep,"DataPastTrigger_dilep/I");

   outputTree->Branch("MCPastTrigger_dilepHT",&MCPastTrigger_dilepHT,"MCPastTrigger_dilepHT/I");
   outputTree->Branch("DataPastTrigger_dilepHT",&DataPastTrigger_dilepHT,"DataPastTrigger_dilepHT/I");

   outputTree->Branch("MCPastTrigger_trilep",&MCPastTrigger_trilep,"MCPastTrigger_trilep/I");
   outputTree->Branch("DataPastTrigger_trilep",&DataPastTrigger_trilep,"DataPastTrigger_trilep/I");

   outputTree->Branch("corr_met_singleLepCalc",&corr_met_singleLepCalc,"corr_met_singleLepCalc/D");
   outputTree->Branch("corr_met_phi_singleLepCalc",&corr_met_phi_singleLepCalc,"corr_met_phi_singleLepCalc/D");

   outputTree->Branch("AllLeptonPt_PtOrdered",&AllLeptonPt_PtOrdered);
   outputTree->Branch("AllLeptonEta_PtOrdered",&AllLeptonEta_PtOrdered);
   outputTree->Branch("AllLeptonPhi_PtOrdered",&AllLeptonPhi_PtOrdered);
   outputTree->Branch("AllLeptonEnergy_PtOrdered",&AllLeptonEnergy_PtOrdered);
   outputTree->Branch("AllLeptonMiniIso_PtOrdered",&AllLeptonMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonFlavor_PtOrdered",&AllLeptonFlavor_PtOrdered);
   outputTree->Branch("AllLeptonIsTight_PtOrdered",&AllLeptonIsTight_PtOrdered);
   outputTree->Branch("AllLeptonCharge_PtOrdered",&AllLeptonCharge_PtOrdered);

   outputTree->Branch("TightLeptonPt_PtOrdered",&TightLeptonPt_PtOrdered);
   outputTree->Branch("TightLeptonEta_PtOrdered",&TightLeptonEta_PtOrdered);
   outputTree->Branch("TightLeptonPhi_PtOrdered",&TightLeptonPhi_PtOrdered);
   outputTree->Branch("TightLeptonEnergy_PtOrdered",&TightLeptonEnergy_PtOrdered);
   outputTree->Branch("TightLeptonMiniIso_PtOrdered",&TightLeptonMiniIso_PtOrdered);
   outputTree->Branch("TightLeptonFlavor_PtOrdered",&TightLeptonFlavor_PtOrdered);
   outputTree->Branch("TightLeptonCharge_PtOrdered",&TightLeptonCharge_PtOrdered);

   outputTree->Branch("theJetPt_JetSubCalc_PtOrdered",&theJetPt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetEta_JetSubCalc_PtOrdered",&theJetEta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetPhi_JetSubCalc_PtOrdered",&theJetPhi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetEnergy_JetSubCalc_PtOrdered",&theJetEnergy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_JetSubCalc_PtOrdered",&theJetBTag_JetSubCalc_PtOrdered);
//new format
//    outputTree->Branch("theJetBTag_bSFup_JetSubCalc_PtOrdered",&theJetBTag_bSFup_JetSubCalc_PtOrdered);
//    outputTree->Branch("theJetBTag_bSFdn_JetSubCalc_PtOrdered",&theJetBTag_bSFdn_JetSubCalc_PtOrdered);
//    outputTree->Branch("theJetBTag_lSFup_JetSubCalc_PtOrdered",&theJetBTag_lSFup_JetSubCalc_PtOrdered);
//    outputTree->Branch("theJetBTag_lSFdn_JetSubCalc_PtOrdered",&theJetBTag_lSFdn_JetSubCalc_PtOrdered);
   
   outputTree->Branch("theJetBTagBuggy_JetSubCalc_PtOrdered",&theJetBTagBuggy_JetSubCalc_PtOrdered);
   outputTree->Branch("BJetLeadPtWithSF_JetSubCalc",&BJetLeadPtWithSF_JetSubCalc,"BJetLeadPtWithSF_JetSubCalc/F");
   outputTree->Branch("AK4HTpMETpLepPt",&AK4HTpMETpLepPt,"AK4HTpMETpLepPt/F");
   outputTree->Branch("AK4HT",&AK4HT,"AK4HT/F");

//    outputTree->Branch("WPt_JetSubCalc",&WPt_JetSubCalc);
//    outputTree->Branch("WEta_JetSubCalc",&WEta_JetSubCalc);
//    outputTree->Branch("WPhi_JetSubCalc",&WPhi_JetSubCalc);
//    outputTree->Branch("WEnergy_JetSubCalc",&WEnergy_JetSubCalc);
//    outputTree->Branch("WdecayDR_JetSubCalc",&WdecayDR_JetSubCalc);

   outputTree->Branch("theJetAK8Pt_JetSubCalc_PtOrdered",&theJetAK8Pt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Eta_JetSubCalc_PtOrdered",&theJetAK8Eta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Phi_JetSubCalc_PtOrdered",&theJetAK8Phi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Energy_JetSubCalc_PtOrdered",&theJetAK8Energy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8PrunedMass_JetSubCalc_PtOrdered",&theJetAK8PrunedMass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDropMass_JetSubCalc_PtOrdered",&theJetAK8SoftDropMass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8MaxSubCSV_JetSubCalc_PtOrdered",&theJetAK8MaxSubCSV_JetSubCalc_PtOrdered);

   outputTree->Branch("theJetAK8NjettinessTau1_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau1_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau2_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau2_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau3_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau3_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8PrunedMassJMRSmeared_JetSubCalc",&theJetAK8PrunedMassJMRSmeared_JetSubCalc);
   outputTree->Branch("theJetAK8PrunedMassJMRSmearedUp_JetSubCalc",&theJetAK8PrunedMassJMRSmearedUp_JetSubCalc);
   outputTree->Branch("theJetAK8PrunedMassJMRSmearedDn_JetSubCalc",&theJetAK8PrunedMassJMRSmearedDn_JetSubCalc);
   outputTree->Branch("theJetAK8Wmatch_JetSubCalc_PtOrdered",&theJetAK8Wmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("WJetLeadPt",&leadWJetPtak8,"WJetLeadPt/F");
   outputTree->Branch("WJetLeadPt_shifts",&leadWJetPtak8_shifts);
   outputTree->Branch("minDR_leadAK8otherAK8",&minDR_leadAK8otherAK8,"minDR_leadAK8otherAK8/F");

   outputTree->Branch("pileupWeight",&pileupWeight,"pileupWeight/F");
   outputTree->Branch("pileupWeight72ub",&pileupWeight72ub,"pileupWeight72ub/F");
   outputTree->Branch("pileupWeightUp",&pileupWeightUp,"pileupWeightUp/F");
   outputTree->Branch("pileupWeightDown",&pileupWeightDown,"pileupWeightDown/F");
   outputTree->Branch("TrigEffWeight",&TrigEffWeight,"TrigEffWeight/F");
   outputTree->Branch("isoSF",&isoSF,"isoSF/F");
   outputTree->Branch("lepIdSF",&lepIdSF,"lepIdSF/F");
   outputTree->Branch("JetSF_pTNbwflat",&JetSF_pTNbwflat,"JetSF_pTNbwflat/F");
   outputTree->Branch("JetSFup_pTNbwflat",&JetSFup_pTNbwflat,"JetSFup_pTNbwflat/F");
   outputTree->Branch("JetSFdn_pTNbwflat",&JetSFdn_pTNbwflat,"JetSFdn_pTNbwflat/F");
   outputTree->Branch("JetSFupwide_pTNbwflat",&JetSFupwide_pTNbwflat,"JetSFupwide_pTNbwflat/F");
   outputTree->Branch("JetSFdnwide_pTNbwflat",&JetSFdnwide_pTNbwflat,"JetSFdnwide_pTNbwflat/F");
   outputTree->Branch("renormWeights",&renormWeights);
   outputTree->Branch("pdfWeights",&pdfWeights);
   outputTree->Branch("ddBkgWeights",&ddBkgWeights);

   outputTree->Branch("NJets_JetSubCalc",&NJets_JetSubCalc,"NJets_JetSubCalc/I");
   outputTree->Branch("NJetsAK8_JetSubCalc",&NJetsAK8_JetSubCalc,"NJetsAK8_JetSubCalc/I");
   outputTree->Branch("NJetsCSV_JetSubCalc",&NJetsCSV_JetSubCalc,"NJetsCSV_JetSubCalc/I");
   outputTree->Branch("NJetsCSVwithSF_JetSubCalc",&NJetsCSVwithSF_JetSubCalc,"NJetsCSVwithSF_JetSubCalc/I");
   outputTree->Branch("NJetsWtagged_0p6",&NJetsWtagged_0p6,"NJetsWtagged_0p6/I");
   outputTree->Branch("NJetsWtagged_0p6_shifts",&NJetsWtagged_0p6_shifts);
   outputTree->Branch("NJetsHtagged",&NJetsHtagged,"NJetsHtagged/I");

   outputTree->Branch("genTopPt",&genTopPt,"genTopPt/F");
   outputTree->Branch("genAntiTopPt",&genAntiTopPt,"genAntiTopPt/F");
   outputTree->Branch("topPtWeight",&topPtWeight,"topPtWeight/F");
   outputTree->Branch("topPtWeightPast400",&topPtWeightPast400,"topPtWeightPast400/F");
   outputTree->Branch("topPtWeightHighPt",&topPtWeightHighPt,"topPtWeightHighPt/F");
   
   outputTree->Branch("deltaR_lep1Jets",&deltaR_lep1Jets);
   outputTree->Branch("deltaR_lep2Jets",&deltaR_lep2Jets);
   outputTree->Branch("deltaR_lep3Jets",&deltaR_lep3Jets);
   outputTree->Branch("deltaR_lepClosestJet",&deltaR_lepClosestJet);
   outputTree->Branch("PtRelLepClosestJet",&PtRelLepClosestJet);

   outputTree->Branch("Mll_sameFlavorOS",&Mll_sameFlavorOS,"Mll_sameFlavorOS/F");
   outputTree->Branch("Mll_allComb",&Mll_allComb); // NOT FILLED YET!!


   TLorentzVector jet_lv;
   TLorentzVector bjet_lv;
   TLorentzVector wjet1_lv;
   std::vector<TLorentzVector> lepton_lv;
   TLorentzVector ak8_lv;
   
   // basic cuts
   float metCut=0;
   float jetEtaCut=2.4;
   int   njetsCut=0;
   float JetLeadPtCut=0;
   float JetSubLeadPtCut=0;
   float lepPtCut=20;

   std::vector<float> ptRangeTpTp, ptRangeTTbar;
   float ptminTTbar[15] = {200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1200};
   for (int i=0;i<15;++i) ptRangeTTbar.push_back(ptminTTbar[i]);
   float ptminTpTp[17] = {200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200};
   for (int i=0;i<17;++i) ptRangeTpTp.push_back(ptminTpTp[i]);

   float SignalEff[17] = {0.260129,0.317269,0.346859,0.374089,0.396727,0.418234,0.436933,0.453725,0.464151,0.479066,0.48227,0.503652,0.494932,0.503458,0.496269,0.462555,0.457404};
   float TTbarEff[15] = {0.415831,0.514135,0.49113,0.448312,0.407475,0.369593,0.346835,0.31726,0.312786,0.290524,0.29417,0.272038,0.277081,0.287097,0.273381};
      
   //read CSC bad event filter file
   vector <int> CSC_run;
   vector <int> CSC_ls;
   vector <int> CSC_event;
   cout << "Reading CSC file" << std::endl;
   ifstream infileCSCm( "csc2015_Dec01.txt" );
   while (infileCSCm)
   {
     string s;
     if (!getline( infileCSCm, s )) break;

     istringstream ss( s );
     vector <string> line;
     while (ss)
     {
       string s;
       if (!getline( ss, s, ':' )) break;
       line.push_back( s );
     }
     CSC_run.push_back( std::atoi(line[0].c_str()) );
     CSC_ls.push_back( std::atoi(line[1].c_str()) );
     CSC_event.push_back( std::atoi(line[2].c_str()) );
   }
   if (!infileCSCm.eof())
   {
     cerr << "Error while reading CSC filter file!\n";
   }
   cout << "Done reading CSC file, testing vector size" << std::endl;
   cout << "Nevents = " << CSC_run.size() << ", " << CSC_ls.size() << ", " << CSC_event.size() << std::endl;

   //read bad ECAL SC filter file
   vector <int> ECALSC_run;
   vector <int> ECALSC_ls;
   vector <int> ECALSC_event;
   cout << "Reading ECAL SCN file" << std::endl;
   ifstream infileCSCe( "ecalscn1043093_Dec01.txt" );
   while (infileCSCe)
   {
     string s;
     if (!getline( infileCSCe, s )) break;

     istringstream ss( s );
     vector <string> line;
     while (ss)
     {
       string s;
       if (!getline( ss, s, ':' )) break;
       line.push_back( s );
     }
     ECALSC_run.push_back( std::atoi(line[0].c_str()) );
     ECALSC_ls.push_back( std::atoi(line[1].c_str()) );
     ECALSC_event.push_back( std::atoi(line[2].c_str()) );
   }
   if (!infileCSCe.eof())
   {
     cerr << "Error while reading ECAL SCN filter file!\n";
   }
   cout << "Done reading ECAL SCN file, testing vector size" << std::endl;
   cout << "Nevents = " << ECALSC_run.size() << ", " << ECALSC_ls.size() << ", " << ECALSC_event.size() << std::endl;
   
   
   double puweight260627_72ub[60] = {1.048445e+02, 1.417593e+02, 8.807366e+01, 3.236995e+01, 1.683957e+01, 2.831305e+00, 1.423759e+00, 1.612828e+00, 2.306693e+00, 2.473619e+00, 2.514170e+00, 2.546666e+00, 2.333108e+00, 1.836848e+00, 1.221869e+00, 6.836922e-01, 3.275329e-01, 1.432766e-01, 6.667120e-02, 3.763312e-02, 2.341225e-02, 1.359301e-02, 6.804618e-03, 2.922054e-03, 1.130104e-03, 4.448707e-04, 2.080687e-04, 1.239100e-04, 8.786009e-05, 6.837745e-05, 5.143024e-05, 3.476586e-05, 1.906542e-05, 9.115409e-06, 3.556074e-06, 1.447242e-06, 5.171527e-07, 1.940254e-07, 6.513423e-08, 2.309190e-08, 7.790329e-09, 2.199365e-09, 6.795396e-10, 1.624286e-10, 4.931596e-11, 1.298753e-11, 7.930341e-12, 2.315454e-12, 1.497868e-11, 2.172998e-12, 9.012326e-14, 1.094585e-14, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};
   double puweight260627_69ub[60] = {1.245238e+02, 1.562054e+02, 9.528614e+01, 3.645428e+01, 2.049345e+01, 3.843197e+00, 2.215886e+00, 2.747772e+00, 3.412640e+00, 3.156122e+00, 2.921218e+00, 2.709273e+00, 2.214740e+00, 1.509242e+00, 8.529270e-01, 4.047681e-01, 1.706805e-01, 7.408239e-02, 3.853898e-02, 2.208110e-02, 1.157933e-02, 5.111779e-03, 1.897273e-03, 6.326908e-04, 2.194698e-04, 9.396686e-05, 5.134064e-05, 3.356329e-05, 2.432826e-05, 1.843384e-05, 1.299881e-05, 8.002472e-06, 3.916437e-06, 1.648432e-06, 5.607770e-07, 1.975807e-07, 6.075239e-08, 1.950465e-08, 5.573450e-09, 1.673234e-09, 4.755563e-10, 1.125301e-10, 2.899281e-11, 5.749377e-12, 1.440875e-12, 3.115802e-13, 1.554955e-13, 3.630806e-14, 2.427227e-13, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};
   double puweight260627_65ub[60] = {1.458817e+02, 1.724645e+02, 1.043786e+02, 4.182011e+01, 2.579572e+01, 5.495080e+00, 3.731141e+00, 4.618505e+00, 4.765473e+00, 3.872168e+00, 3.259346e+00, 2.705177e+00, 1.908453e+00, 1.092269e+00, 5.137612e-01, 2.085454e-01, 8.454498e-02, 4.109705e-02, 2.206794e-02, 1.053976e-02, 4.084606e-03, 1.298473e-03, 3.698050e-04, 1.135070e-04, 4.460047e-05, 2.240654e-05, 1.319444e-05, 8.644198e-06, 5.969210e-06, 4.142850e-06, 2.600931e-06, 1.398830e-06, 5.905424e-07, 2.124612e-07, 6.132579e-08, 1.821361e-08, 4.691640e-09, 1.254258e-09, 2.966644e-10, 7.328361e-11, 1.703655e-11, 3.277952e-12, 6.826269e-13, 1.087907e-13, 2.182661e-14, 3.753385e-15, 1.408114e-15, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};
   double puweight260627_72ub_central[60] = {1.088e+02, 1.446e+02, 8.940e+01, 3.287e+01, 1.730e+01, 2.948e+00, 1.504e+00, 1.727e+00, 2.433e+00, 2.557e+00, 2.567e+00, 2.573e+00, 2.328e+00, 1.803e+00, 1.176e+00, 6.448e-01, 3.032e-01, 1.315e-01, 6.179e-02, 3.525e-02, 2.165e-02, 1.219e-02, 5.878e-03, 2.434e-03, 9.180e-04, 3.608e-04, 1.720e-04, 1.043e-04, 7.446e-05, 5.795e-05, 4.336e-05, 2.903e-05, 1.572e-05, 7.404e-06, 2.842e-06, 1.137e-06, 3.988e-07, 1.468e-07, 4.833e-08, 1.679e-08, 5.547e-09, 1.533e-09, 4.632e-10, 1.082e-10, 3.210e-11, 8.253e-12, 4.917e-12, 1.400e-12, 8.834e-12, 1.222e-12, 5.321e-14, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};

   int npass_trigger      = 0;
   int npass_met          = 0;
   int npass_njets        = 0;
   int npass_JetLeadPt    = 0;
   int npass_all          = 0;
   
   int totalLep = 0;

	int Neee[4]={0};
	int Neem[6]={0};
	int Nemm[6]={0};
	int Nmmm[4]={0};

	int nPassTrilepton=0;

   cout << "RUN CONFIG: " << endl;
   cout << "isSig = " << isSig << ", isTOP = " << isTOP << ", isMC = " << isMC << endl;
   
   Long64_t nentries = inputTree->GetEntriesFast();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = inputTree->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) != 1) continue;
      
      //      if (ientry > 5000) continue;
      
      std::cout << " " << endl;
      std::cout << "=======================================================" << endl;
      
      if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;
      
//       std::cout << "Check GetEntry: " << endl;
//       std::cout	<< "elPt_singleLepCalc->size() = " << elPt_singleLepCalc->size() << endl;
//       std::cout << "muPt_singleLepCalc->size() = " << muPt_singleLepCalc->size() << endl;

      // Filter input file by mass or decay
      if(isTTincMtt0to700 && ttbarMass_TTbarMassCalc >= 700.) continue;
      if(isTTincMtt700to1000 && (ttbarMass_TTbarMassCalc < 700. || ttbarMass_TTbarMassCalc >= 1000.)) continue;
      if(isTTincMtt1000toInf && ttbarMass_TTbarMassCalc < 1000.) continue;
      if(outBWBW && !isBWBW_TpTpCalc) continue;
      if(outTZBW && !isTZBW_TpTpCalc) continue;
      if(outTHBW && !isTHBW_TpTpCalc) continue;
      if(outTZTH && !isTZTH_TpTpCalc) continue;
      if(outTZTZ && !isTZTZ_TpTpCalc) continue;
      if(outTHTH && !isTHTH_TpTpCalc) continue;
      if(outTWTW && !isTWTW_TpTpCalc) continue;
      if(outBZTW && !isBZTW_TpTpCalc) continue;
      if(outBHTW && !isBHTW_TpTpCalc) continue;
      if(outBZBH && !isBZBH_TpTpCalc) continue;
      if(outBZBZ && !isBZBZ_TpTpCalc) continue;
      if(outBHBH && !isBHBH_TpTpCalc) continue;

      //CSC filter (aka muon halo filter) NOTE: filtering data sets by running both SE and SM CSC filters!
      bool filterEvent = false;
      for(unsigned int i=0; i < CSC_run.size(); i++){
      	if(CSC_run[i]==run_CommonCalc && CSC_ls[i]==lumi_CommonCalc && CSC_event[i]==event_CommonCalc) filterEvent = true;
      }
      for(unsigned int i=0; i < ECALSC_run.size(); i++){
      	if(ECALSC_run[i]==run_CommonCalc && ECALSC_ls[i]==lumi_CommonCalc && ECALSC_event[i]==event_CommonCalc) filterEvent = true;
      }
      if(filterEvent) continue;
     	     
      std::vector<double> TightLeptonPt;
      std::vector<double> TightLeptonEta;
      std::vector<double> TightLeptonPhi;
      std::vector<double> TightLeptonEnergy;
      std::vector<double> TightLeptonMiniIso;
      std::vector<int> TightLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> TightLeptonCharge; // 0 - electron, 1 - muon
      std::vector<int> TightLeptonIdx; // index in LJMet ntuple
      std::vector<pair<double,int>> tightlepptindpair;      

      std::vector<double> LooseNotTightLeptonPt;
      std::vector<double> LooseNotTightLeptonEta;
      std::vector<double> LooseNotTightLeptonPhi;
      std::vector<double> LooseNotTightLeptonEnergy;
      std::vector<double> LooseNotTightLeptonMiniIso;
      std::vector<int> LooseNotTightLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> LooseNotTightLeptonCharge; // 0 - electron, 1 - muon
      std::vector<int> LooseNotTightLeptonIdx; // index in LJMet ntuple
      std::vector<pair<double,int>> loosenottightlepptindpair;      

      std::vector<double> AllLeptonPt;
      std::vector<double> AllLeptonEta;
      std::vector<double> AllLeptonPhi;
      std::vector<double> AllLeptonEnergy;
      std::vector<double> AllLeptonMiniIso;
      std::vector<int> AllLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> AllLeptonIsTight; 
      std::vector<int> AllLeptonCharge;       
      std::vector<int> AllLeptonIdx; // index in LJMet ntuple
      std::vector<pair<double,int>> alllepptindpair;

      int tightlepindex = 0;
      int loosenottightlepindex = 0;
            
      //collect all electrons.
      for(unsigned int iel = 0; iel < elPt_singleLepCalc->size(); iel++){
		bool isTightEl = false;
		if(elPt_singleLepCalc->at(iel) < lepPtCut || fabs(elEta_singleLepCalc->at(iel)) > 2.4) continue;
		if(elMiniIso_singleLepCalc->at(iel) < 0.1){
		  if(fabs(elEta_singleLepCalc->at(iel)) <= 0.8 && elMVAValue_singleLepCalc->at(iel) > 0.967083) isTightEl = true;
		  else if(fabs(elEta_singleLepCalc->at(iel)) <= 1.479 && elMVAValue_singleLepCalc->at(iel) > 0.929117) isTightEl = true;
		  else if(fabs(elEta_singleLepCalc->at(iel)) <= 2.5 && elMVAValue_singleLepCalc->at(iel) > 0.726311) isTightEl = true;
		}

		if(isTightEl){
		  TightLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  TightLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  TightLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  TightLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  TightLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  TightLeptonFlavor.push_back(0);
		  TightLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  TightLeptonIdx.push_back(iel);

		  tightlepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),tightlepindex));
		  tightlepindex++;
		}
		if(!isTightEl){
		  LooseNotTightLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  LooseNotTightLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  LooseNotTightLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  LooseNotTightLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  LooseNotTightLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  LooseNotTightLeptonFlavor.push_back(0);
		  LooseNotTightLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  LooseNotTightLeptonIdx.push_back(iel);
		  
		  loosenottightlepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),loosenottightlepindex));
		  loosenottightlepindex++;
		}
		
      }
      
      //collect all muons.
      for(unsigned int imu = 0; imu < muPt_singleLepCalc->size(); imu++){
		bool isTightMu = false;
		if(muPt_singleLepCalc->at(imu) < lepPtCut || fabs(muEta_singleLepCalc->at(imu)) > 2.4) continue;
		//ATTENTION! there is mistake in new 74x LJMet ntuple muMiniIso twice filled!! hence the imu*2
		if(muMiniIso_singleLepCalc->at(imu*2) < 0.2 && muIsTight_singleLepCalc->at(imu) > 0) isTightMu = true;

		if(isTightMu){
		  TightLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  TightLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  TightLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  TightLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  TightLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu*2));//ATTENTION! there is mistake in new 74x LJMet ntuple muMiniIso twice filled!! hence the imu*2
		  TightLeptonFlavor.push_back(1);
		  TightLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  TightLeptonIdx.push_back(imu);

		  tightlepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),tightlepindex));
		  tightlepindex++;
		}

		if(!isTightMu){
		  LooseNotTightLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  LooseNotTightLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  LooseNotTightLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  LooseNotTightLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  LooseNotTightLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu*2));//ATTENTION! there is mistake in new 74x LJMet ntuple muMiniIso twice filled!! hence the imu*2
		  LooseNotTightLeptonFlavor.push_back(1);
		  LooseNotTightLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  LooseNotTightLeptonIdx.push_back(imu);
		  
		  loosenottightlepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),loosenottightlepindex));
		  loosenottightlepindex++;
		}

      }
      
      std::cout << "Nleptons = " << tightlepindex+loosenottightlepindex << endl;
      if(tightlepindex+loosenottightlepindex<3) continue; //skip if there is less than 3 loose leptons.
// CHECK and UNCOMMENT BELOW if necessary!!
//       if(isMC && tightlepindex<3) continue; //skip if there is less than 3 tight leptons for MC (not creating ddBKg).

      //Pt ordering
      AllLeptonPt_PtOrdered.clear();
      AllLeptonEta_PtOrdered.clear();
      AllLeptonPhi_PtOrdered.clear();
      AllLeptonEnergy_PtOrdered.clear();
      AllLeptonMiniIso_PtOrdered.clear();
      AllLeptonFlavor_PtOrdered.clear();
      AllLeptonIsTight_PtOrdered.clear();      
      AllLeptonCharge_PtOrdered.clear();      
      AllLeptonIdx_PtOrdered.clear();      
 
      //Pt ordering - for Tight leptons - then add to All leptons list/vector
      int Nel = 0;
      int Nmu = 0;
      std::sort(tightlepptindpair.begin(), tightlepptindpair.end(), comparepair);
      TightLeptonPt_PtOrdered.clear();
      TightLeptonEta_PtOrdered.clear();
      TightLeptonPhi_PtOrdered.clear();
      TightLeptonEnergy_PtOrdered.clear();
      TightLeptonMiniIso_PtOrdered.clear();
      TightLeptonFlavor_PtOrdered.clear();
      TightLeptonCharge_PtOrdered.clear();
      TightLeptonIdx_PtOrdered.clear();
      for(unsigned int ilep=0; ilep < tightlepptindpair.size(); ilep++){
      	TightLeptonPt_PtOrdered.push_back(TightLeptonPt.at(tightlepptindpair[ilep].second));
      	TightLeptonEta_PtOrdered.push_back(TightLeptonEta.at(tightlepptindpair[ilep].second));
      	TightLeptonPhi_PtOrdered.push_back(TightLeptonPhi.at(tightlepptindpair[ilep].second));
      	TightLeptonEnergy_PtOrdered.push_back(TightLeptonEnergy.at(tightlepptindpair[ilep].second));
      	TightLeptonMiniIso_PtOrdered.push_back(TightLeptonMiniIso.at(tightlepptindpair[ilep].second));
      	TightLeptonFlavor_PtOrdered.push_back(TightLeptonFlavor.at(tightlepptindpair[ilep].second));
      	TightLeptonCharge_PtOrdered.push_back(TightLeptonCharge.at(tightlepptindpair[ilep].second));
      	TightLeptonIdx_PtOrdered.push_back(TightLeptonIdx.at(tightlepptindpair[ilep].second));
 
		if(ilep < 3){
		  if(TightLeptonFlavor.at(tightlepptindpair[ilep].second) == 0) Nel++;
		  if(TightLeptonFlavor.at(tightlepptindpair[ilep].second) == 1) Nmu++;
		}
		
		//push back for all leptons order in pt AND TIGHT
		AllLeptonPt_PtOrdered.push_back(TightLeptonPt.at(tightlepptindpair[ilep].second));
      	AllLeptonEta_PtOrdered.push_back(TightLeptonEta.at(tightlepptindpair[ilep].second));
      	AllLeptonPhi_PtOrdered.push_back(TightLeptonPhi.at(tightlepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrdered.push_back(TightLeptonEnergy.at(tightlepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrdered.push_back(TightLeptonMiniIso.at(tightlepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrdered.push_back(TightLeptonFlavor.at(tightlepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrdered.push_back(1);
      	AllLeptonCharge_PtOrdered.push_back(TightLeptonCharge.at(tightlepptindpair[ilep].second));				
      	AllLeptonIdx_PtOrdered.push_back(TightLeptonIdx.at(tightlepptindpair[ilep].second));				
      }           

      //Pt ordering - for Loose Not Tight - then append to All leptons list/vector
      std::sort(loosenottightlepptindpair.begin(), loosenottightlepptindpair.end(), comparepair);
      for(unsigned int ilep=0; ilep < loosenottightlepptindpair.size(); ilep++){

		//push back for all leptons order in pt AND LOOSEnotTIGHT
		AllLeptonPt_PtOrdered.push_back(LooseNotTightLeptonPt.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonEta_PtOrdered.push_back(LooseNotTightLeptonEta.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonPhi_PtOrdered.push_back(LooseNotTightLeptonPhi.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrdered.push_back(LooseNotTightLeptonEnergy.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrdered.push_back(LooseNotTightLeptonMiniIso.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrdered.push_back(LooseNotTightLeptonFlavor.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrdered.push_back(0);
      	AllLeptonCharge_PtOrdered.push_back(LooseNotTightLeptonCharge.at(loosenottightlepptindpair[ilep].second));
				
      }           
      
      int Nel_top3_all = 0;
      int Nmu_top3_all = 0;
      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
      	if(ilep < 3){
      		if(AllLeptonFlavor_PtOrdered.at(ilep)==0) Nel_top3_all++;
      		if(AllLeptonFlavor_PtOrdered.at(ilep)==1) Nmu_top3_all++;
      	}
      	std::cout<< "ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrdered.at(ilep) << ", charge = " << AllLeptonCharge_PtOrdered.at(ilep) << ", pT = "<< AllLeptonPt_PtOrdered.at(ilep)  <<", isTight = " << AllLeptonIsTight_PtOrdered.at(ilep) << endl; 
      }

      
      std::cout << "Nel = " << Nel << ",  Nmu = " << Nmu << endl; 
      std::cout << "Nel_top3_all = " << Nel_top3_all << ",  Nmu_top3_all = " << Nmu_top3_all << endl; 

      isEEE = 0; isEEM =0; isEMM =0; isMMM= 0;
      	
      if(Nel + Nmu != 3) cout << "First 3 tight leps don't add up to 3!" << endl;
      if(Nel_top3_all + Nmu_top3_all != 3) cout << "First 3 All leps don't add up to 3, something's wrong" << endl;

      if(Nel_top3_all == 3 && Nmu_top3_all == 0){isEEE = 1; isEEM = 0; isEMM = 0; isMMM = 0;}
      else if(Nel_top3_all == 2 && Nmu_top3_all == 1){isEEE = 0; isEEM = 1; isEMM = 0; isMMM = 0;}
      else if(Nel_top3_all == 1 && Nmu_top3_all == 2){isEEE = 0; isEEM = 0; isEMM = 1; isMMM = 0;}
      else if(Nel_top3_all == 0 && Nmu_top3_all == 3){isEEE = 0; isEEM = 0; isEMM = 0; isMMM = 1;}
      
      isPassTrilepton = false;
      if(Nel + Nmu >= 3){
		nPassTrilepton++;
		isPassTrilepton = true;
		std::cout << "pass trilepton cut! (3 tight leptons)" << endl;
      }
      else{
      	std::cout << "fail trilepton cut! (no 3 tight leptons), must be for ddbkg?" << endl;
      }
      
      std::cout << " isEEE = "<< isEEE << ", isEEM = "<< isEEM << ", isEMM = "<<isEMM << ", isMMM = "<<isMMM << std::endl; 
	     
      //Determine bkgweights here IF processing DATA. - start
      const int nmodes = 5;
      //for this to work there has to be a nLooseLepton == 2 cut. 
      //mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus
      //see feModeBehavior in fakerate.h
      double bkgweights[nmodes] = {0};
      if(!isMC){
	
			vector<double> lep1_info,lep2_info,lep3_info; //at(0): isE, at(1): isTight, at(2): pt, at(3): eta
			lep1_info.push_back(AllLeptonFlavor_PtOrdered.at(0));lep1_info.push_back(AllLeptonIsTight_PtOrdered.at(0));lep1_info.push_back(AllLeptonPt_PtOrdered.at(0));lep1_info.push_back(AllLeptonEta_PtOrdered.at(0));
			lep2_info.push_back(AllLeptonFlavor_PtOrdered.at(1));lep2_info.push_back(AllLeptonIsTight_PtOrdered.at(1));lep2_info.push_back(AllLeptonPt_PtOrdered.at(1));lep2_info.push_back(AllLeptonEta_PtOrdered.at(1));
			lep3_info.push_back(AllLeptonFlavor_PtOrdered.at(2));lep3_info.push_back(AllLeptonIsTight_PtOrdered.at(2));lep3_info.push_back(AllLeptonPt_PtOrdered.at(2));lep3_info.push_back(AllLeptonEta_PtOrdered.at(2));
			for(int imode=0;imode<nmodes;imode++){
				bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info, lep3_info);
			}
			
// 			if(isEEE){
// 				for(int imode=0;imode<nmodes;imode++){
// 					bkgweights[imode] = GetWeight_eee(Nel, imode);
// // 					bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info, lep3_info);
// 				}
// 			}
// 			else if(isMMM){
// 				for(int imode=0;imode<nmodes;imode++){
// 					bkgweights[imode] = GetWeight_mmm(Nmu, imode);
// // 					bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info, lep3_info);
// 				}
// 			}
// 			else if(isEEM){
// 				for(int imode=0;imode<nmodes;imode++){
// 					bkgweights[imode] = GetWeight_eem(Nel, Nmu, imode);
// // 					bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info, lep3_info);
// 				}
// 			}
// 			else if(isEMM){
// 				for(int imode=0;imode<nmodes;imode++){
// 					bkgweights[imode] = GetWeight_emm(Nel, Nmu, imode);
// // 					bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info, lep3_info);
// 				}
// 			}
// 			else{ cerr<<"Error! no combination of eee, eem, emm, mmm, so what the hell is it?"<<endl; assert(0);}
		}//end make background weights.
// 		if(printlevel >=3){ 
			for(int imode=0;imode<nmodes;imode++)cout << "bkgweights["<<imode<<"] ="<< bkgweights[imode]<<endl;	
// 		}
		
		ddBkgWeights.clear();
		for(int imode=0; imode<nmodes;imode++){ddBkgWeights.push_back(bkgweights[imode]);}
			
// 		if(printlevel > 5) cout << "check point A" << endl; //debug rizki
		
		if(isEEE){
			Neee[Nel]++;
		}
		else if(isEEM){
			Neem[2*Nel + Nmu]++;
		}
		else if(isEMM){
			Nemm[Nel + 2*Nmu]++;
		}
		else if(isMMM){
			Nmmm[Nmu]++;
		}
// 		if(printlevel > 5) cout << "check point B" << endl; //debug rizki
      
      //Determine bkgweights here IF processing DATA. - end
	
      float leadJetPtcsv = 0;
      int   njets = 0;
      int   nbtags = 0;
      float ht = 0;
      vector<pair<double,int>> jetptindpair;
      JetSF_pTNbwflat = 1.0;
      JetSFup_pTNbwflat = 1.0;
      JetSFdn_pTNbwflat = 1.0;
      JetSFupwide_pTNbwflat = 1.0;
      JetSFdnwide_pTNbwflat = 1.0;

      std::vector<int> theJetBTagBuggy;

      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc->size(); ijet++){
      	
      	fabs(theJetEta_JetSubCalc->at(ijet)) > jetEtaCut) continue; //IS this needed??
		
		// Not needed for new LJMet ntuples - start
		/// FIX THE MISTAGS -- value in theJetBTag is correct if flavor is 4/5
		theJetBTagBuggy.push_back(theJetBTag_JetSubCalc->at(ijet));

		if(isMC && AK4JetFlav_singleLepCalc->at(ijet) != 4 && AK4JetFlav_singleLepCalc->at(ijet) != 5){
		  double mistagSF = 1.0;

		  if(MistagSFup) mistagSF = 1.34022; // up
		  else if(MistagSFdn) mistagSF = 0.94022; // down
		  else mistagSF = 1.14022; // central
 
		  double mistageff = 0.0;
		  double pt = theJetPt_JetSubCalc->at(ijet);
		  if(pt < 20) mistageff = 0.003402;
		  else if(pt < 40) mistageff = 0.008067;
		  else if(pt < 60) mistageff = 0.006980;
		  else if(pt < 80) mistageff = 0.006316;
		  else if(pt < 100) mistageff = 0.006713;
		  else if(pt < 115) mistageff = 0.006598;
		  else if(pt < 400) mistageff = -0.00242504 + 9.15452e-05*pt - 9.63553e-08*pt*pt;
		  else mistageff = 0.0134038 + 1.24358e-05*pt;

		  bool isBTagged = (theJetCSV_JetSubCalc->at(ijet) > 0.890);
		  bool newBTag = isBTagged;

		  //throw die
		  float coin = gRandom->Uniform(1.);    
  
		  if(mistagSF > 1){  // use this if SF>1
			if( !isBTagged ) {

			  //fraction of jets that need to be upgraded
			  float mistagPercent = (1.0 - mistagSF) / (1.0 - (mistagSF/mistageff) );

			  //upgrade to tagged
			  if( coin < mistagPercent ) {newBTag = true;} // is was false before
			}	    
		  }else{  // use this if SF<1
  
			//downgrade tagged to untagged
			if( isBTagged && coin > mistagSF ) {newBTag = false;} // it was true before
		  }
		  theJetBTag_JetSubCalc->at(ijet) =  newBTag;
		}
		
		// Not needed for new LJMet ntuples - end


		AK4HTnoSF += theJetPt_JetSubCalc->at(ijet);

		if(isMC){
		  float one = 1.0;
		
		  float jetpt = theJetPt_JetSubCalc->at(ijet);
		  float jetsf = 1.09383 - 0.000477777*jetpt;
		  float jetsferr = sqrt(0.00314541714554 + 2.18390370364e-08*jetpt*jetpt + 2*jetpt*(-7.85447860996e-06));
	  
		  float wideup = min(one,max(float(0.747382 + 0.164524),jetsf+jetsferr));				    
		  float widedn = min(one,max(jetsf-jetsferr,float(0.747382 - 0.164524)));
	  
		  if(isTOP || isSig){
			if(jetpt >= 200){
			  if(jetpt < 725){
			JetSF_pTNbwflat *= min(one,jetsf);
			JetSFup_pTNbwflat *= wideup;
			JetSFdn_pTNbwflat *= widedn;
			JetSFupwide_pTNbwflat *= wideup;
			JetSFdnwide_pTNbwflat *= widedn;
			  }else{
			JetSF_pTNbwflat *= 0.747382;
			JetSFup_pTNbwflat *= wideup;
			JetSFdn_pTNbwflat *= widedn;
			JetSFupwide_pTNbwflat *= wideup;
			JetSFdnwide_pTNbwflat *= widedn;
			  }
			}
		  }else{
			jetsf = 1.24507 - 0.000664768*jetpt;
			jetsferr = sqrt(0.000506216376592 + 3.1532423475e-09*jetpt*jetpt + 2*jetpt*(-1.17981363543e-06));
			if(jetpt < 1020){
			  JetSF_pTNbwflat *= min(one,jetsf);
			  JetSFup_pTNbwflat *= min(one,max(jetsf+jetsferr,float(0.568135+0.0522921)));
			  JetSFdn_pTNbwflat *= min(one,max(jetsf-jetsferr,float(0.568135-0.0522921)));
			  JetSFupwide_pTNbwflat *= max(wideup,min(one,max(jetsf+jetsferr,float(0.568135+0.0522921))));
			  JetSFdnwide_pTNbwflat *= min(widedn,min(one,max(jetsf-jetsferr,float(0.568135-0.0522921))));
			}else{
			  JetSF_pTNbwflat *= 0.568135;
			  JetSFup_pTNbwflat *= min(one,max(jetsf+jetsferr,float(0.568135+0.0522921)));
			  JetSFdn_pTNbwflat *= min(one,max(jetsf-jetsferr,float(0.568135-0.0522921)));
			  JetSFupwide_pTNbwflat *= max(wideup,min(one,max(jetsf+jetsferr,float(0.568135+0.0522921))));
			  JetSFdnwide_pTNbwflat *= min(widedn,min(one,max(jetsf-jetsferr,float(0.568135-0.0522921))));
			}
		  }
	  
		  jetptindpair.push_back(std::make_pair(theJetPt_JetSubCalc->at(ijet),ijet));
		  njets+=1;
		  ht+=theJetPt_JetSubCalc->at(ijet);
		  if(theJetCSV_JetSubCalc->at(ijet) > 0.890) nbtags+=1;
	  
		}else{
		  jetptindpair.push_back(std::make_pair(theJetPt_JetSubCalc->at(ijet),ijet));
		  njets+=1;
		  ht+=theJetPt_JetSubCalc->at(ijet);
		  if(theJetCSV_JetSubCalc->at(ijet) > 0.890) nbtags+=1;
		}
      }
	
      //Pt ordering
      std::sort(jetptindpair.begin(), jetptindpair.end(), comparepair);
      theJetPt_JetSubCalc_PtOrdered.clear();
      theJetEta_JetSubCalc_PtOrdered.clear();
      theJetPhi_JetSubCalc_PtOrdered.clear();
      theJetEnergy_JetSubCalc_PtOrdered.clear();
      theJetCSV_JetSubCalc_PtOrdered.clear();
      theJetBTag_JetSubCalc_PtOrdered.clear();
//new format
//       theJetBTag_bSFdn_JetSubCalc_PtOrdered.clear();
//       theJetBTag_bSFup_JetSubCalc_PtOrdered.clear();
//       theJetBTag_lSFdn_JetSubCalc_PtOrdered.clear();
//       theJetBTag_lSFup_JetSubCalc_PtOrdered.clear();

      theJetBTagBuggy_JetSubCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetptindpair.size(); ijet++){
      	theJetPt_JetSubCalc_PtOrdered.push_back(theJetPt_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetEta_JetSubCalc_PtOrdered.push_back(theJetEta_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetPhi_JetSubCalc_PtOrdered.push_back(theJetPhi_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetEnergy_JetSubCalc_PtOrdered.push_back(theJetEnergy_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetCSV_JetSubCalc_PtOrdered.push_back(theJetCSV_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetBTag_JetSubCalc_PtOrdered.push_back(theJetBTag_JetSubCalc->at(jetptindpair[ijet].second));
//new format
//       	theJetBTag_bSFdn_JetSubCalc_PtOrdered.push_back(theJetBTag_bSFdn_JetSubCalc->at(jetptindpair[ijet].second));
//       	theJetBTag_bSFup_JetSubCalc_PtOrdered.push_back(theJetBTag_bSFup_JetSubCalc->at(jetptindpair[ijet].second));
//       	theJetBTag_lSFdn_JetSubCalc_PtOrdered.push_back(theJetBTag_lSFdn_JetSubCalc->at(jetptindpair[ijet].second));
//       	theJetBTag_lSFup_JetSubCalc_PtOrdered.push_back(theJetBTag_lSFup_JetSubCalc->at(jetptindpair[ijet].second));

      	theJetBTagBuggy_JetSubCalc_PtOrdered.push_back(theJetBTagBuggy.at(jetptindpair[ijet].second));
      }

      //require "njetsCut" jets
      int isPastNJetsCut = 0;
      if(njets >= njetsCut){npass_njets+=1;isPastNJetsCut=1;}
      
      //check for high pt jet
      int isPastJetLeadPtCut = 0;
      if(theJetPt_JetSubCalc_PtOrdered[0] > JetLeadPtCut){npass_JetLeadPt+=1;isPastJetLeadPtCut=1;}
      
      //check met requirement
      int isPastMETcut = 0;
      if(corr_met_singleLepCalc > metCut){npass_met+=1;isPastMETcut=1;}
            
      // check all the cuts!
      if(!(isPastMETcut && isPastNJetsCut && isPastJetLeadPtCut)) continue;
      npass_all+=1;

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /////////////// ONLY ON SELECTED EVENTS ////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      double puweight = puweight260627_69ub[nTrueInteractions_singleLepCalc];
      double puweightup = puweight260627_65ub[nTrueInteractions_singleLepCalc];
      double puweightdown = puweight260627_72ub[nTrueInteractions_singleLepCalc];
      double puweight72ub = puweight260627_72ub_central[nTrueInteractions_singleLepCalc];

      int   isPastTrig = 0;
      int   isPastTrigAlt = 0;
      int   isPastTrigMC = 0;
      int   isPastTrigMCAlt = 0;
 
      int   isPastTrig_trilep = 0;
      int   isPastTrigMC_trilep = 0;
      int   isPastTrig_dilep = 0;
      int   isPastTrigMC_dilep = 0;
      int   isPastTrig_dilepHT = 0;
      int   isPastTrigMC_dilepHT = 0;

      float TrigEffAlt = 1.0;
      float TrigEff = 1.0;
      float isosf = 1.0;
      float lepidsf = 1.0;

      if(isMC){ //MC triggers check

//example for looping trigger. create output branch!      
//       if(isE){
// 		  for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
// 			if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WP75_Gsf_v1" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) isPastTrigMC = 1;
// 			if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v1" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) isPastTrigMCAlt = 1;
// 	  }

      	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
      		if(viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) std::cout << "pass trigger : " << vsSelMCTriggersEl_singleLepCalc->at(itrig) << endl;
      		}
      	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
      		if(viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) std::cout << "pass trigger : " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << endl;
      		}


   		if(isEEE){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_trilep = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
			}
	  	}
   		if(isEEM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_trilep = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
				if((vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelMCTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
			}
	  	}
   		if(isEMM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_trilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
			}
	  	}
   		if(isMMM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_trilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
				if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v1" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v2" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v3" || 
					vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v4") && 
					viSelMCTriggersMu_singleLepCalc->at(itrig) > 0){
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepHT = 1;
				}
			}
	  	}


		// GET SOME TRIGGER SCALE FACTORS PER EVENT

		for(unsigned int ilep = 0; ilep < TightLeptonPt_PtOrdered.size(); ilep++){
		  double lepeta = TightLeptonEta_PtOrdered.at(ilep);
		  double leppt = TightLeptonPt_PtOrdered.at(ilep);
	  
		  if(TightLeptonFlavor_PtOrdered.at(ilep) == 0){

			//miniIso < 0.1 scale factors from https://indico.cern.ch/event/370512/contribution/1/attachments/1176496/1701148/2015_10_26_tnp.pdf
			if(fabs(lepeta) < 1.442){
			  if(leppt > 10 && leppt < 20) isosf *= 0.979; // +/-0.004 
			  else if(leppt < 30) isosf *= 0.988; // +/-0.002
			  else if(leppt < 40) isosf *= 0.995; // +/-0.022
			  else if(leppt < 50) isosf *= 0.995; // +/-0.011
			  else if(leppt < 200) isosf *= 0.995; // +/-0.000
			}
			else if(fabs(lepeta) < 1.566){
			  if(leppt > 10 && leppt < 20) isosf *= 0.909; // +/-0.05 
			  else if(leppt < 30) isosf *= 0.982; // +/-0.014
			  else if(leppt < 40) isosf *= 1.001; // +/-0.006
			  else if(leppt < 50) isosf *= 0.993; // +/-0.007
			  else if(leppt < 200) isosf *= 0.988; // +/-0.014
			}
			else if(fabs(lepeta) < 2.5){
			  if(leppt > 10 && leppt < 20) isosf *= 0.984; // +/-0.011
			  else if(leppt < 30) isosf *= 0.997; // +/-0.002
			  else if(leppt < 40) isosf *= 1.000; // +/-0.001
			  else if(leppt < 50) isosf *= 1.019; // +/-0.002
			  else if(leppt < 200) isosf *= 1.000; // +/-0.002
			}
			else isosf *= 1.;
		
			//MVA-based ID scale factors (non-triggering) from Clint Richardson https://indico.cern.ch/event/459111/contribution/1/attachments/1180755/1709309/B2G_Meeting_11.03.2015.pdf
			if(lepeta > -2.5 && lepeta < -1.6){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9880;
			  else if(leppt < 50.) lepidsf *= 0.9663; 
			  else if(leppt < 70.) lepidsf *= 0.9884;
			  else if(leppt < 90.) lepidsf *= 0.9762; 
			  else if(leppt < 130.) lepidsf *= 0.9727; 
			  else if(leppt < 180.) lepidsf *= 0.9978; 
			  else if(leppt < 250.) lepidsf *= 0.9118;
			  else if(leppt < 1000.) lepidsf *= 0.9205;
			} 
			else if(lepeta < -1.4){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9788; 
			  else if(leppt < 50.) lepidsf *= 0.9821; 
			  else if(leppt < 70.) lepidsf *= 0.9567; 
			  else if(leppt < 90.) lepidsf *= 0.9926; 
			  else if(leppt < 130.) lepidsf *= 0.9889; 
			  else if(leppt < 180.) lepidsf *= 1.0034; 
			  else if(leppt < 250.) lepidsf *= 1.1316; 
			  else if(leppt < 1000.) lepidsf *= 1.0000;
			}
			else if(lepeta < -0.8){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9945;
			  else if(leppt < 50.) lepidsf *= 0.9849; 
			  else if(leppt < 70.) lepidsf *= 0.9944;
			  else if(leppt < 90.) lepidsf *= 1.0008; 
			  else if(leppt < 130.) lepidsf *= 1.0077; 
			  else if(leppt < 180.) lepidsf *= 0.9915; 
			  else if(leppt < 250.) lepidsf *= 0.9556; 
			  else if(leppt < 1000.) lepidsf *= 0.9274;
			} 
			else if(lepeta < 0.0){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9923; 
			  else if(leppt < 50.) lepidsf *= 0.9794; 
			  else if(leppt < 70.) lepidsf *= 0.9887; 
			  else if(leppt < 90.) lepidsf *= 0.9742; 
			  else if(leppt < 130.) lepidsf *= 0.9611; 
			  else if(leppt < 180.) lepidsf *= 1.0176; 
			  else if(leppt < 250.) lepidsf *= 0.9990; 
			  else if(leppt < 1000.) lepidsf *= 0.9677;
			} 
			else if(lepeta < 0.8){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9990; 
			  else if(leppt < 50.) lepidsf *= 0.9808; 
			  else if(leppt < 70.) lepidsf *= 0.9657; 
			  else if(leppt < 90.) lepidsf *= 0.9963; 
			  else if(leppt < 130.) lepidsf *= 0.9963; 
			  else if(leppt < 180.) lepidsf *= 0.9725; 
			  else if(leppt < 250.) lepidsf *= 0.9769; 
			  else if(leppt < 1000.) lepidsf *= 0.9334;
			} 
			else if(lepeta < 1.4){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9934; 
			  else if(leppt < 50.) lepidsf *= 0.9814; 
			  else if(leppt < 70.) lepidsf *= 0.9871; 
			  else if(leppt < 90.) lepidsf *= 0.9846; 
			  else if(leppt < 130.) lepidsf *= 0.9545; 
			  else if(leppt < 180.) lepidsf *= 1.0141; 
			  else if(leppt < 250.) lepidsf *= 0.9824; 
			  else if(leppt < 1000.) lepidsf *= 0.9443;
			} 
			else if(lepeta < 1.6){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9771; 
			  else if(leppt < 50.) lepidsf *= 0.9796; 
			  else if(leppt < 70.) lepidsf *= 0.9811; 
			  else if(leppt < 90.) lepidsf *= 1.0291; 
			  else if(leppt < 130.) lepidsf *= 0.9010; 
			  else if(leppt < 180.) lepidsf *= 1.0490; 
			  else if(leppt < 250.) lepidsf *= 0.6082; 
			  else if(leppt < 1000.) lepidsf *= 1.1424;
			} 
			else if(lepeta < 2.5){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9746; 
			  else if(leppt < 50.) lepidsf *= 0.9835; 
			  else if(leppt < 70.) lepidsf *= 0.9868; 
			  else if(leppt < 90.) lepidsf *= 0.9843; 
			  else if(leppt < 130.) lepidsf *= 1.0039; 
			  else if(leppt < 180.) lepidsf *= 0.9597; 
			  else if(leppt < 250.) lepidsf *= 0.9987; 
			  else if(leppt < 1000.) lepidsf *= 1.0271;
			}
			else{lepidsf *= 1.0;}
		  }

		  //////// MUONS
		  if(TightLeptonFlavor_PtOrdered.at(ilep) == 1){

			//Mini-iso < 0.2 SFs from SUSY TWiki
			if(leppt < 40){
			  if(fabs(lepeta) < 0.9) isosf *= 1.000;
			  else if(fabs(lepeta) <  1.2) isosf *= 1.000;
			  else if(fabs(lepeta) <  2.1) isosf *= 0.999;
			  else if(fabs(lepeta) <  2.4) isosf *= 0.999;
			}
			else if(leppt < 50){
			  if(fabs(lepeta) < 0.9) isosf *= 1.000;
			  else if(fabs(lepeta) <  1.2) isosf *= 1.000;
			  else if(fabs(lepeta) <  2.1) isosf *= 0.999;
			  else if(fabs(lepeta) <  2.4) isosf *= 1.000;
			}
			else if(leppt < 60){
			  if(fabs(lepeta) < 0.9) isosf *= 1.000;
			  else if(fabs(lepeta) <  1.2) isosf *= 1.000;
			  else if(fabs(lepeta) <  2.1) isosf *= 1.000;
			  else if(fabs(lepeta) <  2.4) isosf *= 1.000;
			}
			else{
			  if(fabs(lepeta) < 0.9) isosf *= 1.000;
			  else if(fabs(lepeta) <  1.2) isosf *= 0.999;
			  else if(fabs(lepeta) <  2.1) isosf *= 0.998;
			  else if(fabs(lepeta) <  2.4) isosf *= 1.000;
			}
		
			//Cut-based ID scale factors from Clint Richardson https://indico.cern.ch/event/459111/contribution/1/attachments/1180755/1709309/B2G_Meeting_11.03.2015.pdf
			if(lepeta >= -2.4 && lepeta < -2.1){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9812;
			  else if(leppt < 60.) lepidsf *= 0.9793;
			  else if(leppt < 100.) lepidsf *= 0.9600;
			  else if(leppt < 1000.) lepidsf *= 0.9738;
			} 
			else if(lepeta < -1.2){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9910;
			  else if(leppt < 60.) lepidsf *= 0.9922;
			  else if(leppt < 100.) lepidsf *= 0.9923;
			  else if(leppt < 1000.) lepidsf *= 1.0039;
			}
			else if(lepeta < -0.9){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9828;
			  else if(leppt < 60.) lepidsf *= 0.9886;
			  else if(leppt < 100.) lepidsf *= 0.9873;
			  else if(leppt < 1000.) lepidsf *= 0.9876;
			}
			else if(lepeta < -0.4){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9909;
			  else if(leppt < 60.) lepidsf *= 0.9920; 
			  else if(leppt < 100.) lepidsf *= 0.9854;
			  else if(leppt < 1000.) lepidsf *= 0.9951;
			}
			else if(lepeta < 0.0){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9878;
			  else if(leppt < 60.) lepidsf *= 0.9874;
			  else if(leppt < 100.) lepidsf *= 0.9885;
			  else if(leppt < 1000.) lepidsf *= 0.9985;
			}
			else if(lepeta < 0.4){
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9847;
			  else if(leppt < 60.) lepidsf *= 0.9877;
			  else if(leppt < 100.) lepidsf *= 0.9896;
			  else if(leppt < 1000.) lepidsf *= 1.0165;
			}
			else if(lepeta < 0.9){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9869;
			  else if(leppt < 60.) lepidsf *= 0.9898;
			  else if(leppt < 100.) lepidsf *= 0.9875;
			  else if(leppt < 1000.) lepidsf *= 0.9754;
			}
			else if(lepeta < 1.2){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9724;
			  else if(leppt < 60.) lepidsf *= 0.9746;
			  else if(leppt < 100.) lepidsf *= 0.9696;
			  else if(leppt < 1000.) lepidsf *= 0.9757;
			}
			else if(lepeta < 2.1){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9929;
			  else if(leppt < 60.) lepidsf *= 0.9947;
			  else if(leppt < 100.) lepidsf *= 0.9929;
			  else if(leppt < 1000.) lepidsf *= 0.9987;
			}
			else if(lepeta < 2.4){ 
			  if(leppt > 30. && leppt < 40.) lepidsf *= 0.9818;
			  else if(leppt < 60.) lepidsf *= 0.9851;
			  else if(leppt < 100.) lepidsf *= 0.9724;
			  else if(leppt < 1000.) lepidsf *= 1.0028;
			}
			else{lepidsf *=  1.0;} 
		  }
		}
		
		isPastTrig = 1;
		isPastTrigAlt = 1; 
		isPastTrig_trilep = 1;
		isPastTrig_dilep = 1;
		isPastTrig_dilepHT = 1;
		
      }
      else{ //Data triggers check
      	
      	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
      		if(viSelTriggersEl_singleLepCalc->at(itrig) > 0) std::cout << "pass trigger : " << vsSelTriggersEl_singleLepCalc->at(itrig) << endl;
      		}
      	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
      		if(viSelTriggersMu_singleLepCalc->at(itrig) > 0) std::cout << "pass trigger : " << vsSelTriggersMu_singleLepCalc->at(itrig) << endl;
      		}

      	
   		if(isEEE){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_trilep = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
			}
	  	}
   		if(isEEM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_trilep = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
				if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelTriggersEl_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
			}
	  	}
   		if(isEMM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_trilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
			}
	  	}
   		if(isMMM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TripleMu_12_10_5_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_trilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu17_Mu8_SameSign_DZ_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu30_TkMu11_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){ 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT250_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
				if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v1" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v2" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v3" || 
					vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_DoubleMu8_Mass8_PFHT300_v4") && 
					viSelTriggersMu_singleLepCalc->at(itrig) > 0){
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepHT = 1;
				}
			}
	  	}

      	isPastTrigMC = 1;
		isPastTrigMCAlt = 1; 
		isPastTrigMC_trilep = 1;
		isPastTrigMC_dilep = 1;
		isPastTrigMC_dilepHT = 1;

      }
      
      if(isPastTrig) npass_trigger+=1;
               
      float st = ht + corr_met_singleLepCalc;
      if(isPassTrilepton){
		  for(unsigned int ilep = 0; ilep < TightLeptonPt_PtOrdered.size(); ilep++){
			st += TightLeptonPt_PtOrdered.at(ilep);
		  }
      }
      else{ //for ddbkg (just take 3 top leps in All Lepton List.)
		  for(unsigned int ilep = 0; ilep < 3; ilep++){
			st += AllLeptonPt_PtOrdered.at(ilep);
		  }      
      }
//UNCOMMENT LATER! - start
      //count up tags
      int nHtags = 0;      
      int njetsak8 = 0;
      vector<float> maxsubcsv;
      vector<pair<double,int>> jetak8ptindpair;
//UNCOMMENT LATER! - start
//       for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc->size(); ijet++){
// 		maxsubcsv.push_back(-99.0);
// 		if(theJetAK8Pt_JetSubCalc->at(ijet) < 200 || fabs(theJetAK8Eta_JetSubCalc->at(ijet)) > 2.4) continue;
// 		if(theJetAK8NjettinessTau1_JetSubCalc->at(ijet)==0) continue;
// 
// 		njetsak8 += 1; 
// 		jetak8ptindpair.push_back(std::make_pair(theJetAK8Pt_JetSubCalc->at(ijet),ijet));
// 	  
// 		int firstsub = theJetAK8SDSubjetIndex_JetSubCalc->at(ijet);
// 		int nsubs = theJetAK8SDSubjetSize_JetSubCalc->at(ijet);
// 		double maxCSVsubjet = 0;
// 		TLorentzVector tempsubjet;
// 		TLorentzVector sumsubjets; sumsubjets.SetPtEtaPhiM(0,0,0,0);
// 		for(int isub = firstsub; isub < firstsub + nsubs; isub++){
// 		  tempsubjet.SetPtEtaPhiM(theJetAK8SDSubjetPt_JetSubCalc->at(isub),theJetAK8SDSubjetEta_JetSubCalc->at(isub),theJetAK8SDSubjetPhi_JetSubCalc->at(isub),theJetAK8SDSubjetMass_JetSubCalc->at(isub));
// 		  sumsubjets += tempsubjet;
// 		  if(theJetAK8SDSubjetCSV_JetSubCalc->at(isub) > maxCSVsubjet) maxCSVsubjet = theJetAK8SDSubjetCSV_JetSubCalc->at(isub);
// 		  if(isub != firstsub && theJetAK8SDSubjetPt_JetSubCalc->at(isub) == theJetAK8SDSubjetPt_JetSubCalc->at(firstsub)) cout << "subjets have matching pT, something's wrong" << endl;
// 		}
// 		maxsubcsv.at(ijet) = maxCSVsubjet;
// 		if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVMSF_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) nHtags += 1; 
//       }
//UNCOMMENT LATER! - end

      //Pt ordering for AK8
      std::sort(jetak8ptindpair.begin(), jetak8ptindpair.end(), comparepair);
      theJetAK8Pt_JetSubCalc_PtOrdered.clear();
      theJetAK8Eta_JetSubCalc_PtOrdered.clear();
      theJetAK8Phi_JetSubCalc_PtOrdered.clear();
      theJetAK8Energy_JetSubCalc_PtOrdered.clear();
      theJetAK8Mass_JetSubCalc_PtOrdered.clear();
      theJetAK8PrunedMass_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDropMass_JetSubCalc_PtOrdered.clear();
      theJetAK8MaxSubCSV_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetak8ptindpair.size(); ijet++){
      	theJetAK8Pt_JetSubCalc_PtOrdered.push_back(theJetAK8Pt_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Eta_JetSubCalc_PtOrdered.push_back(theJetAK8Eta_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Phi_JetSubCalc_PtOrdered.push_back(theJetAK8Phi_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Energy_JetSubCalc_PtOrdered.push_back(theJetAK8Energy_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Mass_JetSubCalc_PtOrdered.push_back(theJetAK8Mass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8PrunedMass_JetSubCalc_PtOrdered.push_back(theJetAK8PrunedMass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDropMass_JetSubCalc_PtOrdered.push_back(theJetAK8SoftDropMass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8MaxSubCSV_JetSubCalc_PtOrdered.push_back(maxsubcsv.at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau1_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau2_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau3_JetSubCalc->at(jetak8ptindpair[ijet].second));
      }
      
      // Set lepton 4-vectors - NEED TO IMPLEMENT elTrigPresel HERE!!
      double lepM; 
      TLorentzVector lv_temp;
      lepton_lv.clear();
      if(AllLeptonPt_PtOrdered.size()<3) std::cout << "Trilepton cut fail!! will segfault when setting lepton_lv 123!!" << std::endl;
      for (unsigned int ilep=0; ilep < 3 ; ilep++){
//       	std::cout << "AllLeptonPt_PtOrdered.size() : " << AllLeptonPt_PtOrdered.size() << std::endl;
//       	std::cout << "ilep : " << ilep << " AllLeptonPt_PtOrdered : " << AllLeptonPt_PtOrdered.at(ilep) << std::endl;
      	lepM = ( AllLeptonFlavor_PtOrdered[ilep]==0? 0.00051099891:0.105658367);
      	lv_temp.SetPtEtaPhiM(AllLeptonPt_PtOrdered.at(ilep),AllLeptonEta_PtOrdered.at(ilep),AllLeptonPhi_PtOrdered.at(ilep),lepM);
      	lepton_lv.push_back(lv_temp);
//       	std::cout << "lep " << ilep+1 << " , flavor :" <<  AllLeptonFlavor_PtOrdered[ilep] << " , pt : " <<AllLeptonPt_PtOrdered.at(ilep) << " ,  eta : "<<AllLeptonEta_PtOrdered.at(ilep) << " , phi : "<<AllLeptonPhi_PtOrdered.at(ilep) << " , mass : " << lepM << std::endl;
      }
	
      
      //calculate Mll - start
      Mll_sameFlavorOS = -1.;
      if(AllLeptonFlavor_PtOrdered.at(0)==AllLeptonFlavor_PtOrdered.at(1) && AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(1)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(0)+lepton_lv.at(1);
      	Mll_sameFlavorOS = temp.M();
      	std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep0+lep1)" << std::endl;
      	std::cout << "pT1 = " << lepton_lv.at(0).Pt() << " pT2 = " << lepton_lv.at(1).Pt() << std::endl;
      	std::cout << "eta1 = " << lepton_lv.at(0).Eta() << " eta2 = " << lepton_lv.at(1).Eta() << std::endl;

      } 
      else if(AllLeptonFlavor_PtOrdered.at(0)==AllLeptonFlavor_PtOrdered.at(2) && AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(2)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(0)+lepton_lv.at(2);
      	Mll_sameFlavorOS = temp.M();
      	std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep0+lep2)" << std::endl;
      	std::cout << "pT1 = " << lepton_lv.at(0).Pt() << " pT2 = " << lepton_lv.at(2).Pt() << std::endl;
      	std::cout << "eta1 = " << lepton_lv.at(0).Eta() << " eta2 = " << lepton_lv.at(2).Eta() << std::endl;

      } 
      else if(AllLeptonFlavor_PtOrdered.at(1)==AllLeptonFlavor_PtOrdered.at(2) && AllLeptonCharge_PtOrdered.at(1)*AllLeptonCharge_PtOrdered.at(2)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(1)+lepton_lv.at(2);
      	Mll_sameFlavorOS = temp.M();
      	std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep1+lep2)" << std::endl;
      	std::cout << "pT1 = " << lepton_lv.at(1).Pt() << " pT2 = " << lepton_lv.at(2).Pt() << std::endl;
      	std::cout << "eta1 = " << lepton_lv.at(1).Eta() << " eta2 = " << lepton_lv.at(2).Eta() << std::endl;

      }
      else{
      	Mll_sameFlavorOS = -1.;
      	std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << std::endl;      	
      } 
      //calculate Mll - end
      
      
	
      int   nbtagWithSF = 0;
      float leadBJetPt = 0;
      float mindeltar1 = 1e8;
      float mindeltar2 = 1e8;
      float mindeltar3 = 1e8;
      float ptrel_lep1closestjet = -99;
      float ptrel_lep2closestjet = -99;
      float ptrel_lep3closestjet = -99;
      deltaR_lep1Jets.clear();
      deltaR_lep2Jets.clear();
      deltaR_lep3Jets.clear();

      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc_PtOrdered.size(); ijet++){
        jet_lv.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered.at(ijet),theJetEta_JetSubCalc_PtOrdered.at(ijet),theJetPhi_JetSubCalc_PtOrdered.at(ijet),theJetEnergy_JetSubCalc_PtOrdered.at(ijet));

		if(theJetBTag_JetSubCalc_PtOrdered.at(ijet) == 1){
		  nbtagWithSF += 1;
		  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > leadBJetPt) leadBJetPt = theJetPt_JetSubCalc_PtOrdered.at(ijet);
		}
//new format
// 		if(theJetBTag_JetSubCalc_PtOrdered.at(ijet) == 1){
// 		  nbtagWithSF += 1;
// 		  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt) BJetLeadPt = theJetPt_JetSubCalc_PtOrdered.at(ijet);
// 		}
// 		if(theJetBTag_bSFup_JetSubCalc_PtOrdered.at(ijet) == 1){
// 		  NJetsCSVwithSF_JetSubCalc_shifts.at(0) += 1;
// 		  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(0)) BJetLeadPt_shifts.at(0) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
// 		}
// 		if(theJetBTag_bSFdn_JetSubCalc_PtOrdered.at(ijet) == 1){
// 		  NJetsCSVwithSF_JetSubCalc_shifts.at(1) += 1;
// 		  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(1)) BJetLeadPt_shifts.at(1) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
// 		}
// 		if(theJetBTag_lSFup_JetSubCalc_PtOrdered.at(ijet) == 1){
// 		  NJetsCSVwithSF_JetSubCalc_shifts.at(2) += 1;
// 		  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(2)) BJetLeadPt_shifts.at(2) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
// 		}
// 		if(theJetBTag_lSFdn_JetSubCalc_PtOrdered.at(ijet) == 1){
// 		  NJetsCSVwithSF_JetSubCalc_shifts.at(3) += 1;
// 		  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(3)) BJetLeadPt_shifts.at(3) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
// 		}

		deltaR_lep1Jets.push_back(lepton_lv.at(0).DeltaR(jet_lv));
		deltaR_lep2Jets.push_back(lepton_lv.at(1).DeltaR(jet_lv));
		deltaR_lep3Jets.push_back(lepton_lv.at(2).DeltaR(jet_lv));
		if(deltaR_lep1Jets[ijet] < mindeltar1) {
// 		  std::cout<< "pre mindeltar1 = " << mindeltar1 << std::endl;		
		  mindeltar1 = deltaR_lep1Jets[ijet];
// 		  std::cout<< "post mindeltar1 = " << mindeltar1 << std::endl;
		  ptrel_lep1closestjet = lepton_lv.at(0).P()*(jet_lv.Vect().Cross(lepton_lv.at(0).Vect()).Mag()/jet_lv.P()/lepton_lv.at(0).P());
		  
		}
		if(deltaR_lep2Jets[ijet] < mindeltar2) {
// 		  std::cout<< "pre mindeltar2 = " << mindeltar2 << std::endl;		
		  mindeltar2 = deltaR_lep2Jets[ijet];
// 		  std::cout<< "post mindeltar2 = " << mindeltar2 << std::endl;
		  ptrel_lep2closestjet = lepton_lv.at(1).P()*(jet_lv.Vect().Cross(lepton_lv.at(1).Vect()).Mag()/jet_lv.P()/lepton_lv.at(1).P());
		}
		if(deltaR_lep3Jets[ijet] < mindeltar3) {
// 		  std::cout<< "pre mindeltar3 = " << mindeltar3 << std::endl;		
		  mindeltar3 = deltaR_lep3Jets[ijet];
// 		  std::cout<< "post mindeltar3 = " << mindeltar3 << std::endl;		
		  ptrel_lep3closestjet = lepton_lv.at(2).P()*(jet_lv.Vect().Cross(lepton_lv.at(2).Vect()).Mag()/jet_lv.P()/lepton_lv.at(2).P());
		}

      
      }

      //8TeV Top Pt Reweighting
      float gen_tpt = -999;
      float gen_anti_tpt = -999;
      for(unsigned int ijet=0; ijet < topPt_TTbarMassCalc->size(); ijet++){
		if(gen_tpt < 0 && topID_TTbarMassCalc->at(ijet) == 6) gen_tpt = topPt_TTbarMassCalc->at(ijet);
		if(gen_anti_tpt < 0 && topID_TTbarMassCalc->at(ijet) == -6) gen_anti_tpt = topPt_TTbarMassCalc->at(ijet);
      }
      
      float toppt_temp = gen_tpt;
      if(gen_tpt > 400) toppt_temp = 400;
      float antitoppt_temp = gen_anti_tpt;
      if(gen_anti_tpt > 400) antitoppt_temp = 400;
      
      float SFtop = TMath::Exp(0.156-0.00137*toppt_temp); // using 8TeV TopPtReweighting: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
      float SFantitop = TMath::Exp(0.156-0.00137*antitoppt_temp);
      float weight_toppt = TMath::Sqrt(SFtop*SFantitop)/0.99277; //0.99277-->average weight
      
      float SFtopPast400 = TMath::Exp(0.156-0.00137*gen_tpt);
      float SFantitopPast400 = TMath::Exp(0.156-0.00137*gen_anti_tpt);
      float weightPast400_toppt = TMath::Sqrt(SFtopPast400*SFantitopPast400)/0.9927;

      float SFtopHighPt = 0.98  - 0.00026*gen_tpt;  // 0.98 +- 0.24, 0.0026 +- 0.00039
      float SFantitopHighPt = 0.98  - 0.00026*gen_anti_tpt;
      float weightHighPt_toppt = TMath::Sqrt(SFtopHighPt*SFantitopHighPt);

      
      int nWtags = 0;
      NJetsWtagged_0p6 = 0;
      leadWJetPtak8 = -99.0;

      NJetsWtagged_0p6_shifts.clear();
      theJetAK8Wmatch_JetSubCalc_PtOrdered.clear();
      leadWJetPtak8_shifts.clear();
      WJetTaggedPt.clear();
      WJetTaggedPtJMRup.clear();
      WJetTaggedPtJMRdn.clear();
      WJetTaggedPtJMSup.clear();
      WJetTaggedPtJMSdn.clear();
      WJetTaggedPtTAUup.clear();
      WJetTaggedPtTAUdn.clear();
      theJetAK8PrunedMassJMRSmeared_JetSubCalc.clear();
      theJetAK8PrunedMassJMRSmearedUp_JetSubCalc.clear();
      theJetAK8PrunedMassJMRSmearedDn_JetSubCalc.clear();

      wjet1_lv.SetPtEtaPhiM(0,0,0,0);
      ak8_lv.SetPtEtaPhiM(0,0,0,0);

      for(int i = 0; i < 6; i++){
	NJetsWtagged_0p6_shifts.push_back(0);
	leadWJetPtak8_shifts.push_back(-99.0);
      }

      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc_PtOrdered.size(); ijet++){
	
	ak8_lv.SetPtEtaPhiE(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),theJetAK8Energy_JetSubCalc_PtOrdered.at(ijet));

	float tau21 = theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.at(ijet);
	float mass = theJetAK8PrunedMass_JetSubCalc_PtOrdered.at(ijet);

	if(tau21 < 0.6 && mass > 65.0 && mass < 105.0) nWtags += 1;

	//Wtagging with jet mass resolution smearing	
	//Jet Mass Resolution smearing: sqrt(c^2-1)*sigma_MC, where c = 1.12 +/- 0.07, sigma_MC = 7.3+/-0.4 // current values are from "AN2015_196_v7"
	//Smear nominal with sqrt(c^2-1)*sigma_MC = ~3.7, where c = 1.12 and sigma_MC = 7.3
	//+1sigma with sqrt(c^2-1)*sigma_MC = ~4.7, where c = 1.19 and sigma_MC = 7.3
	//-1sigma with sqrt(c^2-1)*sigma_MC = ~2.3, where c = 1.05 and sigma_MC = 7.3
	//
	//Jet Mass Scale: 1.011 +/- 0.016 with 1.6% uncertainty
	//1sigma up  : smeared pruned mass * 1.0270
	//1sigma down: smeared pruned mass * 0.0995
	
	float AK8massScale=1.0; //nominal (scale factor is consistent with one)
	float AK8massScaleUp=0.997; //scale up
	float AK8massScaleDn=0.987; //scale down
	float AK8massSmear=3.7; //nominal
	float AK8massSmearUp=4.7; //1sigma up
	float AK8massSmearDn=2.3; //1sigma down

	float gran = gRandom->Gaus(0, AK8massSmear);
	float granUp = gRandom->Gaus(0, AK8massSmearUp);
	float granDn = gRandom->Gaus(0, AK8massSmearDn);
	float prunedMassSmeared = (mass+gran)*AK8massScale;
	float prunedMassSmearedUp = (mass+granUp)*AK8massScale;
	float prunedMassSmearedDn = (mass+granDn)*AK8massScale;
	float prunedMassSmearedScaleUp = (mass+gran)*AK8massScaleUp;
	float prunedMassSmearedScaleDn = (mass+gran)*AK8massScaleDn;
	float tau0p6SF = 1.0;
	float tau0p6SFup = 1.0;
	float tau0p6SFdn = 1.0;

	if(isMC){
	  theJetAK8PrunedMassJMRSmeared_JetSubCalc.push_back(prunedMassSmeared);
	  theJetAK8PrunedMassJMRSmearedUp_JetSubCalc.push_back(prunedMassSmearedUp);
	  theJetAK8PrunedMassJMRSmearedDn_JetSubCalc.push_back(prunedMassSmearedDn);

	  float minDR = 1000;
	  float matchedPt= -99;
	  bool ismatched = false;
	  TLorentzVector trueW;

//UNCOMMENT LATER! - start
// 	  for(unsigned int iW = 0; iW < WPt_JetSubCalc->size(); iW++){
// 	    if(WPt_JetSubCalc->at(iW) < 200) continue;
// 
// 	    trueW.SetPtEtaPhiE(WPt_JetSubCalc->at(iW),WEta_JetSubCalc->at(iW),WPhi_JetSubCalc->at(iW),WEnergy_JetSubCalc->at(iW));
// 	    if(ak8_lv.DeltaR(trueW) < minDR){
// 	      minDR = ak8_lv.DeltaR(trueW);
// 	      matchedPt = WPt_JetSubCalc->at(iW);
// 	    }
//    	  }	 
//UNCOMMENT LATER! - end
	  if(minDR < 0.8) ismatched = true;

	  double coin = gRandom->Rndm();

	  // SCALE FACTOR ONLY USED ON MATCHED JETS
	  double tau0p6Eff = 1.0;
	  if(ismatched){	    
	    tau0p6SF = 1.03;
	    tau0p6SFup = 1.16;
	    tau0p6SFdn = 0.90;
	  
	    // Use matched W to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
	    if(isSig){
	      int bin = (std::upper_bound(ptRangeTpTp.begin(), ptRangeTpTp.end(), matchedPt)-ptRangeTpTp.begin())-1;
	      tau0p6Eff = SignalEff[bin];
	    }else{
	      int bin = (std::upper_bound(ptRangeTTbar.begin(), ptRangeTTbar.end(), matchedPt)-ptRangeTTbar.begin())-1;
	      tau0p6Eff = TTbarEff[bin];
	    }
	  }

	  // Set the initial tagged/untagged state
	  int tag_JMS_JMR_tau0p6 = (prunedMassSmeared > 65) && (prunedMassSmeared < 105) && (tau21 < 0.6);
	  int tag_JMSup_JMR_tau0p6 = (prunedMassSmeared*AK8massScaleUp > 65) && (prunedMassSmeared*AK8massScaleUp < 105) && (tau21 < 0.6);
	  int tag_JMSdn_JMR_tau0p6 = (prunedMassSmeared*AK8massScaleDn > 65) && (prunedMassSmeared*AK8massScaleDn < 105) && (tau21 < 0.6);
	  int tag_JMS_JMRup_tau0p6 = (prunedMassSmearedUp > 65) && (prunedMassSmearedUp < 105) && (tau21 < 0.6);
	  int tag_JMS_JMRdn_tau0p6 = (prunedMassSmearedDn > 65) && (prunedMassSmearedDn < 105) && (tau21 < 0.6);
	  int tag_JMS_JMR_tau0p6up = (prunedMassSmeared > 65) && (prunedMassSmeared < 105) && (tau21 < 0.6);
	  int tag_JMS_JMR_tau0p6dn = (prunedMassSmeared > 65) && (prunedMassSmeared < 105) && (tau21 < 0.6);
 
	  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
	  // For 0p6 central and up-shift scale factor, only care about > 1 case and "upgrading" tags
	  if(tau0p6SF > 1){
	    float mistagpercent = (1.0 - tau0p6SF) / (1.0 - (tau0p6SF/tau0p6Eff));
	    if(tag_JMS_JMR_tau0p6 == 0 && coin < mistagpercent) tag_JMS_JMR_tau0p6 = 1;	    
	    if(tag_JMSup_JMR_tau0p6 == 0 && coin < mistagpercent) tag_JMSup_JMR_tau0p6 = 1;	    
	    if(tag_JMSdn_JMR_tau0p6 == 0 && coin < mistagpercent) tag_JMSdn_JMR_tau0p6 = 1;	    
	    if(tag_JMS_JMRup_tau0p6 == 0 && coin < mistagpercent) tag_JMS_JMRup_tau0p6 = 1;	    
	    if(tag_JMS_JMRdn_tau0p6 == 0 && coin < mistagpercent) tag_JMS_JMRdn_tau0p6 = 1;	    
	  }
	  if(tau0p6SFup > 1){
	    float mistagpercent = (1.0 - tau0p6SF) / (1.0 - (tau0p6SF/tau0p6Eff));
	    if(tag_JMS_JMR_tau0p6up == 0 && coin < mistagpercent) tag_JMS_JMR_tau0p6up = 1;	    
	  }
	  // For 0p6 down-shifted scale factor, only care about < 1 case and "downgrading" tags
	  if(tau0p6SFdn < 1){
	    if(tag_JMS_JMR_tau0p6dn == 1 && coin > tau0p6SF) tag_JMS_JMR_tau0p6dn = 0;
	  }

	  // Now increase the tag count in the right variable	  
	  NJetsWtagged_0p6 += tag_JMS_JMR_tau0p6;
	  NJetsWtagged_0p6_shifts[0] += tag_JMS_JMRup_tau0p6;
	  NJetsWtagged_0p6_shifts[1] += tag_JMS_JMRdn_tau0p6;
	  NJetsWtagged_0p6_shifts[2] += tag_JMSup_JMR_tau0p6;
	  NJetsWtagged_0p6_shifts[3] += tag_JMSdn_JMR_tau0p6;
	  NJetsWtagged_0p6_shifts[4] += tag_JMS_JMR_tau0p6up;
	  NJetsWtagged_0p6_shifts[5] += tag_JMS_JMR_tau0p6dn;

	  if(NJetsWtagged_0p6 == 1) leadWJetPtak8 = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  if(NJetsWtagged_0p6_shifts[0] == 1) leadWJetPtak8_shifts[0] = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  if(NJetsWtagged_0p6_shifts[1] == 1) leadWJetPtak8_shifts[1] = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  if(NJetsWtagged_0p6_shifts[2] == 1) leadWJetPtak8_shifts[2] = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  if(NJetsWtagged_0p6_shifts[3] == 1) leadWJetPtak8_shifts[3] = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  if(NJetsWtagged_0p6_shifts[4] == 1) leadWJetPtak8_shifts[4] = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  if(NJetsWtagged_0p6_shifts[5] == 1) leadWJetPtak8_shifts[5] = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);

	}else{
	  
	  if(tau21 < 0.6 && mass > 65.0 && mass < 105.0){
	    NJetsWtagged_0p6 += 1;
	    leadWJetPtak8 = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  }
	}
      }

      TLorentzVector leadak8;
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 2) minDR_leadAK8otherAK8 = -99.0;
      else{
	leadak8.SetPtEtaPhiE(theJetAK8Pt_JetSubCalc_PtOrdered.at(0),theJetAK8Eta_JetSubCalc_PtOrdered.at(0),theJetAK8Phi_JetSubCalc_PtOrdered.at(0),theJetAK8Energy_JetSubCalc_PtOrdered.at(0));
	minDR_leadAK8otherAK8 = 1000;
      
	for(unsigned int ijet = 1; ijet < theJetAK8Pt_JetSubCalc_PtOrdered.size(); ijet++){
	  ak8_lv.SetPtEtaPhiE(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),theJetAK8Energy_JetSubCalc_PtOrdered.at(ijet));
	  
	  float tempdr = leadak8.DeltaR(ak8_lv);
	  if(tempdr < minDR_leadAK8otherAK8){
	    minDR_leadAK8otherAK8 = tempdr;
	  }
	}
      }

      //PDF and RENORM weights
      std::vector<double> renorm;
      std::vector<double> pdf;
      renormWeights.clear();
      pdfWeights.clear();
      if(isSig){
	// SEEMS TO APPLY TO ALL B2G MG+PYTHIA SIGNALS. LEADING ORDER 4-FLAVOR PDF
	for(unsigned int i = 0; i < LHEWeightids_singleLepCalc->size(); i++){
	  if(LHEWeightids_singleLepCalc->at(i) > 1 && LHEWeightids_singleLepCalc->at(i) < 10){
	    if(LHEWeightids_singleLepCalc->at(i) == 6 || LHEWeightids_singleLepCalc->at(i) == 8) continue;
	    renorm.push_back(LHEWeights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEWeights_singleLepCalc->at(i));
	  }
	  if(LHEWeightids_singleLepCalc->at(i) > 111 && LHEWeightids_singleLepCalc->at(i) < 212){
	    pdf.push_back(LHEWeights_singleLepCalc->at(i));	    
	    pdfWeights.push_back(LHEWeights_singleLepCalc->at(i));	    
	  }
	}
      }
      else if(isMadgraphBkg){
	// SEEMS TO APPLY TO OTHER MG+PYTHIA BACKGROUNDS. LEADING ORDER 5-FLAVOR PDF
	for(unsigned int i = 0; i < LHEWeightids_singleLepCalc->size(); i++){
	  if(LHEWeightids_singleLepCalc->at(i) > 1 && LHEWeightids_singleLepCalc->at(i) < 10){
	    if(LHEWeightids_singleLepCalc->at(i) == 6 || LHEWeightids_singleLepCalc->at(i) == 8) continue;
	    renorm.push_back(LHEWeights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEWeights_singleLepCalc->at(i));
	  }
	  if(LHEWeightids_singleLepCalc->at(i) > 10 && LHEWeightids_singleLepCalc->at(i) < 111){
	    pdf.push_back(LHEWeights_singleLepCalc->at(i));
	    pdfWeights.push_back(LHEWeights_singleLepCalc->at(i));
	  }
	}
      }
      else{
	// SEEMS TO APPLY TO ALL POWHEG AND MC@NLO BACKGROUNDS. NLO PDFs
	for(unsigned int i = 0; i < LHEWeightids_singleLepCalc->size(); i++){
	  if(LHEWeightids_singleLepCalc->at(i) > 1001 && LHEWeightids_singleLepCalc->at(i) < 1010){
	    if(LHEWeightids_singleLepCalc->at(i) == 1006 || LHEWeightids_singleLepCalc->at(i) == 1008) continue;
	    renorm.push_back(LHEWeights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEWeights_singleLepCalc->at(i));
	  }
	  if(LHEWeightids_singleLepCalc->at(i) > 2000 && LHEWeightids_singleLepCalc->at(i) < 2101){
	    pdf.push_back(LHEWeights_singleLepCalc->at(i));
	    pdfWeights.push_back(LHEWeights_singleLepCalc->at(i));
	  }
	  if(LHEWeightids_singleLepCalc->at(i) == 2101 || LHEWeightids_singleLepCalc->at(i) == 2102){
	    alphaSWeights.push_back(LHEWeights_singleLepCalc->at(i));
	  }
	}
      }

      if(renormWeights.size() == 0){
	for(int irn = 0; irn < 6; irn++){
	  renormWeights.push_back(1.0);
	}
      }
      if(pdfWeights.size() == 0){
	for(int ipdf = 0; ipdf < 100; ipdf++){
	  pdfWeights.push_back(1.0);
	}
      }
           
      BJetLeadPt_JetSubCalc = (float) leadBJetPt;
      WJetLeadPt_JetSubCalc = (float) leadWJetPtak8;
      AK4HTpMETpLepPt       = (float) st;
      AK4HT                 = (float) ht;
      NJets_JetSubCalc      = (int) njets;
      NJetsAK8_JetSubCalc   = (int) njetsak8;
      NJetsCSV_JetSubCalc   = (int) nbtags;
      NJetsCSVwithSF_JetSubCalc = (int) nbtagWithSF;
      NJetsHtagged          = (int) nHtags;
      
      pileupWeight          = (float) puweight;
      pileupWeight72ub      = (float) puweight72ub;
      pileupWeightUp        = (float) puweightup;
      pileupWeightDown      = (float) puweightdown;
      TrigEffWeight         = (float) TrigEff;
      isoSF                 = (float) isosf;
      lepIdSF               = (float) lepidsf;
      MCPastTrigger         = (int)   isPastTrigMC;
      MCPastTriggerAlt      = (int)   isPastTrigMCAlt;
      DataPastTrigger       = (int)   isPastTrig;
      DataPastTriggerAlt    = (int)   isPastTrigAlt;

      MCPastTrigger_dilep         = (int)   isPastTrigMC_dilep;
      DataPastTrigger_dilep       = (int)   isPastTrig_dilep;
      MCPastTrigger_dilepHT         = (int)   isPastTrigMC_dilepHT;
      DataPastTrigger_dilepHT       = (int)   isPastTrig_dilepHT;
      MCPastTrigger_trilep         = (int)   isPastTrigMC_trilep;
      DataPastTrigger_trilep       = (int)   isPastTrig_trilep;

      genTopPt       = (float) gen_tpt;
      genAntiTopPt   = (float) gen_anti_tpt;
      topPtWeight    = (float) weight_toppt;
      topPtWeightPast400    = (float) weightPast400_toppt;
      topPtWeightHighPt    = (float) weightHighPt_toppt;
      
      deltaR_lepClosestJet.clear();
      PtRelLepClosestJet.clear();
      deltaR_lepClosestJet.push_back( (float) mindeltar1 );
      deltaR_lepClosestJet.push_back( (float) mindeltar2 );
      deltaR_lepClosestJet.push_back( (float) mindeltar3 );

      PtRelLepClosestJet.push_back( (float) ptrel_lep1closestjet );
      PtRelLepClosestJet.push_back( (float) ptrel_lep2closestjet );
      PtRelLepClosestJet.push_back( (float) ptrel_lep3closestjet );


      outputTree->Fill();
   }
   std::cout<<"Npassed_Trigger(DATA)  = "<<npass_trigger<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MET            = "<<npass_met<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_nJets          = "<<npass_njets<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_JetLeadPt      = "<<npass_JetLeadPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL            = "<<npass_all<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL_Triplepton            = "<<nPassTrilepton<<" / "<<nentries<<std::endl;
	printf("Counts of eee: LLL(%i), LLT(%i), LTT(%i), TTT(%i)\n", Neee[0], Neee[1], Neee[2], Neee[3]);
	printf("Counts of eem: LLL(%i), LLT(%i), LTL(%i), LTT(%i), TTL(%i), TTT(%i)\n", Neem[0], Neem[1], Neem[2], Neem[3], Neem[4], Neem[5]);
	printf("Counts of emm: LLL(%i), TLL(%i), LLT(%i), TLT(%i), LTT(%i), TTT(%i)\n", Nemm[0], Nemm[1], Nemm[2], Nemm[3], Nemm[4], Nemm[5]);
	printf("Counts of mmm: LLL(%i), LLT(%i), LTT(%i), TTT(%i)\n", Nmmm[0], Nmmm[1], Nmmm[2], Nmmm[3]);

   outputTree->Write();

}