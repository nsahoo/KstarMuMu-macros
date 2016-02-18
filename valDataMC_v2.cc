//************************************************************************************************
//  macro to validate diff. kinematic and dynamic observables for B -> K* mu+ mu- analysis
//  @ original author: Niladribihari Sahoo <nsahoo@cern.ch>  
//  @ date created: 16 Feb 2016 TUE 14:02 
//************************************************************************************************

void setStyle(){

  gStyle->SetPadBorderMode(0);
  gStyle->SetOptFit(1);
  //gStyle->SetOptStat(1110);                                                                                                                                             
  gStyle->SetOptStat(1);
  //gStyle->SetPadTickX(1);                                                                                                                                                     
  //gStyle->SetPadTickY(1);                                                                                                                                                    
  gStyle->SetFrameFillColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetTitleFillColor(33);
  gStyle->SetTitleW(.77);
  gStyle->SetTitleH(.07);
  gStyle->SetTitleFillColor(33);
  gStyle->SetHistMinimumZero(true);

}


void valDataMC_v2(){

  setStyle();

  //*******************
  //    DATA TREE 
  //*******************
  TChain *chdat = new TChain("tree");
  chdat->Add("~/Desktop/cut0/data/sel_singlecand-BuToKstarMuMu-2012*.root");
  TTree *trdat = chdat;
                    
  //*******************                                                                                                             
  //   JPSI MC TREE 
  //*******************
  TChain *chjps = new TChain("tree");                                                                                                                                     
  chjps->Add("~/Desktop/cut0/BToKstarJpsi/sel_singlecand-BuToKstarJPsi-8TeV-*.root");              
  TTree *trjps = chjps;                                                           

  //******************
  //   PSIP MC TREE   
  //******************                                                                                                                                            
  TChain *chpsp = new TChain("tree");
  chpsp->Add("~/Desktop/cut0/BToKstarPsi2s/sel_singlecand*.root");
  TTree *trpsp = chpsp;


  const unsigned int nH = 8;


  //******************
  //  SAMPLE LUMI
  //******************
  double DATALUMI = 19.98;
  double JPSILUMI = 295.761;
  double PSIPLUMI = 218.472;
  double SIGNLUMI = 37378.629;


  // -- DATA VARS --
  double Kstmas(0), Bmas(0), MMmas(0), MMmasE(0);

  vector<double> var(nH,0);
  chdat->SetBranchStatus("*", 0);
  chdat->SetBranchStatus("B*"                , 1);
  chdat->SetBranchStatus("Trk*"              , 1);
  chdat->SetBranchStatus("Kshortpt"          , 1);
  chdat->SetBranchStatus("Mumu*"             , 1);
  chdat->SetBranchAddress("Bpt"              , &var[0]);
  chdat->SetBranchAddress("Bphi"             , &var[1]);
  chdat->SetBranchAddress("Bvtxcl"           , &var[2]);
  chdat->SetBranchAddress("Blxysig"          , &var[3]);
  chdat->SetBranchAddress("Bcosalphabs2d"    , &var[4]);
  chdat->SetBranchAddress("Trkpt"            , &var[5]);
  chdat->SetBranchAddress("Trkdcasigbs"      , &var[6]);
  chdat->SetBranchAddress("Kshortpt"         , &var[7]);
  chdat->SetBranchAddress("Kstarmass"        , &Kstmas);
  chdat->SetBranchAddress("Bmass"            , &Bmas);
  chdat->SetBranchAddress("Mumumass"         , &MMmas);
  chdat->SetBranchAddress("Mumumasserr"      , &MMmasE);
  //

  // -- JPSI VARS --
  double KstmasJP(0), BmasJP(0), MMmasJP(0), MMmasEJP(0);

  vector<double> varJP(nH,0);
  chjps->SetBranchStatus("*", 0);
  chjps->SetBranchStatus("B*"                , 1);
  chjps->SetBranchStatus("Trk*"              , 1);
  chjps->SetBranchStatus("Kshortpt"          , 1);
  chjps->SetBranchStatus("Mumu*"             , 1);
  chjps->SetBranchAddress("Bpt"              , &varJP[0]);
  chjps->SetBranchAddress("Bphi"             , &varJP[1]);
  chjps->SetBranchAddress("Bvtxcl"           , &varJP[2]);
  chjps->SetBranchAddress("Blxysig"          , &varJP[3]);
  chjps->SetBranchAddress("Bcosalphabs2d"    , &varJP[4]);
  chjps->SetBranchAddress("Trkpt"            , &varJP[5]);
  chjps->SetBranchAddress("Trkdcasigbs"      , &varJP[6]);
  chjps->SetBranchAddress("Kshortpt"         , &varJP[7]);
  chjps->SetBranchAddress("Kstarmass"        , &KstmasJP);
  chjps->SetBranchAddress("Bmass"            , &BmasJP);
  chjps->SetBranchAddress("Mumumass"         , &MMmasJP);
  chjps->SetBranchAddress("Mumumasserr"      , &MMmasEJP);


  // -- PSIP VARS --                                                                                                                                                
  double KstmasPS(0), BmasPS(0), MMmasPS(0), MMmasEPS(0);

  vector<double> varPS(nH,0);
  chpsp->SetBranchStatus("*", 0);
  chpsp->SetBranchStatus("B*"                , 1);
  chpsp->SetBranchStatus("Trk*"              , 1);
  chpsp->SetBranchStatus("Kshortpt"          , 1);
  chpsp->SetBranchStatus("Mumu*"             , 1);
  chpsp->SetBranchAddress("Bpt"              , &varPS[0]);
  chpsp->SetBranchAddress("Bphi"             , &varPS[1]);
  chpsp->SetBranchAddress("Bvtxcl"           , &varPS[2]);
  chpsp->SetBranchAddress("Blxysig"          , &varPS[3]);
  chpsp->SetBranchAddress("Bcosalphabs2d"    , &varPS[4]);
  chpsp->SetBranchAddress("Trkpt"            , &varPS[5]);
  chpsp->SetBranchAddress("Trkdcasigbs"      , &varPS[6]);
  chpsp->SetBranchAddress("Kshortpt"         , &varPS[7]);
  chpsp->SetBranchAddress("Kstarmass"        , &KstmasPS);
  chpsp->SetBranchAddress("Bmass"            , &BmasPS);
  chpsp->SetBranchAddress("Mumumass"         , &MMmasPS);
  chpsp->SetBranchAddress("Mumumasserr"      , &MMmasEPS);



  // -- PRINT --
  printf("\n");

  printf("INFO: %lld entries in K*Jpsi mc\n"    , chjps->GetEntries());
  printf("INFO: %lld entries in K*Psip mc\n"    , chpsp->GetEntries());
  printf("INFO: %lld entries in (8TeV) data\n"  , chdat->GetEntries());


  //*******************
  // DEFINE CONSTANTS
  //*******************
  const double KSTARPLUS_MASS = 0.892;
  const double BPLUS_MASS = 5.279 ;
  const double JPSI_MASS = 3.097 ;
  const double PSI2S_MASS = 3.686 ;
  const double sigma = 0.0315;


  double nBinsX[nH] = {100, 60, 100, 100, 100, 50, 50, 100};
  double   minX[nH] = {0., -3.0, 0., 0., 0.999, 0., 0., 0.};
  double   maxX[nH] = {100., 3.0, 1., 100., 1., 5., 50., 10.};


  //**********************
  //  DEFINE HISTOGRAMS 
  //**********************
  TH1D *h_data_sig[nH];
  TH1D *h_data_bkg[nH];
  TH1D *h_data_diff[nH];

  TH1D *h_jps_sig[nH];
  TH1D *h_jps_bkg[nH];
  TH1D *h_jps_diff[nH];

  TH1D *h_psp_sig[nH];
  TH1D *h_psp_bkg[nH];
  TH1D *h_psp_diff[nH];


  //*****************
  // DEFINE CANVAS 
  //*****************
  TCanvas *d[nH];
  TCanvas *e[nH];
  TCanvas *f[nH];

  TCanvas *d1[nH];
  TCanvas *e1[nH];
  TCanvas *f1[nH];

  TCanvas *d2[nH];
  TCanvas *e2[nH];
  TCanvas *f2[nH];

  //
  TString varName[nH] = {"BpT", "Bphi", "Bvtxcl", "Bls", "Bcos", "Trkpt", "Trkdca", "Kshortpt"};
  TString  Xtitle[nH] = {"B^{+} p_{T} (GeV)", "B^{+} #phi", "B^{+} vtx. CL", "B^{+} L_{xy}/#sigma", "B^{+} cos(#alpha)", "#pi trk p_{T} (GeV)", "#pi trk DCA/#sigma", "K_{s} p_{T} (GeV)"};
  TString Ytitle = "Norm. entries";
  //


  for (int j = 0; j < nH; j++){



    h_data_sig[j]  = new TH1D(Form("h_data_sig[%i]",j),"", nBinsX[j], minX[j], maxX[j]);
    h_data_bkg[j]  = new TH1D(Form("h_data_bkg[%i]",j),"", nBinsX[j], minX[j], maxX[j]);
    h_data_diff[j] = new TH1D(Form("h_data_diff[%i]",j),"", nBinsX[j], minX[j], maxX[j]);

    h_jps_sig[j]   = new TH1D(Form("h_jps_sig[%i]",j),"", nBinsX[j], minX[j], maxX[j]);
    h_jps_bkg[j]   = new TH1D(Form("h_jps_bkg[%i]",j),"", nBinsX[j], minX[j], maxX[j]);
    h_jps_diff[j]  = new TH1D(Form("h_jps_diff[%i]",j),"", nBinsX[j], minX[j], maxX[j]);

    h_psp_sig[j]   = new TH1D(Form("h_psp_sig[%i]",j),"", nBinsX[j], minX[j], maxX[j]);
    h_psp_bkg[j]   = new TH1D(Form("h_psp_bkg[%i]",j),"", nBinsX[j], minX[j], maxX[j]);
    h_psp_diff[j]  = new TH1D(Form("h_psp_diff[%i]",j),"", nBinsX[j], minX[j], maxX[j]);



    for (Int_t i=0; i<chdat->GetEntries(); i++){ // data entry loop start
      chdat->GetEntry(i);

      // fill histo selecting Jpsi & Psip region
      if ( ( MMmas > (JPSI_MASS - 3*MMmasE) && MMmas < (JPSI_MASS + 3*MMmasE) ) || ( MMmas > (PSI2S_MASS - 3*MMmasE) && MMmas < (PSI2S_MASS + 3*MMmasE) ) ) {  

	if (!(Bmas > 5.0 && Bmas < 5.56)) continue;
	if (!(Bmas > BPLUS_MASS-2.5*sigma && Bmas < BPLUS_MASS+2.5*sigma ) ) continue;
	//if (!(Bmas > 5.22 && Bmas < 5.34)) continue;
	if (!(Kstmas > 0.792 && Kstmas < 0.992)) continue;
	if (!(var[3] > 10. && var[4] > 0.999 && var[5] > 0.35 && var[6] > 0.7 && var[7] > 0.9)) continue;

	h_data_sig[j]->Fill(var[j]);
      }

      // fill histo selecting sideband ONLY
      if ( ( MMmas < (JPSI_MASS - 3*MMmasE) || MMmas > (JPSI_MASS + 3*MMmasE) ) && ( MMmas < (PSI2S_MASS - 3*MMmasE) || MMmas > (PSI2S_MASS + 3*MMmasE) )  ) {

	//if (!( MMmas < (PSI2S_MASS - 3*MMmasE) || MMmas > (PSI2S_MASS + 3*MMmasE) ) ) continue; 
	if (!(Bmas > 0)) continue;
	if (!(Bmas > 5.0 &&Bmas < 5.56)) continue;
	if (!( (Bmas < BPLUS_MASS-2.5*sigma && Bmas > BPLUS_MASS-5*sigma) || (Bmas > BPLUS_MASS+2.5*sigma && Bmas < BPLUS_MASS+5*sigma) ) ) continue;
	//if (!( ( Bmas < 5.22 && Bmas > 5.16 ) || (Bmas > 5.34 && Bmas < 5.40) ) ) continue;
	if (!(Kstmas > 0.792 && Kstmas < 0.992)) continue;
	if (!(var[3] > 10. && var[4] > 0.999 && var[5] > 0.35 && var[6] > 0.7 && var[7] > 0.9)) continue;

	h_data_bkg[j]->Fill(var[j]);
      }

     
      h_data_diff[j]->Add(h_data_sig[j],h_data_bkg[j], 1., -1.);

    } // data entry loop end


    cout << "------- INTEGRAL VALUES (DATA): VAR " << j << " --------" << endl;						   						   
    cout << h_data_sig[j]->Integral() << endl;
    cout << h_data_bkg[j]->Integral() << endl;						   					  
    cout << h_data_diff[j]->Integral() << endl;


    //-------- DATA CANVAS -------
    d[j] = new TCanvas(Form("d[%i]",j),Form("Canvas_data_sig_%i",j), 800, 600);
    //h_data_sig[j]->Sumw2();
    h_data_sig[j]->Scale(1./h_data_sig[j]->Integral());
    h_data_sig[j]->GetYaxis()->SetTitleOffset(1.5);
    h_data_sig[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
    h_data_sig[j]->SetYTitle(Form("%s", Ytitle.Data()));
    //h_data_sig[j]->SetMarkerStyle(20);
    h_data_sig[j]->Draw("");
    //d[j]->Print(Form("valJPS/data_sig_%s.pdf", varName.Data()));
    d[j]->SaveAs(Form("valJPS/data_sig_%s.pdf", varName[j].Data()));
    
 
    e[j] = new TCanvas(Form("e[%i]",j),Form("Canvas_data_bkg_%i",j), 800, 600);
    //h_data_bkg[j]->Sumw2();
    h_data_bkg[j]->Scale(1./h_data_bkg[j]->Integral());
    h_data_bkg[j]->GetYaxis()->SetTitleOffset(1.5);
    h_data_bkg[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
    h_data_bkg[j]->SetYTitle(Form("%s", Ytitle.Data()));
    //h_data_bkg[j]->SetMarkerStyle(20);
    h_data_bkg[j]->Draw("");
    //e[j]->Print(Form("valJPS/data_bkg_%s.pdf", varName.Data()));
    e[j]->SaveAs(Form("valJPS/data_bkg_%s.pdf", varName[j].Data()));


    f[j] = new TCanvas(Form("f[%i]",j),Form("Canvas_data_diff_%i",j), 800, 600);
    //h_data_diff[j]->Sumw2();
    h_data_diff[j]->Scale(1./h_data_diff[j]->Integral());
    h_data_diff[j]->GetYaxis()->SetTitleOffset(1.5);
    h_data_diff[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
    h_data_diff[j]->SetYTitle(Form("%s", Ytitle.Data()));
    //h_data_diff[j]->SetLineColor(kBlack);
    //h_data_diff[j]->SetLineStyle(1);
    //h_data_diff[j]->SetLineWidth(2);
    //h_data_diff[j]->SetMarkerStyle(20);
    h_data_diff[j]->Draw("");
    //f[j]->Print(Form("valJPS/data_diff_%s.pdf", varName.Data()));
    f[j]->SaveAs(Form("valJPS/data_diff_%s.pdf", varName[j].Data()));


   
  for (Int_t i=0; i<chjps->GetEntries(); i++){ // JPSI entry loop start                                                                                                          
    chjps->GetEntry(i);

    // fill histo selecting Jpsi region ONLY                                                                                                                                     
    if ( ( MMmasJP > (JPSI_MASS - 3*MMmasEJP) && MMmasJP < (JPSI_MASS + 3*MMmasEJP) ) ) {

      if (!(BmasJP > 5.0 && BmasJP < 5.56)) continue;
      if (!(BmasJP > BPLUS_MASS-2.5*sigma && BmasJP < BPLUS_MASS+2.5*sigma ) ) continue;
      //if (!(BmasJP > 5.22 && BmasJP < 5.34)) continue;
      if (!(KstmasJP > 0.792 && KstmasJP < 0.992)) continue;
      if (!(varJP[3] > 10. && varJP[4] > 0.999 && varJP[5] > 0.35 && varJP[6] > 0.7 && varJP[7] > 0.9)) continue;

      h_jps_sig[j]->Fill(varJP[j]);
    }

    // fill histo selecting sideband ONLY                                                                                                                                        
    if ( ( MMmasJP < (JPSI_MASS - 2.5*MMmasEJP) || MMmasJP > (JPSI_MASS + 2.5*MMmasEJP) ) ) {

      if (!(BmasJP > 0)) continue;
      if (!(BmasJP > 5.0 && BmasJP < 5.56)) continue;
      if (!( (BmasJP < BPLUS_MASS-2.5*sigma && BmasJP > BPLUS_MASS-5*sigma) || (BmasJP > BPLUS_MASS+2.5*sigma && BmasJP < BPLUS_MASS+5*sigma) ) ) continue;
      //if (!( ( BmasJP < 5.22 && BmasJP > 5.16 ) || (BmasJP > 5.34 && BmasJP < 5.40) ) ) continue;
      if (!(KstmasJP > 0.792 && KstmasJP < 0.992)) continue;
      if (!(varJP[3] > 10. && varJP[4] > 0.999 && varJP[5] > 0.35 && varJP[6] > 0.7 && varJP[7] > 0.9)) continue;

      h_jps_bkg[j]->Fill(varJP[j]);
    }


    h_jps_diff[j]->Add(h_jps_sig[j],h_jps_bkg[j], 1., -1.);

  } // JPSI entry loop end                                                                                                                                                       


  cout << "------ INTEGRAL VALUES (JPSI): VAR " << j << " -------" << endl;
  cout << h_jps_sig[j]->Integral() << endl;
  cout << h_jps_bkg[j]->Integral() << endl;
  cout << h_jps_diff[j]->Integral() << endl;


  //-------- JPSI CANVAS -------                                                                                                                                                 
  d1[j] = new TCanvas(Form("d1[%i]",j),Form("Canvas_jps_sig_%i",j), 800, 600);
  h_jps_sig[j]->Scale(1./h_jps_sig[j]->Integral());
  h_jps_sig[j]->GetYaxis()->SetTitleOffset(1.5);
  h_jps_sig[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
  h_jps_sig[j]->SetYTitle(Form("%s", Ytitle.Data()));
  //h_jps_sig[j]->SetMarkerStyle(20);                                                                                                                                           
  h_jps_sig[j]->Draw("");
  //d1[j]->Print(Form("valJPS/jps_sig_%s.pdf", varName.Data()));                                                                                                               
  d1[j]->SaveAs(Form("valJPS/jps_sig_%s.pdf", varName[j].Data()));                                                                                                           


  e1[j] = new TCanvas(Form("e1[%i]",j),Form("Canvas_jps_bkg_%i",j), 800, 600);
  h_jps_bkg[j]->Scale(1./h_jps_bkg[j]->Integral());
  h_jps_bkg[j]->GetYaxis()->SetTitleOffset(1.5);
  h_jps_bkg[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
  h_jps_bkg[j]->SetYTitle(Form("%s", Ytitle.Data()));
  //h_jps_bkg[j]->SetMarkerStyle(20);                                                                                                                                           
  h_jps_bkg[j]->Draw("");
  //e1[j]->Print(Form("valJPS/jps_bkg_%s.pdf", varName.Data()));                                                                                                               
  e1[j]->SaveAs(Form("valJPS/jps_bkg_%s.pdf", varName[j].Data()));                                                                                                           


  f1[j] = new TCanvas(Form("f1[%i]",j),Form("Canvas_jps_diff_%i",j), 800, 600);
  //h_jps_diff[j]->Scale(DATALUMI/JPSILUMI);    // scale according to lumi
  h_jps_diff[j]->Scale(1./h_jps_diff[j]->Integral());
  h_jps_diff[j]->GetYaxis()->SetTitleOffset(1.5);
  h_jps_diff[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
  h_jps_diff[j]->SetYTitle(Form("%s", Ytitle.Data()));
  //h_jps_diff[j]->SetLineColor(kBlack);
  //h_jps_diff[j]->SetFillColor(kAzure+6);
  //h_jps_diff[j]->SetLineColor(kRed);
  //h_jps_diff[j]->SetLineStyle(1);
  //h_jps_diff[j]->SetLineWidth(2);
  //h_jps_diff[j]->Sumw2();
  //h_jps_diff[j]->SetMarkerStyle(20);                                                                                                                                          
  h_jps_diff[j]->Draw("");
  //f1[j]->Print(Form("valJPS/jps_diff_%s.pdf", varName.Data()));                                                                                                              
  f1[j]->SaveAs(Form("valJPS/jps_diff_%s.pdf", varName[j].Data()));                                                                                                          



  for (Int_t i=0; i<chpsp->GetEntries(); i++){ // PSIP entry loop start                                                                                                           
    chpsp->GetEntry(i);

    // fill histo selecting psip region ONLY                                                                                                                              
    if ( ( MMmasPS > (PSI2S_MASS - 2.5*MMmasEPS) && MMmasPS < (PSI2S_MASS + 2.5*MMmasEPS) ) ) {

      if (!(BmasPS > 5.0 && BmasPS < 5.56)) continue;
      //if (!(BmasPS > BPLUS_MASS-2.5*sigma && BmasPS < BPLUS_MASS+2.5*sigma ) ) continue;                                                                                     
      if (!(BmasPS > 5.22 && BmasPS < 5.34)) continue;
      if (!(KstmasPS > 0.792 && KstmasPS < 0.992)) continue;
      if (!(varPS[3] > 10. && varPS[4] > 0.999 && varPS[5] > 0.35 && varPS[6] > 0.7 && varPS[7] > 0.9)) continue;

      h_psp_sig[j]->Fill(varPS[j]);
    }

    // fill histo selecting sideband ONLY                                                                                                                               
    if ( ( MMmasPS < (PSI2S_MASS - 2.5*MMmasEPS) || MMmasPS > (PSI2S_MASS + 2.5*MMmasEPS) ) ) {

      if (!(BmasPS > 0)) continue;
      if (!(BmasPS > 5.0 && BmasPS < 5.56)) continue;
      //if (!( (BmasPS < BPLUS_MASS-2.5*sigma && BmasPS > BPLUS_MASS-5*sigma) || (BmasPS > BPLUS_MASS+2.5*sigma && BmasPS < BPLUS_MASS+5*sigma) ) ) continue;                   
      if (!( ( BmasPS < 5.22 && BmasPS > 5.16 ) || (BmasPS > 5.34 && BmasPS < 5.40) ) ) continue;
      if (!(KstmasPS > 0.792 && KstmasPS < 0.992)) continue;
      if (!(varPS[3] > 10. && varPS[4] > 0.999 && varPS[5] > 0.35 && varPS[6] > 0.7 && varPS[7] > 0.9)) continue;

      h_psp_bkg[j]->Fill(varPS[j]);
    }

    h_psp_diff[j]->Add(h_psp_sig[j],h_psp_bkg[j], 1., -1.);

  } // PSIP entry loop end      

  cout << "------ INTEGRAL VALUES (PSIP): VAR " << j << " -------" << endl;
  cout << h_psp_sig[j]->Integral() << endl;
  cout << h_psp_bkg[j]->Integral() << endl;
  cout << h_psp_diff[j]->Integral() << endl;


  //-------- PSIP CANVAS -------                                                                                                                                               
  d2[j] = new TCanvas(Form("d2[%i]",j),Form("Canvas_psp_sig_%i",j), 800, 600);
  h_psp_sig[j]->Scale(1./h_psp_sig[j]->Integral());
  h_psp_sig[j]->GetYaxis()->SetTitleOffset(1.5);
  h_psp_sig[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
  h_psp_sig[j]->SetYTitle(Form("%s", Ytitle.Data()));
  h_psp_sig[j]->SetStats(1);
  //h_psp_sig[j]->SetMarkerStyle(20);                                                                                                                                   
  h_psp_sig[j]->Draw("");
  //d2[j]->Print(Form("valPSP/psp_sig_%s.pdf", varName.Data()));                                                                                                
  d2[j]->SaveAs(Form("valPSP/psp_sig_%s.pdf", varName[j].Data()));


  e2[j] = new TCanvas(Form("e2[%i]",j),Form("Canvas_psp_bkg_%i",j), 800, 600);
  h_psp_bkg[j]->Scale(1./h_psp_bkg[j]->Integral());
  h_psp_bkg[j]->GetYaxis()->SetTitleOffset(1.5);
  h_psp_bkg[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
  h_psp_bkg[j]->SetYTitle(Form("%s", Ytitle.Data()));
  h_psp_bkg[j]->SetStats(1);
  //h_psp_bkg[j]->SetMarkerStyle(20);                                                                                                                             
  h_psp_bkg[j]->Draw("");
  //e2[j]->Print(Form("valPSP/psp_bkg_%s.pdf", varName.Data()));                                                                                                      
  e2[j]->SaveAs(Form("valPSP/psp_bkg_%s.pdf", varName[j].Data()));


  f2[j] = new TCanvas(Form("f2[%i]",j),Form("Canvas_psp_diff_%i",j), 800, 600);                                                                                                
  //h_psp_diff[j]->Scale(DATALUMI/PSIPLUMI);
  h_psp_diff[j]->Scale(1./h_psp_diff[j]->Integral());
  h_psp_diff[j]->GetYaxis()->SetTitleOffset(1.5);
  h_psp_diff[j]->SetXTitle(Form("%s", Xtitle[j].Data()));
  h_psp_diff[j]->SetYTitle(Form("%s", Ytitle.Data()));
  //h_psp_diff[j]->SetLineColor(kBlack);                                                                                                                                          
  //h_psp_diff[j]->SetFillColor(kAzure+6);                                                                                                                                        
  h_psp_diff[j]->SetLineColor(kRed);
  h_psp_diff[j]->SetLineStyle(1);
  h_psp_diff[j]->SetLineWidth(2);
  //h_psp_diff[j]->Sumw2();                                                                                                                                                       
  //h_psp_diff[j]->SetMarkerStyle(20);                                                                                                                                            
  h_psp_diff[j]->Draw("");                                                                                                                                                     
  //f2[j]->Print(Form("valPSP/psp_diff_%s.pdf", varName.Data()));                                                                                                              
  f2[j]->SaveAs(Form("valPSP/psp_diff_%s.pdf", varName[j].Data()));            






  /* 
  for (unsigned int it = 0; it < nBinsX[j]; it++){
    h_jps_diff[j]->SetBinContent(it+1,h_jps_diff[j]->GetBinContent(it+1) / h_jps_diff[j]->GetBinWidth(it+1));
    h_jps_diff[j]->SetBinError(it+1,h_jps_diff[j]->GetBinError(it+1) / h_jps_diff[j]->GetBinWidth(it+1));
      
    h_data_diff[j]->SetBinContent(it+1,h_data_diff[j]->GetBinContent(it+1) / h_data_diff[j]->GetBinWidth(it+1));
    h_data_diff[j]->SetBinError(it+1,h_data_diff[j]->GetBinError(it+1) / h_data_diff[j]->GetBinWidth(it+1));
  }
  */


  f1[j] = new TCanvas(Form("f1[%i]",j),Form("Canvas_val_dataMC_var%i",j), 800, 600); 
  h_jps_diff[j]->Draw("");
  h_data_diff[j]->Draw("same");


  h_jps_diff[j]->GetYaxis()->SetRangeUser(0.0,(h_jps_diff[j]->GetBinContent(h_jps_diff[j]->GetMaximumBin()) > h_data_diff[j]->GetBinContent(h_data_diff[j]->GetMaximumBin()) ?
					      h_jps_diff[j]->GetBinContent(h_jps_diff[j]->GetMaximumBin()) : h_data_diff[j]->GetBinContent(h_data_diff[j]->GetMaximumBin()))*1.1);
  h_data_diff[j]->GetYaxis()->SetRangeUser(0.0,(h_jps_diff[j]->GetBinContent(h_jps_diff[j]->GetMaximumBin()) > h_data_diff[j]->GetBinContent(h_data_diff[j]->GetMaximumBin()) ?
					      h_jps_diff[j]->GetBinContent(h_jps_diff[j]->GetMaximumBin()) : h_data_diff[j]->GetBinContent(h_data_diff[j]->GetMaximumBin()))*1.1);


  TLegend *leg = new TLegend(0.63,0.645,0.83,0.845,"");
  leg->AddEntry(h_jps_diff[j],"J/#psiK* MC");
  leg->AddEntry(h_data_diff[j],"J/#psiK* Data");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

  f1[j]->Modified();
  f1[j]->Update();
  f1[j]->SaveAs(Form("valJPS/val_dataMC_jpsi_%s.pdf", varName[j].Data()));



  }
  
  // --- JPSI LOOP END ---


}
