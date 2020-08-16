void gain_55V(){

  TChain *tree = new TChain("tree");
  tree->Add("r0000180.root");
  TCanvas *c = new TCanvas("c","c",800,600);

  double range = 100.;//Hist range, [peak-range,peak+range]
  double nbins = 200;//nbins of Hist
  double view_range = 4000.;//View range, [peak-view_range,peak+view_range]
  double nbins_of_view = 4000;//nbins of View
  double fit_range = 5.;//Fit range, [peak-fit_range,peak+fit_range]

  TH1D *View,*Hist;     
  View = new TH1D("View","View",nbins_of_view,0.,view_range);
  tree->Project("View","qdc[0]","","");
  double main_part = (View->GetBinCenter(View->GetMaximumBin()))-view_range/nbins_of_view/2;
  Hist = new TH1D("Hist","Hist",250,250.,500.);
  tree->Project("Hist","qdc[0]","","");
  SetTH1(Hist,"Vop=55.25 [V]","QDC [ch]","Counts"); 

  char condi[1000];

  TF1 *f1 = new TF1("f1","gausn(0)+gausn(3)+gausn(6)",250.,500.);
  f1->SetParameters(5000.,280.,10.,10000.,350.,30.,10000.,400.,40.);
  double center = (Hist->GetBinCenter(Hist->GetMaximumBin()))-range/(double)nbins;
//  cout << "Maximum at " << center << " [ch]" <<endl; 

  c->SetLogy(0);//Linear
  Hist->Draw("");
  TFitResultPtr r = Hist->Fit("f1","S","",276,447.);
  f1->SetLineStyle(2);
  f1->Draw("same");
  //TMatrixD cor = r->GetCorrelationMatrix();
  //cor.Print();
  TMatrixD cov = r->GetCovarianceMatrix();
  cov.Print();

  Hist -> SetStats(0); //statistic box does not appear
	

}
