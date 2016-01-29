//++++++++++++++++++++++++++++++++++++++++++++++++++
//  calculate the efficiency no. from signal mc
//++++++++++++++++++++++++++++++++++++++++++++++++++
//   author: N Sahoo @ NISER, Bhubaneswar
//     date: 26-01-2016  Tuesday   
//==================================================
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

#include <TSystem.h>
#include <TStyle.h>
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
#include <TChain.h> 
#include <TChainElement.h>
#include <TPaveText.h>
#include <TLatex.h>
#include <TLine.h>
#include <TString.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>

#include <RooConstVar.h>
#include <RooRealVar.h>
#include <RooAbsPdf.h>
#include <RooAddPdf.h>
#include <RooGaussian.h>
#include <RooBifurGauss.h>
#include <RooChebychev.h> 
#include <RooGenericPdf.h> 
#include <RooExponential.h>
#include <RooBernstein.h>
#include <RooPolynomial.h>
#include <RooExtendPdf.h>
#include <RooProdPdf.h>
#include <RooDataHist.h>
#include <RooDataSet.h>
#include <RooAbsData.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooAddition.h>
#include <RooProduct.h>
#include <RooMinuit.h>
#include <RooWorkspace.h>
#include <RooRandom.h>

//calculate reco eff
void calR_EffInCosL(TString data, TString type, int iBin){

  int nrec(0), nrecpass(0);
  const int nbins = 7;
  double clRangeDn[nbins]={-1., -0.7, -0.3, 0., 0.3, 0.7, -1.};
  double clRangeUp[nbins]={-0.7, -0.3, 0., 0.3, 0.7, 1., 1.};


  
  // read data
  double Q2 = 0;
  double gQ2 = 0;
  double CosK = 0;
  double CosL = 0;
  double gCosL = 0;
  double Tpt = 0;
  double Tsigbs = 0;
  double Kpt = 0;
  double Kmass = 0;
  double Blxysig = 0;
  double Bcos2d = 0;
  double Bmass = 0;
  double MMmass = 0;
  double MMerr = 0;


  TChain *ch = new TChain("tree");
  if (data == "small"){
    ch->Add("../../afb-run1/mc-cut0-jul14/sel_BToKstarMuMu-8TeV-merged-cut0_mc.lite_s0.root");
  } else if(data == "large"){
    ch->Add("../../afb-run1/mc-cut0-jul14/sel_BToKstarMuMu-8TeV-merged-*.root");
  }

  TTree *treein = ch;
  printf("%lld entries processed.\n",ch->GetEntries());


  //
  treein->SetBranchStatus("*",0);
  treein->SetBranchStatus("Q2"            , 1);
  treein->SetBranchStatus("genCosTheta*"  , 1);
  treein->SetBranchStatus("CosTheta*"     , 1);
  treein->SetBranchStatus("Mumu*"         , 1);
  treein->SetBranchStatus("Trk*"          , 1);
  treein->SetBranchStatus("Ks*"           , 1);
  treein->SetBranchStatus("B*"            , 1);
  treein->SetBranchAddress("Q2"           , &Q2);
  treein->SetBranchAddress("genQ2"        , &gQ2);
  treein->SetBranchAddress("CosThetaK"    , &CosK);
  //if (type == "reco")
    treein->SetBranchAddress("CosThetaL"    , &CosL);
    //else if (type == "gen")
    treein->SetBranchAddress("genCosThetaL" , &gCosL);
  treein->SetBranchAddress("Trkpt"        , &Tpt);
  treein->SetBranchAddress("Trkdcasigbs"  , &Tsigbs);
  treein->SetBranchAddress("Kshortpt"     , &Kpt);
  treein->SetBranchAddress("Kstarmass"    , &Kmass);
  treein->SetBranchAddress("Blxysig"      , &Blxysig);
  treein->SetBranchAddress("Bcosalphabs2d", &Bcos2d);
  treein->SetBranchAddress("Bmass"        , &Bmass);
  treein->SetBranchAddress("Mumumass"     , &MMmass);
  treein->SetBranchAddress("Mumumasserr"  , &MMerr);
  //

  for (int entry = 0; entry < ch->GetEntries(); entry++){
    ch->GetEntry(entry);

    if (gCosL > clRangeUp[iBin] || gCosL < clRangeDn[iBin]) continue;

    nrec++;

    if (type == "gen"){
      if (gCosL > clRangeUp[iBin] || gCosL < clRangeDn[iBin]) continue;
  } else if (type == "reco"){
      if (CosL > clRangeUp[iBin] || CosL < clRangeDn[iBin]) continue;
  }

    if ( !(Tpt > 0.35 && Tsigbs > 0.7 && Kpt > 0.9 && Kmass > 0.792 && Kmass < 0.992 && Blxysig > 10. && Bcos2d > 0.999 && Bmass > 5.0 && Bmass < 5.56 )) continue;
    nrecpass++;
    
  }

  printf("\n");
  printf("INFO: gen cosl range: [ %.2f-%.2f ] \n", clRangeDn[iBin], clRangeUp[iBin]);
  printf("INFO: #reco evts in bin %d : %d \n", iBin, nrec);
  printf("INFO: #passed reco evts in bin %d : %d \n", iBin, nrecpass);
  printf("INFO: reco. efficiency in bin %d : %8.6f \n",iBin,(double)nrecpass/(double)nrec);
  printf("----------------------------------------------------------\n");

}



  int main(int argc, char** argv) {

    if (argc == 3) {
      TString data = argv[1];
      TString type = argv[2];
      for (int iBin = 0; iBin < 7; iBin++) {
	calR_EffInCosL(data,type,iBin);
      }
    }else{
      printf("Wrong argument given, please xcheck !\n");
      printf("./calR_EffInCosL data type\n");
      printf("data: small, large; type: gen, reco \n");
      return 0;
    }
  }


