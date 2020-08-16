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

void draw(){


  TChain *tree = new TChain("tree");
  tree->Add("10676.root");

  //                     ch1    ch2

   float pedestal[2] = { 194.3, 86.0 };
   float peak_pe[2] = { 319.8, 195.6 };

    TH1D *ch1_qdc;     //ohhldadc[7]
    ch1_qdc = new TH1D("ch1_qdc","ch1_qdc",1000,0,3000);  //qdc channel
    
    TH1D *ch1_pe;      //number of photoelectron
    ch1_pe = new TH1D("ch1_pe","ch1_pe",35,-5,30);
    SetTH1(ch1_pe,"ch1_pe","Number of photoelectron","Counts");
    tree->Project("ch1_qdc","ohhldadc[7]","","");

  char condi[1000];
  sprintf( condi, "(ohhldadc[7]-%f)/%f", pedestal[0], peak_pe[0]-pedestal[0] ); 

    TH1D *ch2_qdc;     //ohhldadc[8]
    ch2_qdc = new TH1D("ch2_qdc","ch2_qdc",1000,0,3000);  //qdc channel
    
    TH1D *ch2_pe;      //number of photoelectron
    ch2_pe = new TH1D("ch2_pe","ch2_pe",35,-5,30);
    SetTH1(ch2_pe,"ch2_pe","Number of photoelectron","Counts");
    tree->Project("ch2_qdc","ohhldadc[8]","","");


  char condi2[1000];

  sprintf( condi2, "(ohhldadc[8]-%f)/%f", pedestal[1], peak_pe[1]-pedestal[1] );

    char condi3[1000];
    sprintf( condi3, "%s:%s", condi, condi2 );
    
    TH2D *ch1vsch2;
    ch1vsch2 = new TH2D("ch1_pe_ch2_pe","ch1_pe vs. ch2_pe",20,0.,10.,20,0.,10.);

    tree->Project("ch1_pe_ch2_pe", condi3, "ohhldadc[4]>0&&ohhldadc[5]>0&&ohhldtdc[4]>0&&ohhldtdc[5]>0&&abs(ohhldadc[3]-1000)<500&&abs(ohhldadc[6]-1850)<350");

    ch1vsch2->Draw("colz");


}
