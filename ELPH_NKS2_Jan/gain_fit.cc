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
void gain_fit(){

  TChain *tree = new TChain("tree");
  tree->Add("10680.root");

    TH1D *Hist;     //qdc[1]
    Hist = new TH1D("Hist","Hist",250,0,1000);  //qdc channel
    tree->Project("Hist","ohhldadc[8]","ohhldtdc[8]>0","");

  char condi[1000];

//    tree->Project("Total", condi, "qdc[0]>600&&qdc[3]>1000&&tdc[1]>0&&tdc[2]>0&&qdc[1]>0&&qdc[2]>0&&tdc[4]+1.115*tdc[5]>1020&&tdc[4]+1.115*tdc[5]<1070&&tdc[4]-tdc[5]<-180&&tdc[4]-tdc[5]>-240");

  gStyle->SetOptLogy(0);
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  Hist->Draw("");

  Hist -> SetStats(0); //statistic box does not appear
	

}
