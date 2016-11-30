import FWCore.ParameterSet.Config as cms

# set default max events
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('python')
options.setDefault('maxEvents', 1000 )
options.parseArguments()

process = cms.Process("Validation")

applyJEC = True #changed to true by Shimaa
corrLabel = 'ak4PFCHSL1FastL2L3Corrector'

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.load("Configuration.StandardSequences.Reconstruction_cff") #Added by Shima
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')

# Reasonable logging level
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Load DQM
process.load("DQMServices.Components.DQMEnvironment_cfi")
process.load("DQMServices.Core.DQM_cfg")
process.load("DQMOffline.RecoB.bTagCommon_cff")

# Events to process
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))

# Input files
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)


#################################################
## Remake jets
#################################################

## Select charged hadron subtracted packed PF candidates
process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))
from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
## Define PFJetsCHS
process.ak4PFJetsCHS = ak4PFJets.clone(src = 'pfCHS')

####################

# MiniAOD collections 
primaryVertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices")
secondaryVertexCollection = cms.InputTag('slimmedSecondaryVertices')
#jetCollection = cms.InputTag("slimmedJets")
jetCollection = cms.InputTag("ak4PFJetsCHS")
genJetCollection  = cms.InputTag("slimmedGenJets")
#candidateCollection = cms.InputTag("packedPFCandidates")
candidateCollection = cms.InputTag("ak4PFJetsCHS")
muonCollection = cms.InputTag("slimmedMuons")
electronCollection = cms.InputTag("slimmedElectrons")
genParticleCollection = cms.InputTag("prunedGenParticles")

# Load b-tagging modules
process.load("RecoBTag.Configuration.RecoBTag_cff")
process.load("RecoBTag.CTagging.RecoCTagging_cff")

# use pfBtagging sequence
process.btagSeq = cms.Sequence(process.pfBTagging * process.pfCSVscikit)
process.ctagSeq = cms.Sequence(process.pfCTagging)

# remove IVF modules which do not have to be re-run
process.btagSeq.remove(process.inclusiveCandidateVertexFinder)
process.btagSeq.remove(process.candidateVertexMerger)
process.btagSeq.remove(process.candidateVertexArbitrator)
process.btagSeq.remove(process.inclusiveCandidateSecondaryVertices)

process.ctagSeq.remove(process.inclusiveCandidateVertexingCvsL)

# For MC-based pileup jet ID
process.ak4GenJetsForPUid = cms.EDFilter("GenJetSelector",
    src = genJetCollection, 
    cut = cms.string('pt > 8.'),
    filter = cms.bool(False)
)

# Gen matching for PAT jets
process.load("PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi")
process.patJetGenJetMatch.src = jetCollection
process.patJetGenJetMatch.matched = cms.InputTag("ak4GenJetsForPUid")
process.patJetGenJetMatch.maxDeltaR = cms.double(0.25)
process.patJetGenJetMatch.resolveAmbiguities = cms.bool(True)

#for MC jet flavour
process.load("PhysicsTools.JetMCAlgos.HadronAndPartonSelector_cfi")
process.load("PhysicsTools.JetMCAlgos.AK4PFJetsMCFlavourInfos_cfi")
#process.load("PhysicsTools.JetMCAlgos.CaloJetsMCFlavour_cfi") #add by Shimaa
process.ak4JetFlavourInfos.jets = jetCollection 
process.ak4JetFlavourInfos.hadronFlavourHasPriority = cms.bool(True)
process.selectedHadronsAndPartons.particles = genParticleCollection
process.flavourSeq = cms.Sequence(
    process.selectedHadronsAndPartons *
    process.ak4JetFlavourInfos
)

if applyJEC:
    process.load("JetMETCorrections.Configuration.JetCorrectors_cff")
    process.JECseq = cms.Sequence(process.ak4PFCHSL1FastL2L3CorrectorChain)

# Load b-tag validation
process.load("Validation.RecoB.bTagAnalysis_cfi")
# Some common plot parameters 
flavPlots = "allbcl" 
ptRanges = cms.vdouble(50.0,80.0,120.0)
etaRanges = cms.vdouble(0.0,1.4,2.4)

# Specify taggers for which produce the validation plots
from DQMOffline.RecoB.bTagCommon_cff import *
# tagger configuration (from bTagCommon)
tagConfig = cms.VPSet(
        #cms.PSet(
#            bTagTrackIPAnalysisBlock,
#            type = cms.string('CandIP'),
#            label = cms.InputTag("pfImpactParameterTagInfos"),
#            folder = cms.string("IPTag")
#        ),
#        cms.PSet(
#            bTagCombinedSVAnalysisBlock,
#            listTagInfos = cms.VInputTag(
#                cms.InputTag("pfImpactParameterTagInfos"),
#                cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos")
#            ),
#            type = cms.string('GenericMVA'),
#            label = cms.InputTag("candidateCombinedSecondaryVertexV2Computer"),
#            folder = cms.string("CSVTag")
#        ),
#        cms.PSet(
#            bTagTrackCountingAnalysisBlock,
#            label = cms.InputTag("pfTrackCountingHighEffBJetTags"),
#            folder = cms.string("TCHE")
#        ),
#        cms.PSet(
#            bTagProbabilityAnalysisBlock,
#            label = cms.InputTag("pfJetProbabilityBJetTags"),
#            folder = cms.string("JP")
#        ),
#        cms.PSet(
#            bTagBProbabilityAnalysisBlock,
#            label = cms.InputTag("pfJetBProbabilityBJetTags"),
#            folder = cms.string("JBP")
#        ),
#        cms.PSet(
#            bTagSimpleSVAnalysisBlock,
#            label = cms.InputTag("pfSimpleSecondaryVertexHighEffBJetTags"),
#            folder = cms.string("SSVHE")
#        ),
#        cms.PSet(
#            bTagSimpleSVAnalysisBlock,
#            label = cms.InputTag("pfSimpleInclusiveSecondaryVertexHighEffBJetTags"),
#            folder = cms.string("SISVHE")
#        ),
        cms.PSet(
            bTagGenericAnalysisBlock,
            label = cms.InputTag("pfCombinedInclusiveSecondaryVertexV2BJetTags"),
            folder = cms.string("CSVv2")
        ),
	cms.PSet(
            bTagGenericAnalysisBlock,
            #CSVscikitAnalysisBlock,
            #label = cms.InputTag("pfCSVscikit"),
            label = cms.InputTag("pfCSVscikitJetTags"),
            folder = cms.string("CSVscikit"),
        )
#        cms.PSet(
#            bTagSymmetricAnalysisBlock,
#            label = cms.InputTag("pfCombinedMVAV2BJetTags"),
#            folder = cms.string("combMVAv2")
#        ), 
#        cms.PSet(
#            bTagSoftLeptonAnalysisBlock,
#            label = cms.InputTag("softPFMuonBJetTags"),
#            folder = cms.string("SMT")
#        ),
#        cms.PSet(
#            bTagSoftLeptonAnalysisBlock,
#            label = cms.InputTag("softPFElectronBJetTags"),
#            folder = cms.string("SET")
#        ),
#       cms.PSet(
#           cTagCombinedSVAnalysisBlock,
#           listTagInfos = cms.VInputTag(
#               cms.InputTag("pfImpactParameterTagInfos"),
#               cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"),                
#               cms.InputTag("softPFMuonsTagInfos"),
#               cms.InputTag("softPFElectronsTagInfos")
#           ),
#           type = cms.string('GenericMVA'),
#           label = cms.InputTag("candidateCombinedSecondaryVertexSoftLeptonCvsLComputer"),
#           folder = cms.string("CtaggerTag")
#        ),
#       cms.PSet(
#            cTagGenericAnalysisBlock,
#            label = cms.InputTag("pfCombinedCvsLJetTags"),
#            folder = cms.string("Ctagger_CvsL"),
#            doCTagPlots = cms.bool(True)
#        ),
#        cms.PSet(
#            cTagGenericAnalysisBlock,
#            label = cms.InputTag("pfCombinedCvsBJetTags"),
#            folder = cms.string("Ctagger_CvsB"),
#            doCTagPlots = cms.bool(True)
#        ),
#       cms.PSet(
#            cTagCorrelationAnalysisBlock,
#            type = cms.string('TagCorrelation'),
#            label1 = cms.InputTag("pfCombinedCvsLJetTags"),
#            label2 = cms.InputTag("pfCombinedCvsBJetTags"),
#            folder = cms.string("Ctagger_TagCorrelation"),
#            doCTagPlots = cms.bool(True)
#        )
    )

# Validation configuration
process.bTagValidation.jetMCSrc = 'ak4JetFlavourInfos'
process.bTagValidation.applyPtHatWeight = cms.bool(False)
process.bTagValidation.genJetsMatched = cms.InputTag("patJetGenJetMatch")
process.bTagValidation.softLeptonInfo = cms.InputTag("softPFElectronsTagInfos")
process.bTagValidation.doPUid = cms.bool(True)
process.bTagValidation.flavPlots = flavPlots
process.bTagValidation.ptRanges = ptRanges
process.bTagValidation.etaRanges = etaRanges
process.bTagValidation.tagConfig = tagConfig
process.bTagValidation.doJEC = cms.bool(applyJEC)
if applyJEC:
    process.bTagValidation.JECsource = cms.InputTag(corrLabel)
# Harvesting parameters (same as validation)
process.bTagHarvestMC.flavPlots = flavPlots
process.bTagHarvestMC.ptRanges = ptRanges
process.bTagHarvestMC.etaRanges = etaRanges
process.bTagHarvestMC.tagConfig = tagConfig

# Setup saving DQM parameters
process.dqmEnv.subSystemFolder = 'BTAG'
process.dqmSaver.producer = 'DQM'
process.dqmSaver.workflow = '/POG/BTAG/BJET_MiniAod_41Vars_NewScikitTrain_DQMadapted'
process.dqmSaver.convention = 'Offline'
process.dqmSaver.saveByRun = cms.untracked.int32(-1)
process.dqmSaver.saveAtJobEnd =cms.untracked.bool(True)
process.dqmSaver.forceRunNumber = cms.untracked.int32(1)

# Adapt module configurations to MiniAOD input
process.pfImpactParameterTagInfos.jets = jetCollection
process.pfImpactParameterTagInfos.primaryVertex = primaryVertexCollection
process.pfImpactParameterTagInfos.candidates = candidateCollection
process.pfInclusiveSecondaryVertexFinderTagInfos.extSVCollection = secondaryVertexCollection
process.pfInclusiveSecondaryVertexFinderCvsLTagInfos.extSVCollection = secondaryVertexCollection
process.softPFMuonsTagInfos.jets = jetCollection
process.softPFMuonsTagInfos.primaryVertex = primaryVertexCollection
process.softPFMuonsTagInfos.muons = muonCollection
process.softPFElectronsTagInfos.jets = jetCollection
process.softPFElectronsTagInfos.primaryVertex = primaryVertexCollection
process.softPFElectronsTagInfos.electrons = electronCollection

# Run Path
if not applyJEC:
    #process.dqm = cms.Path( process.btagSeq * process.ctagSeq * process.ak4GenJetsForPUid * process.patJetGenJetMatch * process.bTagValidation * process.bTagHarvestMC * process.dqmSaver)

    process.dqm = cms.Path( process.btagSeq * process.ctagSeq * process.ak4GenJetsForPUid * process.patJetGenJetMatch * process.flavourSeq * process.bTagValidation * process.bTagHarvestMC * process.dqmSaver)
else:
    #process.dqm = cms.Path( process.JECseq * process.btagSeq * process.ctagSeq * process.ak4GenJetsForPUid * process.patJetGenJetMatch * process.bTagValidation * process.bTagHarvestMC * process.dqmSaver)
    process.dqm = cms.Path( process.JECseq * process.btagSeq * process.ctagSeq * process.ak4GenJetsForPUid * process.patJetGenJetMatch * process.flavourSeq * process.bTagValidation * process.bTagHarvestMC * process.dqmSaver)

# Set filenames
process.PoolSource.fileNames = [
'root://cms-xrd-global.cern.ch//store/mc/RunIISpring16MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/08341A1D-2633-E611-B9D5-44A84225CABC.root'
]
