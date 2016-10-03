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
