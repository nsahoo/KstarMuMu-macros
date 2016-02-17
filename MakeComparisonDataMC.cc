//************************************************************************************************
//  macro to validate diff. kinematic and dynamic observables for B -> K* mu+ mu- analysis
//  @ original author: Niladribihari Sahoo <nsahoo@cern.ch>  
//  @ date created: 16 Feb 2016 TUE 14:02 
//************************************************************************************************

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <getopt.h> // passing unix-like arguments
//#include <regex> //c++11 feature should be fine using gcc491.

#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1.h>
#include <TH2.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TMinuit.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TPad.h> 
#include <TCanvas.h> 
#include <TTree.h>
#include <TChain.h> 
#include <TChainElement.h>
#include <TPaveText.h>
#include <TLatex.h>
#include <TLine.h>
#include <TString.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>
#include <TApplication.h>


// ###########################
// # Function Implementation #
// ###########################
void SetStyle(){

  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetTextFont(42);

  gStyle->SetOptFit(1112);
  gStyle->SetOptStat(1110);
  gStyle->SetOptTitle(0);

  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadTopMargin(0.11);
  gStyle->SetPadBottomMargin(0.12);

  gStyle->SetTitleFont(42,"x");
  gStyle->SetTitleFont(42,"y");
  gStyle->SetTitleOffset(1.05,"x");
  gStyle->SetTitleOffset(0.95,"y");
  gStyle->SetTitleSize(0.05,"x");
  gStyle->SetTitleSize(0.05,"y");

  gStyle->SetLabelFont(42,"x");
  gStyle->SetLabelFont(42,"y");
  gStyle->SetLabelSize(0.05,"x");
  gStyle->SetLabelSize(0.05,"y");

  TGaxis::SetMaxDigits(3);
  gStyle->SetStatY(0.9);

}


void MakeComparisonDataMC(TString plotType){
  // #############################################
  // # plotType =  0 --> B pT                   #
  // # plotType =  1 --> B eta                  #
  // # plotType =  2 --> B vtx CL               #
  // # plotType =  3 --> B L/sigma              #
  // # plotType =  4 --> B cos(alpha)           #
  // #############################################
  // # plotType =  5 --> mu+ pT                  #
  // # plotType =  6 --> mu- pT                  #
  // # plotType =  7 --> mu+ eta                 #
  // # plotType =  8 --> mu- eta                 #
  // #############################################
  // # plotType =  9 --> K* trk pT               #
  // # plotType = 10 --> K* trk eta              #
  // # plotType = 11 --> K* trk DCA/sigma        #
  // #############################################
  // # plotType = 12 --> cos(theta_K)            #
  // # plotType = 13 --> cos(theta_l)            #
  // # plotType = 14 --> phi                     #
  // #############################################

  SetStyle();


  // --- READ TREES --
  TChain *chsig = new TChain("tree");
  chsig->Add("~/Desktop/cut0/BToKstarMuMu/sel_BToKstarMuMu-8TeV-merged-*.root");
  TTree *trsig = chsig;
  
  TChain *chjps = new TChain("tree");
  chjps->Add("~/Desktop/cut0/BToKstarJpsi/sel_singlecand-BuToKstarJPsi-8TeV-*.root");
  TTree *trjps = chjps;

  TChain *chpsp = new TChain("tree");
  chpsp->Add("~/Desktop/cut0/BToKstarPsi2s/sel_singlecand*.root");
  TTree *trpsp = chpsp;

  TChain *chdat = new TChain("tree");
  chdat->Add("~/Desktop/cut0/data/sel_singlecand-BuToKstarMuMu-2012*.root");
  TTree *trdat = chdat;

  /*
  // -- SIGNAL VARS --
  double Bpt(0), Bphi(0), Bvcl(0), Bls(0), Bcos(0), Tpt(0), Tdca(0), Kpt(0), MMmas(0), MMmasE(0);
  chsig->SetBranchStatus("*", 0);
  chsig->SetBranchStatus("B*"                , 1);
  chsig->SetBranchStatus("Trk*"              , 1);
  chsig->SetBranchStatus("Kshortpt"          , 1);
  chsig->SetBranchStatus("Mumu*"             , 1);
  chsig->SetBranchAddress("Bpt"              , &Bpt);
  chsig->SetBranchAddress("Bphi"             , &Bphi);
  chsig->SetBranchAddress("Bvtxcl"           , &Bvcl);
  chsig->SetBranchAddress("Blxysig"          , &Bls);
  chsig->SetBranchAddress("Bcosalphabs2d"    , &Bcos);
  chsig->SetBranchAddress("Trkpt"            , &Tpt);
  chsig->SetBranchAddress("Trkdcasigbs"      , &Tdca);
  chsig->SetBranchAddress("Kshortpt"         , &Kpt);
  chsig->SetBranchAddress("Mumumass"         , &MMmas);
  chsig->SetBranchAddress("Mumumasserr"      , &MMmasE);

  // -- CTRL(JPSI) VARS --
  double Bpt(0), Bphi(0), Bvcl(0), Bls(0), Bcos(0), Tpt(0), Tdca(0), Kpt(0), MMmas(0), MMmasE(0);
  chjps->SetBranchStatus("*", 0);
  chjps->SetBranchStatus("B*"                , 1);
  chjps->SetBranchStatus("Trk*"              , 1);
  chjps->SetBranchStatus("Kshortpt"          , 1);
  chjps->SetBranchStatus("Mumu*"             , 1);
  chjps->SetBranchAddress("Bpt"              , &Bpt);
  chjps->SetBranchAddress("Bphi"             , &Bphi);
  chjps->SetBranchAddress("Bvtxcl"           , &Bvcl);
  chjps->SetBranchAddress("Blxysig"          , &Bls);
  chjps->SetBranchAddress("Bcosalphabs2d"    , &Bcos);
  chjps->SetBranchAddress("Trkpt"            , &Tpt);
  chjps->SetBranchAddress("Trkdcasigbs"      , &Tdca);
  chjps->SetBranchAddress("Kshortpt"         , &Kpt);
  chjps->SetBranchAddress("Mumumass"         , &MMmas);
  chjps->SetBranchAddress("Mumumasserr"      , &MMmasE);

  // -- CTRL(PSIP) VARS --
  double Bpt(0), Bphi(0), Bvcl(0), Bls(0), Bcos(0), Tpt(0), Tdca(0), Kpt(0), MMmas(0), MMmasE(0);
  chpsp->SetBranchStatus("*", 0);
  chpsp->SetBranchStatus("B*"                , 1);
  chpsp->SetBranchStatus("Trk*"              , 1);
  chpsp->SetBranchStatus("Kshortpt"          , 1);
  chpsp->SetBranchStatus("Mumu*"             , 1);
  chpsp->SetBranchAddress("Bpt"              , &Bpt);
  chpsp->SetBranchAddress("Bphi"             , &Bphi);
  chpsp->SetBranchAddress("Bvtxcl"           , &Bvcl);
  chpsp->SetBranchAddress("Blxysig"          , &Bls);
  chpsp->SetBranchAddress("Bcosalphabs2d"    , &Bcos);
  chpsp->SetBranchAddress("Trkpt"            , &Tpt);
  chpsp->SetBranchAddress("Trkdcasigbs"      , &Tdca);
  chpsp->SetBranchAddress("Kshortpt"         , &Kpt);
  chpsp->SetBranchAddress("Mumumass"         , &MMmas);
  chpsp->SetBranchAddress("Mumumasserr"      , &MMmasE);

  */
  // -- DATA VARS --
  double Bpt(0), Bphi(0), Bvcl(0), Bls(0), Bcos(0), Tpt(0), Tdca(0), Kpt(0), MMmas(0), MMmasE(0);
  chdat->SetBranchStatus("*", 0);
  chdat->SetBranchStatus("B*"                , 1);
  chdat->SetBranchStatus("Trk*"              , 1);
  chdat->SetBranchStatus("Kshortpt"          , 1);
  chdat->SetBranchStatus("Mumu*"             , 1);
  chdat->SetBranchAddress("Bpt"              , &Bpt);
  chdat->SetBranchAddress("Bphi"             , &Bphi);
  chdat->SetBranchAddress("Bvtxcl"           , &Bvcl);
  chdat->SetBranchAddress("Blxysig"          , &Bls);
  chdat->SetBranchAddress("Bcosalphabs2d"    , &Bcos);
  chdat->SetBranchAddress("Trkpt"            , &Tpt);
  chdat->SetBranchAddress("Trkdcasigbs"      , &Tdca);
  chdat->SetBranchAddress("Kshortpt"         , &Kpt);
  chdat->SetBranchAddress("Mumumass"         , &MMmas);
  chdat->SetBranchAddress("Mumumasserr"      , &MMmasE);

  // -- PRINT --
  printf("\n");
  printf("INFO: %lld entries in K*mumu mc\n"    , chsig->GetEntries());
  printf("INFO: %lld entries in K*Jpsi mc\n"    , chjps->GetEntries());
  printf("INFO: %lld entries in K*Psip mc\n"    , chpsp->GetEntries());
  printf("INFO: %lld entries in (8TeV) data\n"  , chdat->GetEntries());



  TString fileName = "";
  TString varName = "";
  double minX = 0.0;
  double maxX = 40.0;
  unsigned int nBinsX = 100;
  TString Xtitle = "";

  double minY = 0.0;
  double maxY = 0.0;

  double datasetLumi[4] = {19.98, 37378.629, 295.761, 218.472};  // data, BToK*mumu, BToK*Jpsi, BToK*Psi'


  const double KSTARPLUS_MASS = 0.892;
  const double BPLUS_MASS = 5.279 ;
  const double JPSI_MASS = 3.097 ;
  const double PSI2S_MASS = 3.686 ;
  const double sigma = 0.0315;
  const unsigned int nHisto = 3; 

  //======
  //  B+
  //======

  if (plotType == "0"){

    Xtitle = "B^{+} p_{T} (GeV)";
    maxX = 100.0;

    varName = "Bpt";
    fileName = "BpT.pdf";

  } else if (plotType == "1"){

    Xtitle = "B^{+} #eta";
    minX = -3.0;
    maxX = 3.0;

    nBinsX = 60;

    varName = "Beta";
    fileName = "Beta.pdf";

  } else if (plotType == "2"){

    Xtitle = "B^{+} vtx. CL";
    minX = 0.0;
    maxX = 1.0;

    varName = "Bvcl";
    fileName = "BvtxCL.pdf";

  } else if (plotType == "3"){

    Xtitle = "B^{+} L_{xy}/#sigma";
    minX = 0.0;
    maxX = 100.0;

    varName = "Bls";
    fileName = "BvtxLS.pdf";

  } else if (plotType == "4"){

    Xtitle = "B^{+} cos(#alpha)";
    minX = 0.999;
    maxX = 1.0;

    varName = "Bcos";
    fileName = "BcosAlphaBS.pdf";

  }


  TH1D *h_sig[nHisto];
  TH1D *h_data;

  TCanvas *c[nHisto];
  TCanvas *d;


  for (Int_t i=0; i<chdat->GetEntries(); i++){
    chdat->GetEntry(i);
    if ( ( MMmas > (JPSI_MASS - 5*MMmasE) && MMmas < (JPSI_MASS + 3*MMmasE) ) || ( MMmas > (PSI2S_MASS - 3*MMmasE) && MMmas < (PSI2S_MASS + 3*MMmasE) ) ) {
      h_data->Fill(varName);
    }

  }


  d = new TCanvas("d","Canvas_data", 600, 600);
  h_data->Draw();
  std::cout << " histogram draw done!" << std::endl;







}

void printHelpMessage(){
  printf("Usage  : ./compDataMC plotType \n");
  printf("For [Data-MC comparison]: \n");
  printf("0 = B pT            \n");
  printf("1 = B eta           \n");
  printf("2 = B vtxcl         \n");
  printf("3 = B L/sigma       \n");
  printf("4 = B cos(alpha)    \n");

}


int main(int argc, char** argv){

  if (argc == 2) {
    TString plotType = argv[2];
    MakeComparisonDataMC(plotType);
  }else{
    printHelpMessage();
    return 0;
  }

}
