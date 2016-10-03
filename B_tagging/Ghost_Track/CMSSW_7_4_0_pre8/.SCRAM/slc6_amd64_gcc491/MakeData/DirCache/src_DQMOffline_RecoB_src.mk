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
