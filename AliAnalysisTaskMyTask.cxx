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
#include "TProfile.h"
#include "TList.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliESDEvent.h"
#include "AliESDInputHandler.h"
#include "AliAnalysisTaskMyTask.h"
#include "AliESDtrackCuts.h"
//#include "AliESDHeader.h"
#include "AliAnalysisTaskESDfilter.h"

#include <iostream>

class AliAnalysisTaskMyTask;    // your analysis class
class AliESD;
class AliTRDdigitsExtract;

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskMyTask) // classimp: necessary for root

AliAnalysisTaskMyTask::AliAnalysisTaskMyTask() : AliAnalysisTaskSE(), 
    fESD(0), fOutputList(0), fHistPt(0), fhtrdpt(0), fhdy(0), fhy(0), fhz(0), fhpid(0), 
    fhepid(0), fhPID(0), fhntl(0), fhapt(0), fhtrdapt(0), fhtrf(0), fhD(0), fhZ(0), fhptg(0), fhptm(0), fhphietag(0),fhphietam(0),
    fhpapt(0), fhp1_5pt(0), fhp2pt(0), fhp2_5pt(0), fhp3pt(0),
    fhp3_5pt(0), fhpapte(0), fhp1_5pte(0) ,fhp2pte(0), fhp2_5pte(0), fhp3pte(0), fhp3_5pte(0), 
    fpapt(0), fpp2pt(0), fpp2_5pt(0), fpp3pt(0), fpp3_5pt(0), fpp4pt(0)

{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char* name) : AliAnalysisTaskSE(name),
    fESD(0), fOutputList(0), fHistPt(0), fhtrdpt(0), fhdy(0), fhy(0), fhz(0), fhpid(0), 
    fhepid(0), fhPID(0), fhntl(0), fhapt(0), fhtrdapt(0), fhtrf(0), fhD(0), fhZ(0), fhptg(0), fhptm(0), fhphietag(0), fhphietam(0),
    fhpapt(0), fhp1_5pt(0), fhp2pt(0), fhp2_5pt(0), fhp3pt(0),
    fhp3_5pt(0), fhpapte(0), fhp1_5pte(0), fhp2pte(0), fhp2_5pte(0), fhp3pte(0), fhp3_5pte(0), 
    fpapt(0), fpp2pt(0), fpp2_5pt(0), fpp3pt(0), fpp3_5pt(0), fpp4pt(0)




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
    fHistPt  = new TH1F("fHistPt", "fHistPt", 100, 0, 10);       // create your histogra
    fhtrdpt  = new TH1F("fhtrdpt", "fhtrdpt", 100,0,10);
    fhdy     = new TH1F("fhdy","fhdy",100,0,100);    
    fhy      = new TH1F("fhy","fhy",100,0,10000); 
    fhz      = new TH1F("fhz","fhz",100, 0, 100); 
    fhpid    = new TH1F("fhpid","fhpid", 280, 0, 280);
    fhepid   = new TH1F("fhepid","fhepid",280,0,280); 
    fhPID    = new TH1F("fhPID","fhPID",280,0,280);
    fhntl    = new TH1F("fhntl","fhntl", 7, 0, 7);
    fhapt    = new TH2F("fhapt","fhapt",10000,0,20000,4000,0,500);
    fhtrdapt = new TH2F("fhtrdapt","fhtrdapt",10000,0,20000,4000,0,500);
    fhtrf    = new TH1F("fhtrf","fhtrf",50,0,50);
    fhD	     = new TH1F("fhD","fhD",2000,-100,100);
    fhZ	     = new TH1F("fhZ","fhZ",2000,-100,100); 
    fhptg    = new TH1F("fhptg","fhptg", 1000, 0, 10);
    fhptm    = new TH1F("fhptm","fhptm", 1000, 0, 10); 
    fhphietag= new TH2F("fhphietag","fhphietag",1000, -1, 7, 1000, -10, 10);  
    fhphietam= new TH2F("fhphietam","fhphietam",1000, -1, 7, 1000, -10, 10);  

    // profile histogram
    fhpapt   = new TH1F("fhpapt","fhpapt",400,-5,5);
    fhp1_5pt = new TH1F("fhp1_5pt","fhp1_5pt",400,-5,5);
    fhp2pt   = new TH1F("fhp2pt","fhp2pt",400,-5,5);
    fhp2_5pt = new TH1F("fhp2_5pt","fhp2_5pt",400,-5,5);
    fhp3pt   = new TH1F("fhp3pt","fhp3pt",400,-5,5);
    fhp3_5pt = new TH1F("fhp3_5pt","fhp3_5pt",400,-5,5);
   
    fhpapte  = new TH1F("fhpapte","fhpapte",400,-5,5);
    fhp1_5pte= new TH1F("fhp1_5pte","fhp1_5pte",400,-5,5);
    fhp2pte  = new TH1F("fhp2pte","fhp2pte",400,-5,5);
    fhp2_5pte= new TH1F("fhp2_5pte","fhp2_5pte",400,-5,5);
    fhp3pte  = new TH1F("fhp3pte","fhp3pte",400,-5,5);
    fhp3_5pte= new TH1F("fhp3_5pte","fhp3_5pte",400,-5,5);
    fpapt    = new TProfile("fpapt","fpapt",1000,0,10,-10,10);
    fpp2pt   = new TProfile("fpp2pt",  "fpp2pt"  ,1000,-5,5,-10,10); 
    fpp2_5pt = new TProfile("fpp2_5pt","fpp2_5pt",1000,1,5,-10,10); 
    fpp3pt   = new TProfile("fpp3pt",  "fpp3pt"  ,1000,1,5,-10,10); 
    fpp3_5pt = new TProfile("fpp3_5pt","fpp3_5pt",1000,1,5,-10,10); 
    fpp4pt   = new TProfile("fpp4pt",  "fpp4pt"  ,1000,1,5,-10,10); 
 
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
    fOutputList->Add(fhD);
    fOutputList->Add(fhZ);
    fOutputList->Add(fhptg);
    fOutputList->Add(fhptm);
    fOutputList->Add(fhphietag);
    fOutputList->Add(fhphietam);

    fOutputList->Add(fhpapt);
    fOutputList->Add(fhp1_5pt);
    fOutputList->Add(fhp2pt);
    fOutputList->Add(fhp2_5pt);
    fOutputList->Add(fhp3pt);
    fOutputList->Add(fhp3_5pt);
    fOutputList->Add(fhpapte);
    fOutputList->Add(fhp1_5pte);
    fOutputList->Add(fhp2pte);
    fOutputList->Add(fhp2_5pte);
    fOutputList->Add(fhp3pte);
    fOutputList->Add(fhp3_5pte);
    
    fOutputList->Add(fpapt);
    fOutputList->Add(fpp2pt);		// TProfile
    fOutputList->Add(fpp2_5pt);
    fOutputList->Add(fpp3pt);
    fOutputList->Add(fpp3_5pt);
    fOutputList->Add(fpp4pt);

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
    AliESDHeader* header = fESD->GetHeader(); 
    //AliESDRun run = fESD->GetESDRun();
    cout << "i should really clean up my code " << std::hex << header->GetTriggerMask() << endl; 
    cout << "trgger mask " << fESD->GetTriggerMask() << endl;
    cout << "trigger class " << (fESD->GetESDRun())->GetFiredTriggerClasses(fESD->GetTriggerMask()) << endl;

    //fESD->GetVertex()->Print();
    Int_t iTracks(fESD->GetNumberOfTracks());           // see how many tracks there are in the event
    Int_t iTrdTracks( fESD->GetNumberOfTrdTracks());
     
    Int_t trig = 0;
    Int_t trigt= 0;
    for (Int_t i(0); i < iTracks; i++){
        
	//if (  ) trig += 1;
	AliESDtrack* track = fESD->GetTrack(i);         // get a track (type AliAODTrack) from the event
	if (!track) continue;

	//cout << "trigger class " << (fESD->GetESDRun())->GetTriggerClass(i) << endl;
	//cout << "ESD " << AliAnalysisTaskESDfilter::GetTrackFilter() << endl;

	fhptg->Fill(track->Pt());
	//cout << "Eta " << track->Eta() << " phi " << track->Phi() << endl;
	
	if (track->Pt() > 2) fhphietag->Fill(track->Phi(), track->Eta());	

	for(Int_t j(0); j < iTrdTracks; j++) {                 // loop ove rall these tracks
	    	
	    //if (  ) trigt += 1; 
	    AliESDTrdTrack* trdtrack = fESD->GetTrdTrack(j);	
	
	    if (!trdtrack) continue;

	    //cout << "flags first " << trdtrack->GetFlags() << endl;
	    //fHistPt->Fill(track->Pt());
       	    AliVTrack* alivtrack = trdtrack->GetTrackMatch();
	    if (alivtrack != track){ continue; }
	   
	    UShort_t shrt = trdtrack->GetFlags(); 
	    UChar_t chr   = trdtrack->GetFlags();
	    //cout << "flags " << (chr=='') << "   " << "%c"+trdtrack->GetFlags() << endl;
	    printf("%c", trdtrack->GetFlags());
	    //cout << "we have a match " << track << "  " << alivtrack << "   " << trdtrack << endl;	
	    Float_t D = 0;
	    Float_t Z = 0;
	    track->GetImpactParameters(D, Z);

	    fhD->Fill(D);
	    fhZ->Fill(Z);
	    fhptm->Fill(track->Pt());	
	    if (track->Pt() > 2) fhphietam->Fill(track->Phi(), track->Eta());	

	    cout << "get impact parameters " << D << "  " << Z << endl;

	    Int_t tracklets = 0;  // layers of the trd?
	    for (Int_t k = 0; k < 6; k++){
		AliESDTrdTracklet* tracklet = trdtrack->GetTracklet(j);
	        //cout << "tracklet " << j << ": " << tracklet << endl;
	        if (!tracklet) continue;
	   
	        fhpid->Fill(tracklet->GetPID());
	        if (std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kElectron)) > 3 ){
	//	   cout << "not an electron" << endl;
	       	   //continue;
	        }		
 	        // cout << "Match trd track " << trdtrack->GetTrackMatch() << endl;	   
	        tracklets++;
	        fhdy->Fill(tracklet->GetBinDy());
	        fhy->Fill(tracklet->GetBinY());
	        fhz->Fill(tracklet->GetBinZ());
	        fhepid->Fill(tracklet->GetPID());
	  
	        //if (tracklet->GetPID() != trdtrack->GetPID()){ 
	   //    cout << "PID values don't match "<< tracklet->GetPID() << " and " << trdtrack->GetPID() << endl; 
	   //}
	    }
	      //cout << "a is here " << trdtrack->GetA() << endl;
	    //cout << "Match trd track " << trdtrack->GetTrackMatch() << endl;	
        
	    if (!alivtrack) continue; 
	
	    fhtrdpt->Fill(trdtrack->Pt());                     // plot the pt value of the track in a histogram
	    fhapt->Fill(trdtrack->GetA(), alivtrack->Pt());
	    fhtrdapt->Fill(trdtrack->GetA(), trdtrack->Pt());
	    fhntl->Fill(tracklets);
	    fhtrf->Fill(trdtrack->GetFlags());
	    fhPID->Fill(trdtrack->GetPID());
 	    //cout << "flags: dec " << std::dec << trdtrack->GetPID() << " and hexdec: " << std::hex << trdtrack->GetPID() << endl;
	
	    Double_t diff = ( std::abs(trdtrack->Pt()) - std::abs(alivtrack->Pt()) )/std::abs(alivtrack->Pt());
	    //Double_t diff = ( trdtrack->Pt() - alivtrack->Pt() )/alivtrack->Pt();
	    fhpapt->Fill(diff);
	    fpapt->Fill(alivtrack->Pt(), diff);
	    //fpp2pt->Fill(alivtrack->Pt(), diff);
	    if (1.5 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 2){ fhp1_5pt->Fill(diff); }
	    if (2 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 2.5){ fhp2pt->Fill(diff);   }// fpp2pt->Fill(alivtrack->Pt(), diff); }
     	    if (2.5 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 3){ fhp2_5pt->Fill(diff); }// fpp2_5pt->Fill(alivtrack->Pt(), diff); }
    	    if (3 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 3.5){ fhp3pt->Fill(diff);   }// fpp3pt->Fill(alivtrack->Pt(), diff); }
    	    if (3.5 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 4){ fhp3_5pt->Fill(diff); }// fpp3_5pt->Fill(alivtrack->Pt(), diff); }
	    //if (4 <= std::abs(alivtrack->Pt())){ fpp4pt->Fill(alivtrack->Pt(), diff); }
	    //cout << "PID " << trdtrack->GetPID() << endl;

	    if (std::abs(fPIDResponse->NumberOfSigmasTPC(alivtrack, AliPID::kElectron)) > 3 ){
	    //cout << std::abs(fPIDResponse->NumberOfSigmasTPC(alivtrack, AliPID::kElectron)) << endl; 	
	    //cout << trdtrack->GetPID() << endl;
	        continue;
	    }
	    //if (fV0tags[i] != 11) continue;	
	    //cout << trdtrack->GetPID() << endl;
	    //cout << "momentum " << alivtrack->Pt() << "  " << trdtrack->Pt() << endl;    	
	    fhpapte->Fill(diff);
	    if (1.5 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 2){ fhp1_5pte->Fill(diff); }
	    if (2 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 2.5){ fhp2pte->Fill(diff); }
    	    if (2.5 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 3){ fhp2_5pte->Fill(diff); }
     	    if (3 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 3.5){ fhp3pte->Fill(diff); }
    	    if (3.5 < std::abs(alivtrack->Pt()) & std::abs(alivtrack->Pt()) < 4){ fhp3_5pte->Fill(diff); }
        }
    
    //cout << "trigger "<< trig << " trd trigger " << trigt << endl;
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
