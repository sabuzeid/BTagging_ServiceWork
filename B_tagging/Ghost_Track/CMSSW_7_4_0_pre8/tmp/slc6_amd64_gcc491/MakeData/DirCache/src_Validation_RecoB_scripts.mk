src_Validation_RecoB_scripts_files := $(filter-out \#% %\#,$(notdir $(wildcard $(foreach dir,$(LOCALTOP)/src/Validation/RecoB/scripts,$(dir)/*))))
$(eval $(call Src2StoreCopy,src_Validation_RecoB_scripts,src/Validation/RecoB/scripts,$(SCRAMSTORENAME_BIN),*))
