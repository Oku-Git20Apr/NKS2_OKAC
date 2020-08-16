double F_Gauss(double *t, double *par){

	double x = t[0];
	double scale = par[0];
	double mean = par[1];
	double sigma = par[2];

	double y = 1/sqrt(2.*TMath::Pi()*sigma*sigma)*TMath::Exp(-pow((x-mean),2.)/2/sigma/sigma);
	return y;
}


void func(){

const Double_t a = 1000.; //scale
const Double_t b = 500.; //mean
const Double_t c = 100.; //sigma
 

 TF1 *f1 = new TF1("f1", F_Gauss, 0., 1000., 3);
 f1->SetParameter(0, a);
 f1->SetParameter(1, b);
 f1->SetParameter(2, c);

 f1->Draw("");
 
}
