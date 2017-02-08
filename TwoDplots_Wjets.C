void removeCharsFromString( string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
         str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}
	    
void TwoDplots_Wjets()
{
  gStyle->SetOptStat(0);

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

float factor[7] = {
	0.755,	0.0086,
	0.404,	0.0005,
	0.2808,	0.0287,
	0.0395
};

    TFile * f100 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets100a_mu.root");
    TFile * f1200 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets1200a_mu.root");
    TFile * f200 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets200a_mu.root");
    TFile * f2500 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets2500a_mu.root");
    TFile * f400 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets400a_mu.root");
    TFile * f600 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets600a_mu.root");
    TFile * f800 = new TFile("/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/WWTree_WJets800ext1_mu.root");

    TTree *t100 = (TTree*)f100->Get("otree");
    TTree *t1200 = (TTree*)f1200->Get("otree");
    TTree *t200 = (TTree*)f200->Get("otree");
    TTree *t2500 = (TTree*)f2500->Get("otree");
    TTree *t400 = (TTree*)f400->Get("otree");
    TTree *t600 = (TTree*)f600->Get("otree");
    TTree *t800 = (TTree*)f800->Get("otree");


    TCut cut = "l_pt>30 && abs(l_eta)<2.1 && v_pt>200 && PuppiAK8_jet_pt_so>200 && abs(ungroomed_PuppiAK8_jet_eta)<2.4 && PuppiAK8_jet_tau2tau1<0.55 && pfMETpuppi>50 && PuppiAK8_jet_mass_pr>40 && PuppiAK8_jet_mass_pr<140 && vbf_maxpt_j1_pt>40 && vbf_maxpt_j2_pt>40 && abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>3.5 && vbf_maxpt_j1_bDiscriminatorCSV<0.244 && vbf_maxpt_j2_bDiscriminatorCSV<0.244 && vbf_maxpt_jj_m>800 && mass_lvj_type0>800 && deltaphi_METak8jet>2.0 && deltaR_lPuppiak8jet>1.57";

 
    const char * variable[12] = {
	"vbf_maxpt_j1_pt","vbf_maxpt_j1_eta",
	"vbf_maxpt_j2_pt","vbf_maxpt_j2_eta",
	"PuppiAK8_jet_pt_so","vbf_maxpt_j1_pt",
	"PuppiAK8_jet_pt_so","vbf_maxpt_j2_pt",
	"PuppiAK8_jet_pt_so","vbf_maxpt_j1_pt*vbf_maxpt_j2_pt",
	"l_pt*PuppiAK8_jet_pt_so","vbf_maxpt_j1_pt*vbf_maxpt_j2_pt"
    };

    Int_t bin[6] = {20,20,20,20,20,20};
    Double_t range[24] = {
	-4.5,4.5,30,900,
	-4.5,4.5,30,500,
	30,900,200,1000,
	30,500,200,1000,
	1000,25000,200,1000,
	1000,25000,6000,25000
    };

TCanvas *c1 = new TCanvas("c1","c1",800,600);
c1->SetRightMargin(0.15);
c1->SetGridx();
c1->SetGridy();
c1->SetLogz();
for(int i = 0; i<5; i++)
{
    TH2F * h1 = new TH2F("h1", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t100->Draw(Form("%s:%s>>h1",variable[i*2],variable[i*2+1]),cut,"colz");
    h1->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h1->GetZaxis()->SetRange(0,100);
    h1->Scale(factor[0]);

    TH2F * h2 = new TH2F("h2", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t1200->Draw(Form("%s:%s>>h2",variable[i*2],variable[i*2+1]),cut,"colz");
    h2->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h2->GetZaxis()->SetRange(0,100);
    h2->Scale(factor[1]);

    TH2F * h3 = new TH2F("h3", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t200->Draw(Form("%s:%s>>h3",variable[i*2],variable[i*2+1]),cut,"colz");
    h3->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h3->GetZaxis()->SetRange(0,100);
    h3->Scale(factor[2]);

    TH2F * h4 = new TH2F("h4", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t2500->Draw(Form("%s:%s>>h4",variable[i*2],variable[i*2+1]),cut,"colz");
    h4->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h4->GetZaxis()->SetRange(0,100);
    h4->Scale(factor[3]);

    TH2F * h5 = new TH2F("h5", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t400->Draw(Form("%s:%s>>h5",variable[i*2],variable[i*2+1]),cut,"colz");
    h5->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h5->GetZaxis()->SetRange(0,100);
    h5->Scale(factor[4]);

    TH2F * h6 = new TH2F("h6", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t600->Draw(Form("%s:%s>>h6",variable[i*2],variable[i*2+1]),cut,"colz");
    h6->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h6->GetZaxis()->SetRange(0,100);
    h6->Scale(factor[5]);

    TH2F * h7 = new TH2F("h7", "WJets-HTbin",bin[i], range[i*4],range[i*4+1] , bin[i],range[i*4+2] , range[i*4+3]);
    t800->Draw(Form("%s:%s>>h7",variable[i*2],variable[i*2+1]),cut,"colz");
    h7->SetTitle(Form("WJets-HTbin ; %s ; %s", variable[i*2+1],variable[i*2]));
    h7->GetZaxis()->SetRange(0,100);
    h7->Scale(factor[6]);

    TList *list = new TList;
    list->Add(h1);
    list->Add(h2);
    list->Add(h3);
    list->Add(h4);
    list->Add(h5);
    list->Add(h6);
    list->Add(h7);

    TH1F *h = (TH1F*)h1->Clone("h");
    h->Reset();
    h->Merge(list);
    h->Draw("colz");
    h->GetZaxis()->SetRangeUser(0,1);
    const char * ext = ".png";
    const char * pre = "Scatter_WJets-HTbin_";
    string name = string(pre) + string(variable[i*2])+string(variable[i*2+1]) + string(ext);
    
    char chars[] = ":*+-/";
    removeCharsFromString( name, chars);

    c1->SaveAs(name.c_str());
    c1->Clear();
    h1->Clear();
    h2->Clear();
    h3->Clear();
    h4->Clear();
    h5->Clear();
    h6->Clear();
    h7->Clear();

 }   

}
