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
