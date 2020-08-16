void gain_fit_mppc(){

  TChain *tree = new TChain("tree");
  tree->Add("r0000225.root");
  TCanvas *c = new TCanvas("c","c",800,600);

  double mean = 310;//from fitting
  double sigma = 3;//from fitting

  double fit_range = 1.5*sigma;//Fit range, [peak-fit_range,peak+fit_range]

  TH1D *Hist;     
  Hist = new TH1D("Hist","Hist",150,250.,400.);
  tree->Project("Hist","qdc[0]","","");
//  SetTH1(Hist,"Vop=52.27 [V]","QDC [ch]","Counts"); 


  TF1 *f1 = new TF1("f1","gausn",250.,400.);
  f1->SetParameters(1000.,mean,sigma);

  c->SetLogy(0);//Linear
  Hist->Draw("");
  Hist->Fit("f1","","",mean-fit_range,mean+fit_range);
  f1->SetLineStyle(2);
  f1->Draw("same");

  Hist -> SetStats(0); //statistic box does not appear
	

}
