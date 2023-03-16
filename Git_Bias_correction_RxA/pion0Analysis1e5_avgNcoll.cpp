/***************************************
* pion0 Analysis

* Calculate average Ncoll by each
  centrality class

* 100,000 events
***************************************/

void pion0Analysis1e5_avgNcoll()
{
	//read files
	TChain *opt3 = new TChain("T");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00000.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00001.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00002.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00003.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00004.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00005.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00006.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00007.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00008.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00009.root");
	
	//centrality reference his
	TFile* input = new TFile("pAu200GeV_option3_pTcent_refhis_v1.root", "read");
	TH1F* refhis = (TH1F*)input -> Get("centRef_pTe5");

	//set variables to hold information
	int np = 5000;
	int p_id[np];
	float p_eta[np];
	float p_pt[np];

	int i_nAbsProj;
	int i_nDiffProj;
	int i_nAbsTarg;
	int i_nDiffTarg;
	int i_nElProj;
	int i_nElTarg;

	//link branch address
	opt3 -> SetBranchAddress("np", &np);
	opt3 -> SetBranchAddress("p_id", &p_id);
	opt3 -> SetBranchAddress("p_eta", &p_eta);
	opt3 -> SetBranchAddress("p_pt", &p_pt);
	opt3 -> SetBranchAddress("i_nAbsProj", &i_nAbsProj);
	opt3 -> SetBranchAddress("i_nDiffProj", &i_nDiffProj);
	opt3 -> SetBranchAddress("i_nAbsTarg", &i_nAbsTarg);
	opt3 -> SetBranchAddress("i_nDiffTarg", &i_nDiffTarg);
	opt3 -> SetBranchAddress("i_nElProj", &i_nElProj);
	opt3 -> SetBranchAddress("i_nElTarg", &i_nElTarg);
	
	//Analysis
	
	double pTsum = 0.;
	double centrality = 0.;
	double ncoll = 0.;

	//bin edges
	double bins[] = {0, 10, 20, 40, 60, 80};

	//create TProfile
	TProfile* avgNcoll = new TProfile("avgNcoll", "", 5, 0, 80);
	avgNcoll -> GetXaxis() -> Set(5, bins);

 //	avgNcoll -> Fill(5, 10);
 //	avgNcoll -> Fill(15, 20);
 //	avgNcoll -> Fill(25, 30);
 //	avgNcoll -> Fill(35, 40);
 //	avgNcoll -> Fill(45, 50);
 //	avgNcoll -> Fill(55, 60);
 //	avgNcoll -> Fill(65, 70);
 //	avgNcoll -> Fill(75, 80);
 //	avgNcoll -> Fill(85, 90);
 //	avgNcoll -> Fill(95, 100);
	
	for(int i = 0; i < opt3 -> GetEntries(); i++){
		opt3 -> GetEntry(i);
		if(i_nAbsProj == 1 and i_nAbsTarg != 0){
			
			//ncoll calculation
			ncoll = i_nAbsTarg + i_nAbsProj - 1;

			for(int j = 0; j < np; j++){
				if(p_eta[j] > -3.9 and p_eta[j] < -3.0 and p_id[j] != 111){
					pTsum += p_pt[j];
				}//pTsum for centcal			 
			}//j

			centrality = 100*((refhis -> Integral(refhis -> FindBin(pTsum), 1e5))/(refhis -> Integral(1, 1e5)));
			
			avgNcoll -> Fill(centrality, ncoll);
		}

		pTsum = 0;
	}//i

 //	avgNcoll -> Draw();
	
	//save histogram as root file
	TFile *file = new TFile("pAu200GeV_option3_INEL_avgNcoll.root", "recreate");
	
	avgNcoll -> Write();

	file -> Close();

}