ALL_COMMONRULES += src_Validation_RecoB_test
src_Validation_RecoB_test_parent := Validation/RecoB
src_Validation_RecoB_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_Validation_RecoB_test,src/Validation/RecoB/test,TEST))
