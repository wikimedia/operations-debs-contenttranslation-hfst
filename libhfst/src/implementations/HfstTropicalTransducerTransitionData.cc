// Copyright (c) 2016 University of Helsinki                          
//                                                                    
// This library is free software; you can redistribute it and/or      
// modify it under the terms of the GNU Lesser General Public         
// License as published by the Free Software Foundation; either       
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more      
// information.

#include "HfstTropicalTransducerTransitionData.h"

namespace hfst {

  namespace implementations {

    HfstTropicalTransducerTransitionData::Number2SymbolVector
    HfstTropicalTransducerTransitionData::number2symbol_map;
    Number2SymbolVectorInitializer 
    dummy1(HfstTropicalTransducerTransitionData::number2symbol_map);
    
    HfstTropicalTransducerTransitionData::Symbol2NumberMap 
    HfstTropicalTransducerTransitionData::symbol2number_map;
    Symbol2NumberMapInitializer 
    dummy2(HfstTropicalTransducerTransitionData::symbol2number_map);
    
    unsigned int HfstTropicalTransducerTransitionData::max_number=2;

  }

}
