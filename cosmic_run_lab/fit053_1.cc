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

  double lambda = 3.;    //average of #photon
  double res = 1.0;      //energy resolution factor
  int roop = 4000;        //menseki

  TChain *tree = new TChain("tree");
  tree->Add("r0000053.root");

  //                     H1949    H7195
  float pedestal[2] = { 117.563, 116.383 };  
  float peak_pe[2] = { 331.290, 200.892 };

    TH1D *H1949_qdc;     //qdc[1]
    H1949_qdc = new TH1D("H1949_qdc","H1949_qdc",1000,0,2000);  //qdc channel
    
    TH1D *H1949_pe;      //number of photoelectron
    H1949_pe = new TH1D("H1949_pe","H1949_pe",150,-10,20);
    SetTH1(H1949_pe,"H1949_pe","Number of photoelectron","Counts");
    tree->Project("H1949_qdc","qdc[1]","","");

  char condi[1000];

  sprintf( condi, "(qdc[1]-%f)/%f", pedestal[0], peak_pe[0]-pedestal[0] );   //qdc channel -> number of photoelectron
    tree->Project( "H1949_pe", condi, "tdc[1]>0&&qdc[1]>0&&tdc[4]+1.115*tdc[5]>1020&&tdc[4]+1.115*tdc[5]<1070" );

 TF1 *f1 = new TF1("f1",F_Pois,0,20,3);
  f1->SetNpx(500);
  f1->SetParameters(lambda,res,roop);
  H1949_pe->Fit(f1,"0","",0,20);    //fitting

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.15,0.15,0.15);
    H1949_pe->Draw();
    f1->Draw("same");

}
