ALL_COMMONRULES += src_DQMOffline_RecoB_test
src_DQMOffline_RecoB_test_parent := DQMOffline/RecoB
src_DQMOffline_RecoB_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_test,src/DQMOffline/RecoB/test,TEST))
