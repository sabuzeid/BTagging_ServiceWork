ifeq ($(strip $(DQMOfflineRecoBPlugins)),)
DQMOfflineRecoBPlugins := self/src/DQMOffline/RecoB/plugins
PLUGINS:=yes
DQMOfflineRecoBPlugins_files := $(patsubst src/DQMOffline/RecoB/plugins/%,%,$(foreach file,BTagPerformanceAnalyzerOnData.cc PrimaryVertexMonitor.cc BTagPerformanceHarvester.cc,$(eval xfile:=$(wildcard src/DQMOffline/RecoB/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/DQMOffline/RecoB/plugins/$(file). Please fix src/DQMOffline/RecoB/plugins/BuildFile.))))
DQMOfflineRecoBPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/DQMOffline/RecoB/plugins/BuildFile
DQMOfflineRecoBPlugins_LOC_USE := self  root DQMOffline/RecoB DQMServices/Core CommonTools/Statistics
DQMOfflineRecoBPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,DQMOfflineRecoBPlugins,DQMOfflineRecoBPlugins,$(SCRAMSTORENAME_LIB),src/DQMOffline/RecoB/plugins))
DQMOfflineRecoBPlugins_PACKAGE := self/src/DQMOffline/RecoB/plugins
ALL_PRODS += DQMOfflineRecoBPlugins
DQMOffline/RecoB_forbigobj+=DQMOfflineRecoBPlugins
DQMOfflineRecoBPlugins_INIT_FUNC        += $$(eval $$(call Library,DQMOfflineRecoBPlugins,src/DQMOffline/RecoB/plugins,src_DQMOffline_RecoB_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
DQMOfflineRecoBPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,DQMOfflineRecoBPlugins,src/DQMOffline/RecoB/plugins))
endif
ALL_COMMONRULES += src_DQMOffline_RecoB_plugins
src_DQMOffline_RecoB_plugins_parent := DQMOffline/RecoB
src_DQMOffline_RecoB_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DQMOffline_RecoB_plugins,src/DQMOffline/RecoB/plugins,PLUGINS))
