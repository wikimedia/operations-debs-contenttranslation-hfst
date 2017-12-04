// Copyright (c) 2016 University of Helsinki

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef GUARD_hfst_xerox_rules_h
#define GUARD_hfst_xerox_rules_h

//#include "HfstDataTypes.h"
//#include "HfstSymbolDefs.h"
#include "HfstTransducer.h"

/** @file HfstXeroxRules.h
    \brief Declarations of HFST-XFST replace functions and data types. */


namespace hfst
{
    /** \brief A namespace for HFST xeroxRules functions and data types. */
    namespace xeroxRules
    {
        enum ReplaceType {REPL_UP, REPL_DOWN, REPL_RIGHT, REPL_LEFT};

        // this enum is used in xre_parse.yy for the regex2pfst tool
        // it is not in the xre_parse.yy file because we couldn't make it work there
    enum ReplaceArrow {    E_REPLACE_RIGHT,
                           E_OPTIONAL_REPLACE_RIGHT,
                           E_REPLACE_LEFT,
                           E_OPTIONAL_REPLACE_LEFT,
                           E_REPLACE_RIGHT_MARKUP,
                           E_RTL_LONGEST_MATCH,
                           E_RTL_SHORTEST_MATCH,
                           E_LTR_LONGEST_MATCH,
                           E_LTR_SHORTEST_MATCH
    };
        /**
         * \brief A rule that contains mapping and context and replace type (if any).
         * If rule is A -> B || L _ R , than mapping is cross product of transducers A and B,
         *     context is pair of transducers L and R, and replType is enum REPL_UP.
         */
        class Rule
        {
            /* cross product of mapping transducers */
            HfstTransducerPairVector mapping;
            /* context */
            HfstTransducerPairVector context;
            /* if there is a context, it needs to have a direction (up, left, down or right) */
            ReplaceType replType;

          public:
            Rule ( const HfstTransducerPairVector& );
            Rule ( const HfstTransducerPairVector&, const HfstTransducerPairVector&, ReplaceType );
            
            //copy
            Rule ( const Rule& );
            // default constructor needed for SWIG...
            Rule();

            HfstTransducerPairVector get_mapping() const;
            HfstTransducerPairVector get_context() const;
            ReplaceType get_replType() const;
            
            void encodeFlags();
             
            friend std::ostream& operator<<(std::ostream &out, const Rule &r);
        };

        /**
         *  \brief  In the transducer \tr, change all flag diacritics to "non-special" multichar symbols
         *  It means that @ sign will be changed to $ sign
         *  ie. @P.FOO.BAR@ will be changed into $P.FOO.BAR$
         *  */
         HfstTransducer encodeFlagDiacritics( const HfstTransducer &tr );
         
         /**
         *  \brief  In the transducer \tr, change back all "non-special" flag diacritics to normal,
         * functional flag diacritics
         *  It means that $ sign will be changed to @ sign
         *  ie. $P.FOO.BAR$ will be changed into @P.FOO.BAR@
         *  */
        HfstTransducer decodeFlagDiacritics( const HfstTransducer &tr );
         
         
        // Disjunct all transducers from TransducerVector
        HfstTransducer disjunctVectorMembers( const HfstTransducerVector &trVector );

        /**
         *  \brief Remove makers used in replace functions from a \a tr.
         *  Additionally, decode flag diacritics.
         *  */
        HfstTransducer removeMarkers( const HfstTransducer &tr );

        //Used in changing weights to zero (in constraintComposition function)
        float zero_weight(float f);

        /** \brief Generalized Lenient Composition (by Anssi Yli-Jyr�) of a \a t and a \a Constraint.
         * More about this composition can be found in:
         * http://www.ling.helsinki.fi/users/aylijyra/all/YliJyra-2008b:trafropar:inp.pdf
        */
        HfstTransducer constraintComposition( const HfstTransducer &t, const HfstTransducer &Constraint );

        /** \brief If \a optional is false, the function freely inserts in \a t @_LM_@ and @_RM_@.
         * If it is true, it also inserts @_LM2_@ and @_RM2_@
         */
        void insertFreelyAllTheBrackets( HfstTransducer &t, bool optional );

        /** \brief It is used in bracketedReplace, when the replace expression has context.
         *     Cr' = (Rc .*) << Markers (<,>,|) .o. [I:I | <a:b>]*
         *     Cr = Cr | Cr'
         *     (same for left context, (.* Cl))
         */
        HfstTransducer expandContextsWithMapping (const HfstTransducerPairVector &ContextVector,
                                        const HfstTransducer &mappingWithBracketsAndTmpBoundary,
                                        const HfstTransducer &identityExpanded,
                                        ReplaceType replType,
                                        bool optional);


        /**  \brief
         * Unconditional replace, in multiple contexts
         * first: (.* T<a:b>T .*) - [( .* L1 T<a:b>T R1 .*) u (.* L2 T<a:b>T R2 .*)...],
         *                         where .* = [I:I (+ {tmpMarker (T), <,>} in alphabet) | <a:b>]*
         * then: remove tmpMarker from transducer and alphabet, and do negation:
         *         .* - result from upper operations
         *
         * Also note that context is expanded in this way:
         *         Cr' = (Rc .*) << Markers (<,>,|) .o. [I:I | <a:b>]*
         *         Cr = Cr | Cr'
         *         (same for left context, (.* Cl))
        */
        HfstTransducer bracketedReplace( const Rule &rule, bool optional);

        /**  \brief Bracketed replace for parallel rules */
        HfstTransducer parallelBracketedReplace( const std::vector<Rule> &ruleVector, bool optional);



        //---------------------------------
        //    CONSTRAINTS
        //---------------------------------

        // (help function)
        // returns: [ B:0 | 0:B | ?-B ]*
        // which is used in some constraints
        HfstTransducer constraintsRightPart( ImplementationType type );

        // .#. ?* <:0 0:> ?* .#.
        // filters out empty string
        HfstTransducer oneBetterthanNoneConstraint( const HfstTransducer &uncondidtionalTr );


        // ?* <:0 [B:0]* [I-B] [ B:0 | 0:B | ?-B ]*
        HfstTransducer leftMostConstraint( const HfstTransducer &uncondidtionalTr );

        // [ B:0 | 0:B | ?-B ]* [I-B]+  >:0 [ ?-B ]*
        HfstTransducer rightMostConstraint( const HfstTransducer &uncondidtionalTr );

        // Longest match
        // it should be composed to left most transducer........
        // ?* < [?-B]+ 0:> [ ? | 0:< | <:0 | 0:> | B ] [ B:0 | 0:B | ?-B ]*
        HfstTransducer longestMatchLeftMostConstraint( const HfstTransducer &uncondidtionalTr );


        // Longest match RIGHT most
        HfstTransducer longestMatchRightMostConstraint(const HfstTransducer &uncondidtionalTr );


        // Shortest match
        // it should be composed to left most transducer........
        // ?* < [?-B]+ >:0
        // [?-B] or [ ? | 0:< | <:0 | >:0 | B ][?-B]+
        // [ B:0 | 0:B | ?-B ]*
        HfstTransducer shortestMatchLeftMostConstraint( const HfstTransducer &uncondidtionalTr );


        // Shortest match
        // it should be composed to left most transducer........
        //[ B:0 | 0:B | ?-B ]*
        // [?-B] or [?-B]+  [ ? | 0:> | >:0 | <:0 | B ]
        // <:0 [?-B]+   > ?*
        HfstTransducer shortestMatchRightMostConstraint( const HfstTransducer &uncondidtionalTr );


        // ?* [ BL:0 (?-B)+ BR:0 ?* ]+
        HfstTransducer mostBracketsPlusConstraint( const HfstTransducer &uncondidtionalTr );


        // ?* [ BL:0 (?-B)* BR:0 ?* ]+
        HfstTransducer mostBracketsStarConstraint( const HfstTransducer &uncondidtionalTr );

        // ?* B2 ?*
        HfstTransducer removeB2Constraint( const HfstTransducer &t );

        // to avoid repetition in empty replace rule
        HfstTransducer noRepetitionConstraint( const HfstTransducer &t );

        /**  \brief
           * It applies boundary marker from contexts (.#.) to \a t
           *
           * [0:.#. | ? - .#.]*
           *         .o.
           *     tr., ie. a -> b || .#. _ ;
           *         .o.
           *     .#. (? - .#.)* .#.
           *         .o.
           * [.#.:0 | ? - .#.]*
           */
        HfstTransducer applyBoundaryMark( const HfstTransducer &t );


        //---------------------------------
        //    INTERFACE HELPING FUNCTIONS
        //---------------------------------
        //used by hfst-regexp parser
        HfstTransducerPair create_mapping_for_mark_up_replace( const HfstTransducerPair &mappingPair,
                                                          const HfstTransducerPair &marks );
        // HfstTransducerPairVector create_mapping_for_mark_up_replace( const HfstTransducerPairVector &mappingPairVector,
                                                                                        // const StringPair &marks );

        // HfstTransducerPairVector create_mapping_for_mark_up_replace( const HfstTransducerPairVector &mappingPairVector,
                                                                                             // const HfstTransducerPair &marks );
        //---------------------------------
        //    REPLACE FUNCTIONS - INTERFACE
        //---------------------------------

        // replace up, left, right, down
        HfstTransducer replace(    const Rule &rule, bool optional);
        // for parallel rules
        HfstTransducer replace(    const std::vector<Rule> &ruleVector, bool optional);
        // replace up, left, right, down
        HfstTransducer replace_left( const Rule &rule, bool optional);
        // for parallel rules
        HfstTransducer replace_left( const std::vector<Rule> &ruleVector, bool optional);
        // left to right
        HfstTransducer replace_leftmost_longest_match( const Rule &rule );
        // left to right
        HfstTransducer replace_leftmost_longest_match( const std::vector<Rule> &ruleVector );
        // right to left
        HfstTransducer replace_rightmost_longest_match( const Rule &rule );

        // right to left
        HfstTransducer replace_rightmost_longest_match( const std::vector<Rule> &ruleVector );

        HfstTransducer replace_leftmost_shortest_match( const Rule &rule);

        HfstTransducer replace_leftmost_shortest_match(const std::vector<Rule> &ruleVector );
        HfstTransducer replace_rightmost_shortest_match( const Rule &rule );
        HfstTransducer replace_rightmost_shortest_match( const std::vector<Rule> &ruleVector );


        // the problem is that the mark-up rules can be mixed with ordinary rules
        // ie a -> b ... c , a -> d ;
        // this is why each markup mapping should be accessed seperratly
        // HfstTransducer mark_up_replace(    const Rule &rule,
                                // const StringPair &marks,
                                // bool optional);

        // HfstTransducer mark_up_replace(const Rule &rule,
                                           // const HfstTransducerPair &marks,
                                           // bool optional);


        // HfstTransducer mark_up_replace(    const std::vector<MarkUpRule> &markUpRuleVector,
                                // bool optional);

        // replace up, left, right, down
        HfstTransducer replace_epenthesis(    const Rule &rule, bool optional);
        // replace up, left, right, down
        HfstTransducer replace_epenthesis(    const std::vector<Rule> &ruleVector, bool optional);


        //---------------------------------
        //    RESTRICTION FUNCTIONS
        //---------------------------------

        // create marks for given i
        //static StringPair restrictionMarks( int i);

        /*
         * define AA1a [  [. 0 .] -> LEFT_MARK || _ center ];
         * define AA1b [  [. 0 .] -> RIGHT_MARK || center _ ];
         * retval = AA1 .o. AA2
         */
        //static HfstTransducer surroundCenterWithBrackets( const HfstTransducer &center,
        //                                           const HfstTransducer &leftMark,
        //                                           const HfstTransducer &rightMark);
        // Contexts
        // define NOS1 [ %[ -> 0 || b / B _ ];
        // define NOF1 [ %] -> 0 || _ c / B ];
        /*static HfstTransducer removeBracketsInContext( const HfstTransducerPairVector &context,
                                                   const HfstTransducer &leftMark,
                                                   const HfstTransducer &rightMark,
                                                   int i);*/ // NOT DEFINED
        // Restriction function "=>"
        HfstTransducer restriction( const HfstTransducer &automata, const HfstTransducerPairVector &context);
        HfstTransducer before( const HfstTransducer &left, const HfstTransducer &right);
        HfstTransducer after( const HfstTransducer &left, const HfstTransducer &right);
    }
}

// define guard
#endif
