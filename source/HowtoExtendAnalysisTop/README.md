# ABOUT
This is an example skeleton package for extending AnalysisTop functionality.

It contains the following skeleton code:
  * For saving extra variables in output NTuples in `CustomEventSaver`
  * Example extra selector that can be used in the AT configuration text file (`EvenEventNumberSelector`), that simply selects events with even event number
  * Custom tools loader that is responsible for loading any selectors such as above, defined in `HowtoExtendAnalysisTopLoader` class
  * Custom object loader class `CustomObjectLoader`, that is used to alter the object selection, for example for:
    * Jets, as defined in `CustomJet`
    * Muons, as defined in `CustomMuon`
  * `LinkDef.h` for declaring the extra classes in the package for which a ROOT dictionary is to be created

An example AnalysisTop configuration file that shows how to load the custom event saver and custom object loader, is stored in `share/ExtendedAnalysisTop.txt`

# How to use this
Instructions on how to build this package with AnalysisTop and further information on how to extend AnalysisTop is provided in the [AnalysisTop xAOD start guide](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopxAODStartGuideR21#5_Extend_AnalysisTop_for_your_ow)
