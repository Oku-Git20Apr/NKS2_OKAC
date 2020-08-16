void JvsC(){

 
 TGraph *J_o = new TGraph("JFCC_old.txt");//39mm
 TGraph *J_n = new TGraph("JFCC_new.txt");//10mm
 TGraph *C_o = new TGraph("Chiba_old.txt");//43mm
 TGraph *C_n = new TGraph("Chiba_new.txt");//20mm
 TGraph *J_2 = new TGraph("empty.txt");//20mm
 
 const int np_jo = J_o -> GetN();
 const int np_jn = J_n -> GetN();
 const int np_co = C_o -> GetN();
 const int np_cn = C_n -> GetN();
 const int np_j2 = J_2 -> GetN();

 double* y_jo;
 y_jo = J_o -> GetY();

 double* y_jn;
 y_jn = J_n -> GetY();

 double* y_co;
 y_co = C_o -> GetY();

 double* y_cn;
 y_cn = C_n -> GetY();

 double* y_j2;
 y_j2 = J_2 -> GetY();

 double* x_jo;
 x_jo = J_o -> GetX();

 double* x_jn;
 x_jn = J_n -> GetX();

 double* x_co;
 x_co = C_o -> GetX();

 double* x_cn;
 x_cn = C_n -> GetX();

 double* x_j2;
 x_j2 = J_2 -> GetX();

 for( int i=0; i<np_jo;i++){
 if(y_jo[i] < 0) y_jo[i] = 0.;	
}

 for( int i=0; i<np_jn;i++){
 if(y_jn[i] < 0) y_jn[i] = 0.;
}
 
 for( int i=0; i<np_co;i++){
 if(y_co[i] < 0) y_co[i] = 0.;	
}

 for( int i=0; i<np_cn;i++){
 if(y_cn[i] < 0) y_cn[i] = 0.;
}

 for( int i=0; i<np_j2;i++){
 if(y_j2[i] < 0) y_j2[i] = 0.;
}

 double ynorm_jo[np_jo];
 double ynorm_jn[np_jn];
 double ynorm_co[np_co];
 double ynorm_cn[np_cn];
 double ynorm_j2[np_j2];

 for( int i=0; i<np_jo;i++){
	ynorm_jo[i] = pow((y_jo[i]/100.), (10./39.))*100;
}

 for( int i=0; i<np_jn;i++){
	ynorm_jn[i] = pow((y_jn[i]/100.), (10./10.))*100.;
}

 for( int i=0; i<np_co;i++){
	ynorm_co[i] = pow((y_co[i]/100.), (10./43.))*100;
}

 for( int i=0; i<np_cn;i++){
	ynorm_cn[i] = pow((y_cn[i]/100.), (10./20.))*100.;
}

 for( int i=0; i<np_j2;i++){
	ynorm_j2[i] =pow((y_j2[i]/100.), (10./10.))*100.;
}

  Double_t xlo = 400.;    // x の下限
  Double_t xhi = 800.;   // x の上限
  Double_t ylo = 60.;    // y の下限
  Double_t yhi = 110.;   // y の上限
  TCanvas *c1 = new TCanvas("c1","My Canvas",600,600);
  TH1F *frame = gPad->DrawFrame(xlo,ylo,xhi,yhi);

  TGraph *gnorm_jo = new TGraph(np_jo, x_jo, ynorm_jo);
  TGraph *gnorm_jn = new TGraph(np_jn, x_jn, ynorm_jn);
  TGraph *gnorm_co = new TGraph(np_jo, x_co, ynorm_co);
  TGraph *gnorm_cn = new TGraph(np_jn, x_cn, ynorm_cn);
  TGraph *gnorm_j2 = new TGraph(np_j2, x_j2, ynorm_j2);

  gnorm_jo->Draw("P*");
  gnorm_jn->Draw("P*");
  gnorm_co->Draw("P*");
  gnorm_cn->Draw("P*");
  gnorm_j2->Draw("P*");

 
 gnorm_jo->SetMarkerStyle(8);
 gnorm_jo->SetMarkerSize(1);
 gnorm_jo->SetMarkerColor(2);//red
 gnorm_jn->SetMarkerStyle(8);
 gnorm_jn->SetMarkerSize(1);
 gnorm_jn->SetMarkerColor(6); //magenta?
 gnorm_co->SetMarkerStyle(8);
 gnorm_co->SetMarkerSize(1);
 gnorm_co->SetMarkerColor(4);//blue
 gnorm_cn->SetMarkerStyle(8);
 gnorm_cn->SetMarkerSize(1);
 gnorm_cn->SetMarkerColor(3);//green 
 gnorm_j2->SetMarkerStyle(8);
 gnorm_j2->SetMarkerSize(1);
 gnorm_j2->SetMarkerColor(1);//black

// TLegend *tl = new TLegend(0.5,0.7,0.85,0.85);
// tl->AddEntry(g_h,"Layer 9","p");
// tl->AddEntry(g_c,"Layer 13","p");
// tl->AddEntry(g_s,"Layer 18","p");;
// tl->Draw();
}
