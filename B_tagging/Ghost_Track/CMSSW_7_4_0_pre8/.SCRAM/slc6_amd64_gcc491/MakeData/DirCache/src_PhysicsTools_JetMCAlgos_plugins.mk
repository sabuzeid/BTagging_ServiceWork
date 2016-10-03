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
