/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
*/

#include "HowtoExtendAnalysisTop/CustomJet.h"

#include <cmath>

namespace top{
  CustomJet::CustomJet(const double ptMin,const double ptMax,const double etamax, const bool doJVTCut) :
    m_ptMin(ptMin),
    m_ptMax(ptMax),
    m_etamax(etamax),
    m_applyJVTCut(doJVTCut),
    m_jvt_tool("JetJvtEfficiencyTool")
  {
      top::check(m_jvt_tool.retrieve(),                "Failed to retrieve JVT tool");
  }  
  
  bool CustomJet::passSelection(const xAOD::Jet& jet)
  {
    ///-- Jet is not below lower pT cut --///
    if (jet.pt() < m_ptMin)
        return false;
    
    ///-- Jet is not above upper pT cut --///
    ///-- This is a demonstration of how to extend AnalysisTop --///
    if (jet.pt() > m_ptMax)
        return false;   
    
    
    if (std::fabs(jet.eta()) > m_etamax)
        return false;
    
    if (m_applyJVTCut) {
      if (!m_jvt_tool->passesJvtCut(jet)) {
        jet.auxdecor<char>("passJVT")          = 0;
      }
      else {
        jet.auxdecor<char>("passJVT")          = 1;
      }
    }

    
    jet.auxdecor<char>("good")          = 1;
    jet.auxdecor<char>("closeToLepton") = 0;
    
    return true;
  }
  
  void CustomJet::print(std::ostream& os) const {
    os << "CustomJet\n"
       << "    * pT > " << m_ptMin << " && pT < "<<m_ptMax<< "\n"
       << "    * |eta| < " << m_etamax << "\n";
  }
}
