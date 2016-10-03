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
