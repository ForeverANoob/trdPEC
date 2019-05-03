

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH2F.h"
//#include "TNuple.h"
#include "TFolder.h"
#include "TList.h"

#include <iostream>


void histMod(){
	
    	
	//cout << "Does this work" << endl;	

	//TCanvas *C = new TCanvas("C","C",800,600);
	//TProfile hprof;
	//TNuple ntuple;
	//TFile* file = TFile::Open("DigitsExtractQA.root", "OLD");
	//TFile* file = new TFile("AnalysisResults.root", "READ");
	TFile* file = new TFile("ROOTMERGE-3506e898-6827-11e9-9717-51ea9e89beef.root", "READ");
	file->ls();
	//TFolder *histos = (TFolder*)(file->FindObjectAny("cdigitqa"));
	//histos->FindObjectAny("fhpte")->Draw();
	//file->cd("cdigitqa");
	TList *lst1 = (TList*)(file->FindObjectAny("MyTask;1"));
	TList *lst = (TList*)(file->FindObjectAny("MyOutputContainer"));
	
	file->GetListOfKeys()->Print();
	//gPad->SetLogy();
	
	// get your histograms here
	TH2F* H1 = (TH2*)lst->FindObject("fhp2pt");
	TH2F* H2 = (TH2*)lst->FindObject("fhp2pte");
	// Now design your histogram
	//gPad->SetLogy();
	//for (Int_t i = 0; i < 400; i++){
	//    H1[i] -= H2[i]
	//}

	H2->Divide(H1);
	H2->Draw();
	
 	file->Close();
	//
}
