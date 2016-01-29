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


void calEffInCosl(TString data, int iBin){

  int ngen(0), nacc(0);
  const int nbins = 7;
  double clRangeDn[nbins]={-1., -0.7, -0.3, 0., 0.3, 0.7, -1.};
  double clRangeUp[nbins]={-0.7, -0.3, 0., 0.3, 0.7, 1., 1.};

  
  // read data
  double gQ2 = 0;
  double gCosK = 0;
  double gCosL = 0;
  double gmumpt = 0;
  double gmumeta = 0;
  double gmuppt = 0;
  double gmupeta = 0;


  TChain *ch = new TChain("tree");
  if (data == "small"){
    ch->Add("../../afb-run1/v1/BToKstarMuMu/plugins/unfilt-mc-genonly/sel_BToKstarMuMu-genonly-8TeV.root_mc_s0.root");
  } else if(data == "large"){
    ch->Add("../../afb-run1/v1/BToKstarMuMu/plugins/unfilt-mc-genonly/sel_BToKstarMuMu-genonly-8TeV.root_mc_s*.root");
  }
  TTree *treein = ch;
  printf("%lld entries processed.\n",ch->GetEntries());


  //
  treein->SetBranchStatus("*",0);
  treein->SetBranchStatus("genQ2"         , 1);
  treein->SetBranchStatus("genCosTheta*"  , 1);
  treein->SetBranchStatus("genMu*"        , 1);
  treein->SetBranchAddress("genQ2"        , &gQ2);
  treein->SetBranchAddress("genCosThetaK" , &gCosK);
  treein->SetBranchAddress("genCosThetaL" , &gCosL);
  treein->SetBranchAddress("genMupPt"     , &gmuppt);
  treein->SetBranchAddress("genMupEta"    , &gmupeta);
  treein->SetBranchAddress("genMumPt"     , &gmumpt);
  treein->SetBranchAddress("genMumEta"    , &gmumeta);
  //

  for (int entry = 0; entry < ch->GetEntries(); entry++){
    ch->GetEntry(entry);

    if (gCosL > clRangeUp[iBin] || gCosL < clRangeDn[iBin]) continue;
    ngen++;

    if ( fabs(gmumeta) < 2.3 && fabs(gmupeta) < 2.3 && gmumpt > 2.8 && gmuppt > 2.8 ){
      nacc++;
    }
  }

  printf("\n");
  printf("INFO: gen cosl range: [ %.2f-%.2f ] \n", clRangeDn[iBin], clRangeUp[iBin]);
  printf("INFO: #gen. evts in bin %d : %d \n", iBin, ngen);
  printf("INFO: #acc. evts in bin %d : %d \n", iBin, nacc);
  printf("INFO: acceptance efficiency in bin %d : %.4f \n",iBin,(double)nacc/(double)ngen);
  printf("----------------------------------------------------------\n");

}



  int main(int argc, char** argv) {

    if (argc == 2) {
      TString data = argv[1];
      for (int iBin = 0; iBin < 7; iBin++) {
	calEffInCosl(data,iBin);
      }
    }else{
      printf("Wrong argument given, please xcheck !\n");
      printf("./calEff data \n");
      printf("data: small, large \n");
      return 0;
    }
  }


