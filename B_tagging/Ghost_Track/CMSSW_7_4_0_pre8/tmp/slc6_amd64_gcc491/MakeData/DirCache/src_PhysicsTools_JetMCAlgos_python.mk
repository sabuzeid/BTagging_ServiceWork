ifeq ($(strip $(PyPhysicsToolsJetMCAlgos)),)
PyPhysicsToolsJetMCAlgos := self/src/PhysicsTools/JetMCAlgos/python
src_PhysicsTools_JetMCAlgos_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/PhysicsTools/JetMCAlgos/python)
PyPhysicsToolsJetMCAlgos_files := $(patsubst src/PhysicsTools/JetMCAlgos/python/%,%,$(wildcard $(foreach dir,src/PhysicsTools/JetMCAlgos/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyPhysicsToolsJetMCAlgos_LOC_USE := self  
PyPhysicsToolsJetMCAlgos_PACKAGE := self/src/PhysicsTools/JetMCAlgos/python
ALL_PRODS += PyPhysicsToolsJetMCAlgos
PyPhysicsToolsJetMCAlgos_INIT_FUNC        += $$(eval $$(call PythonProduct,PyPhysicsToolsJetMCAlgos,src/PhysicsTools/JetMCAlgos/python,src_PhysicsTools_JetMCAlgos_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyPhysicsToolsJetMCAlgos,src/PhysicsTools/JetMCAlgos/python))
endif
ALL_COMMONRULES += src_PhysicsTools_JetMCAlgos_python
src_PhysicsTools_JetMCAlgos_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_JetMCAlgos_python,src/PhysicsTools/JetMCAlgos/python,PYTHON))
