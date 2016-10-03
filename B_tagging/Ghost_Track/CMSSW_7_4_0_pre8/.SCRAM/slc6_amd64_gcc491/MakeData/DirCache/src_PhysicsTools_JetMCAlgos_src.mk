ifeq ($(strip $(PhysicsTools/JetMCAlgos)),)
ALL_COMMONRULES += src_PhysicsTools_JetMCAlgos_src
src_PhysicsTools_JetMCAlgos_src_parent := PhysicsTools/JetMCAlgos
src_PhysicsTools_JetMCAlgos_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PhysicsTools_JetMCAlgos_src,src/PhysicsTools/JetMCAlgos/src,LIBRARY))
PhysicsToolsJetMCAlgos := self/PhysicsTools/JetMCAlgos
PhysicsTools/JetMCAlgos := PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_files := $(patsubst src/PhysicsTools/JetMCAlgos/src/%,%,$(wildcard $(foreach dir,src/PhysicsTools/JetMCAlgos/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PhysicsToolsJetMCAlgos_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/JetMCAlgos/BuildFile
PhysicsToolsJetMCAlgos_LOC_USE := self  FWCore/Framework FWCore/PluginManager FWCore/ParameterSet PhysicsTools/JetMCUtils
PhysicsToolsJetMCAlgos_EX_LIB   := PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_EX_USE   := $(foreach d,$(PhysicsToolsJetMCAlgos_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PhysicsToolsJetMCAlgos_PACKAGE := self/src/PhysicsTools/JetMCAlgos/src
ALL_PRODS += PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_CLASS := LIBRARY
PhysicsTools/JetMCAlgos_forbigobj+=PhysicsToolsJetMCAlgos
PhysicsToolsJetMCAlgos_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsJetMCAlgos,src/PhysicsTools/JetMCAlgos/src,src_PhysicsTools_JetMCAlgos_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
