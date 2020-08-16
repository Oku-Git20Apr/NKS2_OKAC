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
void npevsnpe(){
	TCanvas *c1;
	c1=new TCanvas("c1","c1",600,600);
  double lambda = 8.;    //average of #photon
  double res = 0.68;      //energy resolution factor
  int roop = 122;        //menseki

  TChain *tree = new TChain("tree");
  tree->Add("10676.root");

    TH2D *npenpe;
    npenpe = new TH2D("npe-npe","",40,0.,4000.,40,0.,4000.);
    tree->Project("npe-npe", "ohhldadc[3]:ohhldadc[6]", "ohhldadc[3]>2500");
 

 
    npenpe->Draw("colz");
	npenpe->SetStats(0);
}
