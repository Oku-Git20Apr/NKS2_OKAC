Double_t fitfunc(Double_t *x, Double_t *param){

   if((int) (((x[0] - param[3])/ param[2])) < 0){

       return 0.;
   }else{
       Double_t fitval
          = param[0] * TMath::Poisson((( x[0] - param[3])/ param[2]), param[1]);
       return fitval;

   }
}



void fittest( const char *input_root_file = "../root/r0000003.root",
              const char *ps_file = "../ps/hist_run003.ps" ,
              const Double_t a = 1500.,            //initial param
              const Double_t b = 4.,
              const Double_t c = 1.5.,
              const Double_t d = 67.,           ) {


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


  for ( int i=0; i<4; i ++ ) {

    sprintf( oname, "tdc%d", i );
    sprintf( tname, "tdc%d", i );
    tdc[i] = new TH1F( oname, "", 512, 0., 4096. );

    sprintf( varexp, "tdc[%d]", i );
    tree -> Project( oname, varexp  );

    tdc[i] -> GetXaxis() -> SetRangeUser( 750., 1050. );

    tdc[i] -> GetXaxis() -> SetTitle( "Time [ch]" );
    tdc[i] -> GetXaxis() -> SetTitleSize( 0.07 );
    tdc[i] -> GetXaxis() -> SetTitleOffset( 1.2 );

    tdc[i] -> GetYaxis() -> SetTitle( "Counts" );
    tdc[i] -> GetYaxis() -> SetTitleSize( 0.07 );
    tdc[i] -> GetYaxis() -> SetTitleOffset( 1.2 );
  }



  TCanvas *c1 = new TCanvas("c1","c1", 600, 600 );

  TPostScript* ps1 = new TPostScript( ps_file, -111 );
  ps1 -> NewPage();


  TPad *p1[4];

  p1[0] = new TPad( "p1_0", "p1_0", 0.0, 0.5,  0.5, 1.0  );
  p1[1] = new TPad( "p1_1", "p1_1", 0.5, 0.5,  1.0, 1.0  );
  p1[2] = new TPad( "p1_2", "p1_2", 0.0, 0.0,  0.5, 0.5  );
  p1[3] = new TPad( "p1_3", "p1_3", 0.5, 0.0,  1.0, 0.5  );

  c1 -> cd();
  for ( int i=0; i<4; i ++ ) {
    p1[i] -> SetTopMargin( 0.05 );
    p1[i] -> SetBottomMargin( 0.20 );
    p1[i] -> SetRightMargin( 0.05 );
    p1[i] -> SetLeftMargin( 0.20 );
    p1[i] -> Draw();

  }
  for ( int i=0; i<4; i ++ ) {
    p1[i] -> cd();
    p1[i] -> SetLogy( 0 );  // linear

    tdc[i] -> Draw();

    TF1 *func = new TF1("func", fitfunc, 50., 100., 4);

    func -> SetParameter(0, a);
    func -> SetParameter(1, b);
    func -> SetParameter(2, c);
    func -> SetParameter(3, d); 

//    fitfunc -> Draw();
    tdc[i] -> Fit("func");


  }

  c1 -> Update();


  ps1 -> NewPage();


  for ( int i=0; i<4; i ++ ) {

    sprintf( oname, "qdc%d", i );
    sprintf( tname, "qdc%d", i );
    qdc[i] = new TH1F( oname, tname, 50, 50., 100. );

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

  for ( int i=0; i<4; i ++ ) {
    p1[i] -> cd();
    p1[i] -> SetLogy(0);  // linear

    qdc[i] -> Draw();

    TF1 *func = new TF1("func", fitfunc, 50., 100., 4);

    func -> SetParameter(0, a);
    func -> SetParameter(1, b);
    func -> SetParameter(2, c);
    func -> SetParameter(3, d); 

//    fitfunc -> Draw();
    qdc[i] -> Fit("func");



  }

  c1 -> Update();


  ps1 -> Close();
  



  // file -> Close();


}
