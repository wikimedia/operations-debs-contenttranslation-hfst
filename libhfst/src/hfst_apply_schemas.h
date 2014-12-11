//       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

/** @file hfst_apply_schemas.h
    \brief declarations for HFST functions that take two or more parameters */

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
 /* Add your library here */
 //#if HAVE_MY_TRANSDUCER_LIBRARY
 //my_namespace::MyFst * (*my_transducer_library_funct)
 //  (my_namespace::MyFst *, my_namespace::MyFst *),
 //#endif
 HfstTransducer &another, bool harmonize );
