#include "SampleAnalyzer/User/Analyzer/FCNC_2SSL.h"
#include "SampleAnalyzer/User/Analyzer/XsectionBkgExtractor.h"
#include "SampleAnalyzer/User/Analyzer/XsectionSignalExtractor.h"
#include "SampleAnalyzer/User/Analyzer/AnalysisHelper.h"
using namespace MA5;
using namespace std;


// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------


bool FCNC_2SSL::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
    cout << "BEGIN Initialization" << endl;
    outputName_ = cfg.GetInputName();
    nevent = 0;
    luminosity = 100000; // lumi in pb
    xsec = -1;
    cout << "Sample = " << cfg.GetInputName() << endl;
    cout << "Lumi = " << luminosity << " pb^-1" << endl;
    debug = false;
    
    // Initialization of cross section table
    XsectionBkgExtractor bkg_table;
    if (!bkg_table.Initialize()) return false;
    if (!bkg_table.CheckTable()) return false;
    XsectionSignalExtractor sig_table;
    if (!sig_table.Initialize()) return false;
    if (!sig_table.CheckTable()) return false;
    //double xsection = -1;
    if (sig_table.DetectAndLoadProcess(cfg.GetInputName()))
    {
        //xsection = 1; // pb
        xsec = sig_table.GetXsection_fixingBRlimit();
        
    }
    else if (bkg_table.DetectAndLoadProcess(cfg.GetInputName()))
    {
        xsec = bkg_table.GetXsection(); // pb
    }
//    else
//    {
//        std::cout << "ERROR: no xsection found for the file " << cfg.GetInputName() << std::endl;
//        //if(outputName_ == "TT_Kappa_Hct_HtoWW") xsec = 10.; //Random chosen number in order to get some results -> needs to be changed to something plausible
//    }
    std::cout << "Great! The xsection is: " << xsec << " [pb]" << std::endl;
    if (xsec<0)
    {
        std::cout << "ERROR: no xsection found for the file " << cfg.GetInputName() << std::endl;
        return false;
    }
    
    
    //----------------------------------------------------
    //output file
    
    output = new TFile(("../Output/Results_All_Final_10Jul_BrUpdate/"+outputName_+ ".root").c_str(),"RECREATE");
    cout << "Outputfile =  ../Output/Results_All_Final_10Jul_BrUpdate/" << outputName_ << ".root" << endl;
    
    ///******************************///
    //create Trees to input for TMVA //
    ///****************************///
    
    tree = new TTree(("Ttree_"+outputName_).c_str(),"Input tree for MVA");
    //tree->Branch("myMVAvar",&myMVAvar,"myMVAvar/D"); --> how to create branches for variables
    tree->Branch("MVA_Ht_Jets" , &MVA_Ht_Jets , "MVA_Ht_Jets/F");
    tree->Branch("MVA_Met" , &MVA_Met , "MVA_Met/F");
    tree->Branch("MVA_Nb_CSVL_bJets", &MVA_Nb_CSVL_bJets,"MVA_Nb_CSVL_bJets/F");
    tree->Branch("MVA_Nb_Jets", &MVA_Nb_Jets, "MVA_Nb_Jets/F");
    tree->Branch("MVA_DeltaR_2SSLep" , &MVA_DeltaR_2SSLep , "MVA_DeltaR_2SSLep/F");
    tree->Branch("MVA_Delta_Phi_2SSLep" , &MVA_Delta_Phi_2SSLep, "MVA_Delta_Phi_2SSLep/F");
    tree->Branch("MVA_Lep1_pt_to_Ht_ratio" , &MVA_Lep1_pt_to_Ht_ratio , "MVA_Lep1_pt_to_Ht_ratio/F");
    tree->Branch("MVA_Mass_Lep0_b" , &MVA_Mass_Lep0_b , "MVA_Mass_Lep0_b/F");
    tree->Branch("MVA_DeltaRmin_Lep0_b" , &MVA_DeltaRmin_Lep0_b , "MVA_DeltaRmin_Lep0_b/F");
    tree->Branch("MVA_DeltaRmin_Lep1_b" , &MVA_DeltaRmin_Lep1_b , "MVA_DeltaRmin_Lep1_b/F");
    tree->Branch("MVA_Leading_Lep_Pt", &MVA_Leading_Lep_Pt, "MVA_Leading_Lep_Pt/F");
    tree->Branch("MVA_second_Leading_Lep_Pt", &MVA_second_Leading_Lep_Pt, "MVA_second_Leading_Lep_Pt/F");
    tree->Branch("MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b", &MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b, "MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b/F");
    tree->Branch("MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b", &MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b, "MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b/F");
    tree->Branch("MVA_Mass_Lep1_b", &MVA_Mass_Lep1_b, "MVA_Mass_Lep1_b/F");
    tree->Branch("MVA_Mass_FCNC_top_Lep1", &MVA_Mass_FCNC_top_Lep1, "MVA_Mass_FCNC_top_Lep1/F");
    tree->Branch("MVA_Mass_FCNC_top_Lep0", &MVA_Mass_FCNC_top_Lep0, "MVA_Mass_FCNC_top_Lep0/F");
    tree->Branch("MVA_St" , &MVA_St , "MVA_St/F");
    tree->Branch("MVA_Sum_lep_Pt" , &MVA_Sum_lep_Pt , "MVA_Sum_lep_Pt/F");
    
    
    
    /////***** second tree after met cut *****////
    tree_Met = new TTree(("Ttree_Met_"+outputName_).c_str(),"Input tree for MVA");
    //tree->Branch("myMVAvar",&myMVAvar,"myMVAvar/D"); --> how to create branches for variables
    tree_Met->Branch("MVA_Ht_Jets" , &MVA_Ht_Jets , "MVA_Ht_Jets/F");
    tree_Met->Branch("MVA_Met" , &MVA_Met , "MVA_Met/F");
    tree_Met->Branch("MVA_Nb_CSVL_bJets", &MVA_Nb_CSVL_bJets,"MVA_Nb_CSVL_bJets/F");
    tree_Met->Branch("MVA_Nb_Jets", &MVA_Nb_Jets, "MVA_Nb_Jets/F");
    tree_Met->Branch("MVA_DeltaR_2SSLep" , &MVA_DeltaR_2SSLep , "MVA_DeltaR_2SSLep/F");
    tree_Met->Branch("MVA_Delta_Phi_2SSLep" , &MVA_Delta_Phi_2SSLep, "MVA_Delta_Phi_2SSLep/F");
    tree_Met->Branch("MVA_Lep1_pt_to_Ht_ratio" , &MVA_Lep1_pt_to_Ht_ratio , "MVA_Lep1_pt_to_Ht_ratio/F");
    tree_Met->Branch("MVA_Mass_Lep0_b" , &MVA_Mass_Lep0_b , "MVA_Mass_Lep0_b/F");
    tree_Met->Branch("MVA_DeltaRmin_Lep0_b" , &MVA_DeltaRmin_Lep0_b , "MVA_DeltaRmin_Lep0_b/F");
    tree_Met->Branch("MVA_DeltaRmin_Lep1_b" , &MVA_DeltaRmin_Lep1_b , "MVA_DeltaRmin_Lep1_b/F");
    tree_Met->Branch("MVA_Leading_Lep_Pt", &MVA_Leading_Lep_Pt, "MVA_Leading_Lep_Pt/F");
    tree_Met->Branch("MVA_second_Leading_Lep_Pt", &MVA_second_Leading_Lep_Pt, "MVA_second_Leading_Lep_Pt/F");
    tree_Met->Branch("MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b", &MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b, "MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b/F");
    tree_Met->Branch("MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b", &MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b, "MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b/F");
    tree_Met->Branch("MVA_Mass_Lep1_b", &MVA_Mass_Lep1_b, "MVA_Mass_Lep1_b/F");
    tree_Met->Branch("MVA_Mass_FCNC_top_Lep1", &MVA_Mass_FCNC_top_Lep1, "MVA_Mass_FCNC_top_Lep1/F");
    tree_Met->Branch("MVA_Mass_FCNC_top_Lep0", &MVA_Mass_FCNC_top_Lep0, "MVA_Mass_FCNC_top_Lep0/F");
    tree_Met->Branch("MVA_St" , &MVA_St , "MVA_St/F");
    tree_Met->Branch("MVA_Sum_lep_Pt" , &MVA_Sum_lep_Pt , "MVA_Sum_lep_Pt/F");


    
    output->cd();
    
    //----------------------------------------------------//
    //              histograms initialization             //
    //----------------------------------------------------//
    
    cutFlow       = new TH1F(("cutFlow_"+outputName_).c_str(),      ("cutFlow_"+outputName_).c_str(),      15, -0.5, 15.5);
    cutFlow->Sumw2();
    
    //***** Pre_selection santy check *****//
    sumet_isol_elec = new TH1F(("sumet_isol_elec_"+outputName_).c_str(),      ("#Sigma E_{T}(e)  "+outputName_).c_str(),      100, 0.0, 250.0);
    sumet_isol_elec->Sumw2();
    sumet_isol_muon = new TH1F(("sumet_isol_muon_"+outputName_).c_str(),      ("#Sigma E_{T}(#mu)  "+outputName_).c_str(),      100, 0.0, 250.0);
    sumet_isol_muon->Sumw2();
    sumpt_isol_elec = new TH1F(("sumpt_isol_elec_"+outputName_).c_str(),      ("#Sigma p_{T}(e) "+outputName_).c_str(),      100, 0.0, 250.0);
    sumpt_isol_elec->Sumw2();
    sumpt_isol_muon = new TH1F(("sumpt_isol_muon_"+outputName_).c_str(),      ("#Sigma E_{T}(#mu)  "+outputName_).c_str(),      100, 0.0, 250.0);
    sumpt_isol_muon->Sumw2();
    comb_isol_elec = new TH1F(("comb_isol_elec_"+outputName_).c_str(),      ("Comb iso e  "+outputName_).c_str(),      100, 0.0, 100.0);
    comb_isol_elec->Sumw2();
    comb_isol_muon = new TH1F(("comb_isol_muon_"+outputName_).c_str(),      ("Comb iso #mu  "+outputName_).c_str(),      100, 0.0, 100.0);
    comb_isol_muon->Sumw2();
    cleanjet_Mult = new TH1F(("cleanjet_Mult_"+outputName_).c_str(),    ("cleanjet_Mult_"+outputName_).c_str(),     10,0,10);
    cleanjet_Mult->Sumw2();
    Nb_elecs = new TH1F(("Nb_elecs_"+outputName_).c_str(),      ("Number of electrons "+outputName_).c_str(),      12, -0.5, 11.5);
    Nb_elecs->Sumw2();
    Nb_muons = new TH1F(("Nb_muons_"+outputName_).c_str(),      ("Number of muons "+outputName_).c_str(),      12, -0.5, 11.5);
    Nb_muons->Sumw2();
    Nb_Jets = new TH1F(("Nb_Jets_"+outputName_).c_str(),      ("Number of jets "+outputName_).c_str(),      12, -0.5, 11.5);
    Nb_Jets->Sumw2();
    Nb_CSVL_jets = new TH1F(("Nb_CSVL_jets_"+outputName_).c_str(),      ("Number of CSVL jets "+outputName_).c_str(),      9, -0.5, 8.5);
    Nb_CSVL_jets->Sumw2();
    Nb_CSVM_jets = new TH1F(("Nb_CSVM_jets_"+outputName_).c_str(),      ("Number of CSVM jets "+outputName_).c_str(),      9, -0.5, 8.5);
    Nb_CSVM_jets->Sumw2();
    Nb_CSVT_jets = new TH1F(("Nb_CSVT_jets_"+outputName_).c_str(),      ("Number of CSVT jets "+outputName_).c_str(),      9, -0.5, 8.5);
    Nb_CSVT_jets->Sumw2();
    Pt_leadingElec_2SSSF       = new TH1F(("Pt_leadingElec_2SSSF_"+outputName_).c_str(),      ("p_{T} Leading-electron "+outputName_).c_str(),      100, 0.0, 300.0);
    Pt_leadingElec_2SSSF->Sumw2();
    Pt_2ndleadingElec_2SSSF       = new TH1F(("Pt_2ndleadingElec_2SSSF_"+outputName_).c_str(),      ("p_{T} 2nd_Leading-electron "+outputName_).c_str(),      100, 0.0, 250.0);
    Pt_2ndleadingElec_2SSSF->Sumw2();
    Eta_leadingElec_2SSSF       = new TH1F(("Eta_leadingElec_2SSSF_"+outputName_).c_str(),      ("#eta Leading-electron "+outputName_).c_str(),      100, -3., 3.);
    Eta_leadingElec_2SSSF->Sumw2();
    Eta_2ndleadingElec_2SSSF       = new TH1F(("Eta_2ndleadingElec_2SSSF_"+outputName_).c_str(),      ("#eta 2nd_Leading-electron "+outputName_).c_str(),      100, -3., 3.);
    Eta_2ndleadingElec_2SSSF->Sumw2();
    Phi_leadingElec_2SSSF       = new TH1F(("Phi_leadingElec_2SSSF_"+outputName_).c_str(),      ("#Phi Leading-electron "+outputName_).c_str(),      100, -4.0, 4.);
    Phi_leadingElec_2SSSF->Sumw2();
    Phi_2ndleadingElec_2SSSF       = new TH1F(("Phi_2ndleadingElec_2SSSF_"+outputName_).c_str(),      ("#Phi 2nd_Leading-electron "+outputName_).c_str(),      100, -4.0, 4.);
    Phi_2ndleadingElec_2SSSF->Sumw2();
    Pt_leadingMuon_2SSSF       = new TH1F(("Pt_leadingMuon_2SSSF_"+outputName_).c_str(),      ("p_{T} Leading-Muon "+outputName_).c_str(),      100, 0.0, 300.0);
    Pt_leadingMuon_2SSSF->Sumw2();
    Pt_2ndleadingMuon_2SSSF       = new TH1F(("Pt_2ndleadingMuon_2SSSF_"+outputName_).c_str(),      ("p_{T} 2nd_Leading-Muon "+outputName_).c_str(),      100, 0.0, 150.0);
    Pt_2ndleadingMuon_2SSSF->Sumw2();
    Eta_leadingMuon_2SSSF       = new TH1F(("Eta_leadingMuon_2SSSF_"+outputName_).c_str(),      ("#eta Leading-electron "+outputName_).c_str(),      100, -3., 3.);
    Eta_leadingMuon_2SSSF->Sumw2();
    Eta_2ndleadingMuon_2SSSF       = new TH1F(("Eta_2ndleadingMuon_2SSSF_"+outputName_).c_str(),      ("#eta 2nd_Leading-Muon "+outputName_).c_str(),      100, -3., 3.);
    Eta_2ndleadingMuon_2SSSF->Sumw2();
    Phi_leadingMuon_2SSSF       = new TH1F(("Phi_leadingMuon_2SSSF_"+outputName_).c_str(),      ("#Phi Leading-Muon "+outputName_).c_str(),      100, -4.0, 4.);
    Phi_leadingMuon_2SSSF->Sumw2();
    Phi_2ndleadingMuon_2SSSF       = new TH1F(("Phi_2ndleadingMuon_2SSSF_"+outputName_).c_str(),      ("#Phi 2nd_Leading-Muon "+outputName_).c_str(),      100, -4.0, 4.);
    Phi_2ndleadingMuon_2SSSF->Sumw2();
    Pt_leadingLepton_2SSOF       = new TH1F(("Pt_leadingLepton_2SSOF_"+outputName_).c_str(),      ("p_{T} Lepton_2SSOF "+outputName_).c_str(),      100, 0.0, 300.0);
    Pt_leadingLepton_2SSOF->Sumw2();
    Pt_2ndleadingLepton_2SSOF       = new TH1F(("Pt_2ndleadingLepton_2SSOF_"+outputName_).c_str(),      ("p_{T} 2nd_Lepton_2SSOF "+outputName_).c_str(),      100, 0.0, 150.0);
    Pt_2ndleadingLepton_2SSOF->Sumw2();
    Eta_leadingLepton_2SSOF       = new TH1F(("Eta_leadingLepton_2SSOF_"+outputName_).c_str(),      ("#eta Lepton_2SSOF "+outputName_).c_str(),      100, -3., 3.);
    Eta_leadingLepton_2SSOF->Sumw2();
    Eta_2ndleadingLepton_2SSOF       = new TH1F(("Eta_2ndleadingLepton_2SSOF_"+outputName_).c_str(),      ("#eta 2nd_Lepton_2SSOF "+outputName_).c_str(),      100, -3., 3.);
    Eta_2ndleadingLepton_2SSOF->Sumw2();
    Phi_leadingLepton_2SSOF       = new TH1F(("Phi_leadingLepton_2SSOF_"+outputName_).c_str(),      ("#Phi Lepton_2SSOF "+outputName_).c_str(),      100, -4.0, 4.);
    Phi_leadingLepton_2SSOF->Sumw2();
    Phi_2ndleadingLepton_2SSOF       = new TH1F(("Phi_2ndleadingLepton_2SSOF_"+outputName_).c_str(),      ("#Phi 2nd_Lepton_2SSOF "+outputName_).c_str(),      100, -4.0, 4.);
    Phi_2ndleadingLepton_2SSOF->Sumw2();
    Pt_leading_Jet = new TH1F(("Pt_leading_Jet_"+outputName_).c_str(),      ("P_{T} leading jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_leading_Jet ->Sumw2();
    Pt_2ndleading_Jet = new TH1F(("Pt_2ndleading_Jet_"+outputName_).c_str(),      ("P_{T} 2nd_leading jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_2ndleading_Jet ->Sumw2();
    Pt_3rdleading_Jet = new TH1F(("Pt_3rdleading_Jet_"+outputName_).c_str(),      ("P_{T}  3rd_leading Jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_3rdleading_Jet ->Sumw2();
    Pt_4thleading_Jet = new TH1F(("Pt_4thleading_Jet_"+outputName_).c_str(),      ("P_{T} 4th_leading jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_4thleading_Jet ->Sumw2();
    Pt_5thleading_Jet = new TH1F(("Pt_5thleading_Jet_"+outputName_).c_str(),      ("P_{T} 5th_leading jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_5thleading_Jet ->Sumw2();
    Pt_6thleading_Jet = new TH1F(("Pt_6thleading_Jet_"+outputName_).c_str(),      ("P_{T} 6th_leading jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_6thleading_Jet ->Sumw2();
    Pt_7thleading_Jet = new TH1F(("Pt_7thleading_Jet_"+outputName_).c_str(),      ("P_{T} 7th_leading jet "+outputName_).c_str(),      100, 0.0, 500.0);
    Pt_7thleading_Jet ->Sumw2();
    Delta_Phi_2SSElec	= new TH1F(("Delta_Phi_2SSElec_"+outputName_).c_str(),      ("#Delta #Phi_2SSElec "+outputName_).c_str(),      100, -4.0, 4.);
    Delta_Phi_2SSElec->Sumw2();
    DeltaR_2SSElec		= new TH1F(("DeltaR_2SSElec_"+outputName_).c_str(),      ("#Delta R 2SSElec "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_2SSElec->Sumw2();
    Delta_Phi_2SSMuon	= new TH1F(("Delta_Phi_2SSMuon_"+outputName_).c_str(),      ("#Delta #Phi 2SSMuon "+outputName_).c_str(),      100, -4.0, 4.);
    Delta_Phi_2SSMuon->Sumw2();
    DeltaR_2SSMuon		= new TH1F(("DeltaR_2SSMuon_"+outputName_).c_str(),      ("#Delta R 2SSMuon "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_2SSMuon->Sumw2();
    Delta_Phi_2SSOF		= new TH1F(("Delta_Phi_2SSOF_"+outputName_).c_str(),      ("#Delta #Phi 2SSOF "+outputName_).c_str(),      100, -4.0, 4.);
    Delta_Phi_2SSOF->Sumw2();
    DeltaR_2SSOF		= new TH1F(("DeltaR_2SSOF_"+outputName_).c_str(),      ("#Delta R 2SSOF "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_2SSOF->Sumw2();
    DeltaRmin_Elec0_b	= new TH1F(("DeltaRmin_Elec0_b_"+outputName_).c_str(),      ("#Delta Rmin Elec_{0} bJet "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaRmin_Elec0_b -> Sumw2();
    DeltaRmin_Mu0_b	= new TH1F(("DeltaRmin_Mu0_b_"+outputName_).c_str(),      ("DeltaRmin Mu_{0} bJet "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaRmin_Mu0_b-> Sumw2();
    DeltaRmin_lep0_b	= new TH1F(("DeltaRmin_lep0_b_"+outputName_).c_str(),      ("DeltaRmin lep_{0} bJet "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaRmin_lep0_b-> Sumw2();
    Mass_Elec0_b		= new TH1F(("Mass_Elec0_b_"+outputName_).c_str(),      ("Mass_Elec_{0} bJet "+outputName_).c_str(),      100, 0.0, 1000.);
    Mass_Elec0_b-> Sumw2();
    Mass_Mu0_b		= new TH1F(("Mass_Mu0_b_"+outputName_).c_str(),      ("Mass_Mu_{0} bJet "+outputName_).c_str(),      100, 0.0, 1000.);
    Mass_Mu0_b-> Sumw2();
    Nb_CSVL_bJets_After_Cuts = new TH1F(("Nb_CSVL_bJets_After_Cuts_"+outputName_).c_str(),      ("Number of selected CSVL b Jets after all cuts"+outputName_).c_str(),      12, -0.5,11.5);
    Nb_CSVL_bJets_After_Cuts-> Sumw2();
    
    Mass_lep0_b		= new TH1F(("Mass_lep0_b_"+outputName_).c_str(),      ("Mass_lep_{0} bJet "+outputName_).c_str(),      100, 0.0, 1000.);
    Mass_lep0_b-> Sumw2();
    Mass_SM_bJet_lep0 = new TH1F(("Mass_SM_bJet_lep0_"+outputName_).c_str(),      ("Mass_SM_bJet_lep_{0} "+outputName_).c_str(),      100, 0.0, 500.);
    Mass_SM_bJet_lep0 -> Sumw2();
    Mass_SM_bJet_lep1 = new TH1F(("Mass_SM_bJet_lep1_"+outputName_).c_str(),      ("Mass_SM_bJet_lep_{1} "+outputName_).c_str(),      100, 0.0, 500.);
    Mass_SM_bJet_lep1 -> Sumw2();
    
    
    Mass_W_Jets		= new TH1F(("Mass_W_Jets_"+outputName_).c_str(),      ("Mass_W_Jets "+outputName_).c_str(),      100, 0.0, 300.);
    Mass_W_Jets-> Sumw2();
    
    Ratio_FCNC_3JetsLep0_to_SM_mLep1b = new TH1F(("Ratio_FCNC_3JetsLep0_to_SM_mLep1b_"+outputName_).c_str(),("Ratio_FCNC_3JetsLep0_to_SM_mLep1b_"+outputName_).c_str(),100.,0.,10.);
    Ratio_FCNC_3JetsLep0_to_SM_mLep1b-> Sumw2();
    Ratio_FCNC_3JetsLep1_to_SM_mLep0b = new TH1F(("Ratio_FCNC_3JetsLep1_to_SM_mLep0b_"+outputName_).c_str(),("Ratio_FCNC_3JetsLep1_to_SM_mLep0b_"+outputName_).c_str(),100.,0.,10.);
    Ratio_FCNC_3JetsLep1_to_SM_mLep0b-> Sumw2();
    
    Mass_FCNC_top_Lep1 = new TH1F(("Mass_FCNC_top_Lep1_"+outputName_).c_str(),      ("Mass_FCNC_top_Lep_{1} "+outputName_).c_str(),      100, 0.0, 500.);
    Mass_FCNC_top_Lep1 -> Sumw2();
    Mass_FCNC_top_Lep0 = new TH1F(("Mass_FCNC_top_Lep0_"+outputName_).c_str(),      ("Mass_FCNC_top_Lep_{0} "+outputName_).c_str(),      100, 0.0, 500.);
    Mass_FCNC_top_Lep0 -> Sumw2();
    
    ////*** New variables for right and wrong combinations ***//////
    M_Wjets_FCNCTop_rightComb_Rec = new TH1F(("M_Wjets_FCNCToptoH_rightComb_Rec_"+outputName_).c_str(),("M_Wjets_FCNCToptoH_rightComb_Rec_"+outputName_).c_str(),100, 0.0, 500.);
    M_Wjets_FCNCTop_rightComb_Rec-> Sumw2();
    M_Wjets_FCNCTop_rightComb_Gen = new TH1F(("M_Wjets_FCNCToptoH_rightComb_Gen_"+outputName_).c_str(),("M_Wjets_FCNCToptoH_rightComb_Gen_"+outputName_).c_str(),100, 0.0, 500.);
    M_Wjets_FCNCTop_rightComb_Gen-> Sumw2();
    M_Wjets_FCNCTop_WrongComb_NoMC_Rec = new TH1F(("M_Wjets_FCNCToptoH_WrongComb_NoMC_Rec_"+outputName_).c_str(),("M_Wjets_FCNCToptoH_WrongComb_NoMC_Rec_"+outputName_).c_str(),100, 0.0, 500.);
    M_Wjets_FCNCTop_WrongComb_NoMC_Rec-> Sumw2();
    
    Pt_SMLep0_rightComb_Rec= new TH1F(("Pt_SMLep0_rightComb_Rec_"+outputName_).c_str(),("P_{t} SMLep_{0}_rightComb_Rec_ "+outputName_).c_str(),100, 0.0, 300.);
    Pt_SMLep0_rightComb_Rec->Sumw2();
    Pt_SMLep0_rightComb_Gen= new TH1F(("Pt_SMLep0_rightComb_Gen_"+outputName_).c_str(),("P_{t} SMLep_{0}_rightComb_Gen_ "+outputName_).c_str(),100, 0.0, 300.);
    Pt_SMLep0_rightComb_Gen->Sumw2();
    Pt_SMLep1_rightComb_Rec= new TH1F(("Pt_SMLep1_rightComb_Rec_"+outputName_).c_str(),("P_{t} SMLep_{1}_rightComb_Rec_ "+outputName_).c_str(),100, 0.0, 300.);
    Pt_SMLep1_rightComb_Rec->Sumw2();
    Pt_SMLep1_rightComb_Gen= new TH1F(("Pt_SMLep1_rightComb_Gen_"+outputName_).c_str(),("P_{t} SMLep_{1}_rightComb_Gen_ "+outputName_).c_str(),100, 0.0, 300.);
    Pt_SMLep1_rightComb_Gen->Sumw2();
    Pt_leading_Lep0_WrongComb_Rec= new TH1F(("Pt_leading_Lep0_WrongComb_Rec_"+outputName_).c_str(),("P_{t} Lep_{0}_WrongComb_Rec_ "+outputName_).c_str(),100, 0.0, 300.);
    Pt_leading_Lep0_WrongComb_Rec->Sumw2();
    Pt_second_leading_Lep1_WrongComb_Rec= new TH1F(("Pt_second_leading_Lep1_WrongComb_Rec_" +outputName_).c_str(),("P_{t} Lep_{1}_rightComb_Rec_ "+outputName_).c_str(),100, 0.0, 300.);
    Pt_second_leading_Lep1_WrongComb_Rec->Sumw2();
    Pt_FCNCLep1_rightComb_Rec = new TH1F(("Pt_FCNCLep1_rightComb_Rec_"+outputName_).c_str(),("P_{t} FCNCLep_{1}_rightComb_Rec_"+outputName_).c_str(),100, 0.0, 300.);
    Pt_FCNCLep1_rightComb_Rec-> Sumw2();
    Pt_FCNCLep1_rightComb_Gen= new TH1F(("Pt_FCNCLep1_rightComb_Gen_"+outputName_).c_str(),("P_{t} FCNCLep_{1}_rightComb_Gen_"+outputName_).c_str(),100, 0.0, 300.);
    Pt_FCNCLep1_rightComb_Gen-> Sumw2();
    Pt_FCNCLep0_rightComb_Rec= new TH1F(("Pt_FCNCLep0_rightComb_Rec_"+outputName_).c_str(),("P_{t} FCNCLep_{0}_rightComb_Rec_"+outputName_).c_str(),100, 0.0, 300.);
    Pt_FCNCLep0_rightComb_Rec->Sumw2();
    Pt_FCNCLep0_rightComb_Gen = new TH1F(("Pt_FCNCLep0_rightComb_Gen_"+outputName_).c_str(),("P_{t} FCNCLep_{0}_rightComb_Gen_"+outputName_).c_str(),100, 0.0, 300.);
    Pt_FCNCLep0_rightComb_Gen-> Sumw2();
    
    Ht_Jets		= new TH1F(("Ht_Jets_"+outputName_).c_str(),      ("H_{T}  All-Jet "+outputName_).c_str(),      100, 0.0, 1000.0);
    Elec1_pt_to_Ht_ratio = new TH1F(("Elec1_pt_to_Ht_ratio_"+outputName_).c_str(),      ("2nd Elec-P_{T} to H_{T} Ratio "+outputName_).c_str(),      100, 0.0, 1.);
    Mu1_pt_to_Ht_ratio = new TH1F(("Mu1_pt_to_Ht_ratio_"+outputName_).c_str(),      ("2nd Mu-P_{T} to H_{T} Ratio "+outputName_).c_str(),      100, 0.0, 1.);
    lep1_pt_to_Ht_ratio = new TH1F(("lep1_pt_to_Ht_ratio_"+outputName_).c_str(),      ("2nd Elec-P_{T} to H_{T} Ratio "+outputName_).c_str(),      100, 0.0, 1.);
    MET_histo = new TH1F(("MET_histo_"+outputName_).c_str(),      ("MET "+outputName_).c_str(),      100, 0.0, 500.0);
    Eta_jets = new TH1F(("Eta_jets_"+outputName_).c_str(),      ("#eta jets "+outputName_).c_str(),      100, -2.5, 2.5);
    Phi_jets = new TH1F(("Phi_jets_"+outputName_).c_str(),      ("#phi jets "+outputName_).c_str(),      100, -4.0, 4.);
    Ht_Jets->Sumw2();
    MET_histo->Sumw2();
    Eta_jets->Sumw2();
    Phi_jets->Sumw2();
    Elec1_pt_to_Ht_ratio -> Sumw2();
    Mu1_pt_to_Ht_ratio -> Sumw2();
    lep1_pt_to_Ht_ratio -> Sumw2();
    
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec= new TH1F(("DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec_"+outputName_).c_str(),("#Delta #Phi SMtoplep_{0} FCNCtoplep_{1} Reco"+outputName_).c_str(), 100, -4.0, 4.);
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen = new TH1F(("DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen_"+outputName_).c_str(),("#Delta #Phi SMtoplep_{0} FCNCtoplep_{1} Gen"+outputName_).c_str(),      100, -4.0, 4.);
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec = new TH1F(("DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec_"+outputName_).c_str(),("#Delta #Phi SMtoplep_{1} FCNCtoplep_{0} Reco"+outputName_).c_str(),      100, -4.0, 4.);
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen = new TH1F(("DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen_"+outputName_).c_str(),("#Delta #Phi SMtoplep_{1} FCNCtoplep_{0} Gen"+outputName_).c_str(),      100, -4.0, 4.);
    DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC = new TH1F(("DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC_"+outputName_).c_str(),("#Delta #Phi SMtoplep_{1} FCNCtoplep_{0} Reco "+outputName_).c_str(),      100, -4.0, 4.);
    DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC = new TH1F(("DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC_"+outputName_).c_str(),("#Delta #Phi SMtoplep_{0} FCNCtoplep_{1} Reco "+outputName_).c_str(),      100, -4.0, 4.);
    
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec= new TH1F(("DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec_"+outputName_).c_str(),("#Delta R SMtoplep_{0} FCNCtoplep_{1} Reco"+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen= new TH1F(("DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen_"+outputName_).c_str(),      ("#Delta R SMtoplep_{0} FCNCtoplep_{1} Gen"+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec= new TH1F(("DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec_"+outputName_).c_str(),      ("#Delta R SMtoplep_{1} FCNCtoplep_{0} Reco "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen= new TH1F(("DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen_"+outputName_).c_str(),      ("#Delta R SMtoplep_{1} FCNCtoplep_{0} Gen "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC= new TH1F(("DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC_"+outputName_).c_str(),      ("#Delta R SMtoplep_{1} FCNCtoplep_{0} Reco "+outputName_).c_str(),      100, 0.0, 5.);
    DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC= new TH1F(("DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC_"+outputName_).c_str(),      ("#Delta R SMtoplep_{0} FCNCtoplep_{1} Reco "+outputName_).c_str(),      100, 0.0, 5.);
    
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec->Sumw2();
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen->Sumw2();
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec-> Sumw2();
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen-> Sumw2();
    DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC-> Sumw2();
    DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC-> Sumw2();
    
    
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec-> Sumw2();
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen-> Sumw2();
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec-> Sumw2();
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen-> Sumw2();
    DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC-> Sumw2();
    DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC-> Sumw2();
    
    ////*** histos for MVA trees ***///
    histo_MVA_Ht_Jets= new TH1F(("histo_MVA_Ht_Jets_"+outputName_).c_str(),      ("H_{T}  All-Jet "+outputName_).c_str(),      100, 0.0, 1000.0);
    histo_MVA_Met= new TH1F(("histo_MVA_Met_"+outputName_).c_str(),      ("MET "+outputName_).c_str(),      100, 0.0, 500.0);
    histo_MVA_Nb_CSVL_bJets= new TH1F(("histo_MVA_Nb_CSVL_bJets_"+outputName_).c_str(),      ("Number of CSVB-jets "+outputName_).c_str(),      10, -0.5, 9.5);
    histo_MVA_Nb_Jets= new TH1F(("histo_MVA_Nb_Jets_"+outputName_).c_str(),      ("Number of selected_jets "+outputName_).c_str(),      12, -0.5, 11.5);
    histo_MVA_DeltaR_2SSLep= new TH1F(("histo_MVA_DeltaR_2SSLep_"+outputName_).c_str(),      ("#Delta R 2SSLep "+outputName_).c_str(),      100, 0.0, 5.);
    histo_MVA_Delta_Phi_2SSLep= new TH1F(("histo_MVA_Delta_Phi_2SSLep_"+outputName_).c_str(),      ("#Delta #Phi 2SSLep "+outputName_).c_str(),      100, -4.0, 4.);
    histo_MVA_Lep1_pt_to_Ht_ratio= new TH1F(("histo_MVA_Lep1_pt_to_Ht_ratio_"+outputName_).c_str(),      ("2nd Lep-P_{T} to H_{T} Ratio "+outputName_).c_str(),      100, 0.0, 1.);
    histo_MVA_Mass_Lep0_b= new TH1F(("histo_MVA_Mass_Lep0_b_"+outputName_).c_str(),      ("Mass Lep_{0} bJet "+outputName_).c_str(),      100, 0.0, 1000.);
    histo_MVA_DeltaRmin_Lep0_b= new TH1F(("histo_MVA_DeltaRmin_Lep0_b_"+outputName_).c_str(),      ("#Delta R_{min} Lep_{0} bJet "+outputName_).c_str(),      100, 0.0, 5.);
    histo_MVA_Leading_Lep_Pt= new TH1F(("histo_MVA_Leading_Lep_Pt_"+outputName_).c_str(),      ("p_{T} Leading Lepton "+outputName_).c_str(),      100, 0.0, 300.0);
    histo_MVA_second_Leading_Lep_Pt= new TH1F(("histo_MVA_second_Leading_Lep_Pt_"+outputName_).c_str(),      ("p_{T} 2nd Leading Lepton "+outputName_).c_str(),      100, 0.0, 300.0);
    //histo_MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b;
    //histo_MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b;
    histo_MVA_Mass_Lep1_b= new TH1F(("histo_MVA_Mass_Lep1_b_"+outputName_).c_str(),      ("Mass Lep_{} bJet "+outputName_).c_str(),      100, 0.0, 500.);
    histo_MVA_DeltaRmin_Lep1_b= new TH1F(("histo_MVA_Mass_Lep1_b_"+outputName_).c_str(),      ("#Delta R_{min} Lep_{1} bJet "+outputName_).c_str(),      100, 0.0, 5.);
    //histo_MVA_Mass_FCNC_top_Lep1;
    //histo_MVA_Mass_FCNC_top_Lep0;
    histo_MVA_St= new TH1F(("histo_MVA_St_"+outputName_).c_str(),      ("histo_MVA_St "+outputName_).c_str(),      100, 0.0, 3000.);
    histo_MVA_Sum_lep_Pt= new TH1F(("histo_MVA_Sum_lep_Pt_"+outputName_).c_str(),      ("histo_MVA_Sum_lep_Pt "+outputName_).c_str(),      100, 0.0, 1000.);
    
    histo_MVA_St->Sumw2();
    histo_MVA_Sum_lep_Pt->Sumw2();
    
    histo_MVA_Ht_Jets->Sumw2();
    histo_MVA_Met->Sumw2();
    histo_MVA_Nb_CSVL_bJets->Sumw2();
    histo_MVA_Nb_Jets->Sumw2();
    histo_MVA_DeltaR_2SSLep->Sumw2();
    histo_MVA_Delta_Phi_2SSLep->Sumw2();
    histo_MVA_Lep1_pt_to_Ht_ratio->Sumw2();
    histo_MVA_Mass_Lep0_b->Sumw2();
    histo_MVA_DeltaRmin_Lep0_b->Sumw2();
    histo_MVA_Leading_Lep_Pt->Sumw2();
    histo_MVA_second_Leading_Lep_Pt->Sumw2();
    //histo_MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b->Sumw2();
    //histo_MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b->Sumw2();
    histo_MVA_Mass_Lep1_b->Sumw2();
    histo_MVA_DeltaRmin_Lep1_b->Sumw2();
    //histo_MVA_Mass_FCNC_top_Lep1->Sumw2();
    //histo_MVA_Mass_FCNC_top_Lep0->Sumw2();
    Nb_Jets_after_2SSLep = new TH1F(("Nb_Jets_after_2SSLep_"+outputName_).c_str(),      ("# jets after 2SSLep "+outputName_).c_str(),      12, -0.5, 11.5);
    Nb_Jets_after_2SSLep->Sumw2();

    
    /////***** 2D histograms ***** //////
    Ht_Met_histo = new TH2F(("Ht_Met_histo_"+outputName_).c_str(),("Ht_Met_histo"+outputName_).c_str(), 100.,0.0,1000., 100., 0.0, 500.);
    Ht_Met_histo->Sumw2();
    SM_mLep0b_FCNC_3JetsLep1 = new TH2F(("SM_mLep0b_FCNC_3JetsLep1_"+outputName_).c_str(),("SM_mLep0b_vs_FCNC_3JetsLep_{1}"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    SM_mLep0b_FCNC_3JetsLep1->Sumw2();
    SM_mLep1b_FCNC_3JetsLep0 = new TH2F(("SM_mLep1b_FCNC_3JetsLep0_"+outputName_).c_str(),("SM_mLep1b_vs_FCNC_3JetsLep_{0}"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    SM_mLep1b_FCNC_3JetsLep0->Sumw2();
    SM_mLep0b_FCNC_3JetsLep0 = new TH2F(("SM_mLep0b_FCNC_3JetsLep0_"+outputName_).c_str(),("SM_mLep0b_vs_FCNC_3JetsLep_{0}"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    SM_mLep0b_FCNC_3JetsLep0->Sumw2();
    SM_mLep1b_FCNC_3JetsLep1 = new TH2F(("SM_mLep1b_FCNC_3JetsLep1_"+outputName_).c_str(),("SM_mLep1b_vs_FCNC_3JetsLep_{1}"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    SM_mLep1b_FCNC_3JetsLep0->Sumw2();
    Pt_Lep0_vs_Lep1 = new TH2F(("Pt_Lep_{0}_vs_Lep_{1}"+outputName_).c_str(),("Pt_Lep_{0}_vs_Lep_{1}"+outputName_).c_str(), 100.,0.0,300., 100., 0.0, 300.);
    Pt_Lep0_vs_Lep1 ->Sumw2();
    Mass_Right_SM_lep0_FCNC_lep1_RecLevel = new TH2F(("Mass_Right_SM_lep0_FCNC_lep1_RecLevel_"+outputName_).c_str(),("Mass_Right_SM_lep0_FCNC_lep1_RecLevel_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Mass_Right_SM_lep0_FCNC_lep1_RecLevel->Sumw2();

    
    Mass_Right_SM_lep0_FCNC_lep1_GenLevel= new TH2F(("Mass_Right_SM_lep0_FCNC_lep1_GenLevel_"+outputName_).c_str(),("Mass_Right_SM_lep0_FCNC_lep1_GenLevel_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Mass_Right_SM_lep0_FCNC_lep1_GenLevel->Sumw2();
    
    Mass_Right_SM_lep1_FCNC_lep0_RecLevel= new TH2F(("Mass_Right_SM_lep1_FCNC_lep0_RecLevel_"+outputName_).c_str(),("Mass_Right_SM_lep1_FCNC_lep0_RecLevel_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Mass_Right_SM_lep1_FCNC_lep0_RecLevel->Sumw2();
    
    Mass_Right_SM_lep1_FCNC_lep0_GenLevel= new TH2F(("Mass_Right_SM_lep1_FCNC_lep0_GenLevel_"+outputName_).c_str(),("Mass_Right_SM_lep1_FCNC_lep0_GenLevel_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Mass_Right_SM_lep1_FCNC_lep0_GenLevel->Sumw2();
    
    Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel= new TH2F(("Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel_"+outputName_).c_str(),("Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel->Sumw2();
    
    Mass_Wrong_SM_lep1_FCNC_le0_RecLevel= new TH2F(("Mass_Wrong_SM_lep1_FCNC_le0_RecLevel_"+outputName_).c_str(),("Mass_Wrong_SM_lep1_FCNC_le0_RecLevel_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Mass_Wrong_SM_lep1_FCNC_le0_RecLevel->Sumw2();
    
    Pt_SMLep0_to_FCNCLep1_rightComb_Rec= new TH2F(("Pt_SMLep0_to_FCNCLep1_rightComb_Rec_"+outputName_).c_str(),("Pt_SMLep0_to_FCNCLep1_rightComb_Rec_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Pt_SMLep0_to_FCNCLep1_rightComb_Rec->Sumw2();
    Pt_SMLep0_to_FCNCLep1_rightComb_Gen= new TH2F(("Pt_SMLep0_to_FCNCLep1_rightComb_Gen_"+outputName_).c_str(),("Pt_SMLep0_to_FCNCLep1_rightComb_Gen_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Pt_SMLep0_to_FCNCLep1_rightComb_Gen->Sumw2();
    Pt_SMLep1_to_FCNCLep0_rightComb_Rec= new TH2F(("Pt_SMLep1_to_FCNCLep0_rightComb_Rec_"+outputName_).c_str(),("Pt_SMLep1_to_FCNCLep0_rightComb_Rec_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Pt_SMLep1_to_FCNCLep0_rightComb_Rec->Sumw2();
    Pt_SMLep1_to_FCNCLep0_rightComb_Gen= new TH2F(("Pt_SMLep1_to_FCNCLep0_rightComb_Gen_"+outputName_).c_str(),("Pt_SMLep1_to_FCNCLep0_rightComb_Gen_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Pt_SMLep1_to_FCNCLep0_rightComb_Gen->Sumw2();
    Pt_SMLep0_to_FCNCLep1_WrongComb_Rec= new TH2F(("Pt_SMLep0_to_FCNCLep1_WrongComb_Rec_"+outputName_).c_str(),("Pt_SMLep0_to_FCNCLep1_WrongComb_Rec_"+outputName_).c_str(), 100.,0.0,500., 100., 0.0, 500.);
    Pt_SMLep0_to_FCNCLep1_WrongComb_Rec->Sumw2();
    
    

    //----------------------------------------------------
    //Calcul event weight
    //do not forget to devide by nevent in "Finalize"
    weight = luminosity*xsec;
    nb_of_fakeElectron = 0;
    nb_of_removed_jets = 0;
    

    //**** for efficiency calculations ****//
    nb_events_after_2SSL=0;
    nb_events_after_2SSL_4Jets=0;
    nb_events_after_2SSL_4Jets_1CSVLB=0;
    nb_events_AllCuts_without_CHeckMC=0;
    nb_events_AllCuts_MC_Right_CSVLB=0;
    nb_events_AllCuts_MC_Wrong_CSVLB=0;
    nb_events_AllCuts_MC_CSVLB=0;
    
    nb_events_AllCuts_MC_Wrong_2SSL=0;
    nb_events_AllCuts_MC_Right_C=0;
    nb_events_AllCuts_MC_Wrong_C=0;
    nb_events_AllCuts_MC_C=0;
    nb_events_AllCuts_MC_Right_FCNC_Wjets=0;
    nb_events_AllCuts_MC_Wrong_FCNC_Wjets=0;
    nb_events_AllCuts_MC_FCNC_Wjets=0;
    
    nb_events_after_lep0_from_FCNCtop=0;
    nb_events_after_lep0_from_SMtop=0;
    nb_events_after_lep1_from_FCNCtop=0;
    nb_events_after_lep1_from_SMtop=0;
    //nb_Elecs_before_misid =0;
    //nb_Elecs_after_misid =0;
    
    cout << "END   Initialization" << endl;
    return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void FCNC_2SSL::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
    cout << "BEGIN Finalization" << endl;
    float scale = 1./nevent;
    
    cutFlow->Scale(scale);
    /////---------------------////
    M_Wjets_FCNCTop_rightComb_Rec->Scale(scale);
    M_Wjets_FCNCTop_rightComb_Gen->Scale(scale);
    M_Wjets_FCNCTop_WrongComb_NoMC_Rec->Scale(scale);
    Pt_SMLep0_rightComb_Rec->Scale(scale);
    Pt_SMLep0_rightComb_Gen->Scale(scale);
    Pt_SMLep1_rightComb_Rec->Scale(scale);
    Pt_SMLep1_rightComb_Gen->Scale(scale);
    Pt_leading_Lep0_WrongComb_Rec->Scale(scale);
    Pt_second_leading_Lep1_WrongComb_Rec->Scale(scale);
    Pt_FCNCLep0_rightComb_Rec-> Scale(scale);
    Pt_FCNCLep0_rightComb_Gen-> Scale(scale);
    Pt_FCNCLep1_rightComb_Rec-> Scale(scale);
    Pt_FCNCLep1_rightComb_Gen-> Scale(scale);
    Mass_W_Jets->Scale(scale);
    Ratio_FCNC_3JetsLep0_to_SM_mLep1b->Scale(scale);
    Ratio_FCNC_3JetsLep1_to_SM_mLep0b->Scale(scale);
    
    
    Mass_Right_SM_lep0_FCNC_lep1_RecLevel->Scale(scale);
    Mass_Right_SM_lep0_FCNC_lep1_GenLevel->Scale(scale);
    Mass_Right_SM_lep1_FCNC_lep0_RecLevel->Scale(scale);
    Mass_Right_SM_lep1_FCNC_lep0_GenLevel->Scale(scale);
    Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel->Scale(scale);
    Mass_Wrong_SM_lep1_FCNC_le0_RecLevel->Scale(scale);
    
    Pt_SMLep0_to_FCNCLep1_rightComb_Rec->Scale(scale);
    Pt_SMLep0_to_FCNCLep1_rightComb_Gen->Scale(scale);
    Pt_SMLep1_to_FCNCLep0_rightComb_Rec->Scale(scale);
    Pt_SMLep1_to_FCNCLep0_rightComb_Gen->Scale(scale);
    Pt_SMLep0_to_FCNCLep1_WrongComb_Rec->Scale(scale);
    Nb_CSVL_bJets_After_Cuts-> Scale(scale);
    Mass_Mu0_b-> Scale(scale);
    DeltaRmin_Mu0_b-> Scale(scale);
    
    /////--------------------///////
    
    sumet_isol_elec->Scale(scale);
    sumet_isol_muon->Scale(scale);
    sumpt_isol_elec->Scale(scale);
    sumpt_isol_muon->Scale(scale);
    comb_isol_elec->Scale(scale);
    comb_isol_muon->Scale(scale);
    cleanjet_Mult->Scale(scale);
    Nb_elecs->Scale(scale);
    Nb_muons->Scale(scale);
    Nb_Jets->Scale(scale);
    Nb_CSVL_jets->Scale(scale);
    Nb_CSVM_jets->Scale(scale);
    Nb_CSVT_jets->Scale(scale);
    Pt_leadingElec_2SSSF->Scale(scale);
    Pt_2ndleadingElec_2SSSF->Scale(scale);
    Pt_leadingMuon_2SSSF->Scale(scale);
    Pt_2ndleadingMuon_2SSSF->Scale(scale);
    Pt_leadingLepton_2SSOF->Scale(scale);
    Pt_2ndleadingLepton_2SSOF->Scale(scale);
    Eta_leadingElec_2SSSF->Scale(scale);
    Eta_2ndleadingElec_2SSSF->Scale(scale);
    Eta_leadingMuon_2SSSF->Scale(scale);
    Eta_2ndleadingMuon_2SSSF->Scale(scale);
    Eta_leadingLepton_2SSOF->Scale(scale);
    Eta_2ndleadingLepton_2SSOF->Scale(scale);
    Phi_leadingElec_2SSSF->Scale(scale);
    Phi_2ndleadingElec_2SSSF->Scale(scale);
    Phi_leadingMuon_2SSSF->Scale(scale);
    Phi_2ndleadingMuon_2SSSF->Scale(scale);
    Phi_leadingLepton_2SSOF->Scale(scale);
    Phi_2ndleadingLepton_2SSOF->Scale(scale);
    Delta_Phi_2SSElec->Scale(scale);
    DeltaR_2SSElec->Scale(scale);
    Delta_Phi_2SSMuon->Scale(scale);
    DeltaR_2SSMuon->Scale(scale);
    Delta_Phi_2SSOF->Scale(scale);
    DeltaR_2SSOF->Scale(scale);
    SM_mLep0b_FCNC_3JetsLep1->Scale(scale);
    SM_mLep0b_FCNC_3JetsLep0->Scale(scale);
    SM_mLep1b_FCNC_3JetsLep1->Scale(scale);
    SM_mLep1b_FCNC_3JetsLep0->Scale(scale);
    Mass_SM_bJet_lep0 -> Scale(scale);
    Mass_SM_bJet_lep1 -> Scale(scale);
    Mass_FCNC_top_Lep1 -> Scale(scale);
    Mass_FCNC_top_Lep0 -> Scale(scale);
    Pt_Lep0_vs_Lep1 -> Scale(scale);
    Mass_lep0_b-> Scale(scale);
    DeltaRmin_Elec0_b->Scale(scale);
    MET_histo ->Scale(scale);
    Eta_jets->Scale(scale);
    Phi_jets->Scale(scale);
    Elec1_pt_to_Ht_ratio ->Scale(scale);
    Mu1_pt_to_Ht_ratio ->Scale(scale);
    lep1_pt_to_Ht_ratio ->Scale(scale);
    Ht_Jets->Scale(scale);
    histo_MVA_Ht_Jets->Scale(scale);
    histo_MVA_Met->Scale(scale);
    histo_MVA_Nb_CSVL_bJets->Scale(scale);
    histo_MVA_Nb_Jets->Scale(scale);
    histo_MVA_DeltaR_2SSLep->Scale(scale);
    histo_MVA_Delta_Phi_2SSLep->Scale(scale);
    histo_MVA_Lep1_pt_to_Ht_ratio->Scale(scale);
    histo_MVA_Mass_Lep0_b->Scale(scale);
    histo_MVA_DeltaRmin_Lep0_b->Scale(scale);
    histo_MVA_Leading_Lep_Pt->Scale(scale);
    histo_MVA_second_Leading_Lep_Pt->Scale(scale);
    histo_MVA_Sum_lep_Pt->Scale(scale);
    histo_MVA_St->Scale(scale);
    Nb_Jets_after_2SSLep->Scale(scale);
    //histo_MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b->Scale(scale);
    //histo_MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b->Scale(scale);
    histo_MVA_Mass_Lep1_b->Scale(scale);
    histo_MVA_DeltaRmin_Lep1_b->Scale(scale);
    //histo_MVA_Mass_FCNC_top_Lep1->Scale(scale);
    //histo_MVA_Mass_FCNC_top_Lep0->Scale(scale);
    Ht_Met_histo->Scale(scale);
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec->Scale(scale);
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen->Scale(scale);
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec->Scale(scale);
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen->Scale(scale);
    DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC->Scale(scale);
    DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC->Scale(scale);
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec->Scale(scale);
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen->Scale(scale);
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec->Scale(scale);
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen->Scale(scale);
    DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC->Scale(scale);
    DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC->Scale(scale);
    
    cout << "///*** ------------------------------------------------- ***///" << endl;
    cout << "///*** the number of events after applied different cuts ***///" << endl;
    cout << "///*** ------------------------------------------------- ***///" << endl;
    cout << "the number of Total events  =  " << nevent << endl;
    cout << "the number of events after 2SSL =  " << nb_events_after_2SSL << endl;
    cout << "the number of events after 2SSL + >= 4jets (50/30/20)  =  " << nb_events_after_2SSL_4Jets << endl;
    cout << "the number of events after 2SSL + >= 4jets + >= 1CSVLB =  " <<nb_events_after_2SSL_4Jets_1CSVLB << endl;
    cout << "the number of events after all cuts with MC and right combination of CSVLB =   " << nb_events_AllCuts_MC_Right_CSVLB << endl;
    cout << "the number of events after all cuts without MC for CSVLB (Wrong) =  " << nb_events_AllCuts_MC_Wrong_CSVLB << endl;
    cout << "the number of events after all cuts with only MC particle for CSVLB (MC exist but with mismatching) =   " << nb_events_AllCuts_MC_CSVLB << endl;
    cout << "the number of events after all cuts with MC and right combination of lep0_from_FCNCtop =  " << nb_events_after_lep0_from_FCNCtop << endl;
    cout << "the number of events after all cuts with  MC and right combination of lep1_from_FCNCtop =  " << nb_events_after_lep1_from_FCNCtop<< endl;
    cout << "the number of events after all cuts with MC and right combination of lep0_from_SMtop =  " << nb_events_after_lep0_from_SMtop << endl;
    cout << "the number of events after all cuts with  MC and right combination of lep1_from_SMtop =  " << nb_events_after_lep1_from_SMtop << endl;
    cout << "the number of events after all cuts without MC particle for 2SSL (Wrong) =  " << nb_events_AllCuts_MC_Wrong_2SSL << endl;
    cout << "the number of events after all cuts with MC and right combination of C-jet  =  " << nb_events_AllCuts_MC_Right_C << endl;
    cout << "the number of events after all cuts with only MC particle for C-jet =   " << nb_events_AllCuts_MC_Wrong_C << endl;
    cout << "the number of events after all cuts without MC for C-jet =  " << nb_events_AllCuts_MC_C << endl;
    cout << "the number of events after all cuts with MC and right combination of FCNC-W-jets =  " << nb_events_AllCuts_MC_Right_FCNC_Wjets << endl;
    cout << "the number of events after all cuts with only MC particle for FCNC-jets =  " << nb_events_AllCuts_MC_Wrong_FCNC_Wjets << endl;
    cout << "the number of events after all cuts without MC for FCNC-W-Jets =  " << nb_events_AllCuts_MC_FCNC_Wjets << endl;
    //cout << "the number of electrons before charge misid  =  " << nb_Elecs_before_misid << endl;
    //cout << "the number of electrons after charge misid  =  " << nb_Elecs_after_misid << endl;
    cout << "the number of fake electrons  =  " << nb_of_fakeElectron << endl;
    cout << "the number of removed jets  =  " << nb_of_removed_jets << endl;
    
    
    
    cout << "///*** ------------------------------------------------------- ***///" << endl;
    cout << "///*** the selection efficiencies after applied different cuts ***///" << endl;
    cout << "///*** ------------------------------------------------------- ***///" << endl;
    cout << "the efficiency after 2SSL   =  " << nb_events_after_2SSL/nevent << endl;
    cout << "the efficiency after 2SSL + >= 4jets (50/30/20)   =  " << nb_events_after_2SSL_4Jets/nevent << endl;
    cout << "the efficiency after 2SSL + >= 4jets + >= 1CSVLB   =  " <<nb_events_after_2SSL_4Jets_1CSVLB/nevent << endl;
    cout << "the efficiency after all cuts but without checking MC particles   =  " <<nb_events_AllCuts_without_CHeckMC/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of CSVLB   =   " << nb_events_AllCuts_MC_Right_CSVLB/nevent << endl;
    cout << "the efficiency after all cuts without MC for CSVLB   =  " << nb_events_AllCuts_MC_Wrong_CSVLB/nevent << endl;
    cout << "the efficiency after all cuts with only MC particle for CSVLB   =  " << nb_events_AllCuts_MC_CSVLB/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of lep0_from_FCNCtop  =   " << nb_events_after_lep0_from_FCNCtop/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of lep1_from_FCNCtop  =   " << nb_events_after_lep1_from_FCNCtop/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of lep0_from_SMtop  =   " << nb_events_after_lep0_from_SMtop/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of lep1_from_SMtop  =   " << nb_events_after_lep1_from_SMtop/nevent << endl;
    cout << "the efficiency after all cuts without MC particle for 2SSL   =   " << nb_events_AllCuts_MC_Wrong_2SSL/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of C-jet   =   " << nb_events_AllCuts_MC_Right_C/nevent << endl;
    cout << "the efficiency after all cuts with only MC particle for C-jet   =   " << nb_events_AllCuts_MC_Wrong_C/nevent << endl;
    cout << "the efficiency after all cuts without MC for C-jet   =  " << nb_events_AllCuts_MC_C/nevent << endl;
    cout << "the efficiency after all cuts with MC and right combination of FCNC-W-jets   =  " << nb_events_AllCuts_MC_Right_FCNC_Wjets/nevent << endl;
    cout << "the efficiency after all cuts with only MC particle for FCNC-jets   =  " << nb_events_AllCuts_MC_Wrong_FCNC_Wjets/nevent << endl;
    cout << "the efficiency after all cuts without MC for FCNC-W-Jets    =  " << nb_events_AllCuts_MC_FCNC_Wjets/nevent << endl;

    ////// axis lables /////
    cutFlow->GetXaxis()->SetBinLabel(1, "initial");
    cutFlow->GetXaxis()->SetBinLabel(2, "== 2 leptons");
    cutFlow->GetXaxis()->SetBinLabel(3, "== 2 SSL");
    //cutFlow->GetXaxis()->SetBinLabel(4, ">= 4 Jets");
    cutFlow->GetXaxis()->SetBinLabel(4, ">= 4 Jets 50/30/20");
    cutFlow->GetXaxis()->SetBinLabel(5, ">= 1 CSVL b-tagged jets");
    cutFlow->GetXaxis()->SetBinLabel(6, "Met E_{t} > 40 ");
    cutFlow->GetXaxis()->SetBinLabel(7, "Met E_{t} < 70 + H_{T} > 140 ");
    cutFlow->GetXaxis()->SetBinLabel(8, "70 < Met E_{t} < 90 + H_{T} > 120");
    
    
    //Regular variables
    Pt_leadingElec_2SSSF->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_2ndleadingElec_2SSSF->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_leadingMuon_2SSSF->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_2ndleadingMuon_2SSSF->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_leadingLepton_2SSOF->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_2ndleadingLepton_2SSOF->GetXaxis()->SetTitle("p_{T} (GeV)");
    Eta_leadingElec_2SSSF->GetXaxis()->SetTitle("#eta");
    Eta_2ndleadingElec_2SSSF->GetXaxis()->SetTitle("#eta");
    Eta_leadingMuon_2SSSF->GetXaxis()->SetTitle("#eta");
    Eta_2ndleadingMuon_2SSSF->GetXaxis()->SetTitle("#eta");
    Eta_leadingLepton_2SSOF->GetXaxis()->SetTitle("#eta");
    Eta_2ndleadingLepton_2SSOF->GetXaxis()->SetTitle("#eta");
    Phi_leadingElec_2SSSF->GetXaxis()->SetTitle("#phi");
    Phi_2ndleadingElec_2SSSF->GetXaxis()->SetTitle("#phi");
    Phi_leadingMuon_2SSSF->GetXaxis()->SetTitle("#phi");
    Phi_2ndleadingMuon_2SSSF->GetXaxis()->SetTitle("#phi");
    Phi_leadingLepton_2SSOF->GetXaxis()->SetTitle("#phi");
    Phi_2ndleadingLepton_2SSOF->GetXaxis()->SetTitle("#phi");
    
    Delta_Phi_2SSElec->GetXaxis()->SetTitle("#Delta #phi 2SSElec");
    DeltaR_2SSElec->GetXaxis()->SetTitle("#Delta R 2SSElec");
    Delta_Phi_2SSMuon->GetXaxis()->SetTitle("#Delta #phi 2SSMuon");
    DeltaR_2SSMuon->GetXaxis()->SetTitle("#Delta R 2SSMuon");
    Delta_Phi_2SSOF->GetXaxis()->SetTitle("#Delta #phi 2SSOF");
    DeltaR_2SSOF->GetXaxis()->SetTitle("#Delta R 2SSOF");
    cleanjet_Mult->GetXaxis()->SetTitle("N clean Jets");
    
    Nb_CSVL_bJets_After_Cuts->GetXaxis()->SetTitle("N CSVL b jets");
    Nb_elecs->GetXaxis()->SetTitle("N electrons");
    Nb_muons->GetXaxis()->SetTitle("N muons");
    Nb_Jets->GetXaxis()->SetTitle("N jets");
    Nb_CSVL_jets->GetXaxis()->SetTitle("N CSVL jets");
    Nb_CSVM_jets->GetXaxis()->SetTitle("N CSVM jets");
    Nb_CSVT_jets->GetXaxis()->SetTitle("N CSVT jets");
    
    Pt_2ndleading_Jet->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_3rdleading_Jet->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_4thleading_Jet ->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_5thleading_Jet ->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_6thleading_Jet ->GetXaxis()->SetTitle("p_{T} (GeV)");
    Pt_7thleading_Jet ->GetXaxis()->SetTitle("p_{T} (GeV)");
    MET_histo ->GetXaxis()->SetTitle("MET (GeV)");
    Eta_jets ->GetXaxis()->SetTitle("#eta");
    Phi_jets ->GetXaxis()->SetTitle("#phi");
    sumet_isol_elec ->GetXaxis()->SetTitle("#Sigma E_{T}(e)");
    sumet_isol_muon ->GetXaxis()->SetTitle("#Sigma E_{T}(#mu)");
    sumpt_isol_elec ->GetXaxis()->SetTitle("#Sigma p_{T}(e)");
    sumpt_isol_muon ->GetXaxis()->SetTitle("#Sigma E_{T}(#mu)");
    comb_isol_elec ->GetXaxis()->SetTitle("Comb iso e");
    comb_isol_muon ->GetXaxis()->SetTitle("Comb iso #mu");
    
    Mass_Mu0_b->GetXaxis()->SetTitle(" mass (#mu_{0}) b");
    DeltaRmin_Mu0_b->GetXaxis()->SetTitle("#Delta #mu_{0} b");
    Mass_lep0_b->GetXaxis()->SetTitle(" mass (lep_{0}) b");
    DeltaRmin_Elec0_b->GetXaxis()->SetTitle("#Delta elec_{0} b");
    Elec1_pt_to_Ht_ratio ->GetXaxis()->SetTitle(" P_{t}(elec_{1}) / H_{T}");
    Mu1_pt_to_Ht_ratio ->GetXaxis()->SetTitle(" P_{t}(#mu_{1}) / H_{T}");
    lep1_pt_to_Ht_ratio ->GetXaxis()->SetTitle(" P_{t}(lep_{1}) / H_{T}");
    Ht_Jets->GetXaxis()->SetTitle("#Sigma E_{T}(jets)");

    
    SM_mLep0b_FCNC_3JetsLep1 ->GetXaxis()->SetTitle("mass SM Lep_{0} b)");
    SM_mLep0b_FCNC_3JetsLep1 ->GetYaxis()->SetTitle("mass FCNC(3Jets Lep_{1})");
    SM_mLep0b_FCNC_3JetsLep0 ->GetXaxis()->SetTitle("mass SM Lep_{0} b)");
    SM_mLep0b_FCNC_3JetsLep0 ->GetYaxis()->SetTitle("mass FCNC(3Jets Lep_{0})");
    SM_mLep1b_FCNC_3JetsLep1 ->GetXaxis()->SetTitle("mass SM Lep_{1} b)");
    SM_mLep1b_FCNC_3JetsLep1 ->GetYaxis()->SetTitle("mass FCNC(3Jets Lep_{1})");
    SM_mLep1b_FCNC_3JetsLep0 ->GetXaxis()->SetTitle("mass SM Lep_{1} b");
    SM_mLep1b_FCNC_3JetsLep0 ->GetYaxis()->SetTitle("mass FCNC(3Jets Lep_{0})");
    Ratio_FCNC_3JetsLep0_to_SM_mLep1b ->GetXaxis()->SetTitle("Ratio_FCNC_top(lep_{0})_to_SM_lb_(lep_{1})");
    Ratio_FCNC_3JetsLep1_to_SM_mLep0b ->GetXaxis()->SetTitle("Ratio_FCNC_top(lep_{1})_to_SM_lb_(lep_{0})");
    Pt_Lep0_vs_Lep1->GetXaxis()->SetTitle("p_{T} Lep_{0} (SM)");
    Pt_Lep0_vs_Lep1->GetYaxis()->SetTitle("p_{T} Lep_{1} (FCNC)");
    
    Mass_SM_bJet_lep0 ->GetXaxis()->SetTitle("SM_m(Lep_{0}_b)");
    Mass_SM_bJet_lep1 ->GetXaxis()->SetTitle("SM_m(Lep_{1}_b)");
    Mass_FCNC_top_Lep1 ->GetXaxis()->SetTitle(" mass FCNCtop Lep_{1}");
    Mass_FCNC_top_Lep0 ->GetXaxis()->SetTitle(" mass FCNCtop Lep_{0}");
    
    ////
    M_Wjets_FCNCTop_rightComb_Rec-> GetXaxis()->SetTitle(" mass FCNCtop jets_{W} Rec");
    M_Wjets_FCNCTop_rightComb_Gen-> GetXaxis()->SetTitle(" mass FCNCtop jets_{W} Gen");
    M_Wjets_FCNCTop_WrongComb_NoMC_Rec-> GetXaxis()->SetTitle(" mass FCNCtop jets_{W} wrong");
    Pt_SMLep0_rightComb_Rec->GetXaxis()->SetTitle("p_{T} SM-Lep_{0} Reco (GeV)");
    Pt_SMLep0_rightComb_Gen->GetXaxis()->SetTitle("p_{T} SM-Lep_{0} Gen (GeV)");
    Pt_SMLep1_rightComb_Rec->GetXaxis()->SetTitle("p_{T} SM-Lep_{1} Reco (GeV)");
    Pt_SMLep1_rightComb_Gen->GetXaxis()->SetTitle("p_{T} SM-Lep_{1} Gen (GeV)");
    Pt_leading_Lep0_WrongComb_Rec->GetXaxis()->SetTitle("p_{T} Lep_{0} wrong (GeV)");
    Pt_second_leading_Lep1_WrongComb_Rec->GetXaxis()->SetTitle("p_{T} Lep_{1} wrong (GeV)");
    Pt_FCNCLep0_rightComb_Rec->GetXaxis()->SetTitle("p_{T} FCNC-Lep_{0} Reco (GeV)");
    Pt_FCNCLep0_rightComb_Gen->GetXaxis()->SetTitle("p_{T} FCNC-Lep_{0} Gen (GeV)");
    Pt_FCNCLep1_rightComb_Rec->GetXaxis()->SetTitle("p_{T} FCNC-Lep_{1} Reco (GeV)");
    Pt_FCNCLep1_rightComb_Gen->GetXaxis()->SetTitle("p_{T} FCNC-Lep_{1} Reco (GeV)");
    Mass_W_Jets->GetXaxis()->SetTitle("Mass_W_Jets");
    
    Ht_Met_histo->GetXaxis()->SetTitle("H_{t} jets");
    Ht_Met_histo->GetYaxis()->SetTitle("Met E_{t}");
    
    Mass_Right_SM_lep0_FCNC_lep1_RecLevel->GetXaxis()->SetTitle("mass SMtop Lep_{0} Rec");
    Mass_Right_SM_lep0_FCNC_lep1_RecLevel->GetYaxis()->SetTitle("mass FCNCtop Lep_{1} Rec");
    
    Mass_Right_SM_lep0_FCNC_lep1_GenLevel->GetXaxis()->SetTitle("mass SMtop Lep_{0} Gen");
    Mass_Right_SM_lep0_FCNC_lep1_GenLevel->GetYaxis()->SetTitle("mass FCNCtop Lep_{1} Gen");
    
    Mass_Right_SM_lep1_FCNC_lep0_RecLevel->GetXaxis()->SetTitle("mass SMtop Lep_{1} Rec");
    Mass_Right_SM_lep1_FCNC_lep0_RecLevel->GetYaxis()->SetTitle("mass FCNCtop Lep_{0} Rec");
    
    Mass_Right_SM_lep1_FCNC_lep0_GenLevel->GetXaxis()->SetTitle("mass SMtop Lep_{1} Gen");
    Mass_Right_SM_lep1_FCNC_lep0_GenLevel->GetYaxis()->SetTitle("mass FCNCtop Lep_{0} Gen");
    
    Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel->GetXaxis()->SetTitle("mass SMtop Lep_{0} wrong");
    Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel->GetYaxis()->SetTitle("mass FCNCtop Lep_{1} wrong");
    
    Mass_Wrong_SM_lep1_FCNC_le0_RecLevel->GetXaxis()->SetTitle("mass SMtop Lep_{1} wrong");
    Mass_Wrong_SM_lep1_FCNC_le0_RecLevel->GetYaxis()->SetTitle("mass FCNCtop Lep_{0} wrong");
    
    Pt_SMLep0_to_FCNCLep1_rightComb_Rec->GetXaxis()->SetTitle("p_{T} Lep_{0} (SM) Rec");
    Pt_SMLep0_to_FCNCLep1_rightComb_Rec->GetYaxis()->SetTitle("p_{T} Lep_{1} (FCNC) Rec ");
    
    Pt_SMLep0_to_FCNCLep1_rightComb_Gen->GetXaxis()->SetTitle("p_{T} Lep_{0} (SM) Gen");
    Pt_SMLep0_to_FCNCLep1_rightComb_Gen->GetYaxis()->SetTitle("p_{T} Lep_{1} (FCNC) Gen");
    
    Pt_SMLep1_to_FCNCLep0_rightComb_Rec->GetXaxis()->SetTitle("p_{T} Lep_{1} (SM) Rec");
    Pt_SMLep1_to_FCNCLep0_rightComb_Rec->GetYaxis()->SetTitle("p_{T} Lep_{0} (FCNC) Rec ");
    Pt_SMLep1_to_FCNCLep0_rightComb_Gen->GetXaxis()->SetTitle("p_{T} Lep_{1} (SM) Gen");
    Pt_SMLep1_to_FCNCLep0_rightComb_Gen->GetYaxis()->SetTitle("p_{T} Lep_{1} (FCNC) Gen");
    
    Pt_SMLep0_to_FCNCLep1_WrongComb_Rec->GetXaxis()->SetTitle("p_{T} Lep_{0} (SM) Wrong");
    Pt_SMLep0_to_FCNCLep1_WrongComb_Rec->GetYaxis()->SetTitle("p_{T} Lep_{1} (FCNC) Wrong ");
    
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec->GetXaxis()->SetTitle("#Delta #phi SMtop-lep_{0} FCNCtop-lep_{1} Reco");
    DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen->GetXaxis()->SetTitle("#Delta #phi SMtop-lep_{0} FCNCtop-lep_{1} Gen");
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec->GetXaxis()->SetTitle("#Delta #phi SMtop-lep_{1} FCNCtop-lep_{0} Reco");
    DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen->GetXaxis()->SetTitle("#Delta #phi SMtop-lep_{1} FCNCtop-lep_{0} Gen");
    DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC->GetXaxis()->SetTitle("#Delta #phi SMtop-lep_{1} FCNCtop-lep_{0} Wrong");
    DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC->GetXaxis()->SetTitle("#Delta #phi SMtop-lep_{0} FCNCtop-lep_{1} Wrong");
    
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec->GetXaxis()->SetTitle("#Delta R SMtop-lep_{0} FCNCtop-lep_{1} Reco");
    DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen->GetXaxis()->SetTitle("#Delta R SMtop-lep_{0} FCNCtop-lep_{1} Gen");
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec->GetXaxis()->SetTitle("#Delta R SMtop-lep_{1} FCNCtop-lep_{0} Reco");
    DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen->GetXaxis()->SetTitle("#Delta R SMtop-lep_{1} FCNCtop-lep_{0} Gen");
    DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC->GetXaxis()->SetTitle("#Delta R SMtop-lep_{1} FCNCtop-lep_{0} Wrong");
    DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC->GetXaxis()->SetTitle("#Delta R SMtop-lep_{0} FCNCtop-lep_{1} Wrong");

    output->Write();
    
    cout << "END   Finalization" << endl;

}


// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------

bool FCNC_2SSL::Execute(SampleFormat& sample, const EventFormat& event)
{
    
    nevent++; // for the first line, needed for lumi reweighting
    cutFlow->Fill(0., weight);  //fill first bin for all events
    
    // only for safty
    if (event.rec()==0) return false;
    
    AnalysisHelper tool; //Initialize the AnalysisHelper, with many very interesting tools
    tool.Initialize(sample,event);
    
    //****************************************
    //************ lepton selection **********
    //****************************************
   	std::vector< const RecLeptonFormat *> selElecsColl;
   	std::vector< const RecLeptonFormat *> selMuonsColl;
   	std::vector<const RecLeptonFormat*> isol_leptons;
    //std::vector<const RecLeptonFormat*> fakeelectrons;
    //std::vector<const RecLeptonFormat*> isol_leptons_without_fake;
    std::vector<const RecLeptonFormat *> selElecsColl_without_fake;
    std::vector<int> Place_el;
    std::vector<int> Place_mu;
    
    
   	
    AnalysisHelper::ConeType cone = AnalysisHelper::CONE04; //Cone for lepton isolation
    double threshold = 0.2; // Isolation requirement. Use it as a default value. Needs to be optimized !!
    
    
    ////-------- selection of muons -------- ////
    
    for (unsigned int i=0;i<event.rec()->muons().size();i++)
   	{
        const RecLeptonFormat& mu = event.rec()->muons()[i];
        
        //Plot isolation variables as sanity check
        sumet_isol_muon->Fill(mu.isolCones()[static_cast<unsigned int>(cone)].sumET(),weight);
        sumpt_isol_muon->Fill(mu.isolCones()[static_cast<unsigned int>(cone)].sumPT(),weight);
        comb_isol_muon->Fill(tool.CombinedIsolationObservable(&mu,cone),weight);
        
        if(mu.pt() > 10 && fabs(mu.eta()) < 2.4)
        {
            if(tool.passCombinedIsolation(mu, threshold, cone))
            {
                selMuonsColl.push_back(&mu);
                isol_leptons.push_back(&mu);
                Place_mu.push_back(i);
                
            }
            
        }
    }

    ////// ------- selection of electron before fake -------- ///////
    
    for (unsigned int i=0;i<event.rec()->electrons().size();i++)
   	{
        const RecLeptonFormat& elec = event.rec()->electrons()[i];
        
        //Plot isolation variables as sanity check
        sumet_isol_elec->Fill(elec.isolCones()[static_cast<unsigned int>(cone)].sumET(),weight);
        sumpt_isol_elec->Fill(elec.isolCones()[static_cast<unsigned int>(cone)].sumPT(),weight);
        comb_isol_elec->Fill(tool.CombinedIsolationObservable(&elec,cone),weight);
        
        if(elec.pt() > 15 && fabs(elec.eta()) < 2.5)
        {
            if(tool.passCombinedIsolation(elec, threshold, cone))
            {
                
                selElecsColl_without_fake.push_back(&elec);
            }
        }
   	}
    
    
    if (debug) cout << "the number of electrons in selElecsColl_without_fake vector  Before fake =  " << selElecsColl_without_fake.size() << endl;

    
    //****************************************
    //************* jet selection ************
    //****************************************
    std::vector< RecJetFormat > selJetsColl;
    std::vector< RecJetFormat > selLBJetsColl;
    std::vector< RecJetFormat > selMBJetsColl;
    std::vector< RecJetFormat > selTBJetsColl;
    std::vector< RecJetFormat > selNonLBJetsColl;
    std::vector< RecJetFormat > selNonMBJetsColl;
    std::vector< RecJetFormat > selNonTBJetsColl;
    std::vector< RecJetFormat > NonLeadingCSVLBJetsColl;
    std::vector< int > Place_jet;
    std::vector< int > Place_CSVLBjet;
    std::vector< int > Place_NonLeadingCSVLB;
    //std::vector< const RecJetFormat*> Cleaned_jets_1st;
    
    
    double DeltaRmax = 0.4; // maximum DR between a jet and a matching lepton
    double PTmin = 2; // possibility to cut on the jet PT
    
    //std::vector<const RecJetFormat*> cleaned_jets = tool.JetCleaning(event,isol_leptons,DeltaRmax,PTmin); // to avoid pushing non-clean jets into selElecColl
    std::vector<const RecJetFormat*> Cleaned_jets_1st = tool.JetCleaning(event,isol_leptons,DeltaRmax,PTmin); // to avoid pushing non-clean jets into selElecColl
    
//    for (unsigned int i =0 ; i < event.rec()->jets().size(); i++ )
//    {
//       const RecJetFormat& jet = event.rec()->jets()[i];
//        unCleaned_jets.push_back(&jet);
//    }
//    
//    std::vector<const RecJetFormat*> cleaned_jets = tool.JetCleaning(unCleaned_jets,isol_leptons,DeltaRmax,PTmin); // to avoid pushing non-clean jets into selElecColl
    
    
    //************ fakeElectron implementation **************//
    float nb_of_jets_before_fake = Cleaned_jets_1st.size();
    tool.FakeElectrons(Cleaned_jets_1st,selElecsColl_without_fake ,15,2.5 , true);
    float nb_of_jets_after_fake = Cleaned_jets_1st.size();
    
    if (debug) cout << "the number of electrons in selElecsColl_without_fake vector = " << selElecsColl_without_fake.size() << endl;
//    for (unsigned int i =0 ; i < selElecsColl_without_fake.size(); i++) {
//        cout << " Pt of the electron " << i << "  After fake is =  " << selElecsColl_without_fake[i]->pt()<< endl;
//    }
    
    /// selecting electrons after fakeelectrons and jet cleaning
    
    for (unsigned int i=0;i<selElecsColl_without_fake.size();i++)
    {
        const RecLeptonFormat* elec = selElecsColl_without_fake[i];
        selElecsColl.push_back(elec);
        Place_el.push_back(i);
        isol_leptons.push_back(elec);
        
    }

    if (debug) cout << "the number of electrons in selElecsColl vector = " << selElecsColl.size() << endl;
    nb_of_fakeElectron += selElecsColl.size() - selElecsColl_without_fake.size();
    nb_of_removed_jets += nb_of_jets_before_fake - nb_of_jets_after_fake;
    
//    for (unsigned int i =0  ; i < selElecsColl.size(); i++) {
//        cout << " Pt of the electron " << i << "  in selElecsColl vector =  " << selElecsColl[i]->pt()<< endl;
//    }


    
    ///// ----------- selecting jets ----------- /////
    
    //cleaned_jets = tool.JetCleaning(event,isol_leptons,DeltaRmax,PTmin); /// clean jets again
    
    std::vector<const RecJetFormat*> cleaned_jets = tool.JetCleaning(Cleaned_jets_1st,isol_leptons,DeltaRmax,PTmin); // clean jets again by using 2nd method that pass jet_collection to the function

    cleanjet_Mult->Fill(cleaned_jets.size(),weight);
    
    for (unsigned int i=0;i<cleaned_jets.size();i++)
    {
        //if (debug)cout << "in selecting jets " << endl;
        
        const RecJetFormat& jet = *cleaned_jets[i];
        
        if(jet.pt()> 20 && fabs(jet.eta()) < 2.4 && (1./jet.EEoverHE()) > 0.15)
        //if(jet.pt()> 20 && fabs(jet.eta()) < 2.4 && jet.EEoverHE() > 0.3)
        {
            selJetsColl.push_back(jet);
            Place_jet.push_back(i);
            
            if (tool.isCSVL(&jet))
            {
                selLBJetsColl.push_back(jet);
                Place_CSVLBjet.push_back(i);
            } else
            {
                selNonLBJetsColl.push_back(jet);
            }
            
            if(tool.isCSVM(&jet))selMBJetsColl.push_back(jet);
            else selNonMBJetsColl.push_back(jet);
            
            if(tool.isCSVT(&jet)) selTBJetsColl.push_back(jet);
            else selNonTBJetsColl.push_back(jet);
            
        }
    }
    
    
    /////  **** selecting non-leading_b Jets **** /////
    
    
    for (unsigned int ijet = 0; ijet < selJetsColl.size() ; ijet++)
    {
        if (selLBJetsColl.size() != 0)
        {
            if (fabs(selJetsColl[ijet].pt() - selLBJetsColl[0].pt()) > .0000000001)
            {
                NonLeadingCSVLBJetsColl.push_back(selJetsColl[ijet]);
                Place_NonLeadingCSVLB.push_back(ijet);
            }
            
        }
    }
    
    
    /////  **** selecting neutrinos **** /////
    TLorentzVector Met;
    Met.SetPxPyPzE(event.rec()->MET().px(),event.rec()->MET().py(),event.rec()->MET().pz(),event.rec()->MET().e());

    //****************************************
    //****** pre-event-selection histos****
    //****************************************
    Nb_elecs->Fill(selElecsColl.size(),weight);
    Nb_muons->Fill(selMuonsColl.size(),weight);
    Nb_Jets->Fill(selJetsColl.size(),weight);
    Nb_CSVL_jets->Fill(selLBJetsColl.size(),weight);
    Nb_CSVM_jets->Fill(selMBJetsColl.size(),weight);
    Nb_CSVT_jets->Fill(selTBJetsColl.size(),weight);

    
    //****************************************
    //************ events selection **********
    //****************************************
    //-- 2SSL = 2 SameSign Leptons (Zmass Veto), >= 4Jets, >=1b-tagged Jets
    
    bool Elec = false;
    bool Mu = false;
    bool EMu = false;
    bool Mu_Elec = false;
    bool Elec_Mu = false;
    bool is_WJet = false;
    bool is_BJet = false;
    bool is_CJet = false;
    bool is_Higgs = false;
    bool Right_SMlep0 = false;
    bool Right_SMlep1 = false;
    bool Right_FCNClep0 = false;
    bool Right_FCNClep1 = false;
    bool Wrong_lep0 = false;
    bool Wrong_lep1 = false;
    bool Right_CSVLB = false;
    bool Wrong_CSVLB = false;
    bool Wrong_Cjets = false;
    bool Right_Cjets = false;
    bool Right_FCNCtop_lep0 = false;
    bool Right_FCNCtop_lep1 = false;
    bool  Wrong_FCNCtop_lep0 = false;
    bool  Wrong_FCNCtop_lep1 = false;
    bool Right_WJets = false;
    bool Wrong_WJets = false;
    bool Right_SMtop_lep0 = false;
    bool Right_SMtop_lep1 = false;
    bool Wrong_SMtop_lep0 = false;
    bool Wrong_SMtop_lep1 = false;
    bool found_mother_mu1 = false;

    
    
    ///// used variables
    float mll = -999;
    float Zmass = 91.1876; // ref --> pdg
    //float Delta_R;
    float sum_Jets_Pt = 0.;
    float Ht_all_Jets = -999;
    float lep1_pt_to_Ht = -999;
    float m_lb = 999.9;
    float m_jj = -999;
    float m_JJ_Pair = -999;
    float Wmass = 80.385; //ref -> pdg
    
    float minimum_mass_diff_from_W = 999.;
    float m_W_JJ_Pair;
    float mass_diff_from_W;
    //float m_3jets;
    float m_3jets_Lep0 = 0.;
    float m_3jets_Lep1 = 0.;
    //float M_FCNC3Jets;
    float M_FCNC3Jets_Lep0= 0.;
    float M_FCNC3Jets_Lep1 = 0.;
    float M_bJet_Lep0 = 0.;
    float M_bJet_Lep1 = 0.;
    vector<int> electroncharge;
    bool found_mother = false;
    bool found_mother1 = false;
    int pdgid_mother = -10000;
    unsigned int loop_counter=0;
    bool found_mother_emu0 = false;
    bool found_mother_emu1 = false;
    bool found_mother_elec0 = false;
    bool found_mother_elec1 = false;
    bool found_mother_mu0 = false;
    float sumLep_Pt = 0.;
    float St_lep_jets = 0.;
    
    
    
    // Leptons for each channel
    TLorentzVector Elec_electron0;
    TLorentzVector Elec_electron1;
    TLorentzVector Mu_muon0;
    TLorentzVector Mu_muon1;
    TLorentzVector EMu_lepton0;
    TLorentzVector EMu_lepton1;
    TLorentzVector Leading_lepton;
    TLorentzVector second_Leading_lepton;
    
    ///// TLorentzVector ////
    TLorentzVector Leading_CSVLB_Jet;
    TLorentzVector right_Rec_Leading_CSVLB;
    TLorentzVector right_Gen_Leading_CSVLB;
    TLorentzVector Wrong_Rec_Leading_CSVLB;
    TLorentzVector Leading_Gen_Jet_With_MC;
    TLorentzVector Leading_Rec_Jet_With_MC;
    
    TLorentzVector Rec_Leading_Lepton0_from_FCNCtop;
    TLorentzVector Gen_Leading_Lepton0_from_FCNCtop;
    TLorentzVector Rec_second_Leading_Lepton1_from_FCNCtop;
    TLorentzVector Gen_second_Leading_Lepton1_from_FCNCtop;
    
    TLorentzVector Rec_Leading_Lepton0_SMtop_true_combination;
    TLorentzVector Gen_Leading_Lepton0_SMtop_true_combination;
    TLorentzVector Rec_second_Leading_Lepton1_SMtop_true_combination;
    TLorentzVector Gen_second_Leading_Lepton1_SMtop_true_combination;
    TLorentzVector Rec_second_Leading_Lepton1_from_Higgs;
    TLorentzVector Gen_second_Leading_Lepton1_from_Higgs;
    TLorentzVector Rec_Leading_Lepton0_from_Higgs;
    TLorentzVector Gen_Leading_Lepton0_from_Higgs;
    TLorentzVector Wrong_Rec_Leading_Lepton;
    TLorentzVector Wrong_Rec_2nd_Leading_Lepton;
    
    TLorentzVector FCNC_C_jet;
    TLorentzVector right_Gen_CJet;
    TLorentzVector right_Rec_CJet;
    TLorentzVector Wrong_Rec_CJet;
    TLorentzVector Rec_CJet_With_MC;
    TLorentzVector Gen_CJet_With_MC;
    TLorentzVector W_1st_Jet;
    TLorentzVector W_2nd_Jet;
    TLorentzVector Wrong_Rec_1st_JetCandidate_W_FCNCtop;
    TLorentzVector Wrong_Rec_2nd_JetCandidate_W_FCNCtop;
    
    
    TLorentzVector right_Gen_1st_JetCandidate_H_FCNCtop;
    TLorentzVector right_Gen_2nd_JetCandidate_H_FCNCtop;
    
//    TLorentzVector right_Rec_1st_JetCandidate_H_FCNCtop;
//    TLorentzVector right_Rec_2nd_JetCandidate_H_FCNCtop;
//    TLorentzVector right_Gen_1st_JetCandidate_H_FCNCtop;
//    TLorentzVector right_Gen_2nd_JetCandidate_H_FCNCtop;
    
    TLorentzVector right_Rec_1st_JetCandidate_H_FCNCtop;
    TLorentzVector right_Rec_2nd_JetCandidate_H_FCNCtop;
    float Mass_Rec_FCNCtop_lep0_rightCombination = -999 ;
    float Mass_Gen_FCNCtop_lep0_rightCombination = -999;
    float Mass_Rec_FCNCtop_lep1_rightCombination = -999;
    float Mass_Gen_FCNCtop_lep1_rightCombination = -999;
    float Mass_Rec_FCNCtop_lep0_NoGenMatching = -999;
    float Mass_Rec_FCNCtop_lep1_NoGenMatching = -999;
    

    float Mass_FCNC_WJets_with_right_combination_RecLevel = -999;
    float Mass_FCNC_top_with_right_combination_RecLevel = -999;
    float Mass_FCNC_WJets_with_right_combination_GenLevel = -999;
    float Mass_FCNC_top_with_right_combination_GenLevel = -999;
    float Mass_FCNC_WJets_with_Wrong_combination_RecLevel = -999;
    float Mass_FCNC_top_with_Wrong_combination_lep0_RecLevel = -999;
    float Mass_FCNC_top_with_Wrong_combination_lep1_RecLevel = -999;
    
    float Mass_FCNC_top_with_right_combination_lep0_RecLevel = -999;
    float Mass_FCNC_top_with_right_combination_lep0_GenLevel= -999;
    float Mass_FCNC_top_with_right_combination_lep1_RecLevel = -999;
    float Mass_FCNC_top_with_right_combination_lep1_GenLevel = -999;
    
    float Mass_Rec_WJets_FCNC_top_rightCombination = -999;
    float Mass_Gen_WJets_FCNC_top_rightCombination = -999;
    float Mass_Rec_WJets_FCNC_top_NoGenMatching = -999;
    
    float Mass_Rec_SMtop_lep0_rightCombination = -999;
    float Mass_Gen_SMtop_lep0_rightCombination = -999;
    float Mass_Rec_SMtop_lep1_rightCombination = -999;
    float Mass_Gen_SMtop_lep1_rightCombination = -999;
    float Mass_Rec_SMtop_lep0_NoGenMatching = -999;
    float Mass_Rec_SMtop_lep1_NoGenMatching = -999;
    
    
    TLorentzVector SMtop_lep0_rightComb_Rec;
    TLorentzVector SMtop_lep0_rightComb_Gen;
    TLorentzVector SMtop_lep1_rightComb_Rec;
    TLorentzVector SMtop_lep1_rightComb_Gen;
    TLorentzVector SMtop_lep0_WrongComb_Rec;
    TLorentzVector SMtop_lep1_WrongComb_Rec;
    
    TLorentzVector FCNCtop_lep0_rightComb_Rec;
    TLorentzVector FCNCtop_lep0_rightComb_Gen;
    TLorentzVector FCNCtop_lep1_rightComb_Rec;
    TLorentzVector FCNCtop_lep1_rightComb_Gen;
    TLorentzVector FCNCtop_lep0_WrongComb_Rec;
    TLorentzVector FCNCtop_lep1_WrongComb_Rec;
    
  ////// **** start cuts *****/////////
    
    if((selElecsColl.size() + selMuonsColl.size()) == 2)  //ask for dilepton
    {
        if (debug) cout << "<-------------- Now the event number is  "<< nevent << "  ------------------->"<<endl;
        cutFlow->Fill(1., weight); // fill the second bin for the events with 2 selected leptons
        if (debug) cout << "the size of selElecsColl  =  " << selElecsColl.size() << endl;
        if (debug) cout << "the size of selMuonsColl  =  " << selMuonsColl.size() << endl;
        
        ///// ****** Charge misidetification ******////////
        //nb_Elecs_before_misid +=1;
        for(unsigned int j=0; j<selElecsColl.size(); j++)
        {
            electroncharge.push_back(selElecsColl[j]->charge());
            if (debug) cout << "j =  " << j << "and the electron charge = " << selElecsColl[j]->charge() << endl;
            
            //now applying charge-misid to electrons: 0.3% in endcap region, 0.03% in barrel region
            //creates a randm number between 0-1.
            double rdmnr = gRandom->Uniform();
            // to save some CPU time only check when the random number is below 0.3%....
            if(rdmnr<=0.003)
            {
                if(fabs(selElecsColl[j]->eta())<1.479)
                {
                    if(rdmnr<0.0003)
                    {
                        electroncharge[j] = electroncharge[j] * -1;
                        if (debug)cout<<"charge flipped!"<<endl;
                    }
                }
                else if(fabs(selElecsColl[j]->eta())<2.5)
                {
                    if(rdmnr<0.003)
                    {
                        electroncharge[j] = electroncharge[j] * -1;
                        if (debug)cout<<"charge flipped!"<<endl;
                    }
                }
            }
        }
        ///*** electrons channel ***//
        if(selElecsColl.size() == 2) // selecting 2 same sign electron
        {
            if (debug) cout << "At di-electron channel " << endl;
            if (electroncharge[0]== electroncharge[1] && selElecsColl[0]->pt() >= 26. && selElecsColl[1]->pt()>=15.)
            {
                if (debug) cout << "fill in the diElec" << endl;
                Elec_electron0.SetPxPyPzE(selElecsColl[0]->px(),selElecsColl[0]->py(),selElecsColl[0]->pz(),selElecsColl[0]->e());
                Elec_electron1.SetPxPyPzE(selElecsColl[1]->px(),selElecsColl[1]->py(),selElecsColl[1]->pz(),selElecsColl[1]->e());
                mll = (Elec_electron0+Elec_electron1).M();
                
                if (debug) cout << " mll of 2 electrons is =  " << mll << endl;
                if (fabs(Zmass-mll) > 15 && mll > 12 ) Elec = true;
                if (debug)cout << " Elec =  " << Elec << endl;
            }
        }
        
        ///*** muons channel ***//
        if(selMuonsColl.size() == 2)
        {
            if (selMuonsColl[0]->charge() == selMuonsColl[1]->charge() && selMuonsColl[0]->pt()>=20. && selMuonsColl[1]->pt()>=11.)
            {
                if (debug) cout << "At di-Muon channel " << endl;
                Mu_muon0.SetPxPyPzE(selMuonsColl[0]->px(),selMuonsColl[0]->py(),selMuonsColl[0]->pz(),selMuonsColl[0]->e());
                Mu_muon1.SetPxPyPzE(selMuonsColl[1]->px(),selMuonsColl[1]->py(),selMuonsColl[1]->pz(),selMuonsColl[1]->e());
                mll = (Mu_muon0 + Mu_muon1).M();
                if (debug) cout << " mll of 2 muons is =  " << mll << endl;
                if (fabs(Zmass - mll)> 15 && mll > 12) Mu= true;
                if (debug)cout << " Mu =  " << Mu << endl;
            }
        }
        
        ///*** Electron-muon  channel ***//
        if(selElecsColl.size() == 1 && selMuonsColl.size() == 1 )
        {
            if (debug) cout << "At EMu Channel " << endl;
            if (selMuonsColl[0]->charge() == electroncharge[0])
            {
                if (debug) cout << "fill in 2SSEMu" << endl;
                if (selMuonsColl[0]->pt() > selElecsColl[0]->pt() && selMuonsColl[0]->pt()>=20. && selElecsColl[0]->pt()>=15.)
                {
                    if (debug) cout << "fill in Mu_Elec channel" << endl;
                    EMu_lepton0.SetPxPyPzE(selMuonsColl[0]->px(),selMuonsColl[0]->py(),selMuonsColl[0]->pz(),selMuonsColl[0]->e());
                    EMu_lepton1.SetPxPyPzE(selElecsColl[0]->px(),selElecsColl[0]->py(),selElecsColl[0]->pz(),selElecsColl[0]->e());
                    
                        EMu = true;
                        Mu_Elec = true;
                }
                if (selElecsColl[0]->pt() > selMuonsColl[0]->pt() && selElecsColl[0]->pt()>=26. && selMuonsColl[0]->pt()>=11.)
                {
                    if (debug) cout << "fill in Elec_Mu channel" << endl;
                    EMu_lepton0.SetPxPyPzE(selElecsColl[0]->px(),selElecsColl[0]->py(),selElecsColl[0]->pz(),selElecsColl[0]->e());
                    EMu_lepton1.SetPxPyPzE(selMuonsColl[0]->px(),selMuonsColl[0]->py(),selMuonsColl[0]->pz(),selMuonsColl[0]->e());
                    
                    EMu = true;
                    Elec_Mu = true;
                    
                }
            }
        }
        
        if (Elec || Mu || EMu)
        {
            if (debug) cout << "in Elec || Mu || EMu " << endl;
            cutFlow->Fill(2.,weight); // fill the 3rd bin for the events with 2 selected Same-Sign leptons
            
            nb_events_after_2SSL+=1;
            
            // jet-correlated variables
            for(unsigned int iJet = 0; iJet < selJetsColl.size(); iJet++)
            {
                Eta_jets->Fill(selJetsColl[iJet].eta(),weight);
                Phi_jets->Fill(selJetsColl[iJet].phi(),weight);
            }
            Nb_Jets_after_2SSLep->Fill(selJetsColl.size());
            if (selJetsColl.size() >= 4)
            {
                if (debug) cout << "after selecting >= 4 jets " << endl;
                //cutFlow->Fill(3.,weight);
                
                if (selJetsColl[0].pt()>=50. && selJetsColl[1].pt()>=30. && selJetsColl[2].pt()>=20. && selJetsColl[3].pt()>=20. )
                {
                    if (debug) cout << "after selecting >= 4 jets and jet Pt cuts " << endl;
                    cutFlow->Fill(3.,weight);
                    nb_events_after_2SSL_4Jets+=1;
                    if (selLBJetsColl.size() >= 1)
                    {
                        if (debug) cout << "after selecting B jets  " << endl;
                        Leading_CSVLB_Jet.SetPxPyPzE(selLBJetsColl[0].px(),selLBJetsColl[0].py(),selLBJetsColl[0].pz(),selLBJetsColl[0].e());
                        cutFlow->Fill(4.,weight);// fill the 4th bin for the events with selected 2SSL + >= 4Jets + >= 1 CSVL b-tagged Jets
                        nb_events_after_2SSL_4Jets_1CSVLB+=1;
                        Nb_CSVL_bJets_After_Cuts->Fill(selLBJetsColl.size(),weight);
                        
                        MET_histo->Fill(Met.Et(),weight);
                        
                        for (unsigned int ijet = 0 ; ijet < selJetsColl.size(); ijet++)
                        {
                            sum_Jets_Pt += selJetsColl[ijet].pt();
                        }
                        
                        Ht_all_Jets = sum_Jets_Pt;
                        Ht_Jets->Fill(Ht_all_Jets, weight);
                        Ht_Met_histo->Fill(Ht_all_Jets,Met.Et(),weight);
                        
                        

                        
//                        if (selLBJetsColl.size()>= 1) Pt_leading_CSVLBJet->Fill(selLBJetsColl[0].pt(),weight);
//                        if (selLBJetsColl.size()>= 2) Pt_2nd_leading_CSVLBJet->Fill(selLBJetsColl[1].pt(),weight);
//                        if (selLBJetsColl.size()>= 3) Pt_3rd_leading_CSVLBJet->Fill(selLBJetsColl[2].pt(),weight);
                        
                       ////// --- checking the MC particle for Bjet ----///////
                        nb_events_AllCuts_without_CHeckMC+=1;
                        const RecJetFormat& BJET = event.rec()->jets()[Place_CSVLBjet[0]];
                        const MCParticleFormat* MC_Bjet = tool.partonMatching(&BJET);
                        
                        if(debug)cout << "the size of selLBJetsColl is    " << selLBJetsColl.size() << endl;
                        if(debug)cout << "the size of Place_CSVLBjet[0] is    " << Place_CSVLBjet.size() << endl;
                        
                        if (MC_Bjet != 0)
                        {
                            if(debug)cout << "after checking MC particle  " <<  endl;
                            if (fabs(MC_Bjet->pdgid()) == 5 && fabs(tool.motherID(MC_Bjet)) == 6)
                            {
                                if(debug)cout << "MC_Bjet->pdgid() =    " << fabs(MC_Bjet->pdgid()) << "   and fabs(tool.motherID(MC_Bjet)) = " << fabs(tool.motherID(MC_Bjet)) << endl;
                                right_Rec_Leading_CSVLB.SetPxPyPzE(BJET.px(),BJET.py(),BJET.pz(),BJET.e());
                                right_Gen_Leading_CSVLB.SetPxPyPzE(MC_Bjet->px(),MC_Bjet->py(),MC_Bjet->pz(),MC_Bjet->e());
                                nb_events_AllCuts_MC_Right_CSVLB+=1;
                                Right_CSVLB = true;
                            } else {
                                Leading_Rec_Jet_With_MC.SetPxPyPzE(BJET.px(),BJET.py(),BJET.pz(),BJET.e());
                                Leading_Gen_Jet_With_MC.SetPxPyPzE(MC_Bjet->px(),MC_Bjet->py(),MC_Bjet->pz(),MC_Bjet->e());
                                nb_events_AllCuts_MC_CSVLB+=1;
                            }
                        } else
                        {
                            Wrong_Rec_Leading_CSVLB.SetPxPyPzE(BJET.px(),BJET.py(),BJET.pz(),BJET.e());
                            nb_events_AllCuts_MC_Wrong_CSVLB+=1;
                            Wrong_CSVLB = true;
                        }
                        
                    
                        
                      ////-----------------------------------------------//
                        

                        if (Elec)
                        {
                            if (debug)cout << " at if (Elec) " << endl;
                            Leading_lepton.SetPxPyPzE(Elec_electron0.Px(),Elec_electron0.Py(),Elec_electron0.Pz(),Elec_electron0.E());
                            second_Leading_lepton.SetPxPyPzE(Elec_electron1.Px(),Elec_electron1.Py(),Elec_electron1.Pz(),Elec_electron1.E());
                            Pt_leadingElec_2SSSF->Fill(Elec_electron0.Pt(),weight);
                            Pt_2ndleadingElec_2SSSF->Fill(Elec_electron1.Pt(),weight);
                            Eta_leadingElec_2SSSF->Fill(Elec_electron0.Eta(),weight);
                            Eta_2ndleadingElec_2SSSF->Fill(Elec_electron1.Eta(),weight);
                            Phi_leadingElec_2SSSF->Fill(Elec_electron0.Phi(),weight);
                            Phi_2ndleadingElec_2SSSF->Fill(Elec_electron1.Phi(),weight);
                            Delta_Phi_2SSElec->Fill(Elec_electron0.DeltaPhi(Elec_electron1),weight);
                            DeltaR_2SSElec->Fill(Elec_electron0.DeltaR(Elec_electron1),weight);
                            lep1_pt_to_Ht = Elec_electron1.Pt()/Ht_all_Jets;
                            Elec1_pt_to_Ht_ratio ->Fill(lep1_pt_to_Ht, weight);
                            m_lb = (Elec_electron0 + Leading_CSVLB_Jet).M();
                            DeltaRmin_Elec0_b->Fill(Elec_electron0.DeltaR(Leading_CSVLB_Jet),weight);
                            Mass_Elec0_b->Fill(m_lb, weight);

                            ///// ----- checking MC particles for SSdiElectrons ---------///
                            if (debug)cout << " the size of Place_el is =   " << Place_el.size() << endl;
                            const RecLeptonFormat& Elec_0 = event.rec()->electrons()[Place_el[0]];
                            const MCParticleFormat* MC_Elec0 = Elec_0.mc();
                            const RecLeptonFormat& Elec_1 = event.rec()->electrons()[Place_el[1]];
                            const MCParticleFormat* MC_Elec1 = Elec_1.mc();
                            
                            
                            if (MC_Elec0 != 0 && MC_Elec1 !=0)
                            {
                                if (fabs(MC_Elec0->pdgid()) == 11 && fabs(MC_Elec1->pdgid()) == 11)
                                {
                                    const MCParticleFormat* myPartelec0 = MC_Elec0;
                                    
                                    while (!found_mother_elec0)
                                    {
                                        loop_counter++;
                                        if (loop_counter>100)
                                        {
                                            cout << "infinite loop " << endl;
                                            break;
                                        }
                                        if(myPartelec0->mother1()->pdgid() == myPartelec0->pdgid())
                                        {
                                            const std::vector<MCParticleFormat*> motherdaughters = myPartelec0->mother1()->daughters();
//                                            for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                            {
//                                                cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                            }
                                        }
                                        if(myPartelec0->pdgid() != myPartelec0->mother1()->pdgid())
                                        {
                                            pdgid_mother = myPartelec0->mother1()->pdgid();
                                            
                                            found_mother_elec0 = true;
                                        }else
                                        {
                                            myPartelec0 = myPartelec0->mother1();
                                        }
                                    }

                                    if (found_mother_elec0)
                                    {
                                        const MCParticleFormat* mother_of_MC_Elec0 =myPartelec0->mother1();
                                        
                                        if (fabs(mother_of_MC_Elec0->pdgid())== 24)
                                        {
                                            
                                            if (fabs(tool.motherID(mother_of_MC_Elec0)) == 6)
                                            {
                                                
                                                const MCParticleFormat* MC_top = mother_of_MC_Elec0->mother1();
                                                const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                
                                                if (debug)cout << "size daughters of MCtop for lepton0 " << daughters.size() << endl;
                                                
                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                {
                                                    if (debug)cout << "in daughter loop" << endl;
                                                    const MCParticleFormat* daughter = daughters[iDaughter];
                                                    int pdgId = daughter->pdgid();
                                                    if (debug)cout << pdgId << endl;
                                                    if (pdgId == 4) {is_CJet = true;}
                                                    if (pdgId == 5) {is_BJet = true;}
                                                    if (pdgId == 24) {is_WJet = true;}
                                                    if (pdgId == 25) {is_Higgs = true;}
                                                    if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                }
                                                if (is_CJet && !is_BJet)
                                                {
                                                    Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(Elec_0.px(),Elec_0.py(),Elec_0.pz(),Elec_0.e());
                                                    Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_Elec0->px(),MC_Elec0->py(),MC_Elec0->pz(),MC_Elec0->e());
                                                    nb_events_after_lep0_from_FCNCtop+=1;
                                                    Right_FCNClep0 = true;
                                                }
                                                if (is_BJet && !is_CJet)
                                                {
                                                    Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(Elec_0.px(),Elec_0.py(),Elec_0.pz(),Elec_0.e());
                                                    Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_Elec0->px(),MC_Elec0->py(),MC_Elec0->pz(),MC_Elec0->e());
                                                    nb_events_after_lep0_from_SMtop+=1;
                                                    Right_SMlep0 = true;
                                                }
                                                
                                            }
                                            if (fabs(tool.motherID(mother_of_MC_Elec0)) == 25)
                                            {
                                                Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(Elec_0.px(),Elec_0.py(),Elec_0.pz(),Elec_0.e());
                                                Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_Elec0->px(),MC_Elec0->py(),MC_Elec0->pz(),MC_Elec0->e());
                                                nb_events_after_lep0_from_FCNCtop+=1;
                                                Right_FCNClep0 = true;
                                            }
                                            
                                        }
                                        if (fabs(mother_of_MC_Elec0->pdgid())== 6)
                                        {
                                            const MCParticleFormat* MC_top = mother_of_MC_Elec0->mother1();
                                            const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                            
                                            if (debug)cout << "size daughters " << daughters.size() << endl;
                                            
                                            for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                            {
                                                if (debug)cout << "in daughter loop" << endl;
                                                const MCParticleFormat* daughter = daughters[iDaughter];
                                                int pdgId = daughter->pdgid();
                                                if (debug)cout << pdgId << endl;
                                                if (pdgId == 4) {is_CJet = true;}
                                                if (pdgId == 5) {is_BJet = true;}
                                                if (pdgId == 24) {is_WJet = true;}
                                                if (pdgId == 25) {is_Higgs = true;}
                                                if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                            }
                                            if (is_CJet && !is_BJet)
                                            {
                                                Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(Elec_0.px(),Elec_0.py(),Elec_0.pz(),Elec_0.e());
                                                Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_Elec0->px(),MC_Elec0->py(),MC_Elec0->pz(),MC_Elec0->e());
                                                nb_events_after_lep0_from_FCNCtop+=1;
                                                Right_FCNClep0 = true;
                                            }
                                            if (is_BJet && !is_CJet)
                                            {
                                                Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(Elec_0.px(),Elec_0.py(),Elec_0.pz(),Elec_0.e());
                                                Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_Elec0->px(),MC_Elec0->py(),MC_Elec0->pz(),MC_Elec0->e());
                                                nb_events_after_lep0_from_SMtop+=1;
                                                Right_SMlep0 = true;
                                            }
                                            
                                        }

                                    }
                                    
                                    ///***** for second leading lepton
                                    
                                    const MCParticleFormat* myPartelec1 = MC_Elec1;
                                    //bool found_mother_elec1 = false;
                                    while (!found_mother_elec1)
                                    {
                                        loop_counter++;
                                        if (loop_counter>100)
                                        {
                                            cout << "infinite loop " << endl;
                                            break;
                                        }
                                        if(myPartelec1->mother1()->pdgid() == myPartelec1->pdgid())
                                        {
                                            const std::vector<MCParticleFormat*> motherdaughters = myPartelec1->mother1()->daughters();
//                                            for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                            {
//                                                cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                            }
                                        }
                                        if( myPartelec1->pdgid() != myPartelec1->mother1()->pdgid() )
                                        {
                                            pdgid_mother = myPartelec1->mother1()->pdgid();
                                            
                                            found_mother_elec1 = true;
                                        }else
                                        {
                                            myPartelec1 = myPartelec1->mother1();
                                        }
                                    }

                                    if (found_mother_elec1)
                                    {
                                        const MCParticleFormat* mother_of_MC_Elec1 = myPartelec1->mother1();
                                        if (fabs(mother_of_MC_Elec1->pdgid())== 24)
                                        {
                                            
                                            if (fabs(tool.motherID(mother_of_MC_Elec1)) == 6)
                                            {
                                                
                                                const MCParticleFormat* MC_top = mother_of_MC_Elec1->mother1();
                                                const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                
                                                if (debug)cout << "size daughters " << daughters.size() << endl;
                                                
                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                {
                                                    if (debug) cout << "in daughter loop" << endl;
                                                    const MCParticleFormat* daughter = daughters[iDaughter];
                                                    int pdgId = daughter->pdgid();
                                                    if (debug)cout << pdgId << endl;
                                                    if (pdgId == 4) {is_CJet = true;}
                                                    if (pdgId == 5) {is_BJet = true;}
                                                    if (pdgId == 24) {is_WJet = true;}
                                                    if (pdgId == 25) {is_Higgs = true;}
                                                    if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                }
                                                if (is_CJet && !is_BJet)
                                                {
                                                    Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(Elec_1.px(),Elec_1.py(),Elec_1.pz(),Elec_1.e());
                                                    Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_Elec1->px(),MC_Elec1->py(),MC_Elec1->pz(),MC_Elec1->e());
                                                    nb_events_after_lep1_from_FCNCtop+=1;
                                                    Right_FCNClep1 = true;
                                                }
                                                if (is_BJet && !is_CJet)
                                                {
                                                    Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(Elec_1.px(),Elec_1.py(),Elec_1.pz(),Elec_1.e());
                                                    Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_Elec1->px(),MC_Elec1->py(),MC_Elec1->pz(),MC_Elec1->e());
                                                    Right_SMlep1 = true;
                                                }
                                                
                                            }
                                            if (fabs(tool.motherID(mother_of_MC_Elec1)) == 25)
                                            {
                                                Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(Elec_1.px(),Elec_1.py(),Elec_1.pz(),Elec_1.e());
                                                Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_Elec1->px(),MC_Elec1->py(),MC_Elec1->pz(),MC_Elec1->e());
                                                nb_events_after_lep1_from_FCNCtop+=1;
                                                Right_FCNClep1 = true;
                                            }
                                            
                                        }
                                        if (fabs(mother_of_MC_Elec1->pdgid())== 6)
                                        {
                                            const MCParticleFormat* MC_top = mother_of_MC_Elec1->mother1();
                                            const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                            
                                            if (debug)cout << "size daughters of MCtop for lepton 1 " << daughters.size() << endl;
                                            
                                            for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                            {
                                                if (debug)cout << "in daughter loop" << endl;
                                                const MCParticleFormat* daughter = daughters[iDaughter];
                                                int pdgId = daughter->pdgid();
                                                if (debug)cout << pdgId << endl;
                                                if (pdgId == 4) {is_CJet = true;}
                                                if (pdgId == 5) {is_BJet = true;}
                                                if (pdgId == 24) {is_WJet = true;}
                                                if (pdgId == 25) {is_Higgs = true;}
                                                if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                            }
                                            if (is_CJet && !is_BJet)
                                            {
                                                Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(Elec_1.px(),Elec_1.py(),Elec_1.pz(),Elec_1.e());
                                                Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_Elec1->px(),MC_Elec1->py(),MC_Elec1->pz(),MC_Elec1->e());
                                                nb_events_after_lep1_from_FCNCtop+=1;
                                                Right_FCNClep1 = true;
                                            }
                                            if (is_BJet && !is_CJet)
                                            {
                                                Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(Elec_1.px(),Elec_1.py(),Elec_1.pz(),Elec_1.e());
                                                Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_Elec1->px(),MC_Elec1->py(),MC_Elec1->pz(),MC_Elec1->e());
                                                Right_SMlep1 = true;
                                            }
                                            
                                        }
                                        
                                    }

                                    }
                                 }else
                            {
                                
                                Wrong_Rec_Leading_Lepton.SetPxPyPzE(Elec_0.px(),Elec_0.py(),Elec_0.pz(),Elec_0.e());
                                Wrong_Rec_2nd_Leading_Lepton.SetPxPyPzE(Elec_1.px(),Elec_1.py(),Elec_1.pz(),Elec_1.e());
                                nb_events_AllCuts_MC_Wrong_2SSL+=1;
                                Wrong_lep0 = true;
                                Wrong_lep1 = true;

                            }
                        }
                        
                            
                            /////// ----------------------------------------------------///
                        
                        if (Mu)
                        {
                            if (debug)cout << " at if (Mu) " << endl;
                            Leading_lepton.SetPxPyPzE(Mu_muon0.Px(),Mu_muon0.Py(),Mu_muon0.Pz(),Mu_muon0.E());
                            second_Leading_lepton.SetPxPyPzE(Mu_muon1.Px(),Mu_muon1.Py(),Mu_muon1.Pz(),Mu_muon1.E());
                            Pt_leadingMuon_2SSSF->Fill(Mu_muon0.Pt(),weight);
                            Pt_2ndleadingMuon_2SSSF->Fill(Mu_muon1.Pt(),weight);
                            Eta_leadingMuon_2SSSF->Fill(Mu_muon0.Eta(),weight);
                            Eta_2ndleadingMuon_2SSSF->Fill(Mu_muon1.Eta(),weight);
                            Phi_leadingMuon_2SSSF->Fill(Mu_muon0.Phi(),weight);
                            Phi_2ndleadingMuon_2SSSF->Fill(Mu_muon1.Phi(),weight);
                            Delta_Phi_2SSMuon->Fill(Mu_muon0.DeltaPhi(Mu_muon1),weight);
                            DeltaR_2SSMuon->Fill(Mu_muon0.DeltaR(Mu_muon1),weight);
                            lep1_pt_to_Ht = Mu_muon1.Pt()/Ht_all_Jets;
                            Mu1_pt_to_Ht_ratio ->Fill(lep1_pt_to_Ht, weight);
                            
                            m_lb = (Mu_muon0 + Leading_CSVLB_Jet).M();
                            DeltaRmin_Mu0_b->Fill(Mu_muon0.DeltaR(Leading_CSVLB_Jet),weight);
                            Mass_Mu0_b->Fill(m_lb, weight);
                            
                            ///// ----- checking MC particles for SSdiMuons ---------///
                            
                            const RecLeptonFormat& Mu_0 = event.rec()->muons()[0];
                            const MCParticleFormat* MC_Mu0 = Mu_0.mc();
                            const RecLeptonFormat& Mu_1 = event.rec()->muons()[1];
                            const MCParticleFormat* MC_Mu1 = Mu_1.mc();
                            
                            
                            if (MC_Mu0 != 0 && MC_Mu1 !=0)
                            {
                                if (fabs(MC_Mu0->pdgid()) == 13 && fabs(MC_Mu1->pdgid()) == 13)
                                {
                                    const MCParticleFormat* myPartmu0 = MC_Mu0;
                                   //bool found_mother_mu0 = false;
                                    while (!found_mother_mu0)
                                    {
                                        loop_counter++;
                                        if (loop_counter>100)
                                        {
                                            cout << "infinite loop " << endl;
                                            break;
                                        }
                                        if(myPartmu0->mother1()->pdgid() == myPartmu0->pdgid())
                                        {
                                            const std::vector<MCParticleFormat*> motherdaughters = myPartmu0->mother1()->daughters();
//                                            for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                            {
//                                                cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                            }
                                        }
                                        if( myPartmu0->pdgid() != myPartmu0->mother1()->pdgid() )
                                        {
                                            pdgid_mother = myPartmu0->mother1()->pdgid();
                                            
                                            found_mother_mu0 = true;
                                        }else
                                        {
                                            myPartmu0 = myPartmu0->mother1();
                                        }
                                    }

                                    if (found_mother_mu0)
                                    {
                                        const MCParticleFormat* mother_of_MC_Mu0 =  myPartmu0->mother1();
                                        
                                        if (fabs(mother_of_MC_Mu0->pdgid())== 24)
                                        {
                                            
                                            if (fabs(tool.motherID(mother_of_MC_Mu0)) == 6)
                                            {
                                                
                                                const MCParticleFormat* MC_top = mother_of_MC_Mu0->mother1();
                                                const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                
                                                if (debug)cout << "size daughters of MCtop of real W of lepton0  " << daughters.size() << endl;
                                                
                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                {
                                                    if (debug)cout << "in daughter loop" << endl;
                                                    const MCParticleFormat* daughter = daughters[iDaughter];
                                                    int pdgId = daughter->pdgid();
                                                    if (debug)cout << pdgId << endl;
                                                    if (pdgId == 4) {is_CJet = true;}
                                                    if (pdgId == 5) {is_BJet = true;}
                                                    if (pdgId == 24) {is_WJet = true;}
                                                    if (pdgId == 25) {is_Higgs = true;}
                                                    if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                }
                                                if (is_CJet && !is_BJet )
                                                {
                                                    Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(Mu_0.px(),Mu_0.py(),Mu_0.pz(),Mu_0.e());
                                                    Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_Mu0->px(),MC_Mu0->py(),MC_Mu0->pz(),MC_Mu0->e());
                                                    nb_events_after_lep0_from_FCNCtop+=1;
                                                    Right_FCNClep0 = true;
                                                }
                                                if (is_BJet && !is_CJet)
                                                {
                                                    Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(Mu_0.px(),Mu_0.py(),Mu_0.pz(),Mu_0.e());
                                                    Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_Mu0->px(),MC_Mu0->py(),MC_Mu0->pz(),MC_Mu0->e());
                                                    nb_events_after_lep0_from_SMtop+=1;
                                                    Right_SMlep0 = true;
                                                }
                                                
                                            }
                                            if (fabs(tool.motherID(mother_of_MC_Mu0)) == 25)
                                            {
                                                Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(Mu_0.px(),Mu_0.py(),Mu_0.pz(),Mu_0.e());
                                                Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_Mu0->px(),MC_Mu0->py(),MC_Mu0->pz(),MC_Mu0->e());
                                                nb_events_after_lep0_from_FCNCtop+=1;
                                                Right_FCNClep0 = true;
                                                
                                            }
                                            
                                        }
                                        if (fabs(mother_of_MC_Mu0->pdgid())== 6)
                                        {
                                            const MCParticleFormat* MC_top = mother_of_MC_Mu0->mother1();
                                            const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                            
                                            if (debug)cout << "size daughters of MCtop for lepton0 directly " << daughters.size() << endl;
                                            
                                            for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                            {
                                                if (debug)cout << "in daughter loop " << endl;
                                                const MCParticleFormat* daughter = daughters[iDaughter];
                                                int pdgId = daughter->pdgid();
                                                if (debug)cout << pdgId << endl;
                                                if (pdgId == 4) {is_CJet = true;}
                                                if (pdgId == 5) {is_BJet = true;}
                                                if (pdgId == 24) {is_WJet = true;}
                                                if (pdgId == 25) {is_Higgs = true;}
                                                if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                            }
                                            if (is_CJet && !is_BJet)
                                            {
                                                Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(Mu_0.px(),Mu_0.py(),Mu_0.pz(),Mu_0.e());
                                                Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_Mu0->px(),MC_Mu0->py(),MC_Mu0->pz(),MC_Mu0->e());
                                                nb_events_after_lep0_from_FCNCtop+=1;
                                                Right_FCNClep0 = true;
                                            }
                                            if (is_BJet && !is_CJet)
                                            {
                                                Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(Mu_0.px(),Mu_0.py(),Mu_0.pz(),Mu_0.e());
                                                Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_Mu0->px(),MC_Mu0->py(),MC_Mu0->pz(),MC_Mu0->e());
                                                nb_events_after_lep0_from_SMtop+=1;
                                                Right_SMlep0 = true;
                                            }
                                            
                                        }
                                    }

                                    ///***** for second leading lepton
                                    const MCParticleFormat* myPartmu1 = MC_Mu1;
                                    
                                    while (!found_mother_mu1)
                                    {
                                        loop_counter++;
                                        if (loop_counter>100)
                                        {
                                            cout << "infinite loop " << endl;
                                            break;
                                        }
                                        if(myPartmu1->mother1()->pdgid() == myPartmu1->pdgid())
                                        {
                                            const std::vector<MCParticleFormat*> motherdaughters = myPartmu1->mother1()->daughters();
//                                            for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                            {
//                                                cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                            }
                                        }
                                        if( myPartmu1->pdgid() != myPartmu1->mother1()->pdgid() )
                                        {
                                            pdgid_mother = myPartmu1->mother1()->pdgid();
                                            
                                            found_mother_mu1 = true;
                                        }else
                                        {
                                            myPartmu1 = myPartmu1->mother1();
                                        }
                                    }

                                    if (found_mother_mu1)
                                    {
                                        const MCParticleFormat* mother_of_MC_Mu1 = myPartmu1->mother1();
                                        if (fabs(mother_of_MC_Mu1->pdgid())== 24)
                                        {
                                            if (fabs(tool.motherID(mother_of_MC_Mu1)) == 6)
                                            {
                                                const MCParticleFormat* MC_top = mother_of_MC_Mu1->mother1();
                                                const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                
                                                if (debug)cout << "size daughters of MCtop of real W to Muon1 " << daughters.size() << endl;
                                                
                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                {
                                                    if (debug)cout << "in daughter loop" << endl;
                                                    const MCParticleFormat* daughter = daughters[iDaughter];
                                                    int pdgId = daughter->pdgid();
                                                    if (debug)cout << pdgId << endl;
                                                    if (pdgId == 4) {is_CJet = true;}
                                                    if (pdgId == 5) {is_BJet = true;}
                                                    if (pdgId == 24) {is_WJet = true;}
                                                    if (pdgId == 25) {is_Higgs = true;}
                                                    if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                }
                                                if (is_CJet && !is_BJet)
                                                {
                                                    Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(Mu_1.px(),Mu_1.py(),Mu_1.pz(),Mu_1.e());
                                                    Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_Mu1->px(),MC_Mu1->py(),MC_Mu1->pz(),MC_Mu1->e());
                                                    nb_events_after_lep1_from_FCNCtop+=1;
                                                    Right_FCNClep1 = true;
                                                }
                                                if (is_BJet && !is_CJet)
                                                {
                                                    Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(Mu_1.px(),Mu_1.py(),Mu_1.pz(),Mu_1.e());
                                                    Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_Mu1->px(),MC_Mu1->py(),MC_Mu1->pz(),MC_Mu1->e());
                                                    nb_events_after_lep1_from_SMtop+=1;
                                                    Right_SMlep1 = true;
                                                }
                                                
                                            }
                                            if (fabs(tool.motherID(mother_of_MC_Mu1)) == 25)
                                            {
                                                Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(Mu_1.px(),Mu_1.py(),Mu_1.pz(),Mu_1.e());
                                                Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_Mu1->px(),MC_Mu1->py(),MC_Mu1->pz(),MC_Mu1->e());
                                                nb_events_after_lep1_from_FCNCtop+=1;
                                                Right_FCNClep1 = true;
                                            }
                                            
                                        }
                                        if (fabs(mother_of_MC_Mu1->pdgid())== 6)
                                        {
                                            const MCParticleFormat* MC_top = mother_of_MC_Mu1->mother1();
                                            const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                            
                                            if (debug)cout << "size daughters of MCtop of muon1 directly " << daughters.size() << endl;
                                            
                                            for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                            {
                                                if (debug)cout << "in daughter loop" << endl;
                                                const MCParticleFormat* daughter = daughters[iDaughter];
                                                int pdgId = daughter->pdgid();
                                                if (debug)cout << pdgId << endl;
                                                if (pdgId == 4) {is_CJet = true;}
                                                if (pdgId == 5) {is_BJet = true;}
                                                if (pdgId == 24) {is_WJet = true;}
                                                if (pdgId == 25) {is_Higgs = true;}
                                                if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                            }
                                            if (is_CJet && !is_BJet)
                                            {
                                                Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(Mu_1.px(),Mu_1.py(),Mu_1.pz(),Mu_1.e());
                                                Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_Mu1->px(),MC_Mu1->py(),MC_Mu1->pz(),MC_Mu1->e());
                                                nb_events_after_lep1_from_FCNCtop+=1;
                                                Right_FCNClep1 = true;
                                            }
                                            if (is_BJet && !is_CJet)
                                            {
                                                Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(Mu_1.px(),Mu_1.py(),Mu_1.pz(),Mu_1.e());
                                                Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_Mu1->px(),MC_Mu1->py(),MC_Mu1->pz(),MC_Mu1->e());
                                                nb_events_after_lep1_from_SMtop+=1;
                                                Right_SMlep1 = true;
                                            }
                                            
                                        }
                                        
                                    }
                                    
                                }

                                    }else
                                    {
                            
                                        Wrong_Rec_Leading_Lepton.SetPxPyPzE(Mu_0.px(),Mu_0.py(),Mu_0.pz(),Mu_0.e());
                                        Wrong_Rec_2nd_Leading_Lepton.SetPxPyPzE(Mu_1.px(),Mu_1.py(),Mu_1.pz(),Mu_1.e());
                                        nb_events_AllCuts_MC_Wrong_2SSL+=1;
                                        Wrong_lep0 = true;
                                        Wrong_lep1 = true;
                            
                                    }
                        }

                            /////// ----------------------------------------------------///
                        
                        if (EMu)
                        {
                            if (debug)cout << " at if (EMu) " << endl;
                            Leading_lepton.SetPxPyPzE(EMu_lepton0.Px(),EMu_lepton0.Py(),EMu_lepton0.Pz(),EMu_lepton0.E());
                            second_Leading_lepton.SetPxPyPzE(EMu_lepton1.Px(),EMu_lepton1.Py(),EMu_lepton1.Pz(),EMu_lepton1.E());
                            Pt_leadingLepton_2SSOF->Fill(EMu_lepton0.Pt(),weight);
                            Pt_2ndleadingLepton_2SSOF->Fill(EMu_lepton1.Pt(),weight);
                            Eta_leadingLepton_2SSOF->Fill(EMu_lepton0.Eta(),weight);
                            Eta_2ndleadingLepton_2SSOF->Fill(EMu_lepton1.Eta(),weight);
                            Phi_leadingLepton_2SSOF->Fill(EMu_lepton0.Phi(),weight);
                            Phi_2ndleadingLepton_2SSOF->Fill(EMu_lepton1.Phi(),weight);
                            Delta_Phi_2SSOF->Fill(EMu_lepton0.DeltaPhi(EMu_lepton1),weight);
                            DeltaR_2SSOF->Fill(EMu_lepton0.DeltaR(EMu_lepton1),weight);
                            lep1_pt_to_Ht = EMu_lepton1.Pt()/Ht_all_Jets;
                            lep1_pt_to_Ht_ratio ->Fill(lep1_pt_to_Ht, weight);
                            m_lb = (EMu_lepton0 + Leading_CSVLB_Jet).M();
                            DeltaRmin_lep0_b->Fill(EMu_lepton0.DeltaR(Leading_CSVLB_Jet),weight);
                            Mass_lep0_b->Fill(m_lb, weight);
                            
                            
                            ///// ----- checking MC particles for SSdiElecMu ---------///
                            if (Elec_Mu)
                            {
                                if (debug)cout << " at if (EMu) and if (Elec_Mu) " << endl;
                                const RecLeptonFormat& EMu_0 = event.rec()->electrons()[Place_el[0]];
                                const MCParticleFormat* MC_EMu0 = EMu_0.mc();
                                const RecLeptonFormat& EMu_1 = event.rec()->muons()[0];
                                const MCParticleFormat* MC_EMu1 = EMu_1.mc();
                                
                                if (MC_EMu0 != 0 && MC_EMu1 !=0)
                                {
                                    if (fabs(MC_EMu0->pdgid()) == 11 && fabs(MC_EMu1->pdgid()) == 13)
                                    {
                                        const MCParticleFormat* myPartemu0 = MC_EMu0;
                                        
                                        while (!found_mother_emu0)
                                        {
                                            loop_counter++;
                                            if (loop_counter>100)
                                            {
                                                cout << "infinite loop " << endl;
                                                break;
                                            }
                                            if(myPartemu0->mother1()->pdgid() == myPartemu0->pdgid())
                                            {
                                                const std::vector<MCParticleFormat*> motherdaughters = myPartemu0->mother1()->daughters();
//                                                for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                                {
//                                                    cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                                }
                                            }
                                            if( myPartemu0->pdgid() != myPartemu0->mother1()->pdgid() )
                                            {
                                                pdgid_mother = myPartemu0->mother1()->pdgid();
                                                
                                                found_mother_emu0 = true;
                                            }else
                                            {
                                                myPartemu0 = myPartemu0->mother1();
                                            }
                                        }

                                        if (found_mother_emu0)
                                        {
                                            const MCParticleFormat* mother_of_MC_EMu0 = myPartemu0->mother1();
                                            
                                            if (fabs(mother_of_MC_EMu0->pdgid())== 24)
                                            {
                                                
                                                if (fabs(tool.motherID(mother_of_MC_EMu0)) == 6)
                                                {
                                                    
                                                    const MCParticleFormat* MC_top = mother_of_MC_EMu0->mother1();
                                                    const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                    
                                                    if (debug)cout << "size daughters of MCtop for lepton0 " << daughters.size() << endl;
                                                    
                                                    for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                    {
                                                        if (debug)cout << "in daughter loop" << endl;
                                                        const MCParticleFormat* daughter = daughters[iDaughter];
                                                        int pdgId = daughter->pdgid();
                                                        if (debug)cout << pdgId << endl;
                                                        if (pdgId == 4) {is_CJet = true;}
                                                        if (pdgId == 5) {is_BJet = true;}
                                                        if (pdgId == 24) {is_WJet = true;}
                                                        if (pdgId == 25) {is_Higgs = true;}
                                                        if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                    }
                                                    if (is_CJet && !is_BJet)
                                                    {
                                                        Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                        Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                        nb_events_after_lep0_from_FCNCtop+=1;
                                                        Right_FCNClep0 = true;
                                                    }
                                                    if (is_BJet && !is_CJet)
                                                    {
                                                        Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                        Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                        nb_events_after_lep0_from_SMtop+=1;
                                                        Right_SMlep0 = true;
                                                    }
                                                    
                                                }
                                                if (fabs(tool.motherID(mother_of_MC_EMu0)) == 25)
                                                {
                                                    Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                    Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                    nb_events_after_lep0_from_FCNCtop+=1;
                                                    Right_FCNClep0 = true;
                                                    
                                                }
                                                if (fabs(mother_of_MC_EMu0->pdgid())== 6)
                                                {
                                                    const MCParticleFormat* MC_top = mother_of_MC_EMu0->mother1();
                                                    const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                    
                                                    if (debug)cout << "size daughters " << daughters.size() << endl;
                                                    
                                                    for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                    {
                                                        if (debug)cout << "in daughter loop" << endl;
                                                        const MCParticleFormat* daughter = daughters[iDaughter];
                                                        int pdgId = daughter->pdgid();
                                                        if (debug)cout << pdgId << endl;
                                                        if (pdgId == 4) {is_CJet = true;}
                                                        if (pdgId == 5) {is_BJet = true;}
                                                        if (pdgId == 24) {is_WJet = true;}
                                                        if (pdgId == 25) {is_Higgs = true;}
                                                        if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                    }
                                                    if (is_CJet && !is_BJet)
                                                    {
                                                        Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                        Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                        nb_events_after_lep0_from_FCNCtop+=1;
                                                        Right_FCNClep0 = true;
                                                    }
                                                    if (is_BJet && !is_CJet)
                                                    {
                                                        Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                        Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                        nb_events_after_lep0_from_SMtop+=1;
                                                        Right_SMlep0 = true;
                                                    }
                                                    
                                                }

                                        }
                                        }
                                        
                                            
                                    ///***** for second leading lepton
                                            
                                            const MCParticleFormat* myPartemu1 = MC_EMu1;
                                        
                                            while (!found_mother_emu1)
                                            {
                                                loop_counter++;
                                                if (loop_counter>100)
                                                {
                                                    cout << "infinite loop " << endl;
                                                    break;
                                                }
                                                if(myPartemu1->mother1()->pdgid() == myPartemu1->pdgid())
                                                {
                                                    const std::vector<MCParticleFormat*> motherdaughters = myPartemu1->mother1()->daughters();
//                                                    for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                                    {
//                                                        cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                                    }
                                                }
                                                if( myPartemu1->pdgid() != myPartemu1->mother1()->pdgid() )
                                                {
                                                    pdgid_mother = myPartemu1->mother1()->pdgid();
                                                    
                                                    found_mother_emu1 = true;
                                                }else
                                                {
                                                    myPartemu1 = myPartemu1->mother1();
                                                }
                                            }

                                            if (found_mother_emu1)
                                            {
                                                const MCParticleFormat* mother_of_MC_EMu1 = myPartemu1->mother1();
                                                if (fabs(mother_of_MC_EMu1->pdgid())== 24)
                                                {
                                                    
                                                    if (fabs(tool.motherID(mother_of_MC_EMu1)) == 6)
                                                    {
                                                        
                                                        const MCParticleFormat* MC_top = mother_of_MC_EMu1->mother1();
                                                        const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                        
                                                        if (debug)cout << "size daughters " << daughters.size() << endl;
                                                        
                                                        for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                        {
                                                            if (debug)cout << "in daughter loop" << endl;
                                                            const MCParticleFormat* daughter = daughters[iDaughter];
                                                            int pdgId = daughter->pdgid();
                                                            if (debug)cout << pdgId << endl;
                                                            if (pdgId == 4) {is_CJet = true;}
                                                            if (pdgId == 5) {is_BJet = true;}
                                                            if (pdgId == 24) {is_WJet = true;}
                                                            if (pdgId == 25) {is_Higgs = true;}
                                                            if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                        }
                                                        if (is_CJet && !is_BJet)
                                                        {
                                                            Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                            Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                            nb_events_after_lep1_from_FCNCtop+=1;
                                                            Right_FCNClep1 = true;
                                                        }
                                                        if (is_BJet && !is_CJet)
                                                        {
                                                            Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                            Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                            nb_events_after_lep1_from_SMtop+=1;
                                                            Right_SMlep1 = true;
                                                        }
                                                        
                                                    }
                                                    if (fabs(tool.motherID(mother_of_MC_EMu1)) == 25)
                                                    {
                                                        Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                        Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                        nb_events_after_lep1_from_FCNCtop+=1;
                                                        Right_FCNClep1 = true;
                                                    }
                                                    
                                                }
                                                if (fabs(mother_of_MC_EMu1->pdgid())== 6)
                                                {
                                                    const MCParticleFormat* MC_top = mother_of_MC_EMu1->mother1();
                                                    const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                    
                                                    if (debug)cout << "size daughters " << daughters.size() << endl;
                                                    
                                                    for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                    {
                                                        if (debug)cout << "in daughter loop" << endl;
                                                        const MCParticleFormat* daughter = daughters[iDaughter];
                                                        int pdgId = daughter->pdgid();
                                                        if (debug)cout << pdgId << endl;
                                                        if (pdgId == 4) {is_CJet = true;}
                                                        if (pdgId == 5) {is_BJet = true;}
                                                        if (pdgId == 24) {is_WJet = true;}
                                                        if (pdgId == 25) {is_Higgs = true;}
                                                        if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                    }
                                                    if (is_CJet && !is_BJet)
                                                    {
                                                        Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                        Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                        nb_events_after_lep1_from_FCNCtop+=1;
                                                        Right_FCNClep1 = true;
                                                    }
                                                    if (is_BJet && !is_CJet)
                                                    {
                                                        Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                        Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                        nb_events_after_lep1_from_SMtop+=1;
                                                        Right_SMlep1 = true;
                                                    }
                                                    
                                                }
                                                
                                            }

                                            }
 
                                }else
                                {
                                    Wrong_Rec_Leading_Lepton.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                    Wrong_Rec_2nd_Leading_Lepton.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                    nb_events_AllCuts_MC_Wrong_2SSL+=1;
                                    Wrong_lep0 = true;
                                    Wrong_lep1 = true;

                                }
                            }
                        //////////////////////////////////////////////////////////////
                            if (Mu_Elec)
                            {
                                if (debug)cout << " at if (EMu) and if (Mu_Elec) " << endl;
                                const RecLeptonFormat& EMu_0 = event.rec()->muons()[0];
                                const MCParticleFormat* MC_EMu0 = EMu_0.mc();
                                const RecLeptonFormat& EMu_1 = event.rec()->electrons()[Place_el[0]];
                                const MCParticleFormat* MC_EMu1 = EMu_1.mc();
                                
                                if (MC_EMu0 != 0 && MC_EMu1 !=0)
                                {
                                    if (debug)cout << " (MC_EMu0 != 0 && MC_EMu1 !=0) " << endl;
                                    if (fabs(MC_EMu0->pdgid()) == 13 && fabs(MC_EMu1->pdgid()) == 11)
                                    {
                                        const MCParticleFormat* myPart = MC_EMu0;
                                        while (!found_mother)
                                        {
                                            loop_counter++;
                                            if (loop_counter>100)
                                            {
                                                cout << "infinite loop " << endl;
                                                break;
                                            }
                                            if(myPart->mother1()->pdgid() == myPart->pdgid())
                                            {
                                                const std::vector<MCParticleFormat*> motherdaughters = myPart->mother1()->daughters();
//                                                for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                                {
//                                                    cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                                }
                                            }
                                            if( myPart->pdgid() != myPart->mother1()->pdgid() )
                                            {
                                                pdgid_mother = myPart->mother1()->pdgid();
                                                
                                                found_mother = true;
                                            }else
                                            {
                                                myPart = myPart->mother1();
                                            }
                                        }
                                        if (found_mother)
                                        {
                                            if (debug)cout << "yes there is mother of myPart and it's pdgid is =  "<< myPart->mother1()->pdgid() <<endl;
                                            const MCParticleFormat* mother_of_MC_EMu0 = myPart->mother1();
                                            if (debug)cout << " hello here 2 " << endl;
                                        
                                            if (debug)cout << "the address of the MC_EMu0 is =  " << MC_EMu0 << endl;
                                            if (debug)cout << "the address of the mother_of_MC_EMu0 is =  " << mother_of_MC_EMu0 << endl;
                                            
                                            //if (mother_of_MC_EMu0==0) cout<<"WARNING: mother not found"<<endl;
                                            //if (mother_of_MC_EMu0!=0) cout<<"WARNING: mother is found and from tool.motherID(MC_EMu0) pdgid is =  "<< fabs(tool.motherID(MC_EMu0)) << "  , but from mother_of_MC_EMu0->pdgid() is =  "<< mother_of_MC_EMu0->pdgid() <<" and from MC_EMu0->mother1()->pdgid is =   " << MC_EMu0->mother1()->pdgid() << endl;
                                            
                                            if (found_mother && fabs(mother_of_MC_EMu0->pdgid())== 24)
                                            {
                                                
                                                if (debug)cout << " tool.motherID(mother_of_MC_EMu0) is =  " << tool.motherID(mother_of_MC_EMu0) << endl;
                                                if (debug)cout << " fabs(mother_of_MC_EMu0->pdgid())== 24 " << endl;
                                                if (fabs(tool.motherID(mother_of_MC_EMu0)) == 6)
                                                {
                                                    if (debug) cout << " fabs(tool.motherID(mother_of_MC_EMu0) =  " << tool.motherID(mother_of_MC_EMu0) << endl;
                                                    const MCParticleFormat* MC_top = mother_of_MC_EMu0->mother1();
                                                    const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                    
                                                    if (debug)cout << "size daughters of MCtop for lepton0 " << daughters.size() << endl;
                                                    
                                                    for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                    {
                                                        if (debug)cout << "in daughter loop" << endl;
                                                        const MCParticleFormat* daughter = daughters[iDaughter];
                                                        int pdgId = daughter->pdgid();
                                                        if (debug)cout << pdgId << endl;
                                                        if (fabs(pdgId) == 4) {is_CJet = true;}
                                                        if (fabs(pdgId) == 5) {is_BJet = true;}
                                                        if (fabs(pdgId) == 24) {is_WJet = true;}
                                                        if (fabs(pdgId) == 25) {is_Higgs = true;}
                                                        if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                    }
                                                    if (is_CJet && !is_BJet)
                                                    {
                                                        Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                        Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                        nb_events_after_lep0_from_FCNCtop+=1;
                                                        Right_FCNClep0 = true;
                                                    }
                                                    if (is_BJet && !is_CJet)
                                                    {
                                                        Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                        Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                        nb_events_after_lep0_from_SMtop+=1;
                                                        Right_SMlep0 = true;
                                                    }
                                                    
                                                }
                                                if (found_mother && fabs(tool.motherID(mother_of_MC_EMu0)) == 25)
                                                {
                                                    if (debug)cout << " hello here at higgs " << endl;
                                                    Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                    Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                    nb_events_after_lep0_from_FCNCtop+=1;
                                                    Right_FCNClep0 = true;
                                                }
                                                
                                            }
                                            if (found_mother && fabs(mother_of_MC_EMu0->pdgid())== 6)
                                            {
                                                if (debug)cout << " hello here at top " << endl;
                                                const MCParticleFormat* MC_top = mother_of_MC_EMu0->mother1();
                                                const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                
                                                if (debug)cout << "size daughters of MCtop mother of W for lepton0" << daughters.size() << endl;
                                                
                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                {
                                                    if (debug)cout << "in daughter loop" << endl;
                                                    const MCParticleFormat* daughter = daughters[iDaughter];
                                                    int pdgId = daughter->pdgid();
                                                    if (debug)cout << pdgId << endl;
                                                    if (fabs(pdgId) == 4) {is_CJet = true;}
                                                    if (fabs(pdgId) == 5) {is_BJet = true;}
                                                    if (fabs(pdgId) == 24) {is_WJet = true;}
                                                    if (fabs(pdgId) == 25) {is_Higgs = true;}
                                                    
                                                    if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                }
                                                if (is_CJet && !is_BJet)
                                                {
                                                    Rec_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                    Gen_Leading_Lepton0_from_FCNCtop.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                    nb_events_after_lep0_from_FCNCtop+=1;
                                                    Right_FCNClep0 = true;
                                                }
                                                if (is_BJet && !is_CJet)
                                                {
                                                    Rec_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                                    Gen_Leading_Lepton0_SMtop_true_combination.SetPxPyPzE(MC_EMu0->px(),MC_EMu0->py(),MC_EMu0->pz(),MC_EMu0->e());
                                                    nb_events_after_lep0_from_SMtop+=1;
                                                    Right_SMlep0 = true;
                                                }
                                                
                                            }
                                        }
                                        ///***** for second leading lepton
                                        const MCParticleFormat* myPart1 = MC_EMu1;
                                        bool found_mother1 =false;
                                            while (!found_mother1)
                                            {
                                                loop_counter++;
                                                if (loop_counter>100)
                                                {
                                                    cout << "infinite loop " << endl;
                                                    break;
                                                }
                                                if(myPart1->mother1()->pdgid() == myPart1->pdgid())
                                                {
                                                    const std::vector<MCParticleFormat*> motherdaughters = myPart1->mother1()->daughters();
//                                                    for(unsigned int d=0; d<motherdaughters.size(); d++)
//                                                    {
//                                                        cout<<" daughter id "<<motherdaughters[d]->pdgid()<<endl;
//                                                    }
                                                }
                                                if( myPart1->pdgid() != myPart1->mother1()->pdgid() )
                                                {
                                                    pdgid_mother = myPart1->mother1()->pdgid();
                                                    found_mother1 = true;
                                                }else
                                                {
                                                    myPart1 = myPart1->mother1();
                                                }
                                            }
                                            if (found_mother1)
                                            {
                                                if(debug)cout << "yes there is mother for myPart1 and it's pdgid is =  "<< myPart1->mother1()->pdgid() <<endl;
                                                const MCParticleFormat* mother_of_MC_EMu1 = myPart1->mother1();
                                                
                                            if (found_mother1 && fabs(mother_of_MC_EMu1->pdgid())== 24)
                                            {

                                            if (fabs(tool.motherID(mother_of_MC_EMu1)) == 6)
                                            {
                                                
                                                const MCParticleFormat* MC_top = mother_of_MC_EMu1->mother1();
                                                const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                                
                                                if (debug)cout << "size daughters " << daughters.size() << endl;
                                                
                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                                {
                                                    if (debug)cout << "in daughter loop" << endl;
                                                    const MCParticleFormat* daughter = daughters[iDaughter];
                                                    int pdgId = daughter->pdgid();
                                                    if (debug)cout << pdgId << endl;
                                                    if (pdgId == 4) {is_CJet = true;}//cout << "c is one of top daughters"<< endl;}
                                                    if (pdgId == 5) {is_BJet = true;}//cout << "b is one of top daughters"<< endl;}
                                                    if (pdgId == 24) {is_WJet = true;}//cout << "W is one of top daughters"<< endl;}
                                                    if (pdgId == 25) {is_Higgs = true;}//cout << "H is one of top daughters"<< endl;}
                                                    if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                                }
                                                if (is_CJet && !is_BJet)
                                                {
                                                    if (debug) cout << "filling lepton1 of FCNCtop " << endl;
                                                    Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                    Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                    nb_events_after_lep1_from_FCNCtop+=1;
                                                    Right_FCNClep1 = true;
                                                }
                                                if (is_BJet && !is_CJet)
                                                {
                                                    if (debug) cout << "filling lepton1 of SMtop " << endl;
                                                    Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                    Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                    nb_events_after_lep1_from_SMtop+=1;
                                                    Right_SMlep1 = true;
                                                }
                                                
                                            }
                                            if (debug) cout << "grandmother of lepton1 is with pdgid =  " << tool.motherID(mother_of_MC_EMu1) << endl;
                                                
                                            if (found_mother1 && fabs(tool.motherID(mother_of_MC_EMu1)) == 25)
                                            {
                                                if (debug) cout << "filling lepton1 of Higgs " << endl;
                                                Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                nb_events_after_lep1_from_FCNCtop+=1;
                                                Right_FCNClep1 = true;
                                                
//                                                const MCParticleFormat* MC_Higgs = mother_of_MC_EMu1->mother1();
//                                                const std::vector<MCParticleFormat*> daughters = MC_Higgs->daughters();
//                                                
//                                                cout << "size daughters of Higgs for lepton1 " << daughters.size() << endl;
//                                                
//                                                for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
//                                                {
//                                                    cout << "in daughter loop" << endl;
//                                                    const MCParticleFormat* daughter = daughters[iDaughter];
//                                                    int pdgId = daughter->pdgid();
//                                                    cout << pdgId << endl;
//                                                    if (pdgId == 5) {is_BJet = true; cout << "b is one of higgs daughters"<< endl;}
//                                                    if (pdgId == 24) {is_WJet = true; cout << "W is one of higgs daughters"<< endl;}
//                                                    cout << "pdg id daughter =" << daughter->pdgid() << endl;
//                                                }
//                                                if (is_WJet)
//                                                {
//                                                    Rec_second_Leading_Lepton1_from_Higgs.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
//                                                    Gen_second_Leading_Lepton1_from_Higgs.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
//                                                }
                                                
                                            }
                                            
                                        }
                                        if (found_mother1 && fabs(mother_of_MC_EMu1->pdgid())== 6)
                                        {
                                            const MCParticleFormat* MC_top = mother_of_MC_EMu1->mother1();
                                            const std::vector<MCParticleFormat*> daughters = MC_top->daughters();
                                            
                                            if (debug)cout << "size daughters " << daughters.size() << endl;
                                            
                                            for(unsigned int iDaughter = 0; iDaughter<daughters.size(); iDaughter++)
                                            {
                                                if (debug)cout << "in daughter loop" << endl;
                                                const MCParticleFormat* daughter = daughters[iDaughter];
                                                int pdgId = daughter->pdgid();
                                                if (debug)cout << pdgId << endl;
                                                if (pdgId == 4) {is_CJet = true;}
                                                if (pdgId == 5) {is_BJet = true;}
                                                if (pdgId == 24) {is_WJet = true;}
                                                if (pdgId == 25) {is_Higgs = true;}
                                                if (debug)cout << "pdg id daughter =" << daughter->pdgid() << endl;
                                            }
                                            if (is_CJet && !is_BJet)
                                            {
                                                Rec_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                Gen_second_Leading_Lepton1_from_FCNCtop.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                nb_events_after_lep1_from_FCNCtop+=1;
                                                Right_FCNClep1 = true;
                                            }
                                            if (is_BJet && !is_CJet)
                                            {
                                                Rec_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                                Gen_second_Leading_Lepton1_SMtop_true_combination.SetPxPyPzE(MC_EMu1->px(),MC_EMu1->py(),MC_EMu1->pz(),MC_EMu1->e());
                                                nb_events_after_lep1_from_SMtop+=1;
                                                Right_SMlep1 = true;
                                            }
                                            
                                        }
                                        
                                    }
                                    }
                                    
                                    
                                }else
                            {
                                if (debug) cout << "filling Wrong EMu channel " << endl;
                                Wrong_Rec_Leading_Lepton.SetPxPyPzE(EMu_0.px(),EMu_0.py(),EMu_0.pz(),EMu_0.e());
                                Wrong_Rec_2nd_Leading_Lepton.SetPxPyPzE(EMu_1.px(),EMu_1.py(),EMu_1.pz(),EMu_1.e());
                                nb_events_AllCuts_MC_Wrong_2SSL+=1;
                                Wrong_lep0 = true;
                                Wrong_lep1 = true;
                            }
                            

                            }
                        
                        }
                        
                
                            /////// ----------------------------------------------------///
                        
                        Pt_leading_Jet->Fill(selJetsColl[0].pt(),weight);
                        Pt_2ndleading_Jet->Fill(selJetsColl[1].pt(),weight);
                        Pt_3rdleading_Jet->Fill(selJetsColl[2].pt(),weight);
                        if (selJetsColl.size()>= 4)Pt_4thleading_Jet ->Fill(selJetsColl[3].pt(),weight);
                        if(selJetsColl.size() >= 5)Pt_5thleading_Jet ->Fill(selJetsColl[4].pt(),weight);
                        if(selJetsColl.size() >= 6)Pt_6thleading_Jet ->Fill(selJetsColl[5].pt(),weight);
                        if(selJetsColl.size() >= 7)Pt_7thleading_Jet ->Fill(selJetsColl[6].pt(),weight);
                        
                        
                        M_bJet_Lep0 = (Leading_lepton + Leading_CSVLB_Jet).M();
                        M_bJet_Lep1 = (second_Leading_lepton + Leading_CSVLB_Jet).M();
                        Mass_SM_bJet_lep0 ->Fill(M_bJet_Lep0,weight);
                        Mass_SM_bJet_lep1 ->Fill(M_bJet_Lep1,weight);
                        
                        
                        //////////// ******* recostruction of FCNC top ************ ////////////
                
                if (NonLeadingCSVLBJetsColl.size() >= 3)
                {
                    if (debug) cout << "at NonLeadingCSVLBJetsColl.size() >= 3 " << endl;
                    for (unsigned int i = 0; i < NonLeadingCSVLBJetsColl.size(); i++)
                    {
                        FCNC_C_jet.SetPxPyPzE(NonLeadingCSVLBJetsColl[0].px(),NonLeadingCSVLBJetsColl[0].py(),NonLeadingCSVLBJetsColl[0].pz(),NonLeadingCSVLBJetsColl[0].e());
                        
                        const RecJetFormat& CJET = NonLeadingCSVLBJetsColl[i];
                        const MCParticleFormat* MC_Cjet = tool.partonMatching(&CJET);
                        
                        if (MC_Cjet != 0)
                        {
                            if (fabs(tool.motherID(MC_Cjet)) == 6)
                            {
                                if (fabs(MC_Cjet->pdgid()) == 4)
                                {
                                    right_Rec_CJet.SetPxPyPzE(CJET.px(),CJET.py(),CJET.pz(),CJET.e());
                                    right_Gen_CJet.SetPxPyPzE(MC_Cjet->px(),MC_Cjet->py(),MC_Cjet->pz(),MC_Cjet->e());
                                    nb_events_AllCuts_MC_Right_C+=1;
                                    Right_Cjets = true;
                                    if (debug) cout << " right C jet is number  =  " << i << "in the NonLeadingCSVLBJetsColl vector" << endl;
                                } else {
                                    Rec_CJet_With_MC.SetPxPyPzE(CJET.px(),CJET.py(),CJET.pz(),CJET.e());
                                    Gen_CJet_With_MC.SetPxPyPzE(MC_Cjet->px(),MC_Cjet->py(),MC_Cjet->pz(),MC_Cjet->e());
                                    nb_events_AllCuts_MC_C+=1;
                                }
                            } else {
                                Rec_CJet_With_MC.SetPxPyPzE(CJET.px(),CJET.py(),CJET.pz(),CJET.e());
                                Gen_CJet_With_MC.SetPxPyPzE(MC_Cjet->px(),MC_Cjet->py(),MC_Cjet->pz(),MC_Cjet->e());
                                nb_events_AllCuts_MC_C+=1;
                            }
                        } else
                        {
                            Wrong_Rec_CJet.SetPxPyPzE(CJET.px(),CJET.py(),CJET.pz(),CJET.e());
                            nb_events_AllCuts_MC_Wrong_C+=1;
                            Wrong_Cjets = true;
                        }
                        
                        
                    }
                    
                    for (unsigned int ijet = 1 ; ijet < NonLeadingCSVLBJetsColl.size(); ijet++)
                    {
                        if (debug) cout << "selecting FCNC w-jets step jet 1 " << endl;
                        for (unsigned int jjet = ijet+1 ; jjet < NonLeadingCSVLBJetsColl.size(); jjet++)
                        {
                            if (debug) cout << "selecting FCNC w-jets step jet 2 " << endl;
                            W_1st_Jet.SetPxPyPzE(NonLeadingCSVLBJetsColl[ijet].px(),NonLeadingCSVLBJetsColl[ijet].py(),NonLeadingCSVLBJetsColl[ijet].pz(),NonLeadingCSVLBJetsColl[ijet].e());
                            W_2nd_Jet.SetPxPyPzE(NonLeadingCSVLBJetsColl[jjet].px(),NonLeadingCSVLBJetsColl[jjet].py(),NonLeadingCSVLBJetsColl[jjet].pz(),NonLeadingCSVLBJetsColl[jjet].e());
                            m_jj = (W_1st_Jet + W_2nd_Jet).M();
                            //Mass_Jets_Pair ->Fill(m_jj, weight);
                            mass_diff_from_W = fabs(Wmass - m_jj);
                            if (mass_diff_from_W < minimum_mass_diff_from_W)
                            {
                                if (debug) cout << "selecting FCNC w-jets step 3 : closest to W mass " << endl;
                                m_JJ_Pair = m_jj;
                                minimum_mass_diff_from_W = mass_diff_from_W;
                                m_3jets_Lep0 = (FCNC_C_jet + W_1st_Jet + W_2nd_Jet + Leading_lepton).M();
                                m_3jets_Lep1 = (FCNC_C_jet + W_1st_Jet + W_2nd_Jet + second_Leading_lepton).M();
                                
                                //// ------ checking MC particles for FCNC wjets --------/////
                                const RecJetFormat& W_1St_JET = event.rec()->jets()[Place_NonLeadingCSVLB [ijet]];
                                //const RecJetFormat& W_1St_JET = NonLeadingCSVLBJetsColl[ijet];
                                const MCParticleFormat* MC_W_1St_JET = tool.partonMatching(&W_1St_JET);
                                
                                const RecJetFormat& W_2nd_JET = event.rec()->jets()[Place_NonLeadingCSVLB [jjet]];
                                //const RecJetFormat& W_2nd_JET = NonLeadingCSVLBJetsColl[jjet];
                                const MCParticleFormat* MC_W_2nd_JET = tool.partonMatching(&W_2nd_JET);
                                
                                if (MC_W_1St_JET != 0 && MC_W_2nd_JET != 0)
                                {
                                    if (debug) cout << "Checking FCNC MC W-jet " << endl;
                                    if (debug) cout << "pdgid of mother of 1st jet =   " << fabs(tool.motherID(MC_W_1St_JET)) << endl;
                                    if (debug) cout << "pdgid of mother of 2nd jet =   " << fabs(tool.motherID(MC_W_2nd_JET)) << endl;
                                    if (fabs(tool.motherID(MC_W_1St_JET)) == 24 && fabs(tool.motherID(MC_W_2nd_JET)) == 24)
                                    {
                                        if (debug) cout << "right MC W-jet and pdgid = 24 " << endl;
                                        const MCParticleFormat* Mother_of_W_jet1 = MC_W_1St_JET->mother1();
                                        const MCParticleFormat* Mother_of_W_jet2 = MC_W_2nd_JET->mother1();
                                        if (fabs(Mother_of_W_jet1 ->pdgid())== 25 && fabs(Mother_of_W_jet2 ->pdgid())== 25)
                                        {
                                            right_Rec_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(W_1St_JET.px(),W_1St_JET.py(),W_1St_JET.pz(),W_1St_JET.e());
                                            right_Rec_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(W_2nd_JET.px(),W_2nd_JET.py(),W_2nd_JET.pz(),W_2nd_JET.e());
                                            right_Gen_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(MC_W_1St_JET->px(),MC_W_1St_JET->py(),MC_W_1St_JET->pz(),MC_W_1St_JET->e());
                                            right_Gen_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(MC_W_2nd_JET->px(),MC_W_2nd_JET->py(),MC_W_2nd_JET->pz(),MC_W_2nd_JET->e());

                                            nb_events_AllCuts_MC_Right_FCNC_Wjets+=1;
                                            Right_WJets = true;
                                        }
//                                        if (fabs(Mother_of_W_jet1 ->pdgid())== 6 && fabs(Mother_of_W_jet2 ->pdgid())== 6)
//                                        {
//                                            //right_Rec_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(W_1St_JET.px(),W_1St_JET.py(),W_1St_JET.pz(),W_1St_JET.e());
//                                            //right_Rec_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(W_2nd_JET.px(),W_2nd_JET.py(),W_2nd_JET.pz(),W_2nd_JET.e());
//                                            Right_WJets = true;
//                                        }
                                    }
                                    if (fabs(tool.motherID(MC_W_1St_JET)) == 25 && fabs(tool.motherID(MC_W_2nd_JET)) == 25)
                                    {
                                        right_Rec_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(W_1St_JET.px(),W_1St_JET.py(),W_1St_JET.pz(),W_1St_JET.e());
                                        right_Rec_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(W_2nd_JET.px(),W_2nd_JET.py(),W_2nd_JET.pz(),W_2nd_JET.e());
                                        right_Gen_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(MC_W_1St_JET->px(),MC_W_1St_JET->py(),MC_W_1St_JET->pz(),MC_W_1St_JET->e());
                                        right_Gen_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(MC_W_2nd_JET->px(),MC_W_2nd_JET->py(),MC_W_2nd_JET->pz(),MC_W_2nd_JET->e());
//
                                        Right_WJets = true;
                                        
//
                                    }
                                   
                                } else
                                {
                                    Wrong_Rec_1st_JetCandidate_W_FCNCtop.SetPxPyPzE(W_1St_JET.px(),W_1St_JET.py(),W_1St_JET.pz(),W_1St_JET.e());
                                    Wrong_Rec_2nd_JetCandidate_W_FCNCtop.SetPxPyPzE(W_2nd_JET.px(),W_2nd_JET.py(),W_2nd_JET.pz(),W_2nd_JET.e());
                                    Wrong_WJets = true;
//
                                }
                            }
                        }
                    }
                }
                
                        
                        
                        m_W_JJ_Pair = m_JJ_Pair;
                        //M_FCNC3Jets = m_3jets;
                        M_FCNC3Jets_Lep0 = m_3jets_Lep0;
                        M_FCNC3Jets_Lep1 = m_3jets_Lep1;
                        
                        Mass_W_Jets ->Fill(m_W_JJ_Pair, weight);
                        Mass_FCNC_top_Lep1 -> Fill(M_FCNC3Jets_Lep1, weight);
                        Mass_FCNC_top_Lep0 -> Fill(M_FCNC3Jets_Lep0, weight);
                        
                        SM_mLep0b_FCNC_3JetsLep1 ->Fill(M_bJet_Lep0,M_FCNC3Jets_Lep1,weight);
                        SM_mLep1b_FCNC_3JetsLep0 ->Fill(M_bJet_Lep1,M_FCNC3Jets_Lep0,weight);
                        SM_mLep0b_FCNC_3JetsLep0 ->Fill(M_bJet_Lep0,M_FCNC3Jets_Lep0,weight);
                        SM_mLep1b_FCNC_3JetsLep1 ->Fill(M_FCNC3Jets_Lep1,M_FCNC3Jets_Lep1,weight);
                        Ratio_FCNC_3JetsLep1_to_SM_mLep0b ->Fill((M_FCNC3Jets_Lep1/M_bJet_Lep0),weight);
                        Ratio_FCNC_3JetsLep0_to_SM_mLep1b ->Fill((M_FCNC3Jets_Lep0/M_bJet_Lep1),weight);
                        Pt_Lep0_vs_Lep1 -> Fill(Leading_lepton.Pt(),second_Leading_lepton.Pt(),weight);
        
                        
                        ////
                        
                        
                        
                        ///// Define new histo for SM, FCNC tops (right, only have PartonMatching, wrong) /////
                        
                        
                        if (Right_CSVLB && Right_SMlep0)
                        {
                            Mass_Rec_SMtop_lep0_rightCombination = (Rec_Leading_Lepton0_SMtop_true_combination+right_Rec_Leading_CSVLB).M();
                            Mass_Gen_SMtop_lep0_rightCombination = (Gen_Leading_Lepton0_SMtop_true_combination+right_Gen_Leading_CSVLB).M();
                            Pt_SMLep0_rightComb_Rec->Fill(Rec_Leading_Lepton0_SMtop_true_combination.Pt(),weight);
                            Pt_SMLep0_rightComb_Gen->Fill(Gen_Leading_Lepton0_SMtop_true_combination.Pt(),weight);
                            Right_SMtop_lep0 = true;
                        }
                        if (Right_CSVLB && Right_SMlep1)
                        {
                            Mass_Rec_SMtop_lep1_rightCombination = (Rec_second_Leading_Lepton1_SMtop_true_combination+right_Rec_Leading_CSVLB).M();
                            Mass_Gen_SMtop_lep1_rightCombination = (Gen_second_Leading_Lepton1_SMtop_true_combination+right_Gen_Leading_CSVLB).M();
                            Pt_SMLep1_rightComb_Rec->Fill(Rec_second_Leading_Lepton1_SMtop_true_combination.Pt(),weight);
                            Pt_SMLep1_rightComb_Gen->Fill(Gen_second_Leading_Lepton1_SMtop_true_combination.Pt(),weight);
                            Right_SMtop_lep1 = true;
                        }
                    
                        if (Wrong_lep0 && Wrong_CSVLB) {
                            Mass_Rec_SMtop_lep0_NoGenMatching = (Wrong_Rec_Leading_Lepton+Wrong_Rec_Leading_CSVLB).M();
                            Wrong_SMtop_lep0 = true;
                        }
                        if (Wrong_CSVLB && Wrong_lep1) {
                            Mass_Rec_SMtop_lep1_NoGenMatching = (Wrong_Rec_2nd_Leading_Lepton+Wrong_Rec_Leading_CSVLB).M();
                            Wrong_SMtop_lep1 = true;
                        }
                        
//                        if (Right_WJets) {
//                            right_Rec_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(W_1St_JET.px(),W_1St_JET.py(),W_1St_JET.pz(),W_1St_JET.e());
//                            right_Rec_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(W_2nd_JET.px(),W_2nd_JET.py(),W_2nd_JET.pz(),W_2nd_JET.e());
//                            right_Gen_1st_JetCandidate_H_FCNCtop.SetPxPyPzE(MC_W_1St_JET->px(),MC_W_1St_JET->py(),MC_W_1St_JET->pz(),MC_W_1St_JET->e());
//                            right_Gen_2nd_JetCandidate_H_FCNCtop.SetPxPyPzE(MC_W_2nd_JET->px(),MC_W_2nd_JET->py(),MC_W_2nd_JET->pz(),MC_W_2nd_JET->e());
//
//                        }
                        
                        if (Right_WJets)
                        {
                            M_Wjets_FCNCTop_rightComb_Rec->Fill((right_Rec_1st_JetCandidate_H_FCNCtop + right_Rec_2nd_JetCandidate_H_FCNCtop).M(),weight);
                            M_Wjets_FCNCTop_rightComb_Gen->Fill((right_Gen_1st_JetCandidate_H_FCNCtop + right_Gen_2nd_JetCandidate_H_FCNCtop).M(),weight);
                            
                        
                            if (Right_Cjets && Right_FCNClep1)
                            {
                                Mass_Rec_FCNCtop_lep1_rightCombination = (right_Rec_CJet + Rec_second_Leading_Lepton1_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop + right_Rec_2nd_JetCandidate_H_FCNCtop).M();
                                Mass_Gen_FCNCtop_lep1_rightCombination = (right_Gen_CJet + Gen_second_Leading_Lepton1_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop + right_Gen_2nd_JetCandidate_H_FCNCtop).M();
                            }
                            if (Right_Cjets && Right_FCNClep0) {
                                Mass_Rec_FCNCtop_lep0_rightCombination = (right_Rec_CJet + Rec_Leading_Lepton0_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop + right_Rec_2nd_JetCandidate_H_FCNCtop).M();
                                Mass_Gen_FCNCtop_lep0_rightCombination = (right_Gen_CJet + Gen_Leading_Lepton0_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop + right_Gen_2nd_JetCandidate_H_FCNCtop).M();
                            }
                        }
//
//                        Mass_Rec_WJets_FCNC_top_rightCombination = Mass_FCNC_WJets_with_right_combination_RecLevel;
//                        Mass_Gen_WJets_FCNC_top_rightCombination = Mass_FCNC_WJets_with_right_combination_GenLevel;
//                        Mass_Rec_WJets_FCNC_top_NoGenMatching = Mass_FCNC_WJets_with_Wrong_combination_RecLevel;
//                        
//                        if (Right_FCNCtop_lep1) {
//                            Mass_Rec_FCNCtop_lep1_rightCombination = Mass_FCNC_top_with_right_combination_lep1_RecLevel;
//                            Mass_Gen_FCNCtop_lep1_rightCombination = Mass_FCNC_top_with_right_combination_lep1_GenLevel;
//                            Pt_FCNCLep1_rightComb_Rec-> Fill(Rec_second_Leading_Lepton1_from_FCNCtop.Pt(),weight);
//                            Pt_FCNCLep1_rightComb_Gen-> Fill(Gen_second_Leading_Lepton1_from_FCNCtop.Pt(),weight);
//                        }
//                        if (Right_FCNCtop_lep0) {
//                            Mass_Rec_FCNCtop_lep0_rightCombination = Mass_FCNC_top_with_right_combination_lep0_RecLevel;
//                            Mass_Gen_FCNCtop_lep0_rightCombination = Mass_FCNC_top_with_right_combination_lep0_GenLevel;
//                        }
//                        if (Wrong_FCNCtop_lep0) {
//                            Mass_Rec_FCNCtop_lep0_NoGenMatching = Mass_FCNC_top_with_Wrong_combination_lep0_RecLevel;
//                            Pt_FCNCLep0_rightComb_Rec-> Fill(Rec_Leading_Lepton0_from_FCNCtop.Pt(),weight);
//                            Pt_FCNCLep0_rightComb_Gen-> Fill(Gen_Leading_Lepton0_from_FCNCtop.Pt(),weight);
//                        }
//                        if (Wrong_FCNCtop_lep1) {
//                            Mass_Rec_FCNCtop_lep1_NoGenMatching = Mass_FCNC_top_with_Wrong_combination_lep1_RecLevel;
//                        }
//                        
//                        
//                        if (Right_WJets)
//                        {
//                            M_Wjets_FCNCTop_rightComb_Rec->Fill(Mass_Rec_WJets_FCNC_top_rightCombination,weight);
//                            M_Wjets_FCNCTop_rightComb_Gen->Fill(Mass_Gen_WJets_FCNC_top_rightCombination,weight);
//                        }
//                        
//                        if (Wrong_WJets) M_Wjets_FCNCTop_WrongComb_NoMC_Rec->Fill(Mass_Rec_WJets_FCNC_top_NoGenMatching,weight);
//                        if (Wrong_lep0) Pt_leading_Lep0_WrongComb_Rec->Fill(Wrong_Rec_Leading_Lepton.Pt(),weight);
//                        if (Wrong_lep1)Pt_second_leading_Lep1_WrongComb_Rec->Fill(Wrong_Rec_2nd_Leading_Lepton.Pt(),weight);
//
//                        
//                        //Pt_FCNCLep1_MCOnly_Rec-> Fill(Rec_lepton1_With_MC.Pt(),weight);
//                        //Pt_FCNCLep1_MCOnly_Gen-> Fill(Gen_lepton1_With_MC.Pt(),weight);
//                        
                        
                        ////2D histogrms after checking genMatching ////
                        
//                        if (Right_SMtop_lep0 && Right_FCNClep1)
//                        {
//                            Mass_Right_SM_lep0_FCNC_lep1_RecLevel->Fill(Mass_Rec_SMtop_lep0_rightCombination,Mass_Rec_FCNCtop_lep1_rightCombination,weight);
//                            Mass_Right_SM_lep0_FCNC_lep1_GenLevel->Fill(Mass_Gen_SMtop_lep0_rightCombination,Mass_Gen_FCNCtop_lep1_rightCombination ,weight);
//                            Pt_SMLep0_to_FCNCLep1_rightComb_Rec->Fill(Rec_Leading_Lepton0_SMtop_true_combination.Pt(),Rec_second_Leading_Lepton1_from_FCNCtop.Pt(),weight);
//                            Pt_SMLep0_to_FCNCLep1_rightComb_Gen->Fill(Gen_Leading_Lepton0_SMtop_true_combination.Pt(),Gen_second_Leading_Lepton1_from_FCNCtop.Pt(),weight);
//                        }
//                        if (Right_SMtop_lep1 && Right_FCNClep0)
//                        {
//                            Mass_Right_SM_lep1_FCNC_lep0_RecLevel->Fill(Mass_Rec_SMtop_lep1_rightCombination,Mass_Rec_FCNCtop_lep0_rightCombination,weight);
//                            Mass_Right_SM_lep1_FCNC_lep0_GenLevel->Fill(Mass_Gen_SMtop_lep1_rightCombination,Mass_Gen_FCNCtop_lep0_rightCombination ,weight);
//                            Pt_SMLep1_to_FCNCLep0_rightComb_Rec->Fill(Rec_second_Leading_Lepton1_SMtop_true_combination.Pt(),Rec_Leading_Lepton0_from_FCNCtop.Pt(),weight);
//                            Pt_SMLep1_to_FCNCLep0_rightComb_Gen->Fill(Gen_second_Leading_Lepton1_SMtop_true_combination.Pt(),Rec_Leading_Lepton0_from_FCNCtop.Pt(),weight);
//
//                        }
//                        
//                        if (Wrong_SMtop_lep0 && Wrong_FCNCtop_lep1)
//                        {
//                            Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel->Fill(Mass_Rec_SMtop_lep0_NoGenMatching,Mass_Rec_SMtop_lep1_NoGenMatching,weight);
//                        }
//                        if (Wrong_SMtop_lep1 && Wrong_FCNCtop_lep0)
//                        {
//                            Mass_Wrong_SM_lep1_FCNC_le0_RecLevel->Fill(Mass_Rec_SMtop_lep1_NoGenMatching,Mass_Rec_FCNCtop_lep0_NoGenMatching,weight);
//                        }
//                        if (Wrong_lep0 && Wrong_lep1) {
//                            Pt_SMLep0_to_FCNCLep1_WrongComb_Rec->Fill(Wrong_Rec_Leading_Lepton.Pt(),Wrong_Rec_2nd_Leading_Lepton.Pt(),weight);
//                        }
//                        
//                        
//                        
//                        
//                        
//                                             //// creation of vectors represent SM , FCNC top systems ////
//                                               ///////////////////////////////////////
//
////                        
//
//                       
//                            SMtop_lep0_rightComb_Rec.SetPxPyPzE((Rec_Leading_Lepton0_SMtop_true_combination + right_Rec_Leading_CSVLB).Px(),(Rec_Leading_Lepton0_SMtop_true_combination + right_Rec_Leading_CSVLB).Py(),(Rec_Leading_Lepton0_SMtop_true_combination + right_Rec_Leading_CSVLB).Pz(),(Rec_Leading_Lepton0_SMtop_true_combination + right_Rec_Leading_CSVLB).E());
//                            
//                            SMtop_lep0_rightComb_Gen.SetPxPyPzE((Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).Px(),(Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).Py(),(Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).Pz(),(Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).E());
//               
//                        
//                        
//                        SMtop_lep1_rightComb_Rec.SetPxPyPzE((Rec_second_Leading_Lepton1_SMtop_true_combination + right_Rec_Leading_CSVLB).Px(),(Rec_second_Leading_Lepton1_SMtop_true_combination + right_Rec_Leading_CSVLB).Py(),(Rec_second_Leading_Lepton1_SMtop_true_combination + right_Rec_Leading_CSVLB).Pz(),(Rec_second_Leading_Lepton1_SMtop_true_combination + right_Rec_Leading_CSVLB).E());
//                        
//                        SMtop_lep1_rightComb_Gen.SetPxPyPzE((Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).Px(),(Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).Py(),(Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).Pz(),(Gen_Leading_Lepton0_SMtop_true_combination + right_Gen_Leading_CSVLB).E());
//                        
//                        SMtop_lep0_WrongComb_Rec.SetPxPyPzE((Wrong_Rec_Leading_Lepton + Wrong_Rec_Leading_CSVLB).Px(),(Wrong_Rec_Leading_Lepton + Wrong_Rec_Leading_CSVLB).Py(),(Wrong_Rec_Leading_Lepton + Wrong_Rec_Leading_CSVLB).Pz(),(Wrong_Rec_Leading_Lepton + Wrong_Rec_Leading_CSVLB).E());
//                        
//                        SMtop_lep1_WrongComb_Rec.SetPxPyPzE((Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_Leading_CSVLB).Px(),(Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_Leading_CSVLB).Py(),(Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_Leading_CSVLB).Pz(),(Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_Leading_CSVLB).E());
//                        
                        /////----- FCNCtop system ---- //////
                        
                        //    TLorentzVector right_Rec_1st_JetCandidate_H_FCNCtop;
                        //    TLorentzVector right_Rec_2nd_JetCandidate_H_FCNCtop;
                        //    TLorentzVector right_Gen_1st_JetCandidate_H_FCNCtop;
                        //    TLorentzVector right_Gen_2nd_JetCandidate_H_FCNCtop;
//
//                        FCNCtop_lep0_rightComb_Rec.SetPxPyPzE((right_Rec_CJet + Rec_Leading_Lepton0_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).Px(),(right_Rec_CJet + Rec_Leading_Lepton0_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).Py(),(right_Rec_CJet + Rec_Leading_Lepton0_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).Pz(),(right_Rec_CJet + Rec_Leading_Lepton0_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).E());
//                        
//                        FCNCtop_lep0_rightComb_Gen.SetPxPyPzE((right_Gen_CJet + Gen_Leading_Lepton0_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop +right_Gen_2nd_JetCandidate_H_FCNCtop).Px(),(right_Gen_CJet + Gen_Leading_Lepton0_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop+right_Gen_2nd_JetCandidate_H_FCNCtop).Py(),(right_Gen_CJet + Gen_Leading_Lepton0_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop+right_Gen_2nd_JetCandidate_H_FCNCtop).Pz(),(right_Gen_CJet + Gen_Leading_Lepton0_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop +right_Gen_2nd_JetCandidate_H_FCNCtop).E());
//                        
//                        FCNCtop_lep1_rightComb_Rec.SetPxPyPzE((right_Rec_CJet + Rec_second_Leading_Lepton1_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop+right_Rec_2nd_JetCandidate_H_FCNCtop).Px(),(right_Rec_CJet + Rec_second_Leading_Lepton1_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).Py(),(right_Rec_CJet + Rec_second_Leading_Lepton1_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).Pz(),(right_Rec_CJet + Rec_second_Leading_Lepton1_from_FCNCtop + right_Rec_1st_JetCandidate_H_FCNCtop +right_Rec_2nd_JetCandidate_H_FCNCtop).E());
//                        
//                        FCNCtop_lep1_rightComb_Gen.SetPxPyPzE((right_Gen_CJet + Gen_second_Leading_Lepton1_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop +right_Gen_2nd_JetCandidate_H_FCNCtop).Px(),(right_Gen_CJet + Gen_second_Leading_Lepton1_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop +right_Gen_2nd_JetCandidate_H_FCNCtop).Py(),(right_Gen_CJet + Gen_second_Leading_Lepton1_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop +right_Gen_2nd_JetCandidate_H_FCNCtop).Pz(),(right_Gen_CJet + Gen_second_Leading_Lepton1_from_FCNCtop + right_Gen_1st_JetCandidate_H_FCNCtop +right_Gen_2nd_JetCandidate_H_FCNCtop).E());
//                        
//                        FCNCtop_lep0_WrongComb_Rec.SetPxPyPzE((Wrong_Rec_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).Px(),(Wrong_Rec_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).Py(),(Wrong_Rec_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).Pz(),(Wrong_Rec_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).E());
//                        
//                        FCNCtop_lep1_WrongComb_Rec.SetPxPyPzE((Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).Px(),(Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).Py(),(Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).Pz(),(Wrong_Rec_2nd_Leading_Lepton + Wrong_Rec_CJet+ Wrong_Rec_1st_JetCandidate_W_FCNCtop+ Wrong_Rec_2nd_JetCandidate_W_FCNCtop).E());
//                        
//                        
//////
//                        
//                        if (Right_SMtop_lep0 && Right_FCNCtop_lep1)
//                        {
//                            DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec->Fill(SMtop_lep0_rightComb_Rec.DeltaPhi(FCNCtop_lep1_rightComb_Rec),weight);
//                            DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen->Fill(SMtop_lep0_rightComb_Gen.DeltaPhi(FCNCtop_lep1_rightComb_Gen),weight);
//                            DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec->Fill(SMtop_lep0_rightComb_Rec.DeltaR(FCNCtop_lep1_rightComb_Rec),weight);
//                            DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen->Fill(SMtop_lep0_rightComb_Gen.DeltaR(FCNCtop_lep1_rightComb_Gen),weight);
//                        }
//                        
//                        if (Right_SMtop_lep1 && Right_FCNCtop_lep0) {
//                            DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec->Fill(SMtop_lep1_rightComb_Rec.DeltaPhi(FCNCtop_lep0_rightComb_Rec),weight);
//                            DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen->Fill(SMtop_lep1_rightComb_Gen.DeltaPhi(FCNCtop_lep0_rightComb_Gen),weight);
//                            DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec->Fill(SMtop_lep1_rightComb_Rec.DeltaR(FCNCtop_lep0_rightComb_Rec),weight);
//                            DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen->Fill(SMtop_lep1_rightComb_Gen.DeltaR(FCNCtop_lep0_rightComb_Gen),weight);
//                        }
//                        
//                        if (Wrong_SMtop_lep0 && Wrong_FCNCtop_lep1)
//                        {
//                            DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC->Fill(SMtop_lep0_WrongComb_Rec.DeltaPhi(FCNCtop_lep1_WrongComb_Rec),weight);
//                            DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC->Fill(SMtop_lep0_WrongComb_Rec.DeltaR(FCNCtop_lep1_WrongComb_Rec),weight);
//                        }
//                        if (Wrong_SMtop_lep1 && Wrong_FCNCtop_lep0) {
//                            DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC->Fill(SMtop_lep1_WrongComb_Rec.DeltaPhi(FCNCtop_lep0_WrongComb_Rec),weight);
//                            DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC->Fill(SMtop_lep1_WrongComb_Rec.DeltaR(FCNCtop_lep0_WrongComb_Rec),weight);
//                        }
//                        
//                        
//                        
//                        
//                        //DeltaPhi_SMtop_FCNCtop_OnlyMC_Rec->Fill(Rec_SMtop_Wrong_NoMC.DeltaPhi(Rec_FCNCtop_Wrong_NoMC),weight);
//                        //DeltaPhi_SMtop_FCNCtop_OnlyMC_Gen->Fill(Rec_SMtop_onlyMC.DeltaPhi(Rec_FCNCtop_onlyMC),weight);
//                        //DeltaR_SMtop_FCNCtop_OnlyMC_Rec->Fill(Rec_SMtop_Wrong_NoMC.DeltaR(Rec_FCNCtop_Wrong_NoMC),weight);
//                        //DeltaR_SMtop_FCNCtop_OnlyMC_Gen->Fill(Rec_SMtop_onlyMC.DeltaR(Rec_FCNCtop_onlyMC),weight);
////
                        
                        //// for global MVA ///
                        sumLep_Pt = Leading_lepton.Pt()+second_Leading_lepton.Pt();
                        St_lep_jets = sumLep_Pt + Ht_all_Jets ;
                        
                        histo_MVA_Ht_Jets->Fill(Ht_all_Jets,weight);
                        histo_MVA_Met->Fill(event.rec()->MET().pt(),weight);
                        histo_MVA_Nb_CSVL_bJets->Fill(selLBJetsColl.size(),weight);
                        histo_MVA_Nb_Jets->Fill(selJetsColl.size(),weight);
                        histo_MVA_DeltaR_2SSLep->Fill(Leading_lepton.DeltaR(second_Leading_lepton),weight);
                        histo_MVA_Delta_Phi_2SSLep->Fill(Leading_lepton.DeltaPhi(second_Leading_lepton),weight);
                        histo_MVA_Lep1_pt_to_Ht_ratio->Fill(second_Leading_lepton.Pt()/Ht_all_Jets,weight);
                        histo_MVA_Mass_Lep0_b->Fill((Leading_lepton + Leading_CSVLB_Jet).M(),weight);
                        histo_MVA_DeltaRmin_Lep0_b->Fill(Leading_lepton.DeltaR(Leading_CSVLB_Jet),weight);
                        histo_MVA_Leading_Lep_Pt->Fill(Leading_lepton.Pt(),weight);
                        histo_MVA_second_Leading_Lep_Pt->Fill(second_Leading_lepton.Pt(),weight);
                        //histo_MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b->Fill(M_FCNC3Jets_Lep1/ M_bJet_Lep0,weight);
                        //histo_MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b->Fill(M_FCNC3Jets_Lep0/ M_bJet_Lep1,weight);
                        histo_MVA_Mass_Lep1_b->Fill((second_Leading_lepton + Leading_CSVLB_Jet).M(),weight);
                        histo_MVA_DeltaRmin_Lep1_b->Fill(second_Leading_lepton.DeltaR(Leading_CSVLB_Jet),weight);
                        //histo_MVA_Mass_FCNC_top_Lep1->Fill(M_FCNC3Jets_Lep1,weight);
                        //histo_MVA_Mass_FCNC_top_Lep0->Fill(M_FCNC3Jets_Lep0,weight);
                        histo_MVA_St->Fill(St_lep_jets,weight);
                        histo_MVA_Sum_lep_Pt->Fill(sumLep_Pt,weight);
                                                
                                                
                        MVA_Ht_Jets = Ht_all_Jets;
                        MVA_Nb_CSVL_bJets = selLBJetsColl.size();
                        MVA_Nb_Jets = selJetsColl.size();
                        MVA_Met = event.rec()->MET().pt();
                        MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b = M_FCNC3Jets_Lep1/ M_bJet_Lep0 ;
                        MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b = M_FCNC3Jets_Lep0/ M_bJet_Lep1 ;
                        MVA_Mass_FCNC_top_Lep1 = M_FCNC3Jets_Lep1;
                        MVA_Mass_FCNC_top_Lep0 = M_FCNC3Jets_Lep0;
                        MVA_St = St_lep_jets;
                        MVA_Sum_lep_Pt = sumLep_Pt;
                        
                        MVA_Leading_Lep_Pt = Leading_lepton.Pt();
                        MVA_second_Leading_Lep_Pt = second_Leading_lepton.Pt();
                        MVA_DeltaR_2SSLep = Leading_lepton.DeltaR(second_Leading_lepton);
                        MVA_Delta_Phi_2SSLep = Leading_lepton.DeltaPhi(second_Leading_lepton);
                        MVA_Lep1_pt_to_Ht_ratio = second_Leading_lepton.Pt()/Ht_all_Jets;
                        MVA_Mass_Lep0_b = (Leading_lepton + Leading_CSVLB_Jet).M();
                        MVA_DeltaRmin_Lep0_b = Leading_lepton.DeltaR(Leading_CSVLB_Jet);
                        MVA_Mass_Lep1_b = (second_Leading_lepton + Leading_CSVLB_Jet).M();
                        MVA_DeltaRmin_Lep1_b = second_Leading_lepton.DeltaR(Leading_CSVLB_Jet);
                        
                        tree -> Fill();
                         
                        }
                    if (Met.Et() >= 40.) {
                        cutFlow->Fill(5.,weight);
                        tree_Met -> Fill();
                    }
                    if (Met.Et() < 70. && Ht_all_Jets > 140.)
                    {
                        cutFlow->Fill(6.,weight);
                        
                    }
                        
                    if (Met.Et() > 70. && Met.Et() < 90. && Ht_all_Jets > 120.)
                    {
                        cutFlow->Fill(7.,weight);
                    }
                    
                }
            }

        }



    }
    
    
    ///////////////////////////////////////////////////////// ***********code is finished ********//////////////////////////////////
    
    return true;
    
}


