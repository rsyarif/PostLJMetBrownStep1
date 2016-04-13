#ifndef _FAKERATE_H
#define _FAKERATE_H
#include <TRandom2.h>
#include "Math/Random.h"
#include <iostream>
#include "CMSStyle.C"

#include "TStyle.h"
#include "TColor.h"
#include <TH1F.h>
#include <TH2.h>
#include "TCanvas.h"

using namespace std;

float Pe(int mode = 0);
inline float uPe();
float Fe(int mode = 0);
inline float uFe();
float Pm(int mode = 0);
inline float uPm();
float Fm(int mode = 0);
inline float uFm();
inline float uQe();
inline double epsilon(double f);//these are guearenteed to be small numbers
inline double eta(double p);//these are guearenteed to be small numbers

inline int feModeBehavior(int mode);
inline int fmModeBehavior(int mode);
inline int peModeBehavior(int mode);
inline int pmModeBehavior(int mode);
inline int qeModeBehavior(int mode);

vector<double> optomizeFP_SFDL(int N_t0, int N_t1, int N_t2, bool ee);
TCanvas* exploreFP_SF(int N_t0, int N_t1, int N_t2);
TCanvas* exploreFP_SFint(int N_t0, int N_t1, int N_t2,int n_t0, int n_t1, int n_t2);

//float eleChargeMisIDRate(float eta, float pt);//this takes 7x longer to run than eleChargeMisIDRate_lin
float eleChargeMisIDRate_lin(float eta, float pt, int mode);//same as eleChargeMisIDRate except in edge cases. 
float eleChargeMisIDRate_lin_guts(float eta, float pt);

vector<double> SingleLepbkg(double f, double p, int N_t0, int N_t1); //output: {N_p, N_f, N_signal, N_bkg}
double SingleLepbkg_simple(double f, double p, int N_t0, int N_t1);


vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);

double ChiSquared(int k);
int ThrowPoissonFromMeasurement(TRandom2* r, int n);


/////////////////// Tripple electron ////////////////////////
double GetWeight_emm(int nTightEle, int nTightMu, int mode);
double GetWeight_eem(int nTightEle, int nTightMu, int mode);
double GetWeight_mmm(int nTightMu, int mode);
double GetWeight_eee(int nTightEle, int mode);

double Wemm_ttt(int mode );
double Wemm_tetmlm(int mode );
double Wemm_tmtmle(int mode );
double Wemm_tmlmle(int mode );
double Wemm_lmlmte(int mode );
double Wemm_lll(int mode );
double Weem_ttt(int mode );
double Weem_tmtele(int mode );
double Weem_tetelm(int mode );
double Weem_telelm(int mode );
double Weem_leletm(int mode );
double Weem_lll(int mode );
double Wmmm_ttt(int mode);
double Wmmm_llt(int mode);
double Wmmm_ltt(int mode);
double Wmmm_lll(int mode); 
double Weee_ttt(int mode);
double Weee_llt(int mode);
double Weee_ltt(int mode);
double Weee_lll(int mode); 
/////////////////////////////

//from AN-15-148 v4 sections 5.2.1 and 5.2.2; see Figure 12 for evidence that the fake rates are pt independent. 
float Pe(int mode){return 0.87 + uPe()*peModeBehavior(mode);}  //ele prompt rate
inline float uPe(){return 0.005;}  //ele prompt rate

float Fe(int mode){return 0.3305 + uFm()*fmModeBehavior(mode);} //ele fake rate //El pt inclusive fake rate = 33.0531% +/- 0.173866 %
inline float uFe(){return 0.017;} //ele fake rate = 0.663 +- 0.009

float Pm(int mode){return 0.9836 + uPm()*pmModeBehavior(mode);} //mu prompt rate
inline float uPm(){return 0.0003;}  //muon prompt rate

float Fm(int mode){return 0.4673 + uFe()*feModeBehavior(mode);} //mu fake rate //Mu pt inclusive fake rate = 46.7348% +/- 0.159149 %
inline float uFm(){return 0.0016;} //muon fake rate= 0.887 +- 0.005

inline float uQe(){return 0.30;}//percent

inline double epsilon(double f){return f/(1.0-f);} 
inline double eta(double p){return (1.0-p)/p;}

float eleChargeMisIDRate_lin(float eta, float pt, int mode){ 
	return eleChargeMisIDRate_lin_guts(eta,pt)*( 1.0+ qeModeBehavior(mode)*uQe() );
}

float eleChargeMisIDRate_lin_guts(float eta, float pt){ //needs testing xxx, make sure this does the same thing as the btree verions, but faster. 
	//returns the charge misID probability. This ought to do the same thing as eleChargeMisIDRate,
	//I'm writing it to see which will run faster. 
	bool lowpt = pt<100;
	//electrons are likely to be central so give them a short return path. 
	if(eta < -0.2){
		if(eta > -0.6) return lowpt?0.00034:0.00265;//-0.6 to -0.2
		else if(eta > -1.0) return lowpt?0.00052:0.00309;//-1.0 to -0.6
		else if(eta > -1.4) return lowpt?0.0009:0.00998;//-1.4 to -1.0
		else if(eta > -1.8) return lowpt?0.00234:0.01792;//-1.8 to -1.4
		else if(eta > -2.2) return lowpt?0.00303:0.0131;//-2.2 to -1.8
		else if(eta > -2.6) return lowpt?0.00304:0.02734;//-2.6 to -2.2
		else return lowpt?0.0:0.0;//-3.0 to -2.6  //probably should be using the -2.6 to -2.2 range. xxx
	}
	else{ //eta > -0.2
		if(eta < 0.2) return lowpt?0.00031:0.00397;//0.6 to 1.0
		else if(eta < 0.6) return lowpt?0.00030:0.00209;//0.6 to 1.0
		else if(eta < 1.0) return lowpt?0.00053:0.00202;//0.6 to 1.0
		else if(eta < 1.4) return lowpt?0.00081:0.00654;//1.0 to 1.4
		else if(eta < 1.8) return lowpt?0.00269:0.01380;//1.4 to 1.8
		else if(eta < 2.2) return lowpt?0.00297:0.01306;//1.8 to 2.2
		else if(eta < 2.6) return lowpt?0.00327:0.01550; //2.2 to 2.6
		else return lowpt?0.0:0.0; //2.6 to 3.0 //probably should be using the -2.6 to -2.2 range. xxx
	}
}//end eleChargeMisIDRate

//    __ 
//   /_ |
//    | |
//    | |
//    | |
//    |_|
//       

vector<double> SingleLepbkg(double f, double p, int N_t0, int N_t1){
	//Calculates all prompt and fake bkg info for same flavor dilepton events 
	//output: {N_p, N_f, N_signal, N_bkg}
	//          0    1     2        3 
	//This is taken from AN-10-261_v1 Section 2
	//N_t0 is #events with a loose lepton that fails tight
	//N_t1 is #events with a tight lepton
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	//N_p is the nubmer of true leptons passing loose 
	//N_f is the number of fake leptons passing loose 
	//N_signal is the number of real leptons passing tight
	//N_bkg is the number of fake leptons passing loose. 
	double div = 1.0/(p-f);
	vector<double> out;	
	out.push_back(div*((1.0-f)*N_t1 - f*N_t0));
	out.push_back(div*(p*N_t0 - (1-p)*N_t1));
	out.push_back(p*out[0]);
	out.push_back(f*out[1]);
	return out;
}

double SingleLepbkg_simple(double f, double p, int N_t0, int N_t1){
	//returns the expected number of fake events in the tight sample (N_bkg from SingleLepbkg above)
	//This is taken from AN-10-261_v1 Section 2
	//N_t0 is #events with a loose lepton that fails tight
	//N_t1 is #events with a tight lepton
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	return f*(p*N_t0 - (1-p)*N_t1)/(p-f);
}


//    ____  
//   |___ \
//     __) |
//    |__ < 
//    ___) |
//   |____/ 
//          
//          


vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
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
	vector<double> out;	
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
inline int feModeBehavior(int mode){ return mode==1?1:(mode==2?-1:0); }//these wad
inline int fmModeBehavior(int mode){ return mode==1?1:(mode==2?-1:0); } //+1,-1 for 1,2, else 0
//inline int fmModeBehavior(int mode){ return mode==5?1:(mode==6?-1:0); } //+1,-1 for 5,6, else 0
inline int peModeBehavior(int mode){ return mode==3?1:(mode==4?-1:0); }
inline int pmModeBehavior(int mode){ return mode==3?1:(mode==4?-1:0); } //+1,-1 for 3,4, else 0
//inline int pmModeBehavior(int mode){ return mode==7?1:(mode==8?-1:0); } //+1,-1 for 3,4, else 0
inline int qeModeBehavior(int mode){ return mode==5?1:(mode==6?-1:0); }

inline double Det_em(double fe, double pe, double fm, double pm, double q){ return -(1.0 - 2.0* q)*(pe - fe)*(pm - fm); } //det is always negative.


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////Tripple Lepton /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
double GetWeight_eee(int nTightEle, int mode){
    switch(nTightEle){
	case 3: return Weee_ttt(mode);
	case 2: return Weee_ltt(mode);
	case 1: return Weee_llt(mode);
	case 0: return Weee_lll(mode);
	default: return 0.0;
    }
}
double GetWeight_mmm(int nTightMu, int mode){
    switch(nTightMu){
	case 3: return Wmmm_ttt(mode);
	case 2: return Wmmm_ltt(mode);
	case 1: return Wmmm_llt(mode);
	case 0: return Wmmm_lll(mode);
	default: return 0.0;
    }
}
double GetWeight_eem(int nTightEle, int nTightMu, int mode){
	if(     nTightEle == 2 and nTightMu == 1) return Weem_ttt(mode);
	else if(nTightEle == 2 and nTightMu == 0) return Weem_tetelm(mode);
	else if(nTightEle == 1 and nTightMu == 0) return Weem_telelm(mode);
	else if(nTightEle == 1 and nTightMu == 1) return Weem_tmtele(mode);
	else if(nTightEle == 0 and nTightMu == 1) return Weem_leletm(mode);
	else if(nTightEle == 0 and nTightMu == 0) return Weem_lll(mode);
	else return 0.0;
}
double GetWeight_emm(int nTightEle, int nTightMu, int mode){
	if(     nTightMu == 2 and nTightEle == 1) return Wemm_ttt(mode);
	else if(nTightMu == 2 and nTightEle == 0) return Wemm_tmtmle(mode);
	else if(nTightMu == 1 and nTightEle == 0) return Wemm_tmlmle(mode);
	else if(nTightMu == 1 and nTightEle == 1) return Wemm_tetmlm(mode);
	else if(nTightMu == 0 and nTightEle == 1) return Wemm_lmlmte(mode);
	else if(nTightMu == 0 and nTightEle == 0) return Wemm_lll(mode);
	else return 0.0;
}

///Tri-electron
//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
double Weee_lll(int mode){ 
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	return -fe*pow(pe,3)*fe*fe/div;
}
double Weee_ltt(int mode){
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	//B = {(fe*pe^3*( (-1 + fe)*(n_ttl - fe*(n_ttl)))  )/(fe - pe)^3}
	//B = {(fe*pe^3* (-1 + fe)*(1-fe)*n_ttl   )/div;
	return (fe*pow(pe,3)*(-1.0 + fe)*(1.0-fe) )/div;
}
double Weee_llt(int mode){
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	//B = {(fe*pe^3*( (-1 + fe)*(- fe*(n_tll ))) )/div;
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	return (fe*pow(pe,3)* (1.0 - fe)*fe )/div;
}
double Weee_ttt(int mode){
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	//B = (  fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	return (  fe*(fe*fe - 3.0*fe*pe + 3.0*pe*pe - (3.0 + (-3.0 + fe)*fe)*pow(pe,3) ))/div;
}

//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
//Tri-muon
//B = {(fm pm^3 (-fm^2 n_lll + (-1 + fm) (n_ttl - fm (n_tll + n_ttl))) + fm (fm^2 - 3 fm pm + 3 pm^2 - (3 + (-3 + fm) fm) pm^3) n_ttt)/(fm - pm)^3
double Wmmm_lll(int mode){ 
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	return -fm*pow(pm,3)*fm*fm/div;
}
double Wmmm_ltt(int mode){
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	//B = {(fm*pm^3*( (-1 + fm)*(n_ttl - fm*(n_ttl)))  )/(fm - pm)^3}
	//B = {(fm*pm^3* (-1 + fm)*(1-fm)*n_ttl   )/div;
	return (fm*pow(pm,3)*(-1.0 + fm)*(1.0-fm) )/div;
}
double Wmmm_llt(int mode){
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	//B = {(fm*pm^3*( (-1 + fm)*(- fm*(n_tll ))) )/div;
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	return (fm*pow(pm,3)* (1.0 - fm)*fm )/div;
}
double Wmmm_ttt(int mode){
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	//B = (  fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	return (  fm*(fm*fm - 3.0*fm*pm + 3.0*pm*pm - (3.0 + (-3.0 + fm)*fm)*pow(pm,3) ))/div;
}


//EEM 
//B = {(1/((fe - pe)^2 (fm - pm)))*(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}
double Weem_lll(int mode ){
	//B = (pe^2*pm*(-fe^2*fm*n_lll - (-1 + fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) + (fm*(fe - pe)^2 - (fe^2 - 2*fe*pe + ((-2 + fe)*fe*(-1 + fm) + fm)*pe^2)*pm)*n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return (-pe*pe*pm*fe*fe*fm)/det;
}
double Weem_leletm(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe^2*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  pe*pe*pm*( fe*fe*(1.0 - fm) )/det;
}

double Weem_telelm(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	cout<< "fe = " << fe << endl;
	double fm = Fm(mode);
	cout<< "fm = " << fm << endl;
	double pe = Pe(mode);
	cout<< "pe = " << pe << endl;
	double pm = Pm(mode);
	cout<< "pm = " << pm << endl;
	double det = pow(fe - pe,2) * (fm - pm);
	cout<< "det = " << det << endl;
	cout<< "Weem_telelm[mode="<<mode<<"] ="<<  (pe*pe*pm*(  (1.0 - fe)*fe*fm) )/det << endl;
	return  (pe*pe*pm*(  (1.0 - fe)*fe*fm) )/det;
}
double Weem_tetelm(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	//B = (pe*pe*pm*(  -fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  (pe*pe*pm*(  -fm + 2.0*fe*fm - fe*fe*fm) )/det;
}

double Weem_tmtele(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	//B = (pe*pe*pm*( - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  (pe*pe*pm*(1.0 - fe)*fe*(-1.0 + fm) )/det;
}

double Weem_ttt(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}
	//B = (pe^2*pm*(-fe^2*fm*n_lll - (-1 + fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) + (fm*(fe - pe)^2 - (fe^2 - 2*fe*pe + ((-2 + fe)*fe*(-1 + fm) + fm)*pe^2)*pm)*n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return (fm*pow(fe - pe,2) - (fe*fe - 2.0*fe*pe + ((-2.0 + fe)*fe*(-1.0 + fm) + fm)*pe*pe)*pm)/det;
}

//EMM

double Wemm_lll(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = (fe - pe)*pow(fm - pm,2);
	//return (-pm*pm*pe*fm*fm*fe)/det;//converted
	return   (-pe*pm*pm*fm*fe*fm)/det; //matches.
}
double Wemm_lmlmte(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  pm*pm*pe*( fm*fm*(1.0 - fe) )/det;//converted 
	return   (pe*pm*pm*(fm*(1.0 - fe)*fm) )/det; //matches.
}

double Wemm_tmlmle(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  (pm*pm*pe*(  (1.0 - fm)*fm*fe) )/det;//converted
	return (pe*pm*pm*fm*(1.0 - fm)*fe )/det;//matches.
}

double Wemm_tmtmle(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  (pm*pm*pe*(  -fe + 2.0*fm*fe - fm*fm*fe) )/det;//converted; 
	return (pe*pm*pm*(  - fe*pow(1.0 - fm,2) ) )/det; //matches.
}

double Wemm_tetmlm(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  (pm*pm*pe*(1.0 - fm)*fm*(-1.0 + fe) )/det; //converetd
	return    (pe*pm*pm*fm*(1.0 - fm)*(-1.0 + fe) )/det; //matches.
}

double Wemm_ttt(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return (fe*pow(fm - pm,2) - (fm*fm - 2.0*fm*pm + ((-2.0 + fm)*fm*(-1.0 + fe) + fe)*pm*pm)*pe)/det;//converted
        return (fm*pe*(-1.0 + pm)*(fm + (-2.0 + fm)*pm) + fe*(fm*fm - 2.0*fm*pm - (-1.0 + pow(-1.0 + fm,2)*pe)*pm*pm))/det;//mathematica .
		//It's not immediately obvious, but this is equivolent ot the converted form. 
}



#endif
