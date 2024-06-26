#include "../headerFiles/configurable.h"


void analysis_correlations_ratioOfChargeEta_scaleAvgNcoll_pTClass2MB_withMidPion0()
{
	//input
	//-----
	TFile *input = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withPion0_ofpTClass.root", "read");
	TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withPion0_TProfileNcollMaxpT.root", "read");
	TFile *input_mb_charge = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH2DpTetaCharge_MBevents.root", "read");
	TFile *input_mb_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");

	TProfile *avgNcoll = (TProfile*)input_avgNcoll -> Get("maxpT_vs_avgNcoll_corrWithMidPion0");

	TH1D *charge_corWithPion0[pTBinNum];
	TH1D *charge_corWithPion0_etaRebinned[pTBinNum];

	TH2D *charge_MB = (TH2D*)input_mb_charge -> Get("pTetaCharge_MBevents");
	TH2D *NeventCent_MB = (TH2D*)input_mb_ncoll -> Get("ncollCent");

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString inputName = Form("charge_eta_corWithPion0_ofpTClass%d_scaled", pT+1);
		charge_corWithPion0[pT] = (TH1D*)input -> Get(inputName);
	}
	
	
	//Analysis0. Get charge-eta distribution of MB events
	//---------------------------------------------------
	TH1D *charge_eta_MB = (TH1D*)charge_MB -> ProjectionX("charge_eta_MB");
	TH1D *charge_eta_MB_etaRebinned = (TH1D*)charge_eta_MB -> Rebin(etaBinNum, "charge_eta_MB_etaRebin", etaBin);

	TH1D *Nevent_cent = (TH1D*)NeventCent_MB -> ProjectionX("Nevent_cent");
	TH1D *Nevent_MB = (TH1D*)Nevent_cent -> Rebin(centBin_MergedNum, "TotalNevent", centBin_Merged);
	
	//scaling-# event, binwidth
	charge_eta_MB_etaRebinned -> Scale(1./Nevent_MB -> GetBinContent(1));
	charge_eta_MB_etaRebinned -> Scale(1./charge_eta_MB_etaRebinned -> GetBinWidth(1));
	
	//avgNcoll calculaiton
	double bin[]={0, 20};
	TProfile *avgNcoll_mb = (TProfile*)avgNcoll -> Rebin(1, "avgNcoll_mb", bin);
	TProfile *avgNcoll_pTClass = (TProfile*)avgNcoll -> Rebin(pTBinNum, "avgNcoll_pTClass", pTBin);

	//Analysis1. calculte <Ncoll> sclaed dNchdeta by pTClass
	//------------------------------------------------------
	TH1D *charge_scaledEta[pTBinNum];
	
	//Events divided by pT-Class
	for(int pT=0; pT<pTBinNum; pT++)
	{	
		TString outputname1 = Form("charge_ncollScaledEta_pTClass%d", pT+1);

		charge_scaledEta[pT] = (TH1D*)charge_corWithPion0[pT] -> Clone(outputname1);
		charge_scaledEta[pT] -> Scale(1./avgNcoll_pTClass -> GetBinContent(pT+1));
		
		cout << avgNcoll_mb -> GetBinContent(1) << " : " << avgNcoll_pTClass -> GetBinContent(pT+1) << " : " << (avgNcoll_mb -> GetBinContent(1))/(avgNcoll_pTClass -> GetBinContent(pT+1)) << endl;
	}

	//MB events
	TH1D *charge_eta_MB_NcollScaled = (TH1D*)charge_eta_MB_etaRebinned -> Clone("charge_ncollScaledEta_MB");
	charge_eta_MB_NcollScaled -> Scale(1./avgNcoll_mb -> GetBinContent(1));

	//Analysis2. Calculated ratio of Ncoll scaled charge eta with MB
	//--------------------------------------------------------------
	TH1D *charge_ratiopTMB[pTBinNum];
	
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		charge_ratiopTMB[pi0pT] = (TH1D*)charge_scaledEta[pi0pT] -> Clone(Form("charge_etaRatio_scaleAvgNcoll_pT%dtoMB", pi0pT+1));
		charge_ratiopTMB[pi0pT] -> Divide(charge_eta_MB_NcollScaled);
	}
	
	//output
	//-----
	TFile *outfile = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_scaleAvgNcoll_pTClass2MB_withMidPion0.root", "recreate");
	outfile -> cd();
	
	//MB, NcollScaled
	charge_eta_MB_NcollScaled -> Write();

	//pTClass, NcollSclaed
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		charge_scaledEta[pi0pT] -> Write();
	}

	// ratio of pTClass 2 MB
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{	
		charge_ratiopTMB[pi0pT] -> Write();
	}
	outfile -> Close();

}

