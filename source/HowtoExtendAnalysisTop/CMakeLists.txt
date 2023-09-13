# Declare the name of this package:
atlas_subdir(HowtoExtendAnalysisTop)

# This package uses ROOT:
find_package( ROOT REQUIRED COMPONENTS Core)

# Generate a CINT dictionary source file:
atlas_add_root_dictionary( HowtoExtendAnalysisTop HowtoExtendAnalysisTopDict
                           ROOT_HEADERS Root/LinkDef.h
                           EXTERNAL_PACKAGES ROOT )

# Build a library that other components can link against:
atlas_add_library( HowtoExtendAnalysisTop Root/*.cxx Root/*.h Root/*.icc
                   HowtoExtendAnalysisTop/*.h HowtoExtendAnalysisTop/*.icc HowtoExtendAnalysisTop/*/*.h
                   HowtoExtendAnalysisTop/*/*.icc ${HowtoExtendAnalysisTopDict}
                   PUBLIC_HEADERS HowtoExtendAnalysisTop
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES}
                   PRIVATE_LINK_LIBRARIES TopObjectSelectionTools
                                          TopEventSelectionTools
                                          TopEvent
                                          TopConfiguration
                                          TopAnalysis
                                          JetAnalysisInterfacesLib
                                          AsgTools )

