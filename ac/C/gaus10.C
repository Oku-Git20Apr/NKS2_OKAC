Double_t fitfunc(Double_t *x, Double_t *param){

   if((int) (((x[0] - param[3])/ param[2])) < 0){

       return 0.;
   }else{
       Double_t fitval
          = param[0] * TMath::Poisson((( x[0] - param[3])/ param[2]), param[1]);
       return fitval;

   }
}



void gaus10(  const char *input_root_file = "../root/r0000053.root",
              const char *ps_file = "../ps/hist_run053.ps" ,
              const Double_t a = 500.,            //initial param //scale
              const Double_t b = 2.,                  //mean of NPE
              const Double_t c = 200.,                 //gain
              const Double_t d = 116.,                    //pedestal mean 
 ) {


  gROOT -> Reset();
  gROOT -> SetStyle( "Plain" );

  TFile *file = new TFile( input_root_file, "READONLY" );

  TTree *tree = new TTree();

  tree = (TTree*)( file -> Get( "tree" ) ); 

  // tree -> Print();

  TH1F* tdc[4];
  TH1F* qdc[4];

  char oname[100];
  char tname[100];
  char varexp[100];


//  for ( int i=0; i<4; i ++ ) {

//    sprintf( oname, "tdc%d", i );
//    sprintf( tname, "tdc%d", i );
//    tdc[i] = new TH1F( oname, "", 50, 50., 100. );

//    sprintf( varexp, "tdc[%d]", i );
//    tree -> Project( oname, varexp  );

//    tdc[i] -> GetXaxis() -> SetRangeUser( 750., 1050. );

//    tdc[i] -> GetXaxis() -> SetTitle( "Time [ch]" );
//    tdc[i] -> GetXaxis() -> SetTitleSize( 0.07 );
//    tdc[i] -> GetXaxis() -> SetTitleOffset( 1.2 );

//    tdc[i] -> GetYaxis() -> SetTitle( "Counts" );
//    tdc[i] -> GetYaxis() -> SetTitleSize( 0.07 );
//   tdc[i] -> GetYaxis() -> SetTitleOffset( 1.2 );
//  }

//  tdc[0] -> Draw();


//  TF1 *func = new TF1("func", fitfunc, 0., 4000., 4);

//    func -> SetParameter(0, a);
//    func -> SetParameter(1, b);
//    func -> SetParameter(2, c);
//    func -> SetParameter(3, d); 

//    func -> Draw();
//    tdc[0] -> Fit("func");


 


  for ( int i=0; i<4; i ++ ) {

    sprintf( oname, "qdc%d", i );
    sprintf( tname, "qdc%d", i );
    qdc[i] = new TH1F( oname, tname, 1000, 50., 4000. );

    sprintf( varexp, "qdc[%d]", i );
    tree -> Project( oname, varexp );

    qdc[i] -> GetXaxis() -> SetRangeUser( 0., 2000. );

    qdc[i] -> GetXaxis() -> SetTitle( "Energy [ch]" );
    qdc[i] -> GetXaxis() -> SetTitleSize( 0.07 );
    qdc[i] -> GetXaxis() -> SetTitleOffset( 1.2 );

    qdc[i] -> GetYaxis() -> SetTitle( "Counts" );
    qdc[i] -> GetYaxis() -> SetTitleSize( 0.07 );
    qdc[i] -> GetYaxis() -> SetTitleOffset( 1.2 );
  }


    qdc[1] -> Draw();

    TF1 *func = new TF1("func", fitfunc, 300., 400., 4);

    func -> SetParameter(0, a);
    func -> SetParameter(1, b);
    func -> SetParameter(2, c);
    func -> SetParameter(3, d); 

//    func -> Draw("SAME");
    qdc[1] -> Fit("gaus");



 

  // file -> Close();
}

