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
