void gain_bias_dependence(){

  TGraphErrors *g = new TGraphErrors("gain_txt2.dat");  
  g->SetLineWidth(4);
  g->SetLineColor(kAzure);
  g->Draw("AP");

  TF1 *f1 = new TF1("f1","[0]*x+[1]",51.5,57.);
  f1->SetParameters(20.,10.);
  g->Fit("f1","","",51.5,57.);
  f1->SetLineStyle(2);
  f1->Draw("same");

  //g -> SetStats(0); //statistic box does not appear

}
