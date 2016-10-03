#ifndef analysis_FCNC_2SSL_h
#define analysis_FCNC_2SSL_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"

namespace MA5
{
class FCNC_2SSL : public AnalyzerBase
{
  INIT_ANALYSIS(FCNC_2SSL,"FCNC_2SSL")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
    
    //bool SortLeptonPt(const RecLeptonFormat* lep1, const RecLeptonFormat* lep2);

  //-----------------------------------------
 //-----------------------------------------
 //output root file
 //-----------------------------------------
 //-----------------------------------------
 TFile* output;
 TTree* tree;
    TTree * tree_Met;
 std::string outputName_;
 
 //-----------------------------------------
 //-----------------------------------------
 //histograms
 //-----------------------------------------
 //-----------------------------------------
 TH1F *cutFlow;
 TH1F *Pt_leadingElec_2SSSF;
 TH1F *Pt_2ndleadingElec_2SSSF;
 TH1F *Pt_leadingMuon_2SSSF;
 TH1F *Pt_2ndleadingMuon_2SSSF;
 TH1F *Pt_leadingLepton_2SSOF;
 TH1F *Pt_2ndleadingLepton_2SSOF;
 TH1F *Eta_leadingElec_2SSSF;
 TH1F *Eta_2ndleadingElec_2SSSF;
 TH1F *Eta_leadingMuon_2SSSF;
 TH1F *Eta_2ndleadingMuon_2SSSF;
 TH1F *Eta_leadingLepton_2SSOF;
 TH1F *Eta_2ndleadingLepton_2SSOF;
 TH1F *Phi_leadingElec_2SSSF;
 TH1F *Phi_2ndleadingElec_2SSSF;
 TH1F *Phi_leadingMuon_2SSSF;
 TH1F *Phi_2ndleadingMuon_2SSSF;
 TH1F *Phi_leadingLepton_2SSOF;
 TH1F *Phi_2ndleadingLepton_2SSOF;
 TH1F *Nb_CSVL_bJets_After_Cuts;
 TH1F *Nb_elecs;
 TH1F *Nb_muons;
 TH1F *Nb_Jets;
 TH1F *Nb_CSVL_jets;
 TH1F *Nb_CSVM_jets;
 TH1F *Nb_CSVT_jets;
 TH1F *Pt_1st_Jet;
 TH1F *Pt_2nd_Jet;
 TH1F *Pt_3rd_Jet;
 TH1F *Pt_4th_Jet;
 TH1F *Pt_5th_Jet;
 TH1F *Pt_6th_Jet;
 TH1F *Pt_7th_Jet;
 TH1F *Pt_leading_Jet;
 TH1F *Pt_2ndleading_Jet;
 TH1F *Pt_3rdleading_Jet;
 TH1F *Pt_4thleading_Jet;
 TH1F *Pt_5thleading_Jet;
 TH1F *Pt_6thleading_Jet;
 TH1F *Pt_7thleading_Jet;
 TH1F *Pt_leading_CSVLBJet;
 TH1F *Pt_2nd_leading_CSVLBJet;
 TH1F *Pt_3rd_leading_CSVLBJet;
 TH1F *Ht_Jets;
 TH1F *Elec1_pt_to_Ht_ratio;
 TH1F *Mu1_pt_to_Ht_ratio;
 TH1F *lep1_pt_to_Ht_ratio;
    TH1F *Nb_Jets_after_2SSLep;
 
 TH1F *MET_histo;
 TH1F *Eta_jets;
 TH1F *Phi_jets;
 TH1F *Delta_Phi_2SSElec;
 TH1F *DeltaR_2SSElec;
 TH1F *Delta_Phi_2SSMuon;
 TH1F *DeltaR_2SSMuon;
 TH1F *Delta_Phi_2SSOF;
 TH1F *DeltaR_2SSOF;

TH1F *DeltaRmin_Elec0_b;
TH1F *DeltaRmin_Mu0_b;
 TH1F *DeltaRmin_lep0_b;
 TH1F *Mass_Elec0_b;
 TH1F *Mass_Mu0_b;
 TH1F *Mass_lep0_b;
 TH1F *Mass_W_Jets;
 TH1F *Mass_Jets_Pair;
 TH1F *sumet_isol_elec;
 TH1F *sumet_isol_muon;
 TH1F *sumpt_isol_elec;
 TH1F *sumpt_isol_muon;
 TH1F *comb_isol_elec;
 TH1F *comb_isol_muon;

    TH1F *fakeElectron_Mult;
    TH1F *fakeElectron_Pt;
    TH1F *fakeElectron_Eta;
    TH1F *fakeElectron_Q;
    TH1F* jet_Mult;
    TH1F* cleanjet_Mult;
    TH1F *Ratio_FCNC_3JetsLep0_to_SM_mLep1b;
    TH1F *Ratio_FCNC_3JetsLep1_to_SM_mLep0b;
    TH1F *Mass_FCNC_top_Lep1;
    TH1F *Mass_FCNC_top_Lep0;
    TH1F *Mass_SM_bJet_lep0;
    TH1F *Mass_SM_bJet_lep1;
    
    TH1F *Mlep0b_SMtop_right_Combination_Rec;
    TH1F *Mlep0b_SMtop_right_Combination_gen;
    TH1F *Mlep0b_SMtop_Wrong_Combination_Rec;
    TH1F *Mlep0b_SMtop_withMCOnly_Rec;
    TH1F *Mlep0b_SMtop_withMCOnly_Gen;
    TH1F *Pt_SMLep0_rightComb_Rec;
    TH1F *Pt_SMLep0_rightComb_Gen;
    TH1F *Pt_SMLep1_rightComb_Rec;
    TH1F *Pt_SMLep1_rightComb_Gen;
    TH1F *Pt_leading_Lep0_WrongComb_Rec;
    TH1F *Pt_second_leading_Lep1_WrongComb_Rec;
    
    //TH1F *Pt_SMLep0_MCOnly_Rec;
    //TH1F *Pt_SMLep0_MCOnly_Gen;
    
    TH1F *Mcqqlep1_FCNCtop_right_Combination_Rec;
    TH1F *Mcqqlep1_FCNCtop_right_Combination_gen;
    TH1F *Mcqqlep1_FCNCtop_Wrong_Combination_Rec;
    TH1F *Mcqqlep1_FCNCtop_withMCOnly_Rec;
    TH1F *Mcqqlep1_FCNCtop_withMCOnly_Gen;
    TH1F *Pt_FCNCLep1_rightComb_Rec;
    TH1F *Pt_FCNCLep1_rightComb_Gen;
    TH1F *Pt_FCNCLep0_rightComb_Rec;
    TH1F *Pt_FCNCLep0_rightComb_Gen;
    
    //TH1F *Pt_FCNCLep1_WrongComb_Rec;
    //TH1F *Pt_FCNCLep1_MCOnly_Rec;
    //TH1F *Pt_FCNCLep1_MCOnly_Gen;
    
    TH1F *M_Wjets_FCNCToptoH_rightComb_Rec;
    TH1F *M_Wjets_FCNCToptoH_rightComb_Gen;
    TH1F *M_Wjets_FCNCToptoH_WrongComb_NoMC_Rec;
    TH1F *M_Wjets_FCNCToptoH_onlyMC_Rec;
    TH1F *M_Wjets_FCNCToptoH_onlyMC_Gen;
    
    TH1F *DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Rec;
    TH1F *DeltaPhi_SMtoplep0_FCNCtoplep1_rightComb_Gen;
    TH1F *DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Rec;
    TH1F *DeltaPhi_SMtoplep1_FCNCtoplep0_rightComb_Gen;
    TH1F *DeltaPhi_SMtoplep1_FCNCtoplep0_Wrong_NOMC;
    TH1F *DeltaPhi_SMtoplep0_FCNCtoplep1_Wrong_NOMC;
    
    TH1F *DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Rec;
    TH1F *DeltaR_SMtoplep0_FCNCtoplep1_rightComb_Gen;
    TH1F *DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Rec;
    TH1F *DeltaR_SMtoplep1_FCNCtoplep0_rightComb_Gen;
    TH1F *DeltaR_SMtoplep1_FCNCtoplep0_Wrong_NOMC;
    TH1F *DeltaR_SMtoplep0_FCNCtoplep1_Wrong_NOMC;
    
    
    /////** new histograms **//
    TH1F *M_Wjets_FCNCTop_rightComb_Rec;
    TH1F *M_Wjets_FCNCTop_rightComb_Gen;
    TH1F *M_Wjets_FCNCTop_WrongComb_NoMC_Rec;
    
    
    
//// 2D hstograms ////
    TH2F *Ht_Met_histo;
    TH2F *SM_mLep0b_FCNC_3JetsLep1;
    TH2F *SM_mLep1b_FCNC_3JetsLep0;
    TH2F *SM_mLep0b_FCNC_3JetsLep0;
    TH2F *SM_mLep1b_FCNC_3JetsLep1;
    TH2F *Pt_Lep0_vs_Lep1;
    
    TH2F *Mass_Right_SM_lep0_FCNC_lep1_RecLevel;
    TH2F *Mass_Right_SM_lep0_FCNC_lep1_GenLevel;
    TH2F *Mass_Right_SM_lep1_FCNC_lep0_RecLevel;
    TH2F *Mass_Right_SM_lep1_FCNC_lep0_GenLevel;
    TH2F *Mass_Wrong_SM_lep0_FCNC_lep1_RecLevel;
    TH2F *Mass_Wrong_SM_lep1_FCNC_le0_RecLevel;
    
    TH2F *Pt_SMLep0_to_FCNCLep1_rightComb_Rec;
    TH2F *Pt_SMLep0_to_FCNCLep1_rightComb_Gen;
    TH2F *Pt_SMLep1_to_FCNCLep0_rightComb_Rec;
    TH2F *Pt_SMLep1_to_FCNCLep0_rightComb_Gen;
    TH2F *Pt_SMLep0_to_FCNCLep1_WrongComb_Rec;

    TH1F *histo_MVA_Ht_Jets;
    TH1F *histo_MVA_Met;
    TH1F *histo_MVA_Nb_CSVL_bJets;
    TH1F *histo_MVA_Nb_Jets;
    TH1F *histo_MVA_DeltaR_2SSLep;
    TH1F *histo_MVA_Delta_Phi_2SSLep;
    TH1F *histo_MVA_Lep1_pt_to_Ht_ratio;
    TH1F *histo_MVA_Mass_Lep0_b;
    TH1F *histo_MVA_DeltaRmin_Lep0_b;
    TH1F *histo_MVA_Leading_Lep_Pt;
    TH1F *histo_MVA_second_Leading_Lep_Pt;
    TH1F *histo_MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b;
    TH1F *histo_MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b;
    TH1F *histo_MVA_Mass_Lep1_b;
    TH1F *histo_MVA_DeltaRmin_Lep1_b;
    TH1F *histo_MVA_Mass_FCNC_top_Lep1;
    TH1F *histo_MVA_Mass_FCNC_top_Lep0;
    TH1F *histo_MVA_St;
    TH1F *histo_MVA_Sum_lep_Pt;
 
 // MVA Variables
 
    float MVA_Ht_Jets;
    float MVA_DeltaR_2SSElec;
    float MVA_Delta_Phi_2SSElec;
    float MVA_Elec1_pt_to_Ht_ratio;
    float MVA_Mass_Elec0_b;
    float MVA_DeltaR_2SSMuon;
    float MVA_Delta_Phi_2SSMuon;
    float MVA_Mu1_pt_to_Ht_ratio;
    float MVA_Mass_Mu0_b;
    float MVA_DeltaR_2SSOF;
    float MVA_Delta_Phi_2SSOF;
    float MVA_lep1_pt_to_Ht_ratio;
    float MVA_Mass_lep0_b;
    float MVA_Met;
    float MVA_DeltaRmin_Elec0_b;
    float MVA_DeltaRmin_Mu0_b;
    float MVA_DeltaRmin_lep0_b;
    float MVA_Nb_CSVL_bJets;
    float MVA_Nb_Jets;
    float MVA_DeltaR_2SSLep;
    float MVA_Delta_Phi_2SSLep;
    float MVA_Lep1_pt_to_Ht_ratio;
    float MVA_Mass_Lep0_b;
    float MVA_DeltaRmin_Lep0_b;
    float MVA_Leading_Lep_Pt;
    float MVA_second_Leading_Lep_Pt;
    float MVA_Ratio_FCNC_3JetsLep1_to_SM_mLep0b;
    float MVA_Ratio_FCNC_3JetsLep0_to_SM_mLep1b;
    float MVA_Mass_Lep1_b;
    float MVA_DeltaRmin_Lep1_b;
    float MVA_Mass_FCNC_top_Lep1;
    float MVA_Mass_FCNC_top_Lep0;
    float  MVA_St;
    float MVA_Sum_lep_Pt;
    
 
  //-----------------------------------------
  //-----------------------------------------
  //for MC reweighting
  //-----------------------------------------
  //-----------------------------------------
  float xsec;
  float nevent;
  float luminosity;
  float weight;
    bool debug;
    float nb_of_fakeElectron;
    float nb_of_removed_jets;
    
    
    float nb_events_after_2SSL;
    float nb_events_after_2SSL_4Jets;
    float nb_events_after_2SSL_4Jets_1CSVLB;
    float nb_events_AllCuts_without_CHeckMC;
    float nb_events_AllCuts_MC_Right_CSVLB;
    float nb_events_AllCuts_MC_Wrong_CSVLB;
    float nb_events_AllCuts_MC_CSVLB;
    float nb_events_AllCuts_MC_Right_2SSL;
    float nb_events_AllCuts_MC_2SSL;
    float nb_events_AllCuts_MC_Wrong_2SSL;
    float nb_events_AllCuts_MC_Right_C;
    float nb_events_AllCuts_MC_Wrong_C;
    float nb_events_AllCuts_MC_C;
    float nb_events_AllCuts_MC_Right_FCNC_Wjets;
    float nb_events_AllCuts_MC_Wrong_FCNC_Wjets;
    float nb_events_AllCuts_MC_FCNC_Wjets;
    float nb_events_after_lep0_from_FCNCtop;
    float nb_events_after_lep0_from_SMtop;
    float nb_events_after_lep1_from_FCNCtop;
    float nb_events_after_lep1_from_SMtop;
    float nb_Elecs_before_misid;
    float nb_Elecs_after_misid;

    
    
};
}

#endif
