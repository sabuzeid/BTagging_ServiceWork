ifeq ($(strip $(PhysicsTools/MVATrainer)),)
ALL_COMMONRULES += src_PhysicsTools_MVATrainer_src
src_PhysicsTools_MVATrainer_src_parent := PhysicsTools/MVATrainer
src_PhysicsTools_MVATrainer_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PhysicsTools_MVATrainer_src,src/PhysicsTools/MVATrainer/src,LIBRARY))
PhysicsToolsMVATrainer := self/PhysicsTools/MVATrainer
PhysicsTools/MVATrainer := PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_files := $(patsubst src/PhysicsTools/MVATrainer/src/%,%,$(wildcard $(foreach dir,src/PhysicsTools/MVATrainer/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PhysicsToolsMVATrainer_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/MVATrainer/BuildFile
PhysicsToolsMVATrainer_LOC_USE := self  FWCore/Framework FWCore/ParameterSet FWCore/ServiceRegistry FWCore/Utilities FWCore/Concurrency CondFormats/PhysicsToolsObjects CondCore/DBOutputService PhysicsTools/MVAComputer boost rootcore roothistmatrix xerces-c
PhysicsToolsMVATrainer_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsMVATrainerCapabilities,PhysicsToolsMVATrainer,$(SCRAMSTORENAME_LIB),src/PhysicsTools/MVATrainer/src))
PhysicsToolsMVATrainer_LCGDICTS  := x 
PhysicsToolsMVATrainer_PRE_INIT_FUNC += $$(eval $$(call LCGDict,PhysicsToolsMVATrainer,src/PhysicsTools/MVATrainer/src/classes.h,src/PhysicsTools/MVATrainer/src/classes_def.xml,$(SCRAMSTORENAME_LIB),$(GENREFLEX_ARGS) --fail_on_warnings,Capabilities))
PhysicsToolsMVATrainer_EX_LIB   := PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_EX_USE   := $(foreach d,$(PhysicsToolsMVATrainer_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PhysicsToolsMVATrainer_PACKAGE := self/src/PhysicsTools/MVATrainer/src
ALL_PRODS += PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_CLASS := LIBRARY
PhysicsTools/MVATrainer_forbigobj+=PhysicsToolsMVATrainer
PhysicsToolsMVATrainer_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsMVATrainer,src/PhysicsTools/MVATrainer/src,src_PhysicsTools_MVATrainer_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
