/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskMyTask_H
#define AliAnalysisTaskMyTask_H

class AliESDEvent;
class AliTRDdigitsManager;
class AliPIDResponse;

#include "AliAnalysisTaskSE.h"
#include "AliPIDResponse.h"

class AliAnalysisTaskMyTask : public AliAnalysisTaskSE  
{
    public:
                                AliAnalysisTaskMyTask();
                                AliAnalysisTaskMyTask(const char *name);
        virtual                 ~AliAnalysisTaskMyTask();

        virtual void            UserCreateOutputObjects();
        virtual void            UserExec(Option_t* option);
        virtual void            Terminate(Option_t* option);

    private:
        AliESDEvent*            fESD;           //! input event
        TList*                  fOutputList;    //! output list
        TH1F*                   fHistPt;        //! dummy histogram
	TH1F*			fhtrdpt;

	TH1F*			fhdy;
	TH1F*			fhy;
	TH1F*			fhz;
	TH1F*			fhpid;		// for the trd tracklets
	TH1F*			fhepid;		// for electrons tracklets using trd pid
	TH1F*			fhPID;		// for the trd track
	TH1F*			fhntl;    	// # of tracklets
	TH2*			fhapt;		// A vs. Pt of the tracks
	TH2*			fhtrdapt;	// A vs. Pt of trd tracks
	TH1F*			fhtrf;		// flag numbers 

	// profile histograms
	TH1F* 			fhpapt;
	TH1F*			fhp1_5pt;
	TH1F*			fhp2pt;
	TH1F*			fhp2_5pt;
	TH1F*			fhp3pt;
	TH1F*			fhp3_5pt;
	TH1F* 			fhpapte;
	TH1F*			fhp1_5pte;
	TH1F*			fhp2pte;
	TH1F*			fhp2_5pte;
	TH1F*			fhp3pte;
	TH1F*			fhp3_5pte;
	
	TProfile*		fpp2pt;
	TProfile*		fpp2_5pt;
	TProfile*		fpp3pt;
	TProfile*		fpp3_5pt;
	TProfile*		fpp4pt;

	AliPIDResponse* fPIDResponse; //! pid response object

        AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&); // not implemented
        AliAnalysisTaskMyTask& operator=(const AliAnalysisTaskMyTask&); // not implemented

        ClassDef(AliAnalysisTaskMyTask, 1);
};

#endif
