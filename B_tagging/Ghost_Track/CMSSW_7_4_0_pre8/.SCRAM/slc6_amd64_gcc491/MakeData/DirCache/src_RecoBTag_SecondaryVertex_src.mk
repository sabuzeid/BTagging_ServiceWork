ifeq ($(strip $(RecoBTag/SecondaryVertex)),)
ALL_COMMONRULES += src_RecoBTag_SecondaryVertex_src
src_RecoBTag_SecondaryVertex_src_parent := RecoBTag/SecondaryVertex
src_RecoBTag_SecondaryVertex_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_RecoBTag_SecondaryVertex_src,src/RecoBTag/SecondaryVertex/src,LIBRARY))
RecoBTagSecondaryVertex := self/RecoBTag/SecondaryVertex
RecoBTag/SecondaryVertex := RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_files := $(patsubst src/RecoBTag/SecondaryVertex/src/%,%,$(wildcard $(foreach dir,src/RecoBTag/SecondaryVertex/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
RecoBTagSecondaryVertex_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoBTag/SecondaryVertex/BuildFile
RecoBTagSecondaryVertex_LOC_USE := self  FWCore/ParameterSet FWCore/Utilities DataFormats/Math DataFormats/TrackReco DataFormats/VertexReco DataFormats/BTauReco DataFormats/PatCandidates RecoVertex/VertexTools rootmath
RecoBTagSecondaryVertex_EX_LIB   := RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_EX_USE   := $(foreach d,$(RecoBTagSecondaryVertex_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
RecoBTagSecondaryVertex_PACKAGE := self/src/RecoBTag/SecondaryVertex/src
ALL_PRODS += RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_CLASS := LIBRARY
RecoBTag/SecondaryVertex_forbigobj+=RecoBTagSecondaryVertex
RecoBTagSecondaryVertex_INIT_FUNC        += $$(eval $$(call Library,RecoBTagSecondaryVertex,src/RecoBTag/SecondaryVertex/src,src_RecoBTag_SecondaryVertex_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
