void analysis_gammaApion0_bypT()
{
    //input
    //-----
    TFile *pion = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *dir = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DdirCent.root", "read");
    
    TFile *input_Ncoll = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCent_allEvents.root", "read");
    TFile *input_avgNcoll = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCent_allEvents.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2centPion0 = (TH2D*)pion -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir -> Get("centDir");
   
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
    TProfile *avgNcoll = (TProfile*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Projection to get Yield by pT
    //CentClass
    //centclass1: 0~10%
    //centclass2: 10~20%
    //centclass3: 20~40%
    //centclass4: 40~60%
    //centclass5: 60~80%
    //----------------------------------------
    TH1D *numPion0pT_cent[5];
    TH1D *numDirpT_cent[5];
    
    numPion0pT_cent[0] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion01", 1, 1);       //centClass1: 0~10%
    numPion0pT_cent[1] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion02", 2, 2);       //centClass2: 10~20%
    numPion0pT_cent[2] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion03", 3, 4);       //centClass3: 20~40%
    numPion0pT_cent[3] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion04", 5, 6);       //centClass4: 40~60%
    numPion0pT_cent[4] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion05", 7, 8);       //centClass5: 60~80%
    
    numDirpT_cent[0] = (TH1D*)h2centDir -> ProjectionY("centClassDir1", 1, 1);             //centClass1: 0~10%
    numDirpT_cent[1] = (TH1D*)h2centDir -> ProjectionY("centClassDir2", 2, 2);             //centClass2: 10~20%
    numDirpT_cent[2] = (TH1D*)h2centDir -> ProjectionY("centClassDir3", 3, 4);             //centClass3: 20~40%
    numDirpT_cent[3] = (TH1D*)h2centDir -> ProjectionY("centClassDir4", 5, 6);             //centClass4: 40~60%
    numDirpT_cent[4] = (TH1D*)h2centDir -> ProjectionY("centClassDir5", 7, 8);             //centClass5: 60~80%
    
    
    //Event number scaling
    TH1D *yieldPion0pT_cent[5];
    TH1D *yieldDirpT_cent[5];

    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX();
    double eventN[5];
    eventN[0] = nEventCent -> GetBinContent(1);
    eventN[1] = nEventCent -> GetBinContent(2);
    eventN[2] = nEventCent -> GetBinContent(3) + nEventCent -> GetBinContent(4);
    eventN[3] = nEventCent -> GetBinContent(5) + nEventCent -> GetBinContent(6);
    eventN[4] = nEventCent -> GetBinContent(7) + nEventCent -> GetBinContent(8);

    for(int i=0; i<5; i++)
    {
        TString hisname_pion0 = Form("yieldPion0pT_cent%d", i+1);
        TString hisname_dir = Form("yieldDirpT_cent%d", i+1);

        yieldPion0pT_cent[i] = (TH1D*)numPion0pT_cent[i] -> Clone(hisname_pion0);
        yieldDirpT_cent[i] = (TH1D*)numDirpT_cent[i] -> Clone(hisname_dir);

        yieldPion0pT_cent[i] -> Scale(1./eventN[i]);
        yieldDirpT_cent[i] -> Scale(1./eventN[i]);
                
    }

    //Analysis2. Rebin for pT
    //-----------------------
    double binEdge[]={0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0};   //10 binning   
    
    TH1D *yieldPion0pT_centR[5];
    TH1D *yieldDirpT_centR[5];

    for(int i=0; i<5; i++)
    {
        TString target_pion0 = Form("Ypion0pT_cent%dR", i+1);
        TString target_dir = Form("YdirpT_cent%dR", i+1);

        yieldPion0pT_centR[i] = (TH1D*)yieldPion0pT_cent[i] -> Rebin(10, target_pion0, binEdge);
        yieldDirpT_centR[i] = (TH1D*)yieldDirpT_cent[i] ->Rebin(10, target_dir, binEdge);
    }
    
   //Analysis3. Dividing pT bin Width
   // 1/Nevent dN/dpT: binwidth not cancled
   // 1/avgNcoll     : binwidth not cancled
   //--------------------------------------
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<10; j++)
        {
            double binwidth = yieldPion0pT_centR[i] -> GetBinWidth(j+1);

            yieldPion0pT_centR[i] -> SetBinContent(j+1, yieldPion0pT_centR[i]->GetBinContent(j+1)/binwidth);
            yieldPion0pT_centR[i] -> SetBinError(j+1, yieldPion0pT_centR[i] -> GetBinError(j+1)/binwidth);

            yieldDirpT_centR[i] -> SetBinContent(j+1, yieldDirpT_centR[i]->GetBinContent(j+1)/binwidth);
            yieldDirpT_centR[i] -> SetBinError(j+1, yieldDirpT_centR[i] -> GetBinError(j+1)/binwidth);
        }
    }   
   

    //Analysis4. Get Yield/<Ncoll> vs pT, by centrality
    //-------------------------------------------------
    TH1D *YavgNcollPion0[5];
    TH1D *YavgNcollDir[5];
    
    double centclass[] = {0, 10, 20, 40, 60, 80};

    TProfile *avgNcollCent = (TProfile*)avgNcoll -> Rebin(5, "avgNcollCent", centclass);

    for(int i=0; i<5; i++)
    {
        TString pion0 = Form("YavgNcollPion0pT_cent%d", i+1);
        TString dir = Form("YavgNcollDirpT_cent%d", i+1);

        YavgNcollPion0[i] = (TH1D*)yieldPion0pT_centR[i] -> Clone(pion0);
        YavgNcollDir[i] = (TH1D*)yieldDirpT_centR[i] -> Clone(dir);

        YavgNcollPion0[i] -> Scale(1./avgNcollCent -> GetBinContent(i+1));
        YavgNcollDir[i] -> Scale(1./avgNcollCent -> GetBinContent(i+1));
    }
    
    //Analysis5. Get ratio of direct photon and pion0 yield
    //Divide pT rebinned direct photon yield with pion0
    //<Ncoll> scaling cancels with ratio
    //|eta|<1 scaling cacels with ratio
    //-----------------------------------------------------
    TH1D *gammaRpion0[5];

    for(int i=0; i<5; i++)
    {
        TString ratio = Form("gammaRpion0_cent%d", i+1);

        gammaRpion0[i] = (TH1D*)yieldDirpT_centR[i] -> Clone(ratio);
        gammaRpion0[i] -> Divide(yieldPion0pT_centR[i]);
    }


    //Write outputs in outputfile
    //---------------------------
    
    //Write yield of pion0 vs pT(not rebinned)
    for(int i=0; i<5; i++)
    {
        yieldPion0pT_cent[i] -> Write();
    }

    //Write Yield of pion0 vs pT(rebinned)
    for(int i=0; i<5; i++)
    {
        yieldPion0pT_centR[i] -> Write();
    }

    //Write Y/avgNcoll
    for(int i=0; i<5; i++)
    {
        YavgNcollPion0[i] -> Write();
    }

    //Write yield of dirPhoton vs pT(not rebinned)
    for(int i=0; i<5; i++)
    {
        yieldDirpT_cent[i] -> Write();
    }
    
    //Write yield of dirPhoton vs pT(rebinned)
    for(int i=0; i<5; i++)
    {
        yieldDirpT_centR[i] -> Write();
    }

    //write YavgNcolll
    for(int i=0; i<5; i++)
    {
        YavgNcollDir[i] -> Write();
    }

    //write gammaRpion0
    for(int i=0; i<5; i++)
    {
        gammaRpion0[i] -> Write();
    }
    
     //Close files
    //-----------
    pion -> Close();
    dir -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

    //disallocation
    delete pion;
    delete dir;
    delete input_Ncoll;
    delete input_avgNcoll;
    delete output;
        
}
