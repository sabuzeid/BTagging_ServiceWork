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
