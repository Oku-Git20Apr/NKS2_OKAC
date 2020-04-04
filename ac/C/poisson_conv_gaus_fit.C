





void poisson_conv_gaus_fit() {


  TFile* f = new TFile( "../root/r0000053.root", "READONLY");

  TTree* tree = (TTree*) f -> Get( "tree" );
  

  //                       H1949      H7195
  float pedestal[2] = { 117.563,  116.383 };
  float peak_pe[2]  = { 331.290,  200.892 };


  TH1F* pH1949_qdc = new TH1F( "H1949_qdc", "", 1024,   0., 4096. );
  TH1F* pH7195_qdc = new TH1F( "H7195_qdc", "", 1024,   0., 4096. );


  // H1949  one photon peak sigma  6.43 [ch]    ->  6.43 / ( 331.290 - 117.563) = 0.0301
  // H7195  one photon peak sigma 11.14 [ch]    -> 11.14 / ( 200.892 - 116.383) = 0.1318

  TH1F* pH1949_pe  = new TH1F( "H1949_pe" , "", 1100, -10.,  100. );
  TH1F* pH7195_pe  = new TH1F( "H7195_pe" , "", 1100, -10.,  100. );

  
  tree -> Project( "H1949_qdc", "qdc[1]", "tdc[1]>0" );
  tree -> Project( "H7195_qdc", "qdc[2]", "tdc[2]>0" );


  char condi[1000];

  sprintf( condi, "(qdc[1]-%f)/%f", pedestal[0],  peak_pe[0]-pedestal[0] );
  tree -> Project( "H1949_pe", condi, "tdc[1]>0" );


  sprintf( condi, "(qdc[2]-%f)/%f", pedestal[1],  peak_pe[1]-pedestal[1] );
  tree -> Project( "H7195_pe", condi, "tdc[2]>0" );



  TCanvas* c1 = new TCanvas( "c1", "c1", 300, 600 );

  TPad* p1[2];
  p1[0] = new TPad( "p1_0", "p1_0", 0.0, 0.5, 1.0, 1.0 );
  p1[1] = new TPad( "p1_1", "p1_1", 0.0, 0.0, 1.0, 0.5 );

  for ( int i= 0; i<2; i++ ) {
    p1[i] -> Draw();
  }


/*
  p1[0] -> cd();
  pH1949_pe -> Draw();


  p1[1] -> cd();
  pH7195_pe -> Draw();
*/




  // Observable: number of photo electron
  //
  RooRealVar x( "x", "x", -10., 100. );

  // Detector response function: Gauss
  //
  RooRealVar   mean( "mean" , "mean" , 0 );
  RooRealVar  sigma( "sigma", "sigma", 0.0301 );
  RooGaussian gauss( "gauss", "gauss", x, mean, sigma );

  // Poisson distribution
  //
  RooRealVar      mn( "mn" , "mn" , 10. );
  RooPoisson poisson( "poisson", "poisson", x, mn );


  // Construct convolution
  //
  RooNumConvPdf pg0( "pg0", "Poisson (X) gauss", x, poisson, gauss );


  RooDataHist data_H1949( "data_H1949",  "H1949", x, pH1949_pe ); 




  p1[0] -> cd();

  RooPlot* xframe_0 = x.frame();
/*
  data_H1949.plotOn(xframe_0);

  pg0.fitTo(data_H1949);
*/

  poisson.plotOn(xframe_0);
  xframe_0-> Draw();


  


  p1[1] -> cd();




//  f->Close();



}
