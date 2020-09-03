void ePlot(){
  TFile *fin=TFile::Open("o_genG4.root","READ");
  TTree *t=(TTree*)fin->Get("t");
  
  const int nStp=61;
  double x[nStp],dx[nStp];
  double y[nStp],dy[nStp];

  TCanvas *c1=new TCanvas();
  c1->Divide(3);
  gStyle->SetOptStat("eM");

  TH1D *h=new TH1D("he","kE",400,0,1000);
  for(int i=0;i<nStp;i++){
    h->Reset();
    float z1= -0.3+i*0.01;
    t->Project("he","kE",Form("z>%4.2f && z<%4.2f",z1,z1+0.01));
    x[i]=z1+0.005;
    dx[i]=0;
    y[i]=h->GetMean();
    dy[i]=h->GetMeanError();
    if(i==4){
      c1->cd(1);
      h->SetTitle(Form("kE @ z=%5.3f",x[i]));
      h->DrawCopy();
      gPad->SetLogy(1);
    }else if(i==56){
      c1->cd(3);
      h->SetTitle(Form("kE @ z=%5.3f",x[i]));
      h->DrawCopy();
    }
  }
  TGraphErrors *g=new TGraphErrors(nStp-1,x,y,dx,dy);
  g->SetTitle("Average kinetic energy;z position in target [mm]; kE [MeV]");
  g->SetMarkerStyle(20);
  c1->cd(2);
  g->Draw("APL");
  fin->Close();
}
