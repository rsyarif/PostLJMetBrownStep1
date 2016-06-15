#ifndef _FAKERATE_H
#define _FAKERATE_H
#include <TRandom2.h>
#include "Math/Random.h"
#include <iostream>
#include "CMSStyle.C"

#include "TStyle.h"
#include "TColor.h"
#include "TFile.h"
#include <TH1F.h>
#include <TH2.h>
#include "TCanvas.h"

using namespace std;

float Pr(int mode,std::vector<double> lep_info);
inline float uPr(std::vector<double> lep_info);
float Fr(int mode,std::vector<double> lep_info);
inline float uFr(std::vector<double> lep_info);

inline float uQe();

inline double epsilon(double f);//these are guearenteed to be small numbers
inline double eta(double p);//these are guearenteed to be small numbers

inline int frModeBehavior(int mode);
inline int prModeBehavior(int mode);
inline int qeModeBehavior(int mode);


std::vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);

double ChiSquared(int k);
int ThrowPoissonFromMeasurement(TRandom2* r, int n);


/////////////////// Tripple electron ////////////////////////
double GetWeight(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info);

double W_ttt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_ttl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_tlt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_ltt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_tll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_ltl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_llt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_lll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );

/////////////////////////////

// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_El_PtEta.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_Mu_PtEta.root");

TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_PtEta.root");
TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_PtEta.root");

// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_Pt_1bin.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_Pt_1bin.root");


TCanvas* c_el = (TCanvas*) file_el->Get("c1");
TCanvas* c_mu = (TCanvas*) file_mu->Get("c1");
TH2D *h_el = (TH2D*) c_el->GetPrimitive("newratioEl");
TH2D *h_mu = (TH2D*) c_mu->GetPrimitive("newratioMu");


float Pr(int mode, std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele prompt rate
// 		std::cout << "Ele: Mode: " << mode << ", " << prModeBehavior(mode) << " * uPr: " << uPr(lep_info)<< endl;
		return 0.87 + uPr(lep_info)*prModeBehavior(mode); //from anthony
// 		return 0.873 + uPr(lep_info)*prModeBehavior(mode); // Clints

	}
	else{
		//muon prompt rate
// 		std::cout << "Mu: Mode: " << mode << ", " << prModeBehavior(mode) << " * uPr: " << uPr(lep_info)<< endl;
		return 0.9836 + uPr(lep_info)*prModeBehavior(mode); //from anthony
// 		return 0.940 + uPr(lep_info)*prModeBehavior(mode); //Clints
	}
}
	
float Fr(int mode, std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele fake rate
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);
		double weight = 0.0;
		if(pt_el>0 && fabs(eta_el)<2.4){
			weight = h_el->GetBinContent(h_el->GetXaxis()->FindBin(pt_el),h_el->GetYaxis()->FindBin(fabs(eta_el)));
		}
		else{
			weight =  1.;	
		}
// 		std::cout << "Ele -- " << ", pt: " << pt_el << ", eta: " << eta_el << ", weight = " << weight << std::endl; 
// 		std::cout << "Ele: Mode: " << mode << ", " << frModeBehavior(mode) << " * uFr: " << uFr(lep_info)<< endl;
		return 0.3305 + uFr(lep_info)*frModeBehavior(mode); //our calculation
// 		return weight + uFr(lep_info)*frModeBehavior(mode);
// 		return 0.298 + uFr(lep_info)*frModeBehavior(mode); //Clints


	}
	else{
		//muon fake rate
		double pt_mu = lep_info.at(2);
		double eta_mu = lep_info.at(3);
		double weight = 0.0;
		if(pt_mu>0 && fabs(eta_mu)<2.4){
			weight = h_mu->GetBinContent(h_mu->GetXaxis()->FindBin(pt_mu),h_mu->GetYaxis()->FindBin(fabs(eta_mu)));
		}
		else{
			weight =  1.;	
		}
// 		std::cout << "Mu -- " << ", pt: " << pt_mu << ", eta: " << eta_mu << ", weight = " << weight << std::endl; 
// 		std::cout << "Mu: Mode: " << mode << ", " << frModeBehavior(mode) << " * uFr: " << uFr(lep_info)<< endl;
		return 0.4673 + uFr(lep_info)*frModeBehavior(mode); //our calculation
// 		return weight + uFr(lep_info)*frModeBehavior(mode);
// 		return 0.371 + uFr(lep_info)*frModeBehavior(mode); //Clints
	}
}

inline float uPr(std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele prompt rate unc
		return 0.005; //from anthony
// 		return 0.001; //Clints
	}
	else{
		//mu prompt rate unc
		return 0.0003; //from anthony
// 		return 0.001; //Clints
	}
}

inline float uFr(std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele fake rate unc
		return 0.017; //our calculation
// 		return 0.003; //Clints
	}
	else{
		//mu fake rate unc
		return 0.0016; //our calculation
// 		return 0.002; //Clints
	}
}


inline float uQe(){return 0.30;}//percent

inline double epsilon(double f){return f/(1.0-f);} 
inline double eta(double p){return (1.0-p)/p;}


//    ____  
//   |___ \
//     __) |
//    |__ < 
//    ___) |
//   |____/ 
//          
//          


std::vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
	//Calculates all prompt and fake bkg info for Same Flavor trilepton events 
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
	//This is taken from AN-10-261_v1 Section 4
	//N_t0 is #events with all 3 loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other 2 passing tight
	//N_t2 is #events with two  loose leptons failing tight and the other one passing tight
	//N_t3 is #events with all 3 loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	//N_fff is the loose leptons from three non-prompt fakes. 
	//N_ffp is the loose leptons with one real lepton and two fakes.
	//N_fpp is the loose leptons with two real lepton and one fakes.
	//N_ppp is the number of true tri-lepton events passing loose 
	//N_signal is the number of true tri-leptons all passing tight
	//N_1fake  is the number of events passing tight-tight with one fake lepton
	//N_2fake  is the number of events passing tight-tight with two fake lepton 
	//N_3fake  is the number of events passing tight-tight with all three leptons fake
	//N_bkg = N_1fake + N_2fake + N_3fakes is the number of events passing tight that are not from two real leptons.
	double div = 1.0/pow(p-f,3);
	double omf = 1.0-f;	
	double omp = 1.0-p;
	std::vector<double> out;	
	out.push_back(div*(omf*omf*omf*N_t0 - f*omf*omf*N_t2 + f*f*omf*N_t1 - f*f*f*N_t0)); //N_ppp 0
	out.push_back(div*( 3.0*p*f*f*N_t0 - (f*f*omp + 2.0*p*f*omf)*N_t1 + (2.0*f*omp*omf + p*omf*omf)*N_t2 - 3.0*omp*omf*omf*N_t3) );//N_fpp 1
	out.push_back(div*(-3.0*p*p*f*N_t0 + (2.0*p*f*omp + p*p*omf)*N_t1 - (f*omp*omp + 2.0*p*omp*omf)*N_t2 + 2.0*omp*omp*omf*N_t3) );//N_ffp 2
	out.push_back(div*(p*p*p*N_t0 - p*p*omp*N_t1 + p*omp*omp*N_t2 - omp*omp*omp*N_t3));// N_fff 3
	out.push_back(p*p*p*out[0]); //4
	out.push_back(p*p*f*out[1]); //5
	out.push_back(p*f*f*out[2]); //6
	out.push_back(f*f*f*out[3]); //7
	out.push_back(out[5] + out[6] + out[7]);
	return out;
}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
	//returns  the number of tight tri-lepton events with at least one fake object (N_bkg from SF3Lepbkg)
	//This is taken from AN-10-261_v1 Section 4
	//N_t0 is #events with all 3 loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other 2 passing tight
	//N_t2 is #events with two  loose leptons failing tight and the other one passing tight
	//N_t3 is #events with all 3 loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	double div = 1.0/pow(p-f,3);
	double omf = 1.0-f;	
	double omp = 1.0-p;
	double N_fpp = div*( 3.0*p*f*f*N_t0 - (f*f*omp + 2.0*p*f*omf)*N_t1 + (2.0*f*omp*omf + p*omf*omf)*N_t2 - 3.0*omp*omf*omf*N_t3); 
	double N_ffp = div*(-3.0*p*p*f*N_t0 + (2.0*p*f*omp + p*p*omf)*N_t1 - (f*omp*omp + 2.0*p*omp*omf)*N_t2 + 2.0*omp*omp*omf*N_t3);
	double N_fff = div*(p*p*p*N_t0 - p*p*omp*N_t1 + p*omp*omp*N_t2 - omp*omp*omp*N_t3);
	return p*p*f*N_fpp + p*f*f*N_ffp + f*f*f*N_fff;
}

/////////////////////////////////////////////////////////////

int ThrowPoissonFromMeasurement(TRandom2* r, int n){//wad
	if(n>100) return (int) r->Gaus(n, sqrt((float)n));
	//figure out what the distribution of poisson parameters are. 
	return r->Poisson( 0.5*ChiSquared(2*(n+1) ) );
}
double ChiSquared(int k){//wad
	ROOT::Math::Random<ROOT::Math::GSLRngMT> r;
	return r.ChiSquare(k);
}


/////////////////////// FUNCTIONS FOR WEIGHTS /////////////////////
///////////////////////coifs for SS emu////////////////////////////
//mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus, 5 = q plus, 6 = q minus
inline int frModeBehavior(int mode){ return mode==1?1:(mode==2?-1:0); } //+1,-1 for 1,2, else 0
inline int prModeBehavior(int mode){ return mode==3?1:(mode==4?-1:0); } //+1,-1 for 3,4, else 0


inline double Det_em(double fe, double pe, double fm, double pm, double q){ return -(1.0 - 2.0* q)*(pe - fe)*(pm - fm); } //det is always negative.


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////Tripple Lepton /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
double GetWeight(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
    if(		lep1_info.at(1)==1 && lep2_info.at(1)==1 && lep3_info.at(1)==1){return W_ttt(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==1 && lep2_info.at(1)==1 && lep3_info.at(1)==0){return W_ttl(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==1 && lep2_info.at(1)==0 && lep3_info.at(1)==0){return W_tll(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==0 && lep2_info.at(1)==0 && lep3_info.at(1)==0){return W_lll(mode, lep1_info, lep2_info, lep3_info);}
    else return 0.0;    
    }

/* Calculation by anthony:

(-(f1*f2*f3*p1*p2*p3*(n_lll)) 

- f1*f2*(-1 + f3)*p1*p2*p3*(n_llt) 

+ f1*f3*p1*p2*p3*(n_ltl) 
- f1*f2*f3*p1*p2*p3*(n_ltl) 

+ f2*f3*p1*p2*p3*(n_tll) 
- f1*f2*f3*p1*p2*p3*(n_tll) 

- f1*p1*p2*p3*(n_ltt) 
+ f1*f2*p1*p2*p3*(n_ltt) 
+ f1*f3*p1*p2*p3*(n_ltt) 
- f1*f2*f3*p1*p2*p3*(n_ltt) 

-  f2*p1*p2*p3*(n_tlt) 
+ f1*f2*p1*p2*p3*(n_tlt) 
+ f2*f3*p1*p2*p3*(n_tlt) 
- f1*f2*f3*p1*p2*p3*(n_tlt) 

- f3*p1*p2*p3*(n_ttl) 
+    f1*f3*p1*p2*p3*(n_ttl) 
+ f2*f3*p1*p2*p3*(n_ttl) 
- f1*f2*f3*p1*p2*p3*(n_ttl) 

+  (f3*(f1 - p1)*(f2 - p2) + (f2*(-f1 + p1) + (f1 - (f1 + f2 - f1*f2 + (-1 + f1)*(-1 + f2)*f3)*p1)*p2)*p3)*(n_ttt))

/((f1 - p1)*(f2 - p2)*(f3 - p3))

*/

///Tri-lep
double W_lll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){ 
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return -f1*f2*f3*p1*p2*p3/div;
}
/*double W_ltt(int mode){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return (-f1*p1*p2*p3 + f1*f2*p1*p2*p3 + f1*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}*/
/*double W_tlt(int mode){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return ( -f2*p1*p2*p3 + f1*f2*p1*p2*p3 + f2*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}*/
double W_ttl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return ( - f3*p1*p2*p3 + f1*f3*p1*p2*p3 + f2*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
/*double W_llt(int mode){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return (-f1*f2*(-1 + f3)*p1*p2*p3 )/div;
}*/
/*double W_ltl(int mode){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return ( f1*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}*/
double W_tll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return ( f2*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
double W_ttt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));	
	return (  (f3*(f1 - p1)*(f2 - p2) + (f2*(-f1 + p1) + (f1 - (f1 + f2 - f1*f2 + (-1 + f1)*(-1 + f2)*f3)*p1)*p2)*p3)  )/div;
}


#endif
