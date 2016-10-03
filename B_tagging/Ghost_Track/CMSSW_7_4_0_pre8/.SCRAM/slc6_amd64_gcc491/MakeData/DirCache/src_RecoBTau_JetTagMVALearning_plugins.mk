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
