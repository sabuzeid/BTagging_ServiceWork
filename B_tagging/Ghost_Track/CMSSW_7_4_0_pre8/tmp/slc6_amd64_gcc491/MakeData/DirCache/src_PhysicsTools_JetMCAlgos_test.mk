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
