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

using namespace std;

bool comparepair( const std::pair<double,int> a, const std::pair<double,int> b) { return a.first > b.first; }

TRandom * gRandom = new TRandom3();

const double MTOP  = 173.5;
const double MW    = 80.4; 

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
   
   //electrons
   inputTree->SetBranchStatus("elPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elEta_singleLepCalc",1);
   inputTree->SetBranchStatus("elPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("elEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("elMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elMVAValue_singleLepCalc",1);
   
   //muons
   inputTree->SetBranchStatus("muPt_singleLepCalc",1);
   inputTree->SetBranchStatus("muEta_singleLepCalc",1);
   inputTree->SetBranchStatus("muPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("muEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("muMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsTight_singleLepCalc",1);
   
   //missing et
   inputTree->SetBranchStatus("corr_met_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_met_phi_singleLepCalc",1);

   //jets
   inputTree->SetBranchStatus("AK4JetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetEnergy_singleLepCalc",1);
   
   
   // OUTPUT FILE
   outputFile->cd();
   NLooseTightEl = new TH1D("NLooseTightEl","",2,0,2);
   NLooseTightMu = new TH1D("NLooseTightMu","",2,0,2);
   
   // basic cuts
   float metCut=25;
   float lepPtMin=25;
   float lepPtMax=35;
      
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
   
   int npass_met          = 0;
   int npass_Jets         = 0;
   int npass_lepPt        = 0;
   int npass_MT           = 0;
   int npass_all          = 0;
   int Nelectrons         = 0;
   int Nmuons             = 0;

   TLorentzVector lepton_lv;
   TLorentzVector jet_lv;

   cout << "RUN CONFIG: " << endl;
   cout << "isSig = " << isSig << ", isTOP = " << isTOP << ", isMC = " << isMC << endl;
   
   Long64_t nentries = inputTree->GetEntriesFast();

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (Cut(ientry) != 1) continue;
      
      //      if (ientry > 5000) continue;
      
      if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;


      //CSC filter (aka muon halo filter) NOTE: filtering data sets by running both SE and SM CSC filters!
      bool filterEvent = false;
      for(unsigned int i=0; i < CSC_run.size(); i++){
      	if(CSC_run[i]==run_CommonCalc && CSC_ls[i]==lumi_CommonCalc && CSC_event[i]==event_CommonCalc) filterEvent = true;
      }
      for(unsigned int i=0; i < ECALSC_run.size(); i++){
      	if(ECALSC_run[i]==run_CommonCalc && ECALSC_ls[i]==lumi_CommonCalc && ECALSC_event[i]==event_CommonCalc) filterEvent = true;
      }
      if(filterEvent) continue;
     	     
      int isE = 0;
      int isM = 0;
      int leplvSetsCheck = 0;
      int muIsTight = -1;
      double muMiniIso = -1;
      double elMiniIso = -1;
      double elMVAValue = -1;
      
      lepton_lv.SetPtEtaPhiM(0,0,0,0);

      for(unsigned int iel = 0; iel < elPt_singleLepCalc->size(); iel++){
	if(elPt_singleLepCalc->at(iel) >= lepPtMin && elPt_singleLepCalc->at(iel) <= lepPtMax){
	  isE++;
	  leplvSetsCheck++;
	  lepton_lv.SetPtEtaPhiM(elPt_singleLepCalc->at(iel),elEta_singleLepCalc->at(iel),elPhi_singleLepCalc->at(iel),0.00051099891);
	  elMiniIso = elMiniIso_singleLepCalc->at(iel);
	  elMVAValue = elMVAValue_singleLepCalc->at(iel);
	}
      }
      for(unsigned int imu = 0; imu < muPt_singleLepCalc->size(); imu++){
	if(muPt_singleLepCalc->at(imu) >= lepPtMin && muPt_singleLepCalc->at(imu) <= lepPtMax){
	  isM++;
	  leplvSetsCheck++;
	  lepton_lv.SetPtEtaPhiM(muPt_singleLepCalc->at(imu),muEta_singleLepCalc->at(imu),muPhi_singleLepCalc->at(imu),0.105658367);
	  muIsTight = muIsTight_singleLepCalc->at(imu);
	  muMiniIso = muMiniIso_singleLepCalc->at(imu);
	}
      }

      if(isE > 0 && isM > 0) continue;
      if(isE == 0 && isM == 0) continue;
      if(isE > 1 || isM > 1) continue;

      if(leplvSetsCheck != 1) cout << "lepton_lv was set more than once, something's wrong" << endl;

      double MT_lepMet = sqrt(2*lepton_lv.Pt()*corr_met_singleLepCalc*(1 - cos(lepton_lv.Phi() - corr_met_phi_singleLepCalc)));

      bool hasLepJetZ = false;
      bool hasAwayJet = false;
      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc->size(); ijet++){
	jet_lv.SetPtEtaPhiE(AK4JetPt_singleLepCalc->at(ijet),AK4JetEta_singleLepCalc->at(ijet),AK4JetPhi_singleLepCalc->at(ijet),AK4JetEnergy_singleLepCalc->at(ijet));

	if(lepton_lv.DeltaR(jet_lv) > 1.0) hasAwayJet = true;

	double MlepJet = (lepton_lv + jet_lv).M();
	if(MlepJet > 81 || MlepJet < 101) hasLepJetZ = true;

      }

      int isPastJetsCut = 0;
      if(hasAwayJet && !hasLepJetZ){npass_Jets += 1; isPastJetsCut = 1;}

      int isPastMETcut = 0;
      if(corr_met_singleLepCalc < metCut){npass_met+=1; isPastMETcut=1;}

      int isPastLepPtCut = 0;
      npass_lepPt+=1; isPastLepPtCut=1;

      int isPastMTCut = 0;
      if(MT_lepMet < 25){npass_MT+=1; isPastMTCut=1;}      

      // check all the cuts!
      if(!(isPastMETcut && isPastJetsCut && isPastLepPtCut && isPastMTCut)) continue;
      npass_all+=1;

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /////////////// ONLY ON SELECTED EVENTS ////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      bool isTightEl = false;
      bool isTightMu = false;
      if(isE){
	if(elMiniIso < 0.1){
	  if(fabs(lepton_lv.Eta()) <= 0.8 && elMVAValue > 0.967083) isTightEl = true;
	  else if(fabs(lepton_lv.Eta()) <= 1.479 && elMVAValue > 0.929117) isTightEl = true;
	  else if(fabs(lepton_lv.Eta()) <= 2.5 && elMVAValue > 0.726311) isTightEl = true;
	}
      }

      if(isM){
	if(muIsTight > 0 && muMiniIso < 0.2) isTightMu = true;
      }

      if(isE){
	NLooseTightEl->Fill(0);
	if(isTightEl) NLooseTightEl->Fill(1);
      }
      if(isM){
	NLooseTightMu->Fill(0);
	if(isTightMu) NLooseTightMu->Fill(1);
      }
   }
   std::cout<<"Npassed_MET            = "<<npass_met<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_Jets           = "<<npass_Jets<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_lepPt          = "<<npass_lepPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MT             = "<<npass_MT<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL            = "<<npass_all<<" / "<<nentries<<std::endl;

   NLooseTightEl->Write();
   NLooseTightMu->Write();

}
