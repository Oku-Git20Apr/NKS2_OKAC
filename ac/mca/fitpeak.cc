Double_t F_lambda( Double_t *x, Double_t *par )
{
 Double_t val;
 Double_t fitgaus1, fitgaus2, fitpoly;

fitgaus = par[3] * TMath::Gaus(x[0], par[4], par[5]);
fitpoly = par[6] * pow(x[0], 3.0)  + par[7] * pow(x[0], 2.0) + par[8] * x[0] + par[9];
val = fitgaus + fitpoly;
 return val;
}

void draw(){

const Double_t a = 12.; //scale of gaus
const Double_t b = 0.08; //mean of gaus
const Double_t c = 0.003; //sigma of gaus
const Double_t d = -4000.; //polynomial, coefficient of x^3
const Double_t e = -80.; //x^2
const Double_t f = 85.; //x
const Double_t g = 3.4; //const


 TFile *file = new TFile( "run1.mca", "READONLY" );
 
 TTree *tree = new TTree();

 TF1 *f1 = new TF1("f1", F_peak, -0.1, 0.15, 10);
 f1->SetParameter(0, a);
 f1->SetParameter(1, b);
 f1->SetParameter(2, c);
 f1->SetParameter(3, d);
 f1->SetParameter(4, e);
 f1->SetParameter(5, f);
 f1->SetParameter(6, g);

 h_mm->Fit(f1,"0","",-0.1,0.15); //fitting

 TCanvas *c1 = new TCanvas("c1","c1",800,600);
 tree->Draw();
 f1->Draw("same");
 
}
