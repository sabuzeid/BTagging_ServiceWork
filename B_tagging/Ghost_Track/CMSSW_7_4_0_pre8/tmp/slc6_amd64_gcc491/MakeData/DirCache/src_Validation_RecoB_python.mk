ifeq ($(strip $(PyValidationRecoB)),)
PyValidationRecoB := self/src/Validation/RecoB/python
src_Validation_RecoB_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/Validation/RecoB/python)
PyValidationRecoB_files := $(patsubst src/Validation/RecoB/python/%,%,$(wildcard $(foreach dir,src/Validation/RecoB/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyValidationRecoB_LOC_USE := self  
PyValidationRecoB_PACKAGE := self/src/Validation/RecoB/python
ALL_PRODS += PyValidationRecoB
PyValidationRecoB_INIT_FUNC        += $$(eval $$(call PythonProduct,PyValidationRecoB,src/Validation/RecoB/python,src_Validation_RecoB_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyValidationRecoB,src/Validation/RecoB/python))
endif
ALL_COMMONRULES += src_Validation_RecoB_python
src_Validation_RecoB_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_Validation_RecoB_python,src/Validation/RecoB/python,PYTHON))
