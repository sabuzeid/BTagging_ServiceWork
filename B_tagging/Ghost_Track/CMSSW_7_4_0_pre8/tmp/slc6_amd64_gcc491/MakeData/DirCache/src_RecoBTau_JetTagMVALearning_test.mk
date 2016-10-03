ALL_COMMONRULES += src_RecoBTau_JetTagMVALearning_test
src_RecoBTau_JetTagMVALearning_test_parent := RecoBTau/JetTagMVALearning
src_RecoBTau_JetTagMVALearning_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoBTau_JetTagMVALearning_test,src/RecoBTau/JetTagMVALearning/test,TEST))
