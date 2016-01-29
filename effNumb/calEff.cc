//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  calculate the total efficiency no. from signal mc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   author: N Sahoo @ NISER, Bhubaneswar
//     date: 26-01-2016  Tuesday   
//======================================================


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <TString.h>

void calEff(TString binType){

  // quote the eff. values for q2 bins
  double  q2acc[7] = { 3.15E-2,  3.38E-2,  3.66E-2,  4.06E-2,  4.52E-2,  4.93E-2,  5.64E-2};
  double q2recR[7] = {3.962E-3, 4.233E-3, 4.124E-3, 4.444E-3, 4.258E-3, 4.551E-3, 4.875E-3};
  double q2recG[7] = {4.0E-3,   4.326E-3, 4.526E-3, 4.705E-3, 4.906E-3, 5.102E-3, 5.228E-3};

  // quote the eff. values for cosk bins
  double  ckacc[5] = { 4.03E-2,  3.89E-2,  3.83E-2,  3.93E-2,   4.0E-2};
  double ckrecR[5] = {4.766E-3, 4.647E-3, 4.002E-3, 3.562E-3, 2.826E-3};
  double ckrecG[5] = {4.932E-3, 4.844E-3, 4.310E-3, 3.730E-3, 2.912E-3};

  // quote the eff. values for cosl bins
  double  clacc[6] = { 1.66E-2,  3.53E-2,  5.20E-2,  5.17E-2,  3.93E-2,  2.92E-2};
  double clrecR[6] = {5.138E-3, 3.984E-3, 3.066E-3, 3.278E-3, 4.632E-3, 6.427E-3};
  double clrecG[6] = {5.280E-3, 4.089E-3, 3.184E-3, 3.401E-3, 4.744E-3, 6.533E-3};

  int nbins(0);

  double totEffr_q2(0), totEffg_q2(0), absDiff_q2(0), perDiff_q2(0);
  double totEffr_ck(0), totEffg_ck(0), absDiff_ck(0), perDiff_ck(0);
  double totEffr_cl(0), totEffg_cl(0), absDiff_cl(0), perDiff_cl(0);
  //


  if (binType == "q2"){
    nbins = 7;
    for (int i = 0; i < nbins; i++){
      totEffr_q2 = q2acc[i]*q2recR[i];
      totEffg_q2 = q2acc[i]*q2recG[i];
      absDiff_q2 = totEffr_q2 - totEffg_q2 ;
      perDiff_q2 = (absDiff_q2/totEffr_q2)*100 ;

      printf("\n >>>>>>    Bin: %i  <<<<<<\n", i);
      printf("total efficiency(reco level) = %10.8f \n", totEffr_q2);
      printf("total efficiency(gen level) = %10.8f \n", totEffg_q2);
      printf("abslute difference = %10.8f \n" , absDiff_q2);
      printf("percentage difference = %.1f \n", perDiff_q2);
      printf("==========================================\n");
    }

  }else if (binType == "cosk"){
    nbins = 5;
    for (int i = 0; i < nbins; i++){
      totEffr_ck = ckacc[i]*ckrecR[i];
      totEffg_ck = ckacc[i]*ckrecG[i];
      absDiff_ck = totEffr_ck - totEffg_ck ;
      perDiff_ck = (absDiff_ck/totEffr_ck)*100 ;

      printf("\n >>>>>>    Bin: %i  <<<<<<\n", i);
      printf("total efficiency(reco level) = %10.8f \n", totEffr_ck);
      printf("total efficiency(gen level) = %10.8f \n", totEffg_ck);
      printf("abslute difference = %10.8f \n" , absDiff_ck);
      printf("percentage difference = %.1f \n", perDiff_ck);
      printf("==========================================\n");
    }

  }else if (binType == "cosl"){
    nbins = 6;
    for (int i = 0; i < nbins; i++){
      totEffr_cl = clacc[i]*clrecR[i];
      totEffg_cl = clacc[i]*clrecG[i];
      absDiff_cl = totEffr_cl - totEffg_cl ;
      perDiff_cl = (absDiff_cl/totEffr_cl)*100 ;

      printf("\n >>>>>>    Bin: %i  <<<<<<\n", i);
      printf("total efficiency(reco level) = %10.8f \n", totEffr_cl);
      printf("total efficiency(gen level) = %10.8f \n", totEffg_cl);
      printf("abslute difference = %10.8f \n" , absDiff_cl);
      printf("percentage difference = %.1f \n", perDiff_cl);
      printf("==========================================\n");
    }

  }

  
  printf("\n=> efficiency was calculated in %i %s bins\n", nbins, binType.Data());

}


// main function
  int main(int argc, char** argv) {

    if (argc == 2) {
      TString binType = argv[1];
      calEff(binType);
    }else{
      printf("Wrong argument given, please xcheck !\n");
      printf("./calEff binType \n");
      printf("binType: q2, cosk, cosl \n");
      return 0;
    }
  }


