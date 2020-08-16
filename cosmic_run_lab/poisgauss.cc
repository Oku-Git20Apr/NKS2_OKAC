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

void draw(){

  double lambda = 10.;
  double res = 1.0;
  int roop = 100000;

  TH1D *h1 = new TH1D("h1","h1",400,0,50);

  gRandom->SetSeed(0);
  for(int i=0;i<roop;i++){
    double pois = gRandom->PoissonD(lambda);
    double gaus = gRandom->Gaus(pois,res*sqrt(pois));
    double val = pois + gaus;
    h1->Fill(val);
  }

  TF1 *f1 = new TF1("f1",F_Pois,0,50,3);
  f1->SetNpx(500);
  f1->SetParameters(lambda,res,roop);
  h1->Fit(f1,"0","",0,50);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.15,0.15,0.15);
    h1->Draw();
    f1->Draw("same");

}
