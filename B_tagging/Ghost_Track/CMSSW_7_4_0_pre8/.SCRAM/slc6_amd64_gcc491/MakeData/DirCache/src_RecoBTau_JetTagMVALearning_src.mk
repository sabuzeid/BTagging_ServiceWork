ifeq ($(strip $(RecoBTau/JetTagMVALearning)),)
ALL_COMMONRULES += src_RecoBTau_JetTagMVALearning_src
src_RecoBTau_JetTagMVALearning_src_parent := RecoBTau/JetTagMVALearning
src_RecoBTau_JetTagMVALearning_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_RecoBTau_JetTagMVALearning_src,src/RecoBTau/JetTagMVALearning/src,LIBRARY))
RecoBTauJetTagMVALearning := self/RecoBTau/JetTagMVALearning
RecoBTau/JetTagMVALearning := RecoBTauJetTagMVALearning
RecoBTauJetTagMVALearning_files := $(patsubst src/RecoBTau/JetTagMVALearning/src/%,%,$(wildcard $(foreach dir,src/RecoBTau/JetTagMVALearning/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
RecoBTauJetTagMVALearning_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoBTau/JetTagMVALearning/BuildFile
RecoBTauJetTagMVALearning_LOC_USE := self  FWCore/Framework FWCore/ParameterSet FWCore/Utilities CondFormats/DataRecord CondFormats/PhysicsToolsObjects PhysicsTools/MVATrainer DataFormats/BTauReco RecoBTau/JetTagComputer SimDataFormats/JetMatching
RecoBTauJetTagMVALearning_EX_LIB   := RecoBTauJetTagMVALearning
RecoBTauJetTagMVALearning_EX_USE   := $(foreach d,$(RecoBTauJetTagMVALearning_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
RecoBTauJetTagMVALearning_PACKAGE := self/src/RecoBTau/JetTagMVALearning/src
ALL_PRODS += RecoBTauJetTagMVALearning
RecoBTauJetTagMVALearning_CLASS := LIBRARY
RecoBTau/JetTagMVALearning_forbigobj+=RecoBTauJetTagMVALearning
RecoBTauJetTagMVALearning_INIT_FUNC        += $$(eval $$(call Library,RecoBTauJetTagMVALearning,src/RecoBTau/JetTagMVALearning/src,src_RecoBTau_JetTagMVALearning_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
