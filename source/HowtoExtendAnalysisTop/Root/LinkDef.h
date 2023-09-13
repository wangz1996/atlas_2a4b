/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
*/

#include "HowtoExtendAnalysisTop/CustomObjectLoader.h"
#include "HowtoExtendAnalysisTop/HowtoExtendAnalysisTopLoader.h"
#include "HowtoExtendAnalysisTop/CustomEventSaver.h"
#include "HowtoExtendAnalysisTop/DynamicKeysEventSaver.h"

#ifdef __CINT__

#pragma extra_include "HowtoExtendAnalysisTop/CustomObjectLoader.h";
#pragma extra_include "HowtoExtendAnalysisTop/HowtoExtendAnalysisTopLoader.h";
#pragma extra_include "HowtoExtendAnalysisTop/CustomEventSaver.h";
#pragma extra_include "HowtoExtendAnalysisTop/DynamicKeysEventSaver.h";

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;

//for loading the object selection at run time
#pragma link C++ class top::CustomObjectLoader+;
#pragma link C++ class top::HowtoExtendAnalysisTopLoader+;
#pragma link C++ class top::CustomEventSaver+;
#pragma link C++ class top::DynamicKeysEventSaver+;

#endif
