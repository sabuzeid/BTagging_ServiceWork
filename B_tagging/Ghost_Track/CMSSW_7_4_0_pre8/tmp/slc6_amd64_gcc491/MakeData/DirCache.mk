ifeq ($(strip $(PyDQMOfflineRecoB)),)
PyDQMOfflineRecoB := self/src/DQMOffline/RecoB/python
src_DQMOffline_RecoB_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/DQMOffline/RecoB/python)
PyDQMOfflineRecoB_files := $(patsubst src/DQMOffline/RecoB/python/%,%,$(wildcard $(foreach dir,src/DQMOffline/RecoB/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyDQMOfflineRecoB_LOC_USE := self  
PyDQMOfflineRecoB_PACKAGE := self/src/DQMOffline/RecoB/python
ALL_PRODS += PyDQMOfflineRecoB
PyDQMOfflineRecoB_INIT_FUNC        += $$(eval $$(call PythonProduct,PyDQMOfflineRecoB,src/DQMOffline/RecoB/python,src_DQMOffline_RecoB_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyDQMOfflineRecoB,src/DQMOffline/RecoB/python))
endif
ALL_COMMONRULES += src_DQMOffline_RecoB_python
src_DQMOffline_RecoB_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_python,src/DQMOffline/RecoB/python,PYTHON))
ALL_SUBSYSTEMS+=DQMOffline
subdirs_src_DQMOffline = src_DQMOffline_RecoB
ifeq ($(strip $(PyValidationRecoB)),)
PyValidationRecoB := self/src/Validation/RecoB/python
src_Validation_RecoB_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/Validation/RecoB/python)
PyValidationRecoB_files := $(patsubst src/Validation/RecoB/python/%,%,$(wildcard $(foreach dir,src/Validation/RecoB/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyValidationRecoB_LOC_USE := self  
PyValidationRecoB_PACKAGE := self/src/Validation/RecoB/python
ALL_PRODS += PyValidationRecoB
PyValidationRecoB_INIT_FUNC        += $$(eval $$(call PythonProduct,PyValidationRecoB,src/Validation/RecoB/python,src_Validation_RecoB_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyValidationRecoB,src/Validation/RecoB/python))
endif
ALL_COMMONRULES += src_Validation_RecoB_python
src_Validation_RecoB_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_Validation_RecoB_python,src/Validation/RecoB/python,PYTHON))
ALL_PACKAGES += DQMOffline/RecoB
subdirs_src_DQMOffline_RecoB := src_DQMOffline_RecoB_src src_DQMOffline_RecoB_plugins src_DQMOffline_RecoB_test src_DQMOffline_RecoB_python
ifeq ($(strip $(matchGenHFHadrons)),)
matchGenHFHadrons := self/src/PhysicsTools/JetMCAlgos/test
matchGenHFHadrons_files := $(patsubst src/PhysicsTools/JetMCAlgos/test/%,%,$(foreach file,matchGenHFHadrons.cc,$(eval xfile:=$(wildcard src/PhysicsTools/JetMCAlgos/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/JetMCAlgos/test/$(file). Please fix src/PhysicsTools/JetMCAlgos/test/BuildFile.))))
matchGenHFHadrons_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/test/BuildFile
matchGenHFHadrons_LOC_USE := self  clhep DataFormats/BTauReco FWCore/Framework FWCore/Utilities CommonTools/UtilAlgos rootmath root
matchGenHFHadrons_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,matchGenHFHadrons,matchGenHFHadrons,$(SCRAMSTORENAME_LIB),src/PhysicsTools/JetMCAlgos/test))
matchGenHFHadrons_PACKAGE := self/src/PhysicsTools/JetMCAlgos/test
ALL_PRODS += matchGenHFHadrons
matchGenHFHadrons_INIT_FUNC        += $$(eval $$(call Library,matchGenHFHadrons,src/PhysicsTools/JetMCAlgos/test,src_PhysicsTools_JetMCAlgos_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
matchGenHFHadrons_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,matchGenHFHadrons,src/PhysicsTools/JetMCAlgos/test))
endif
ifeq ($(strip $(matchOneToOne)),)
matchOneToOne := self/src/PhysicsTools/JetMCAlgos/test
matchOneToOne_files := $(patsubst src/PhysicsTools/JetMCAlgos/test/%,%,$(foreach file,matchOneToOne.cc,$(eval xfile:=$(wildcard src/PhysicsTools/JetMCAlgos/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/JetMCAlgos/test/$(file). Please fix src/PhysicsTools/JetMCAlgos/test/BuildFile.))))
matchOneToOne_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/test/BuildFile
matchOneToOne_LOC_USE := self  clhep DataFormats/BTauReco FWCore/Framework rootmath root
matchOneToOne_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,matchOneToOne,matchOneToOne,$(SCRAMSTORENAME_LIB),src/PhysicsTools/JetMCAlgos/test))
matchOneToOne_PACKAGE := self/src/PhysicsTools/JetMCAlgos/test
ALL_PRODS += matchOneToOne
matchOneToOne_INIT_FUNC        += $$(eval $$(call Library,matchOneToOne,src/PhysicsTools/JetMCAlgos/test,src_PhysicsTools_JetMCAlgos_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
matchOneToOne_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,matchOneToOne,src/PhysicsTools/JetMCAlgos/test))
endif
ifeq ($(strip $(jetMatch)),)
jetMatch := self/src/PhysicsTools/JetMCAlgos/test
jetMatch_files := $(patsubst src/PhysicsTools/JetMCAlgos/test/%,%,$(foreach file,jetMatch.cc,$(eval xfile:=$(wildcard src/PhysicsTools/JetMCAlgos/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/JetMCAlgos/test/$(file). Please fix src/PhysicsTools/JetMCAlgos/test/BuildFile.))))
jetMatch_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/test/BuildFile
jetMatch_LOC_USE := self  clhep DataFormats/BTauReco FWCore/Framework rootmath root
jetMatch_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,jetMatch,jetMatch,$(SCRAMSTORENAME_LIB),src/PhysicsTools/JetMCAlgos/test))
jetMatch_PACKAGE := self/src/PhysicsTools/JetMCAlgos/test
ALL_PRODS += jetMatch
jetMatch_INIT_FUNC        += $$(eval $$(call Library,jetMatch,src/PhysicsTools/JetMCAlgos/test,src_PhysicsTools_JetMCAlgos_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
jetMatch_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,jetMatch,src/PhysicsTools/JetMCAlgos/test))
endif
ifeq ($(strip $(printEvent)),)
printEvent := self/src/PhysicsTools/JetMCAlgos/test
printEvent_files := $(patsubst src/PhysicsTools/JetMCAlgos/test/%,%,$(foreach file,printEvent.cc,$(eval xfile:=$(wildcard src/PhysicsTools/JetMCAlgos/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/JetMCAlgos/test/$(file). Please fix src/PhysicsTools/JetMCAlgos/test/BuildFile.))))
printEvent_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/test/BuildFile
printEvent_LOC_USE := self  clhep DataFormats/BTauReco FWCore/Framework SimGeneral/HepPDTRecord PhysicsTools/JetMCUtils rootmath root
printEvent_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,printEvent,printEvent,$(SCRAMSTORENAME_LIB),src/PhysicsTools/JetMCAlgos/test))
printEvent_PACKAGE := self/src/PhysicsTools/JetMCAlgos/test
ALL_PRODS += printEvent
printEvent_INIT_FUNC        += $$(eval $$(call Library,printEvent,src/PhysicsTools/JetMCAlgos/test,src_PhysicsTools_JetMCAlgos_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
printEvent_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,printEvent,src/PhysicsTools/JetMCAlgos/test))
endif
ALL_COMMONRULES += src_PhysicsTools_JetMCAlgos_test
src_PhysicsTools_JetMCAlgos_test_parent := PhysicsTools/JetMCAlgos
src_PhysicsTools_JetMCAlgos_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_JetMCAlgos_test,src/PhysicsTools/JetMCAlgos/test,TEST))
ALL_PACKAGES += RecoBTau/JetTagMVALearning
subdirs_src_RecoBTau_JetTagMVALearning := src_RecoBTau_JetTagMVALearning_test src_RecoBTau_JetTagMVALearning_src src_RecoBTau_JetTagMVALearning_doc src_RecoBTau_JetTagMVALearning_plugins src_RecoBTau_JetTagMVALearning_interface
ifeq ($(strip $(PyPhysicsToolsJetMCAlgos)),)
PyPhysicsToolsJetMCAlgos := self/src/PhysicsTools/JetMCAlgos/python
src_PhysicsTools_JetMCAlgos_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/PhysicsTools/JetMCAlgos/python)
PyPhysicsToolsJetMCAlgos_files := $(patsubst src/PhysicsTools/JetMCAlgos/python/%,%,$(wildcard $(foreach dir,src/PhysicsTools/JetMCAlgos/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyPhysicsToolsJetMCAlgos_LOC_USE := self  
PyPhysicsToolsJetMCAlgos_PACKAGE := self/src/PhysicsTools/JetMCAlgos/python
ALL_PRODS += PyPhysicsToolsJetMCAlgos
PyPhysicsToolsJetMCAlgos_INIT_FUNC        += $$(eval $$(call PythonProduct,PyPhysicsToolsJetMCAlgos,src/PhysicsTools/JetMCAlgos/python,src_PhysicsTools_JetMCAlgos_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyPhysicsToolsJetMCAlgos,src/PhysicsTools/JetMCAlgos/python))
endif
ALL_COMMONRULES += src_PhysicsTools_JetMCAlgos_python
src_PhysicsTools_JetMCAlgos_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_JetMCAlgos_python,src/PhysicsTools/JetMCAlgos/python,PYTHON))
src_Validation_RecoB_scripts_files := $(filter-out \#% %\#,$(notdir $(wildcard $(foreach dir,$(LOCALTOP)/src/Validation/RecoB/scripts,$(dir)/*))))
$(eval $(call Src2StoreCopy,src_Validation_RecoB_scripts,src/Validation/RecoB/scripts,$(SCRAMSTORENAME_BIN),*))
ALL_SUBSYSTEMS+=PhysicsTools
subdirs_src_PhysicsTools = src_PhysicsTools_JetMCAlgos src_PhysicsTools_MVATrainer
ALL_PACKAGES += RecoBTag/SecondaryVertex
subdirs_src_RecoBTag_SecondaryVertex := src_RecoBTag_SecondaryVertex_python src_RecoBTag_SecondaryVertex_interface src_RecoBTag_SecondaryVertex_src src_RecoBTag_SecondaryVertex_plugins
ALL_COMMONRULES += src_DQMOffline_RecoB_test
src_DQMOffline_RecoB_test_parent := DQMOffline/RecoB
src_DQMOffline_RecoB_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_test,src/DQMOffline/RecoB/test,TEST))
ifeq ($(strip $(testMVATrainerLooper)),)
testMVATrainerLooper := self/src/PhysicsTools/MVATrainer/test
testMVATrainerLooper_files := $(patsubst src/PhysicsTools/MVATrainer/test/%,%,$(foreach file,testMVATrainerLooper.cc,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/test/$(file). Please fix src/PhysicsTools/MVATrainer/test/BuildFile.))))
testMVATrainerLooper_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/test/BuildFile
testMVATrainerLooper_LOC_USE := self  FWCore/Framework FWCore/ParameterSet FWCore/Utilities PhysicsTools/MVAComputer PhysicsTools/MVATrainer
testMVATrainerLooper_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,testMVATrainerLooper,testMVATrainerLooper,$(SCRAMSTORENAME_LIB),src/PhysicsTools/MVATrainer/test))
testMVATrainerLooper_PACKAGE := self/src/PhysicsTools/MVATrainer/test
ALL_PRODS += testMVATrainerLooper
testMVATrainerLooper_INIT_FUNC        += $$(eval $$(call Library,testMVATrainerLooper,src/PhysicsTools/MVATrainer/test,src_PhysicsTools_MVATrainer_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
testMVATrainerLooper_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,testMVATrainerLooper,src/PhysicsTools/MVATrainer/test))
endif
ifeq ($(strip $(testMVATrainer)),)
testMVATrainer_files := $(patsubst src/PhysicsTools/MVATrainer/test/%,%,$(foreach file,testMVATrainer.cpp,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/test/$(file). Please fix src/PhysicsTools/MVATrainer/test/BuildFile.))))
testMVATrainer := self/src/PhysicsTools/MVATrainer/test
testMVATrainer_TEST_RUNNER_CMD :=  testMVATrainer 
testMVATrainer_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/test/BuildFile
testMVATrainer_LOC_USE := self  FWCore/Utilities FWCore/ParameterSet PhysicsTools/MVAComputer PhysicsTools/MVATrainer
testMVATrainer_PACKAGE := self/src/PhysicsTools/MVATrainer/test
ALL_PRODS += testMVATrainer
testMVATrainer_INIT_FUNC        += $$(eval $$(call Binary,testMVATrainer,src/PhysicsTools/MVATrainer/test,src_PhysicsTools_MVATrainer_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_TEST),test,$(SCRAMSTORENAME_LOGS)))
testMVATrainer_CLASS := TEST
else
$(eval $(call MultipleWarningMsg,testMVATrainer,src/PhysicsTools/MVATrainer/test))
endif
ALL_COMMONRULES += src_PhysicsTools_MVATrainer_test
src_PhysicsTools_MVATrainer_test_parent := PhysicsTools/MVATrainer
src_PhysicsTools_MVATrainer_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_MVATrainer_test,src/PhysicsTools/MVATrainer/test,TEST))
ALL_SUBSYSTEMS+=RecoBTau
subdirs_src_RecoBTau = src_RecoBTau_JetTagMVALearning
ifeq ($(strip $(PyRecoBTagSecondaryVertex)),)
PyRecoBTagSecondaryVertex := self/src/RecoBTag/SecondaryVertex/python
src_RecoBTag_SecondaryVertex_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoBTag/SecondaryVertex/python)
PyRecoBTagSecondaryVertex_files := $(patsubst src/RecoBTag/SecondaryVertex/python/%,%,$(wildcard $(foreach dir,src/RecoBTag/SecondaryVertex/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoBTagSecondaryVertex_LOC_USE := self  
PyRecoBTagSecondaryVertex_PACKAGE := self/src/RecoBTag/SecondaryVertex/python
ALL_PRODS += PyRecoBTagSecondaryVertex
PyRecoBTagSecondaryVertex_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoBTagSecondaryVertex,src/RecoBTag/SecondaryVertex/python,src_RecoBTag_SecondaryVertex_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoBTagSecondaryVertex,src/RecoBTag/SecondaryVertex/python))
endif
ALL_COMMONRULES += src_RecoBTag_SecondaryVertex_python
src_RecoBTag_SecondaryVertex_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoBTag_SecondaryVertex_python,src/RecoBTag/SecondaryVertex/python,PYTHON))
ifeq ($(strip $(mvaTreeTrainer)),)
mvaTreeTrainer_files := $(patsubst src/PhysicsTools/MVATrainer/bin/%,%,$(foreach file,mvaTreeTrainer.cpp,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/bin/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/bin/$(file). Please fix src/PhysicsTools/MVATrainer/bin/BuildFile.))))
mvaTreeTrainer := self/src/PhysicsTools/MVATrainer/bin
mvaTreeTrainer_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/bin/BuildFile
mvaTreeTrainer_LOC_USE := self  FWCore/Utilities FWCore/PluginManager PhysicsTools/MVAComputer PhysicsTools/MVATrainer rootcintex rootcore
mvaTreeTrainer_PACKAGE := self/src/PhysicsTools/MVATrainer/bin
ALL_PRODS += mvaTreeTrainer
mvaTreeTrainer_INIT_FUNC        += $$(eval $$(call Binary,mvaTreeTrainer,src/PhysicsTools/MVATrainer/bin,src_PhysicsTools_MVATrainer_bin,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_BIN),bin,$(SCRAMSTORENAME_LOGS)))
mvaTreeTrainer_CLASS := BINARY
else
$(eval $(call MultipleWarningMsg,mvaTreeTrainer,src/PhysicsTools/MVATrainer/bin))
endif
ifeq ($(strip $(mvaTreeComputer)),)
mvaTreeComputer_files := $(patsubst src/PhysicsTools/MVATrainer/bin/%,%,$(foreach file,mvaTreeComputer.cpp,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/bin/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/bin/$(file). Please fix src/PhysicsTools/MVATrainer/bin/BuildFile.))))
mvaTreeComputer := self/src/PhysicsTools/MVATrainer/bin
mvaTreeComputer_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/bin/BuildFile
mvaTreeComputer_LOC_USE := self  FWCore/Utilities FWCore/PluginManager PhysicsTools/MVAComputer rootcintex rootcore
mvaTreeComputer_PACKAGE := self/src/PhysicsTools/MVATrainer/bin
ALL_PRODS += mvaTreeComputer
mvaTreeComputer_INIT_FUNC        += $$(eval $$(call Binary,mvaTreeComputer,src/PhysicsTools/MVATrainer/bin,src_PhysicsTools_MVATrainer_bin,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_BIN),bin,$(SCRAMSTORENAME_LOGS)))
mvaTreeComputer_CLASS := BINARY
else
$(eval $(call MultipleWarningMsg,mvaTreeComputer,src/PhysicsTools/MVATrainer/bin))
endif
ifeq ($(strip $(mvaExtractor)),)
mvaExtractor_files := $(patsubst src/PhysicsTools/MVATrainer/bin/%,%,$(foreach file,mvaExtractor.cpp,$(eval xfile:=$(wildcard src/PhysicsTools/MVATrainer/bin/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/MVATrainer/bin/$(file). Please fix src/PhysicsTools/MVATrainer/bin/BuildFile.))))
mvaExtractor := self/src/PhysicsTools/MVATrainer/bin
mvaExtractor_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/bin/BuildFile
mvaExtractor_LOC_USE := self  FWCore/Utilities PhysicsTools/MVAComputer rootcintex rootcore
mvaExtractor_PACKAGE := self/src/PhysicsTools/MVATrainer/bin
ALL_PRODS += mvaExtractor
mvaExtractor_INIT_FUNC        += $$(eval $$(call Binary,mvaExtractor,src/PhysicsTools/MVATrainer/bin,src_PhysicsTools_MVATrainer_bin,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_BIN),bin,$(SCRAMSTORENAME_LOGS)))
mvaExtractor_CLASS := BINARY
else
$(eval $(call MultipleWarningMsg,mvaExtractor,src/PhysicsTools/MVATrainer/bin))
endif
ALL_COMMONRULES += src_PhysicsTools_MVATrainer_bin
src_PhysicsTools_MVATrainer_bin_parent := PhysicsTools/MVATrainer
src_PhysicsTools_MVATrainer_bin_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_MVATrainer_bin,src/PhysicsTools/MVATrainer/bin,BINARY))
ALL_PACKAGES += PhysicsTools/MVATrainer
subdirs_src_PhysicsTools_MVATrainer := src_PhysicsTools_MVATrainer_bin src_PhysicsTools_MVATrainer_src src_PhysicsTools_MVATrainer_test src_PhysicsTools_MVATrainer_plugins src_PhysicsTools_MVATrainer_interface
ALL_SUBSYSTEMS+=RecoBTag
subdirs_src_RecoBTag = src_RecoBTag_SecondaryVertex
ALL_COMMONRULES += src_RecoBTau_JetTagMVALearning_test
src_RecoBTau_JetTagMVALearning_test_parent := RecoBTau/JetTagMVALearning
src_RecoBTau_JetTagMVALearning_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoBTau_JetTagMVALearning_test,src/RecoBTau/JetTagMVALearning/test,TEST))
ALL_SUBSYSTEMS+=Validation
subdirs_src_Validation = src_Validation_RecoB
ALL_COMMONRULES += src_Validation_RecoB_test
src_Validation_RecoB_test_parent := Validation/RecoB
src_Validation_RecoB_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_Validation_RecoB_test,src/Validation/RecoB/test,TEST))
ALL_PACKAGES += PhysicsTools/JetMCAlgos
subdirs_src_PhysicsTools_JetMCAlgos := src_PhysicsTools_JetMCAlgos_interface src_PhysicsTools_JetMCAlgos_src src_PhysicsTools_JetMCAlgos_doc src_PhysicsTools_JetMCAlgos_plugins src_PhysicsTools_JetMCAlgos_python src_PhysicsTools_JetMCAlgos_test
ALL_PACKAGES += Validation/RecoB
subdirs_src_Validation_RecoB := src_Validation_RecoB_doc src_Validation_RecoB_plugins src_Validation_RecoB_python src_Validation_RecoB_scripts src_Validation_RecoB_test src_Validation_RecoB_src
