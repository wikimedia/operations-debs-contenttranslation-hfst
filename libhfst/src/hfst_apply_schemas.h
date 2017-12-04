// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

/** \brief declarations for HFST functions that take two or more parameters */

HfstTransducer &apply(
#if HAVE_SFST
 SFST::Transducer * (*sfst_funct)(SFST::Transducer *),
#endif
#if HAVE_OPENFST
 fst::StdVectorFst * (*tropical_ofst_funct)(fst::StdVectorFst *),
#if HAVE_OPENFST_LOG
 hfst::implementations::LogFst * (*log_ofst_funct)
 (hfst::implementations::LogFst *),
#endif
#endif
#if HAVE_FOMA
 fsm * (*foma_funct)(fsm *),
#endif
#if HAVE_XFSM
 NETptr (*xfsm_funct)(NETptr),
#endif
 /* Add your library here */
 //#if HAVE_MY_TRANSDUCER_LIBRARY
 //my_namespace::MyFst * (*my_transducer_library_funct)(my_namespace::MyFst *),
 //#endif
 bool dummy /* makes sure there is always a parameter after the
               function pointer parameters, so commas between parameters
               are easier to handle */
);

HfstTransducer &apply(
#if HAVE_SFST
 SFST::Transducer * (*sfst_funct)(SFST::Transducer *, unsigned int),
#endif
#if HAVE_OPENFST
 fst::StdVectorFst * (*tropical_ofst_funct)(fst::StdVectorFst *, unsigned int),
#if HAVE_OPENFST_LOG
 hfst::implementations::LogFst * (*log_ofst_funct)
 (hfst::implementations::LogFst *, unsigned int),
#endif
#endif
#if HAVE_FOMA
 fsm * (*foma_funct)(fsm *, unsigned int),
#endif
#if HAVE_XFSM
 NETptr (*xfsm_funct)(NETptr, unsigned int),
#endif
 /* Add your library here */
 //#if HAVE_MY_TRANSDUCER_LIBRARY
 //my_namespace::MyFst * (*my_transducer_library_funct)
 //(my_namespace::MyFst *, unsigned int),
 //#endif
 unsigned int n);

HfstTransducer &apply(
#if HAVE_SFST
 SFST::Transducer * (*sfst_funct)(SFST::Transducer *, String, String),
#endif
#if HAVE_OPENFST
 fst::StdVectorFst * (*tropical_ofst_funct)(fst::StdVectorFst *,String,
                                            String),
#if HAVE_OPENFST_LOG
 hfst::implementations::LogFst * (*log_ofst_funct)
 (hfst::implementations::LogFst *,
  String,String),
#endif
#endif
#if HAVE_FOMA
 fsm * (*foma_funct)(fsm *, String, String),
#endif
#if HAVE_XFSM
 NETptr (*xfsm_funct)(NETptr, String, String),
#endif
 /* Add your library here */
 //#if HAVE_MY_TRANSDUCER_LIBRARY
 //my_namespace::MyFst * (*my_transducer_library_funct)
 // (my_namespace::MyFst *, String, String),
 //#endif
 String k1, String k2);

HfstTransducer &apply(
#if HAVE_SFST
 SFST::Transducer * (*sfst_funct)(SFST::Transducer *,
                                  SFST::Transducer *),
#endif
#if HAVE_OPENFST
 fst::StdVectorFst * (*tropical_ofst_funct)(fst::StdVectorFst *,
                                            fst::StdVectorFst *),
#if HAVE_OPENFST_LOG
 hfst::implementations::LogFst * (*log_ofst_funct)
 (hfst::implementations::LogFst *,
  hfst::implementations::LogFst *),
#endif
#endif
#if HAVE_FOMA
 fsm * (*foma_funct)(fsm *,
                     fsm *),
#endif
#if HAVE_XFSM
 NETptr (*xfsm_funct)(NETptr, NETptr),
#endif
 /* Add your library here */
 //#if HAVE_MY_TRANSDUCER_LIBRARY
 //my_namespace::MyFst * (*my_transducer_library_funct)
 //  (my_namespace::MyFst *, my_namespace::MyFst *),
 //#endif
 HfstTransducer &another, bool harmonize );
