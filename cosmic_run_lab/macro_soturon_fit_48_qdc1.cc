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

//////////////////////////////////////////////////////////////////////////////
void macro_soturon_fit_48_qdc1(){

  TChain *tree = new TChain("tree");
  tree->Add("r0000048.root");
  TCanvas *c = new TCanvas("c","c",800,600);

  TH1D *Hist;     //qdc[1]
  Hist = new TH1D("Hist","Hist",1000,0.,1000);  //qdc channel
  tree->Project("Hist","qdc[1]","","");

  char condi[1000];

  TF1 *f1 = new TF1("f1","gaus",70.,160.);


  c->SetLogy(1);
  Hist->Draw("");
  Hist->Fit("f1","","",105.,131.);
  f1->SetLineStyle(2);
  f1->Draw("same");

  Hist -> SetStats(0); //statistic box does not appear
	

}
