ifeq ($(strip $(Validation/RecoB)),)
ALL_COMMONRULES += src_Validation_RecoB_src
src_Validation_RecoB_src_parent := Validation/RecoB
src_Validation_RecoB_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_Validation_RecoB_src,src/Validation/RecoB/src,LIBRARY))
ValidationRecoB := self/Validation/RecoB
Validation/RecoB := ValidationRecoB
ValidationRecoB_files := $(patsubst src/Validation/RecoB/src/%,%,$(wildcard $(foreach dir,src/Validation/RecoB/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
ValidationRecoB_BuildFile    := $(WORKINGDIR)/cache/bf/src/Validation/RecoB/BuildFile
ValidationRecoB_LOC_USE := self  root rootcore DataFormats/BTauReco DataFormats/Common DQMServices/Core FWCore/Framework FWCore/ParameterSet FWCore/Utilities
ValidationRecoB_EX_LIB   := ValidationRecoB
ValidationRecoB_EX_USE   := $(foreach d,$(ValidationRecoB_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ValidationRecoB_PACKAGE := self/src/Validation/RecoB/src
ALL_PRODS += ValidationRecoB
ValidationRecoB_CLASS := LIBRARY
Validation/RecoB_forbigobj+=ValidationRecoB
ValidationRecoB_INIT_FUNC        += $$(eval $$(call Library,ValidationRecoB,src/Validation/RecoB/src,src_Validation_RecoB_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
