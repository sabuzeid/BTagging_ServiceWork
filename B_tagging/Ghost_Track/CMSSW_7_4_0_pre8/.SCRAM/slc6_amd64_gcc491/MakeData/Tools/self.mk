ALL_TOOLS      += self
self_EX_INCLUDE := /user_mnt/user/sabuzeid/B_tagging/Ghost_Track/CMSSW_7_4_0_pre8/src /user_mnt/user/sabuzeid/B_tagging/Ghost_Track/CMSSW_7_4_0_pre8/include/LCG /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw/CMSSW_7_4_0_pre8/src /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw/CMSSW_7_4_0_pre8/include/LCG
self_EX_LIBDIR := /user_mnt/user/sabuzeid/B_tagging/Ghost_Track/CMSSW_7_4_0_pre8/lib/slc6_amd64_gcc491 /user_mnt/user/sabuzeid/B_tagging/Ghost_Track/CMSSW_7_4_0_pre8/external/slc6_amd64_gcc491/lib /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw/CMSSW_7_4_0_pre8/lib/slc6_amd64_gcc491 /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw/CMSSW_7_4_0_pre8/external/slc6_amd64_gcc491/lib
self_EX_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH  := 2
self_EX_FLAGS_LLVM_ANALYZER  := llvm-analyzer
self_EX_FLAGS_SKIP_TOOLS_SYMLINK  := cxxcompiler ccompiler f77compiler gcc-cxxcompiler gcc-ccompiler gcc-f77compiler llvm-cxxcompiler llvm-ccompiler llvm-f77compiler llvm-analyzer-cxxcompiler llvm-analyzer-ccompiler icc-cxxcompiler icc-ccompiler icc-f77compiler x11 dpm
self_EX_FLAGS_DEFAULT_COMPILER  := gcc
self_EX_FLAGS_EXTERNAL_SYMLINK  := PATH LIBDIR CMSSW_SEARCH_PATH
self_EX_FLAGS_NO_EXTERNAL_RUNTIME  := LD_LIBRARY_PATH PATH CMSSW_SEARCH_PATH
self_EX_FLAGS_OVERRIDABLE_FLAGS  := CPPDEFINES CXXFLAGS FFLAGS CFLAGS CPPFLAGS LDFLAGS
self_ORDER := 20000
IS_PATCH:=

