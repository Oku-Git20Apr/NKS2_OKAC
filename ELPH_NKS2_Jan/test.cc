//--------------------------------------------------------------------
void SetTH1(TH1 *h, TString name, TString xname, TString yname, int LColor=1, int FStyle=0, int FColor=0){
  h->SetTitle(name);
  h->SetLineColor(LColor);
  h->SetLineWidth(0);
  h->SetTitleSize(0.04,"");
  h->SetTitleFont(42,"");
  h->SetFillStyle(FStyle);
  h->SetFillColor(FColor);

  h->GetXaxis()->SetTitle(xname);
  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetTitleOffset(0.90);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelOffset(0.01);

  h->GetYaxis()->SetTitle(yname);
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleOffset(1.00);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelOffset(0.01);
  ((TGaxis*)h->GetYaxis())->SetMaxDigits(4);
}

///////////////////////////////////////////////////////////////////////////black box
double sqrt2pi = sqrt(2.*3.141592);
double F_Pois( double *x, double *par )
{
  /*
    par[0] : lambda, average of #photon
    par[1] : energy resolution factor
    par[2] : menseki
  */
  double val = 0;
  for( int np=1; np<200; np++ ){
    double pois;
    double sigma = par[1]*sqrt(np);
    if(np<50){
      pois = par[2]*pow( par[0], np )*exp(-par[0])/TMath::Gamma(np+1);
    }
    else{ // stirling's approximation
      pois = par[2]*pow( par[0]/np, np )*exp(-par[0]+np)/(sqrt2pi*pow(np,0.5));
    }
    val += pois/(sqrt2pi*sigma)*exp( -pow(x[0]-np,2)/2./sigma/sigma ); // adding gauss    ian distribution
  }
  return val;
}
//////////////////////////////////////////////////////////////////////////////black box

//////////////////////////////////////////////////////////////////////////////
void draw(){

  double lambda = 8.;    //average of #photon
  double res = 0.68;      //energy resolution factor
  int roop = 2000;        //menseki

  TChain *tree = new TChain("tree");
  tree->Add("10676.root");

  //                     ch1    ch2
  float pedestal[2] = { 98.6, 106.9 };  
  float peak_pe[2] = { 175.8, 143.0 };

    TH1D *ch1_ohhldadc;     //ohhldadc[4]
    ch1_ohhldadc = new TH1D("ch1_ohhldadc","ch1_ohhldadc",1000,0,4000);  //ohhldadc channel
    
    TH1D *ch1_pe;      //number of photoelectron
    ch1_pe = new TH1D("ch1_pe","ch1_pe", 35, -5,30);
    SetTH1(ch1_pe,"ch1_pe","Number of photoelectron","Counts");
    tree->Project("ch1_ohhldadc","ohhldadc[4]","","");


    TH1D *ch2_ohhldadc;     //ohhldadc[5]
    ch2_ohhldadc = new TH1D("ch2_ohhldadc","ch2_ohhldadc",1000,0,4000);  //ohhldadc channel
    
    TH1D *ch2_pe;      //number of photoelectron
    ch2_pe = new TH1D("ch2_pe","ch2_pe",35,-5,30);
    SetTH1(ch2_pe,"ch2_pe","Number of photoelectron","Counts");
    tree->Project("ch2_ohhldadc","ohhldadc[5]","","");

    TH1D *Total;    //ch1+ch2(NPE)
    Total = new TH1D("Total","Total", 35,-5,30);
    SetTH1(Total,"Total","Number of Photo-Electrons","Counts");

  char condi[1000];

  sprintf( condi, "(ohhldadc[4]-%f)/%f+(ohhldadc[5]-%f)/%f",pedestal[0], peak_pe[0]-pedestal[0], pedestal[1], peak_pe[1]-pedestal[1] );


    tree->Project("Total", condi, "ohhldtdc[4]>0&&ohhldtdc[5]>0&&ohhldadc[4]>0&&ohhldadc[5]>0&&abs(ohhldadc[3]-800)<300&&abs(ohhldadc[6]-500)<500");

 TF1 *f1 = new TF1("f1",F_Pois,2,12,3);
  f1->SetNpx(500);
  f1->SetParameters(lambda,res,roop);
  Total->Fit(f1,"0","",2,12);    //fitting

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.15,0.15,0.15);
    Total->Draw("e");
    f1->Draw("same");

}
