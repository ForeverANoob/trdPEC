/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* AliAnaysisTaskMyTask
 *
 * empty task which can serve as a starting point for building an analysis
 * as an example, one histogram is filled
 */

#include "TChain.h"
#include "TH1F.h"
#include "TList.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliESDEvent.h"
#include "AliESDInputHandler.h"
#include "AliAnalysisTaskMyTask.h"

#include <iostream>

class AliAnalysisTaskMyTask;    // your analysis class
class AliESD;
class AliTRDdigitsExtract;

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskMyTask) // classimp: necessary for root

AliAnalysisTaskMyTask::AliAnalysisTaskMyTask() : AliAnalysisTaskSE(), 
    fESD(0), fOutputList(0), fHistPt(0), fhtrdpt(0), fhdy(0), fhy(0), fhz(0), fhpid(0), 
    fhepid(0), fhPID(0), fhntl(0), fhapt(0), fhtrdapt(0), fhtrf(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char* name) : AliAnalysisTaskSE(name),
    fESD(0), fOutputList(0), fHistPt(0), fhtrdpt(0), fhdy(0), fhy(0), fhz(0), fhpid(0), 
    fhepid(0), fhPID(0), fhntl(0), fhapt(0), fhtrdapt(0), fhtrf(0)
{
    // constructor
    DefineInput(0, TChain::Class());    // define the input of the analysis: in this case we take a 'chain' of events
                                        // this chain is created by the analysis manager, so no need to worry about it, 
                                        // it does its work automatically
    DefineOutput(1, TList::Class());    // define the ouptut of the analysis: in this case it's a list of histograms 
                                        // you can add more output objects by calling DefineOutput(2, classname::Class())
                                        // if you add more output objects, make sure to call PostData for all of them, and to
                                        // make changes to your AddTask macro!
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::~AliAnalysisTaskMyTask()
{
    // destructor
    if(fOutputList) {
        delete fOutputList;     // at the end of your task, it is deleted from memory by calling this function
    }
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserCreateOutputObjects()
{
    // create output objects
    //
    // this function is called ONCE at the start of your analysis (RUNTIME)
    // here you ceate the histograms that you want to use 
    //
    // the histograms are in this case added to a tlist, this list is in the end saved
    // to an output file
    //
    fOutputList = new TList();          // this is a list which will contain all of your histograms
                                        // at the end of the analysis, the contents of this list are written
                                        // to the output file
    fOutputList->SetOwner(kTRUE);       // memory stuff: the list is owner of all objects it contains and will delete them
                                        // if requested (dont worry about this now)

    // example of a histogram
    fHistPt = new TH1F("fHistPt", "fHistPt", 100, 0, 10);       // create your histogra
    fhtrdpt = new TH1F("fhtrdpt", "fhtrdpt", 100,0,10);
    fhdy = new TH1F("fhdy","fhdy",100,0,100);    
    fhy = new TH1F("fhy","fhy",100,0,10000); 
    fhz = new TH1F("fhz","fhz",100, 0, 100); 
    fhpid = new TH1F("fhpid","fhpid", 280, 0, 280);
    fhepid = new TH1F("fhepid","fhepid",280,0,280); 
    fhPID = new TH1F("fhPID","fhPID",280,0,280);
    fhntl = new TH1F("fhntl","fhntl", 7, 0, 7);
    fhapt = new TH2F("fhapt","fhapt",10000,0,20000,2000,-500,500);
    fhtrdapt = new TH2F("fhtrdapt","fhtrdapt",10000,0,20000,2000,-500,500);
    fhtrf = new TH1F("fhtrf","fhtrf",50,0,50);


    fOutputList->Add(fHistPt);          // don't forget to add it to the list! the list will be written to file, so if you want
                                        // your histogram in the output file, add it to the list!
    fOutputList->Add(fhtrdpt);
    fOutputList->Add(fhdy); 
    fOutputList->Add(fhy);
    fOutputList->Add(fhz); 
    fOutputList->Add(fhpid); 
    fOutputList->Add(fhepid);
    fOutputList->Add(fhPID);
    fOutputList->Add(fhntl);
    fOutputList->Add(fhapt);
    fOutputList->Add(fhtrdapt); 
    fOutputList->Add(fhtrf);

    PostData(1, fOutputList);           // postdata will notify the analysis manager of changes / updates to the 
                                        // fOutputList object. the manager will in the end take care of writing your output to file
                                        // so it needs to know what's in the output
    
    AliAnalysisManager *man = AliAnalysisManager::GetAnalysisManager();
    if (man) {
        AliInputEventHandler* inputHandler = (AliInputEventHandler*)(man->GetInputEventHandler());
        if (inputHandler)   fPIDResponse = inputHandler->GetPIDResponse();
    }

}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserExec(Option_t *)
{
    // user exec
    // this function is called once for each event
    // the manager will take care of reading the events from file, and with the static function InputEvent() you 
    // have access to the current event. 
    // once you return from the UserExec function, the manager will retrieve the next event from the chain
    fESD = dynamic_cast<AliESDEvent*>(InputEvent());    // get an event (called fESD) from the input file
                                                        // there's another event format (ESD) which works in a similar wya
                                                        // but is more cpu/memory unfriendly. for now, we'll stick with aod's
    if(!fESD) return;                                   // if the pointer to the event is empty (getting it failed) skip this event
        // example part: i'll show how to loop over the tracks in an event 
        // and extract some information from them which we'll store in a histogram
    Int_t iTracks(fESD->GetNumberOfTracks());           // see how many tracks there are in the event
    Int_t iTrdTracks( fESD->GetNumberOfTrdTracks());
    //cout << "New event taken into consideration" << endl;
    cout << "Number of tracks " << fESD->GetNumberOfTracks() << endl;
    cout << "Number of trd tracks " << fESD->GetNumberOfTrdTracks() << endl;
    for(Int_t i(0); i < iTracks; i++) {                 // loop ove rall these tracks
	AliESDtrack* track = static_cast<AliESDtrack*>(fESD->GetTrack(i));         // get a track (type AliAODTrack) from the event

	
	//AliESDTrdTrack* trdtrack = fESD->GetTrdTrack(i);	
	
	if (!track) continue;
	// AliESDfriendTrack* friendtrack = (AliESDfriendTrack*)track->GetFriendTrack();
	//fhapt->Fill(track->GetA(), track->Pt());
	//if ( friendtrack->GetTRDtrack()) cout << "foound one!" << endl;	
	//AliESDTrdTrack* trdtrack;
	//if (track->GetTRDtrack()) {
	//    cout << track->GetTRDtrack() << endl;
	//}
	//Int_t tmp = 0;
	//for (Int_t index = 0; index < fESD->GetNumberOfTrdTracks(); index++){
	//    trdtrack = fESD->GetTrdTrack(index);
	//    if (trdtrack->GetPID() == track->GetPID()) {
	//	tmp = index;
	//	cout << "found one" << endl;
	//	break;
	//    }
	//}
	fHistPt->Fill(track->Pt());

	if (i > iTrdTracks) continue;
	AliESDTrdTrack* trdtrack = fESD->GetTrdTrack(i);
	if (!trdtrack) continue;
	//if (tmp==0) continue;
	cout << "Comparing tracks " << (trdtrack->Pt() == track->Pt()) << endl;
	cout << track->GetTRDtrack() << "  " << trdtrack << endl;


	Int_t tracklets = 0;  // layers of the trd?
	for (Int_t j = 0; j < 6; j++){
	   AliESDTrdTracklet* tracklet = trdtrack->GetTracklet(j);
	   //cout << "tracklet " << j << ": " << tracklet << endl;
	   if (!tracklet) continue;
	   
	   fhpid->Fill(tracklet->GetPID());
	   if (std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kElectron)) > 3 ){
	//	cout << "not an electron" << endl;
		//continue;
	   }		
 	  // cout << "Match trd track " << trdtrack->GetTrackMatch() << endl;	   
	   tracklets++;
	   fhdy->Fill(tracklet->GetBinDy());
	   fhy->Fill(tracklet->GetBinY());
	   fhz->Fill(tracklet->GetBinZ());
	   fhepid->Fill(tracklet->GetPID());
	  
	   if (tracklet->GetPID() != trdtrack->GetPID()){ 
	    //  cout << "PID values don't match "<< tracklet->GetPID() << " and " << trdtrack->GetPID() << endl; 
 	   
}
	}
	//cout << "a is here " << trdtrack->GetA() << endl;
	//cout << "Match trd track " << trdtrack->GetTrackMatch() << endl;	
        fhtrdpt->Fill(track->Pt());                     // plot the pt value of the track in a histogram
	fhtrdapt->Fill(trdtrack->GetA(), trdtrack->Pt());
	fhntl->Fill(tracklets);
	fhtrf->Fill(trdtrack->GetFlags());
	fhPID->Fill(trdtrack->GetPID());
	//cout << "flags: dec " << std::dec << trdtrack->GetPID() << " and hexdec: " << std::hex << trdtrack->GetPID() << endl;
    


    }                                                   // continue until all the tracks are processed
    PostData(1, fOutputList);                           // stream the results the analysis of this event to
                                                        // the output manager which will take care of writing
                                                        // it to a file
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::Terminate(Option_t *)
{
    // terminate
    // called at the END of the analysis (when all events are processed)
    cout << "This has ended" << endl;
}
//_____________________________________________________________________________
