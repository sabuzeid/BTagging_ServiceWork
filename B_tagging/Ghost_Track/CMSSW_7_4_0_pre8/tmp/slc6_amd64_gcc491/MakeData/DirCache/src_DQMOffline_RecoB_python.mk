ifeq ($(strip $(PyDQMOfflineRecoB)),)
PyDQMOfflineRecoB := self/src/DQMOffline/RecoB/python
src_DQMOffline_RecoB_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/DQMOffline/RecoB/python)
PyDQMOfflineRecoB_files := $(patsubst src/DQMOffline/RecoB/python/%,%,$(wildcard $(foreach dir,src/DQMOffline/RecoB/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyDQMOfflineRecoB_LOC_USE := self  
PyDQMOfflineRecoB_PACKAGE := self/src/DQMOffline/RecoB/python
ALL_PRODS += PyDQMOfflineRecoB
PyDQMOfflineRecoB_INIT_FUNC        += $$(eval $$(call PythonProduct,PyDQMOfflineRecoB,src/DQMOffline/RecoB/python,src_DQMOffline_RecoB_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyDQMOfflineRecoB,src/DQMOffline/RecoB/python))
endif
ALL_COMMONRULES += src_DQMOffline_RecoB_python
src_DQMOffline_RecoB_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_python,src/DQMOffline/RecoB/python,PYTHON))
