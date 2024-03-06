void plotMake_correlations_withMidPion0_ratioChargeEta_scaleAvgNcoll_pTClass2MB()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_scaleAvgNcoll_pTClass2MB_withMidPion0.root", "read");

    TH1D *ratio_1 = (TH1D*)input1 -> Get("charge_etaRatio_scaleAvgNcoll_pT1toMB");
    TH1D *ratio_2 = (TH1D*)input1 -> Get("charge_etaRatio_scaleAvgNcoll_pT2toMB");
    TH1D *ratio_3 = (TH1D*)input1 -> Get("charge_etaRatio_scaleAvgNcoll_pT3toMB");
    TH1D *ratio_4 = (TH1D*)input1 -> Get("charge_etaRatio_scaleAvgNcoll_pT4toMB");
    TH1D *ratio_5 = (TH1D*)input1 -> Get("charge_etaRatio_scaleAvgNcoll_pT5toMB");
    TH1D *ratio_6 = (TH1D*)input1 -> Get("charge_etaRatio_scaleAvgNcoll_pT6toMB");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0.5, 5, 3);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{#LTNcoll#GT}#frac{dN^{ch}}{d#eta}_{pTClass} / #frac{1}{#LTNcoll#GT}#frac{dN^{ch}}{d#eta}_{MB}");

        ratio_1 -> SetMarkerStyle(22);
        ratio_1 -> SetMarkerColor(kOrange+10);
        ratio_1 -> SetLineColor(kOrange+10);
        ratio_1 -> Draw("p same");

		ratio_2 -> SetMarkerStyle(34);
        ratio_2 -> SetMarkerColor(kOrange);
        ratio_2 -> SetLineColor(kOrange);
        ratio_2 -> Draw("p same");

        ratio_3 -> SetMarkerStyle(34);
        ratio_3 -> SetMarkerColor(kRed);
        ratio_3 -> SetLineColor(kRed);
        ratio_3 -> Draw("p same");

        ratio_4 -> SetMarkerStyle(28);
        ratio_4 -> SetMarkerColor(kPink);
        ratio_4 -> SetLineColor(kPink);
        ratio_4 -> Draw("p same");
    
        ratio_5 -> SetMarkerStyle(47);
        ratio_5 -> SetMarkerColor(kMagenta);
        ratio_5 -> SetLineColor(kMagenta);
        ratio_5 -> Draw("p same");

		ratio_6 -> SetMarkerStyle(25);
        ratio_6 -> SetMarkerColor(kViolet);
        ratio_6 -> SetLineColor(kViolet);
        ratio_6 -> Draw("p same");

		TLine *one = new TLine(-5, 1, 5, 1);
		one -> Draw();

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(ratio_1, "Events with p_{T} #LT 2 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(ratio_2, "Events with 2 GeV #leq p_{T} 4 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(ratio_3, "Events with 4 GeV #leq p_{T} 7 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(ratio_4, "Events with 7 GeV #leq p_{T} 10 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(ratio_5, "Events with 10 GeV #leq p_{T} 15 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(ratio_6, "Events with 15 GeV #leq p_{T} 20 GeV #pi^{0} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
