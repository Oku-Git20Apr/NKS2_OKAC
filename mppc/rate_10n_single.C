const int nCanvas=1;

void rate_10n_single(){


    cout<<"before file open"<<endl;

	TChain *tree = new TChain("tree");
	tree->Add("r0000186.root");

    cout<<"after file open"<<endl;


    int ENum =tree-> GetEntries();
    cout << "Total Event Number is " << ENum << endl;

	TH1D *h_qdc[7];
      h_qdc[0] = new TH1D("h_qdc[0]","h_qdc[0]",800,200.,1000.);
	  tree->Project("h_qdc[0]","qdc[0]","","");
	  SetTH1(h_qdc[0],"QDC distribution","QDC [ch]","Counts");

	  tree->Reset();

	  tree->Add("r0000187.root");
      h_qdc[1] = new TH1D("h_qdc[1]","h_qdc[1]",800,200.,1000.);
	  tree->Project("h_qdc[1]","qdc[0]","","");
	  SetTH1(h_qdc[1],"QDC distribution","QDC [ch]","Counts");

	  tree->Reset();

	  tree->Add("r0000189.root");
      h_qdc[2] = new TH1D("h_qdc[2]","h_qdc[2]",800,200.,1000.);
	  tree->Project("h_qdc[2]","qdc[0]","","");
	  SetTH1(h_qdc[2],"QDC distribution","QDC [ch]","Counts");

	  tree->Reset();

	  tree->Add("r0000190.root");
      h_qdc[3] = new TH1D("h_qdc[3]","h_qdc[3]",800,200.,1000.);
	  tree->Project("h_qdc[3]","qdc[0]","","");
	  SetTH1(h_qdc[3],"QDC distribution","QDC [ch]","Counts");

	  tree->Reset();

	  tree->Add("r0000191.root");
      h_qdc[4] = new TH1D("h_qdc[4]","h_qdc[4]",800,200.,1000.);
	  tree->Project("h_qdc[4]","qdc[0]","","");
	  SetTH1(h_qdc[4],"QDC distribution","QDC [ch]","Counts");

	TCanvas *c[nCanvas];
    for(int i=0;i<nCanvas;i++){
      c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),800,600);
    }
    c[0]->Clear();
	h_qdc[0]->SetFillColor(kAzure+1);
	h_qdc[1]->SetFillColor(kGreen+1);
	h_qdc[2]->SetFillColor(kGreen+2);
	h_qdc[3]->SetFillColor(kGreen+3);
	h_qdc[4]->SetFillColor(kGreen+4);
	h_qdc[0]->Draw("");
	h_qdc[1]->Draw("same");
	h_qdc[2]->Draw("same");
	h_qdc[3]->Draw("same");
	h_qdc[4]->Draw("same");
//    c[0]->Divide(2,3);
//    c[0]->cd(1);h_qdc[0]->Draw("");h_qdc_cut[0]->Draw("same");
//    c[0]->cd(2);h_qdc[1]->Draw("");h_qdc_cut[1]->Draw("same");
//    c[0]->cd(3);h_pe[0]->Draw("");
//    c[0]->cd(4);h_pe[1]->Draw("");
//    c[0]->cd(5);h_pe[2]->Draw("");h_pe[2]->Fit("f1","","",1.,5.);f1->Draw("same");
//    c[0]->cd(6);h2_qdc[0]->Draw("colz");
//    c[1]->Clear();
//    c[1]->Divide(2,2);
//	c[1]->cd(1);h_tdc[0]->Draw("");
//	c[1]->cd(2);h_tdc[1]->Draw("");
//	c[1]->cd(3);h_tdc[2]->Draw("");
//	c[1]->cd(4);h_tdc[3]->Draw("");
//    for(int i=0;i<4;i++){
//      c[1]->cd(i+1);h_tdc[i]->Draw();
//    }
}
