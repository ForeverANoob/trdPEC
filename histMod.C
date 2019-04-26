

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
	TFile* file = new TFile("DigitsExtractQA.root", "READ");
	file->ls();
	//TFolder *histos = (TFolder*)(file->FindObjectAny("cdigitqa"));
	//histos->FindObjectAny("fhpte")->Draw();
	//file->cd("cdigitqa");
	TList *lst = (TList*)(file->FindObjectAny("cdigitqa;1"));
	TH2F* fhdEdxe = new TH2F("fhdEdxe","fhdEdxe",100, 0, 10, 100, 0, 10);
	//TH2F* fhdEdxp = new TH2F("fhdEdxp","fhdEdxp",100,0,10,100,0,10);
	cout << "I'm tired " << lst->FindObject("fhptp") << endl;
	//C->Add(fhdEdxe);
	//file->Add(fhdEdxe);
	for (Int_t i=0;i<10000;i++){
	    fhdEdxe->Fill(i*0.005, i*0.005);
	    //cout << "hi" << endl;
	}
	//fhdEdxe->Draw();
	//fhdEdxe->Write();	
	//TFile file = new TFile("DigitsExtractQA.root");
	file->GetListOfKeys()->Print();

	// get your histograms here
	TH2F* myHist = (TH2*)lst->FindObject("fhdEdx");
	// 
	// Now design your histogram


	myHist->Draw();
	
 	file->Close();
	//
}
