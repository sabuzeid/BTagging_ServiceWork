ifeq ($(strip $(Validation/RecoB)),)
ALL_COMMONRULES += src_Validation_RecoB_src
src_Validation_RecoB_src_parent := Validation/RecoB
src_Validation_RecoB_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_Validation_RecoB_src,src/Validation/RecoB/src,LIBRARY))
ValidationRecoB := self/Validation/RecoB
Validation/RecoB := ValidationRecoB
ValidationRecoB_files := $(patsubst src/Validation/RecoB/src/%,%,$(wildcard $(foreach dir,src/Validation/RecoB/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
ValidationRecoB_BuildFile    := $(WORKINGDIR)/cache/bf/src/Validation/RecoB/BuildFile
ValidationRecoB_LOC_USE := self  root rootcore DataFormats/BTauReco DataFormats/Common DQMServices/Core FWCore/Framework FWCore/ParameterSet FWCore/Utilities
ValidationRecoB_EX_LIB   := ValidationRecoB
ValidationRecoB_EX_USE   := $(foreach d,$(ValidationRecoB_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ValidationRecoB_PACKAGE := self/src/Validation/RecoB/src
ALL_PRODS += ValidationRecoB
ValidationRecoB_CLASS := LIBRARY
Validation/RecoB_forbigobj+=ValidationRecoB
ValidationRecoB_INIT_FUNC        += $$(eval $$(call Library,ValidationRecoB,src/Validation/RecoB/src,src_Validation_RecoB_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(DQMOffline/RecoB)),)
ALL_COMMONRULES += src_DQMOffline_RecoB_src
src_DQMOffline_RecoB_src_parent := DQMOffline/RecoB
src_DQMOffline_RecoB_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_src,src/DQMOffline/RecoB/src,LIBRARY))
DQMOfflineRecoB := self/DQMOffline/RecoB
DQMOffline/RecoB := DQMOfflineRecoB
DQMOfflineRecoB_files := $(patsubst src/DQMOffline/RecoB/src/%,%,$(wildcard $(foreach dir,src/DQMOffline/RecoB/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
DQMOfflineRecoB_BuildFile    := $(WORKINGDIR)/cache/bf/src/DQMOffline/RecoB/BuildFile
DQMOfflineRecoB_LOC_USE := self  DataFormats/BTauReco DataFormats/Common DataFormats/JetReco DataFormats/TrackReco SimDataFormats/JetMatching FWCore/Framework FWCore/ParameterSet CondFormats/DataRecord RecoBTau/JetTagComputer rootcore DQMServices/Core rootgpad JetMETCorrections/Objects boost
DQMOfflineRecoB_EX_LIB   := DQMOfflineRecoB
DQMOfflineRecoB_EX_USE   := $(foreach d,$(DQMOfflineRecoB_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
DQMOfflineRecoB_PACKAGE := self/src/DQMOffline/RecoB/src
ALL_PRODS += DQMOfflineRecoB
DQMOfflineRecoB_CLASS := LIBRARY
DQMOffline/RecoB_forbigobj+=DQMOfflineRecoB
DQMOfflineRecoB_INIT_FUNC        += $$(eval $$(call Library,DQMOfflineRecoB,src/DQMOffline/RecoB/src,src_DQMOffline_RecoB_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(RecoBTauJetTagMVALearningPlugins)),)
RecoBTauJetTagMVALearningPlugins := self/src/RecoBTau/JetTagMVALearning/plugins
PLUGINS:=yes
RecoBTauJetTagMVALearningPlugins_files := $(patsubst src/RecoBTau/JetTagMVALearning/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/RecoBTau/JetTagMVALearning/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoBTau/JetTagMVALearning/plugins/$(file). Please fix src/RecoBTau/JetTagMVALearning/plugins/BuildFile.))))
RecoBTauJetTagMVALearningPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoBTau/JetTagMVALearning/plugins/BuildFile
RecoBTauJetTagMVALearningPlugins_LOC_USE := self  CondFormats/DataRecord CondFormats/PhysicsToolsObjects DataFormats/BTauReco FWCore/Framework FWCore/ParameterSet FWCore/ServiceRegistry FWCore/Utilities PhysicsTools/MVATrainer RecoBTau/JetTagComputer SimDataFormats/JetMatching
RecoBTauJetTagMVALearningPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoBTauJetTagMVALearningPlugins,RecoBTauJetTagMVALearningPlugins,$(SCRAMSTORENAME_LIB),src/RecoBTau/JetTagMVALearning/plugins))
RecoBTauJetTagMVALearningPlugins_PACKAGE := self/src/RecoBTau/JetTagMVALearning/plugins
ALL_PRODS += RecoBTauJetTagMVALearningPlugins
RecoBTau/JetTagMVALearning_forbigobj+=RecoBTauJetTagMVALearningPlugins
RecoBTauJetTagMVALearningPlugins_INIT_FUNC        += $$(eval $$(call Library,RecoBTauJetTagMVALearningPlugins,src/RecoBTau/JetTagMVALearning/plugins,src_RecoBTau_JetTagMVALearning_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
RecoBTauJetTagMVALearningPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoBTauJetTagMVALearningPlugins,src/RecoBTau/JetTagMVALearning/plugins))
endif
ALL_COMMONRULES += src_RecoBTau_JetTagMVALearning_plugins
src_RecoBTau_JetTagMVALearning_plugins_parent := RecoBTau/JetTagMVALearning
src_RecoBTau_JetTagMVALearning_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoBTau_JetTagMVALearning_plugins,src/RecoBTau/JetTagMVALearning/plugins,PLUGINS))
ifeq ($(strip $(ValidationRecoBPlugins)),)
ValidationRecoBPlugins := self/src/Validation/RecoB/plugins
PLUGINS:=yes
ValidationRecoBPlugins_files := $(patsubst src/Validation/RecoB/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/Validation/RecoB/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/Validation/RecoB/plugins/$(file). Please fix src/Validation/RecoB/plugins/BuildFile.))))
ValidationRecoBPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/Validation/RecoB/plugins/BuildFile
ValidationRecoBPlugins_LOC_USE := self  FWCore/Framework FWCore/ParameterSet FWCore/Utilities DataFormats/Common DataFormats/Math DataFormats/VertexReco DataFormats/BTauReco CommonTools/Statistics TrackingTools/TransientTrack SimGeneral/HepPDTRecord SimTracker/Records SimTracker/TrackAssociation SimTracker/TrackerHitAssociation SimTracker/VertexAssociation SimTracker/TrackHistory PhysicsTools/Utilities DQMServices/Core DQMOffline/RecoB Validation/RecoB boost clhep rootcore root
ValidationRecoBPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,ValidationRecoBPlugins,ValidationRecoBPlugins,$(SCRAMSTORENAME_LIB),src/Validation/RecoB/plugins))
ValidationRecoBPlugins_PACKAGE := self/src/Validation/RecoB/plugins
ALL_PRODS += ValidationRecoBPlugins
Validation/RecoB_forbigobj+=ValidationRecoBPlugins
ValidationRecoBPlugins_INIT_FUNC        += $$(eval $$(call Library,ValidationRecoBPlugins,src/Validation/RecoB/plugins,src_Validation_RecoB_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
ValidationRecoBPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,ValidationRecoBPlugins,src/Validation/RecoB/plugins))
endif
ALL_COMMONRULES += src_Validation_RecoB_plugins
src_Validation_RecoB_plugins_parent := Validation/RecoB
src_Validation_RecoB_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_Validation_RecoB_plugins,src/Validation/RecoB/plugins,PLUGINS))
ifeq ($(strip $(DQMOfflineRecoBPlugins)),)
DQMOfflineRecoBPlugins := self/src/DQMOffline/RecoB/plugins
PLUGINS:=yes
DQMOfflineRecoBPlugins_files := $(patsubst src/DQMOffline/RecoB/plugins/%,%,$(foreach file,BTagPerformanceAnalyzerOnData.cc PrimaryVertexMonitor.cc BTagPerformanceHarvester.cc,$(eval xfile:=$(wildcard src/DQMOffline/RecoB/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/DQMOffline/RecoB/plugins/$(file). Please fix src/DQMOffline/RecoB/plugins/BuildFile.))))
DQMOfflineRecoBPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/DQMOffline/RecoB/plugins/BuildFile
DQMOfflineRecoBPlugins_LOC_USE := self  root DQMOffline/RecoB DQMServices/Core CommonTools/Statistics
DQMOfflineRecoBPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,DQMOfflineRecoBPlugins,DQMOfflineRecoBPlugins,$(SCRAMSTORENAME_LIB),src/DQMOffline/RecoB/plugins))
DQMOfflineRecoBPlugins_PACKAGE := self/src/DQMOffline/RecoB/plugins
ALL_PRODS += DQMOfflineRecoBPlugins
DQMOffline/RecoB_forbigobj+=DQMOfflineRecoBPlugins
DQMOfflineRecoBPlugins_INIT_FUNC        += $$(eval $$(call Library,DQMOfflineRecoBPlugins,src/DQMOffline/RecoB/plugins,src_DQMOffline_RecoB_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
DQMOfflineRecoBPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,DQMOfflineRecoBPlugins,src/DQMOffline/RecoB/plugins))
endif
ALL_COMMONRULES += src_DQMOffline_RecoB_plugins
src_DQMOffline_RecoB_plugins_parent := DQMOffline/RecoB
src_DQMOffline_RecoB_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_plugins,src/DQMOffline/RecoB/plugins,PLUGINS))
ifeq ($(strip $(PhysicsTools/MVATrainer)),)
ALL_COMMONRULES += src_PhysicsTools_MVATrainer_src
src_PhysicsTools_MVATrainer_src_parent := PhysicsTools/MVATrainer
src_PhysicsTools_MVATrainer_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PhysicsTools_MVATrainer_src,src/PhysicsTools/MVATrainer/src,LIBRARY))
PhysicsToolsMVATrainer := self/PhysicsTools/MVATrainer
PhysicsTools/MVATrainer := PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_files := $(patsubst src/PhysicsTools/MVATrainer/src/%,%,$(wildcard $(foreach dir,src/PhysicsTools/MVATrainer/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PhysicsToolsMVATrainer_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/BuildFile
PhysicsToolsMVATrainer_LOC_USE := self  FWCore/Framework FWCore/ParameterSet FWCore/ServiceRegistry FWCore/Utilities FWCore/Concurrency CondFormats/PhysicsToolsObjects CondCore/DBOutputService PhysicsTools/MVAComputer boost rootcore roothistmatrix xerces-c
PhysicsToolsMVATrainer_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsMVATrainerCapabilities,PhysicsToolsMVATrainer,$(SCRAMSTORENAME_LIB),src/PhysicsTools/MVATrainer/src))
PhysicsToolsMVATrainer_LCGDICTS  := x 
PhysicsToolsMVATrainer_PRE_INIT_FUNC += $$(eval $$(call LCGDict,PhysicsToolsMVATrainer,src/PhysicsTools/MVATrainer/src/classes.h,src/PhysicsTools/MVATrainer/src/classes_def.xml,$(SCRAMSTORENAME_LIB),$(GENREFLEX_ARGS) --fail_on_warnings,Capabilities))
PhysicsToolsMVATrainer_EX_LIB   := PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_EX_USE   := $(foreach d,$(PhysicsToolsMVATrainer_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PhysicsToolsMVATrainer_PACKAGE := self/src/PhysicsTools/MVATrainer/src
ALL_PRODS += PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_CLASS := LIBRARY
PhysicsTools/MVATrainer_forbigobj+=PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsMVATrainer,src/PhysicsTools/MVATrainer/src,src_PhysicsTools_MVATrainer_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(PhysicsToolsJetMCAlgosPlugins)),)
PhysicsToolsJetMCAlgosPlugins := self/src/PhysicsTools/JetMCAlgos/plugins
PLUGINS:=yes
PhysicsToolsJetMCAlgosPlugins_files := $(patsubst src/PhysicsTools/JetMCAlgos/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/PhysicsTools/JetMCAlgos/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/JetMCAlgos/plugins/$(file). Please fix src/PhysicsTools/JetMCAlgos/plugins/BuildFile.))))
PhysicsToolsJetMCAlgosPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/plugins/BuildFile
PhysicsToolsJetMCAlgosPlugins_LOC_USE := self  FWCore/Framework FWCore/PluginManager FWCore/ParameterSet CommonTools/Utils PhysicsTools/JetMCAlgos PhysicsTools/JetMCUtils PhysicsTools/HepMCCandAlgos SimDataFormats/JetMatching SimDataFormats/GeneratorProducts DataFormats/HepMCCandidate fastjet
PhysicsToolsJetMCAlgosPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsJetMCAlgosPlugins,PhysicsToolsJetMCAlgosPlugins,$(SCRAMSTORENAME_LIB),src/PhysicsTools/JetMCAlgos/plugins))
PhysicsToolsJetMCAlgosPlugins_PACKAGE := self/src/PhysicsTools/JetMCAlgos/plugins
ALL_PRODS += PhysicsToolsJetMCAlgosPlugins
PhysicsTools/JetMCAlgos_forbigobj+=PhysicsToolsJetMCAlgosPlugins
PhysicsToolsJetMCAlgosPlugins_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsJetMCAlgosPlugins,src/PhysicsTools/JetMCAlgos/plugins,src_PhysicsTools_JetMCAlgos_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
PhysicsToolsJetMCAlgosPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PhysicsToolsJetMCAlgosPlugins,src/PhysicsTools/JetMCAlgos/plugins))
endif
ALL_COMMONRULES += src_PhysicsTools_JetMCAlgos_plugins
src_PhysicsTools_JetMCAlgos_plugins_parent := PhysicsTools/JetMCAlgos
src_PhysicsTools_JetMCAlgos_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_JetMCAlgos_plugins,src/PhysicsTools/JetMCAlgos/plugins,PLUGINS))
ifeq ($(strip $(PhysicsToolsMVATrainerProcMLP)),)
PhysicsToolsMVATrainerProcMLP := self/src/PhysicsTools/MVATrainer/plugins
PLUGINS:=yes
PhysicsToolsMVATrainerProcMLP_files := $(patsubst src/PhysicsTools/MVATrainer/plugins/%,%,$(foreach file,ProcMLP.cc MLP*.cc mlp*.cc,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/plugins/$(file). Please fix src/PhysicsTools/MVATrainer/plugins/BuildFile.))))
PhysicsToolsMVATrainerProcMLP_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/plugins/BuildFile
PhysicsToolsMVATrainerProcMLP_LOC_LIB   := lapack
PhysicsToolsMVATrainerProcMLP_LOC_USE := self  FWCore/Framework PhysicsTools/MVAComputer PhysicsTools/MVATrainer
PhysicsToolsMVATrainerProcMLP_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsMVATrainerProcMLP,PhysicsToolsMVATrainerProcMLP,$(SCRAMSTORENAME_LIB),src/PhysicsTools/MVATrainer/plugins))
PhysicsToolsMVATrainerProcMLP_PACKAGE := self/src/PhysicsTools/MVATrainer/plugins
ALL_PRODS += PhysicsToolsMVATrainerProcMLP
PhysicsTools/MVATrainer_forbigobj+=PhysicsToolsMVATrainerProcMLP
PhysicsToolsMVATrainerProcMLP_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsMVATrainerProcMLP,src/PhysicsTools/MVATrainer/plugins,src_PhysicsTools_MVATrainer_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
PhysicsToolsMVATrainerProcMLP_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PhysicsToolsMVATrainerProcMLP,src/PhysicsTools/MVATrainer/plugins))
endif
ifeq ($(strip $(PhysicsToolsMVATrainerProcTMVA)),)
PhysicsToolsMVATrainerProcTMVA := self/src/PhysicsTools/MVATrainer/plugins
PLUGINS:=yes
PhysicsToolsMVATrainerProcTMVA_files := $(patsubst src/PhysicsTools/MVATrainer/plugins/%,%,$(foreach file,ProcTMVA.cc,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/plugins/$(file). Please fix src/PhysicsTools/MVATrainer/plugins/BuildFile.))))
PhysicsToolsMVATrainerProcTMVA_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/plugins/BuildFile
PhysicsToolsMVATrainerProcTMVA_LOC_USE := self  FWCore/Framework PhysicsTools/MVAComputer PhysicsTools/MVATrainer roottmva
PhysicsToolsMVATrainerProcTMVA_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsMVATrainerProcTMVA,PhysicsToolsMVATrainerProcTMVA,$(SCRAMSTORENAME_LIB),src/PhysicsTools/MVATrainer/plugins))
PhysicsToolsMVATrainerProcTMVA_PACKAGE := self/src/PhysicsTools/MVATrainer/plugins
ALL_PRODS += PhysicsToolsMVATrainerProcTMVA
PhysicsTools/MVATrainer_forbigobj+=PhysicsToolsMVATrainerProcTMVA
PhysicsToolsMVATrainerProcTMVA_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsMVATrainerProcTMVA,src/PhysicsTools/MVATrainer/plugins,src_PhysicsTools_MVATrainer_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
PhysicsToolsMVATrainerProcTMVA_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PhysicsToolsMVATrainerProcTMVA,src/PhysicsTools/MVATrainer/plugins))
endif
ifeq ($(strip $(PhysicsToolsMVATrainerPlugins)),)
PhysicsToolsMVATrainerPlugins := self/src/PhysicsTools/MVATrainer/plugins
PLUGINS:=yes
PhysicsToolsMVATrainerPlugins_files := $(patsubst src/PhysicsTools/MVATrainer/plugins/%,%,$(foreach file,module.cc,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/plugins/$(file). Please fix src/PhysicsTools/MVATrainer/plugins/BuildFile.))))
PhysicsToolsMVATrainerPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/plugins/BuildFile
PhysicsToolsMVATrainerPlugins_LOC_USE := self  FWCore/Framework PhysicsTools/MVAComputer PhysicsTools/MVATrainer
PhysicsToolsMVATrainerPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsMVATrainerPlugins,PhysicsToolsMVATrainerPlugins,$(SCRAMSTORENAME_LIB),src/PhysicsTools/MVATrainer/plugins))
PhysicsToolsMVATrainerPlugins_PACKAGE := self/src/PhysicsTools/MVATrainer/plugins
ALL_PRODS += PhysicsToolsMVATrainerPlugins
PhysicsTools/MVATrainer_forbigobj+=PhysicsToolsMVATrainerPlugins
PhysicsToolsMVATrainerPlugins_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsMVATrainerPlugins,src/PhysicsTools/MVATrainer/plugins,src_PhysicsTools_MVATrainer_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
PhysicsToolsMVATrainerPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PhysicsToolsMVATrainerPlugins,src/PhysicsTools/MVATrainer/plugins))
endif
ALL_COMMONRULES += src_PhysicsTools_MVATrainer_plugins
src_PhysicsTools_MVATrainer_plugins_parent := PhysicsTools/MVATrainer
src_PhysicsTools_MVATrainer_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_MVATrainer_plugins,src/PhysicsTools/MVATrainer/plugins,PLUGINS))
ifeq ($(strip $(PhysicsTools/JetMCAlgos)),)
ALL_COMMONRULES += src_PhysicsTools_JetMCAlgos_src
src_PhysicsTools_JetMCAlgos_src_parent := PhysicsTools/JetMCAlgos
src_PhysicsTools_JetMCAlgos_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PhysicsTools_JetMCAlgos_src,src/PhysicsTools/JetMCAlgos/src,LIBRARY))
PhysicsToolsJetMCAlgos := self/PhysicsTools/JetMCAlgos
PhysicsTools/JetMCAlgos := PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_files := $(patsubst src/PhysicsTools/JetMCAlgos/src/%,%,$(wildcard $(foreach dir,src/PhysicsTools/JetMCAlgos/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PhysicsToolsJetMCAlgos_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/BuildFile
PhysicsToolsJetMCAlgos_LOC_USE := self  FWCore/Framework FWCore/PluginManager FWCore/ParameterSet PhysicsTools/JetMCUtils
PhysicsToolsJetMCAlgos_EX_LIB   := PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_EX_USE   := $(foreach d,$(PhysicsToolsJetMCAlgos_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PhysicsToolsJetMCAlgos_PACKAGE := self/src/PhysicsTools/JetMCAlgos/src
ALL_PRODS += PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_CLASS := LIBRARY
PhysicsTools/JetMCAlgos_forbigobj+=PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsJetMCAlgos,src/PhysicsTools/JetMCAlgos/src,src_PhysicsTools_JetMCAlgos_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
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
ifeq ($(strip $(RecoBTagSecondaryVertexESProducers)),)
RecoBTagSecondaryVertexESProducers := self/src/RecoBTag/SecondaryVertex/plugins
PLUGINS:=yes
RecoBTagSecondaryVertexESProducers_files := $(patsubst src/RecoBTag/SecondaryVertex/plugins/%,%,$(foreach file,JetTagESProducers.cc,$(eval xfile:=$(wildcard src/RecoBTag/SecondaryVertex/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoBTag/SecondaryVertex/plugins/$(file). Please fix src/RecoBTag/SecondaryVertex/plugins/BuildFile.))))
RecoBTagSecondaryVertexESProducers_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoBTag/SecondaryVertex/plugins/BuildFile
RecoBTagSecondaryVertexESProducers_LOC_USE := self  FWCore/Framework FWCore/MessageLogger FWCore/ParameterSet FWCore/Utilities DataFormats/GeometryCommonDetAlgo DataFormats/TrackReco DataFormats/VertexReco DataFormats/BTauReco RecoBTag/SecondaryVertex boost RecoBTau/JetTagComputer
RecoBTagSecondaryVertexESProducers_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoBTagSecondaryVertexESProducers,RecoBTagSecondaryVertexESProducers,$(SCRAMSTORENAME_LIB),src/RecoBTag/SecondaryVertex/plugins))
RecoBTagSecondaryVertexESProducers_PACKAGE := self/src/RecoBTag/SecondaryVertex/plugins
ALL_PRODS += RecoBTagSecondaryVertexESProducers
RecoBTag/SecondaryVertex_forbigobj+=RecoBTagSecondaryVertexESProducers
RecoBTagSecondaryVertexESProducers_INIT_FUNC        += $$(eval $$(call Library,RecoBTagSecondaryVertexESProducers,src/RecoBTag/SecondaryVertex/plugins,src_RecoBTag_SecondaryVertex_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
RecoBTagSecondaryVertexESProducers_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoBTagSecondaryVertexESProducers,src/RecoBTag/SecondaryVertex/plugins))
endif
ifeq ($(strip $(RecoBTagSecondaryVertexProducer)),)
RecoBTagSecondaryVertexProducer := self/src/RecoBTag/SecondaryVertex/plugins
PLUGINS:=yes
RecoBTagSecondaryVertexProducer_files := $(patsubst src/RecoBTag/SecondaryVertex/plugins/%,%,$(foreach file,TemplatedSecondaryVertexProducer.cc BVertexFilter.cc BtoCharmDecayVertexMerger.cc,$(eval xfile:=$(wildcard src/RecoBTag/SecondaryVertex/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoBTag/SecondaryVertex/plugins/$(file). Please fix src/RecoBTag/SecondaryVertex/plugins/BuildFile.))))
RecoBTagSecondaryVertexProducer_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoBTag/SecondaryVertex/plugins/BuildFile
RecoBTagSecondaryVertexProducer_LOC_USE := self  FWCore/Framework FWCore/MessageLogger FWCore/ParameterSet FWCore/Utilities DataFormats/GeometryCommonDetAlgo DataFormats/TrackReco DataFormats/VertexReco DataFormats/BTauReco RecoBTag/SecondaryVertex boost DataFormats/BeamSpot TrackingTools/Records TrackingTools/TransientTrack RecoVertex/ConfigurableVertexReco RecoVertex/GhostTrackFitter fastjet
RecoBTagSecondaryVertexProducer_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoBTagSecondaryVertexProducer,RecoBTagSecondaryVertexProducer,$(SCRAMSTORENAME_LIB),src/RecoBTag/SecondaryVertex/plugins))
RecoBTagSecondaryVertexProducer_PACKAGE := self/src/RecoBTag/SecondaryVertex/plugins
ALL_PRODS += RecoBTagSecondaryVertexProducer
RecoBTag/SecondaryVertex_forbigobj+=RecoBTagSecondaryVertexProducer
RecoBTagSecondaryVertexProducer_INIT_FUNC        += $$(eval $$(call Library,RecoBTagSecondaryVertexProducer,src/RecoBTag/SecondaryVertex/plugins,src_RecoBTag_SecondaryVertex_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
RecoBTagSecondaryVertexProducer_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoBTagSecondaryVertexProducer,src/RecoBTag/SecondaryVertex/plugins))
endif
ALL_COMMONRULES += src_RecoBTag_SecondaryVertex_plugins
src_RecoBTag_SecondaryVertex_plugins_parent := RecoBTag/SecondaryVertex
src_RecoBTag_SecondaryVertex_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoBTag_SecondaryVertex_plugins,src/RecoBTag/SecondaryVertex/plugins,PLUGINS))
ifeq ($(strip $(RecoBTag/SecondaryVertex)),)
ALL_COMMONRULES += src_RecoBTag_SecondaryVertex_src
src_RecoBTag_SecondaryVertex_src_parent := RecoBTag/SecondaryVertex
src_RecoBTag_SecondaryVertex_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_RecoBTag_SecondaryVertex_src,src/RecoBTag/SecondaryVertex/src,LIBRARY))
RecoBTagSecondaryVertex := self/RecoBTag/SecondaryVertex
RecoBTag/SecondaryVertex := RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_files := $(patsubst src/RecoBTag/SecondaryVertex/src/%,%,$(wildcard $(foreach dir,src/RecoBTag/SecondaryVertex/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
RecoBTagSecondaryVertex_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoBTag/SecondaryVertex/BuildFile
RecoBTagSecondaryVertex_LOC_USE := self  FWCore/ParameterSet FWCore/Utilities DataFormats/Math DataFormats/TrackReco DataFormats/VertexReco DataFormats/BTauReco DataFormats/PatCandidates RecoVertex/VertexTools rootmath
RecoBTagSecondaryVertex_EX_LIB   := RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_EX_USE   := $(foreach d,$(RecoBTagSecondaryVertex_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
RecoBTagSecondaryVertex_PACKAGE := self/src/RecoBTag/SecondaryVertex/src
ALL_PRODS += RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_CLASS := LIBRARY
RecoBTag/SecondaryVertex_forbigobj+=RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_INIT_FUNC        += $$(eval $$(call Library,RecoBTagSecondaryVertex,src/RecoBTag/SecondaryVertex/src,src_RecoBTag_SecondaryVertex_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
