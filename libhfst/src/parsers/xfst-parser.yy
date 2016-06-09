%{
// Copyright (c) 2016 University of Helsinki                          
//                                                                    
// This library is free software; you can redistribute it and/or      
// modify it under the terms of the GNU Lesser General Public         
// License as published by the Free Software Foundation; either       
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more      
// information.

//! @file xfst-parser.yy
//!
//! @brief A parser for xfst
//!
//! @author Tommi A. Pirinen

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <cstdlib>
#include <cstdio>

#include <string>
using std::string;

namespace hfst {
  class HfstTransducer;
}

#include "XfstCompiler.h"
#include "xfst-utils.h"

#define CHECK if (hfst::xfst::xfst_->get_fail_flag()) { YYABORT; }

// obligatory yacc stuff
extern int hxfstlineno;
void hxfsterror(const char *text);
int hxfstlex(void);

%}

// ouch
%name-prefix="hxfst"
// yup, nice messages
%error-verbose
// just cos I use the llloc struct
%locations

%union 
{
    char* name;
    char* text;
    char** list;
    char* file;
    void* nothing;
}

%token <text> APROPOS DESCRIBE ECHO SYSTEM QUIT HFST
%token <name> NAMETOKEN NAMECHAR GLOB PROTOTYPE
              DEFINE_NAME DEFINE_FUNCTION
%token <list> RANGE
%token <file> REDIRECT_IN REDIRECT_OUT
%token SAVE_PROLOG FOR REVERSE VIEW LOADD PRINT_LABEL_COUNT
       TEST_OVERLAP TEST_NONNULL CONCATENATE LOADS INVERT PRINT_ALIASES
       PRINT_LABELS XFST_OPTIONAL PRINT_SHORTEST_STRING_SIZE READ_PROPS
       TEST_FUNCT PRINT_LABELMAPS SUBSTRING COMPOSE READ_SPACED
       TEST_UPPER_UNI COLLECT_EPSILON_LOOPS ZERO_PLUS INSPECT
       ROTATE PRINT_WORDS POP SAVE_SPACED DEFINE SHOW
       PRINT_LONGEST_STRING_SIZE TEST_EQ SORT SAVE_DEFINITIONS SAVE_DOT
       TEST_UPPER_BOUNDED COMPLETE PRINT_FILE_INFO INTERSECT END_SUB
       TURN PRINT_LIST SUBSTITUTE_SYMBOL APPLY_UP ONE_PLUS UNDEFINE
       EPSILON_REMOVE PRINT_RANDOM_WORDS CTRLD EXTRACT_UNAMBIGUOUS
       SEMICOLON PRINT_LOWER_WORDS READ_PROLOG CLEAR PRINT_SIGMA_COUNT
       SUBSTITUTE_NAMED PRINT_FLAGS SET NEGATE APPLY_DOWN PRINT_STACK SAVE_STACK
       PUSH TEST_LOWER_BOUNDED PRINT_DEFINED APPLY_MED SHOW_ALL PRINT_ARCCOUNT
       PRINT_SIZE TEST_NULL PRINT_RANDOM_UPPER PRINT_LONGEST_STRING UPPER_SIDE
       XFST_IGNORE TEST_UNAMBIGUOUS PRINT READ_TEXT UNLIST SUBSTITUTE_LABEL
       SAVE_DEFINITION ELIMINATE_FLAG EDIT_PROPS PRINT_UPPER_WORDS NAME
       EXTRACT_AMBIGUOUS DEFINE_ALIAS PRINT_RANDOM_LOWER CROSSPRODUCT
       COMPACT_SIGMA SOURCE AMBIGUOUS ELIMINATE_ALL PRINT_SIGMA
       PRINT_SHORTEST_STRING LEFT_PAREN PRINT_PROPS READ_REGEX
       DEFINE_LIST TEST_ID PRINT_LISTS TEST_SUBLANGUAGE TEST_LOWER_UNI
       COMPILE_REPLACE_UPPER CLEANUP ADD_PROPS PRINT_SIGMA_WORD_COUNT SHUFFLE
       COLON SAVE_TEXT DETERMINIZE SIGMA COMPILE_REPLACE_LOWER UNION
       PRINT_DIR LIST LOWER_SIDE MINIMIZE MINUS PRINT_NAME PRUNE_NET
       PUSH_DEFINED READ_LEXC READ_ATT TWOSIDED_FLAGS WRITE_ATT ASSERT LABEL_NET
       LOOKUP_OPTIMIZE REMOVE_OPTIMIZATION TEST_INFINITELY_AMBIGUOUS
       XFST_ERROR
       NEWLINE

%token <text> REGEX
%token <text> APPLY_INPUT
    
%type <text> COMMAND_SEQUENCE NAMETOKEN_LIST QUOTED_NAMETOKEN_LIST LABEL_LIST LABEL
%%

XFST_SCRIPT: COMMAND_LIST 
           | COMMAND_LIST CTRLD
           ;

COMMAND_LIST: COMMAND_LIST COMMAND 
            | COMMAND
            ;

COMMAND: ADD_PROPS REDIRECT_IN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->add_props(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | ADD_PROPS NAMETOKEN_LIST CTRLD {
            hfst::xfst::xfst_->add_props($2);
            free($2); CHECK;
       }
       | EDIT_PROPS END_COMMAND {
            hxfsterror("NETWORK PROPERTY EDITOR unimplemented\n");
            return EXIT_FAILURE;
       }
       // apply
       | APPLY_UP END_COMMAND {
       	    hfst::xfst::xfst_->apply_up(stdin); CHECK;
       }
       | APPLY_UP APPLY_INPUT END_COMMAND {
       	    hfst::xfst::xfst_->apply_up($2); CHECK;
       }
       | APPLY_UP NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->apply_up($2);
            free($2); CHECK;
       }
       | APPLY_UP REDIRECT_IN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->apply_up(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | APPLY_UP END_COMMAND NAMETOKEN_LIST END_SUB {
            hfst::xfst::xfst_->apply_up($3);
            free($3); CHECK;
       }
       | APPLY_DOWN END_COMMAND {
            hfst::xfst::xfst_->apply_down(stdin); CHECK;
       }
       | APPLY_DOWN APPLY_INPUT END_COMMAND {
       	    hfst::xfst::xfst_->apply_down($2); CHECK;
       }
       | APPLY_DOWN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->apply_down($2);
            free($2); CHECK;
       }
       | APPLY_DOWN REDIRECT_IN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->apply_down(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | APPLY_DOWN END_COMMAND NAMETOKEN_LIST END_SUB {
            hfst::xfst::xfst_->apply_down($3);
            free($3); CHECK;
       }
       | APPLY_MED NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->apply_med($2);
            free($2); CHECK;
       }
       | APPLY_MED REDIRECT_IN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->apply_med(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | APPLY_MED END_COMMAND NAMETOKEN_LIST END_SUB {
            hfst::xfst::xfst_->apply_med($3);
            free($3); CHECK;
       }
       | LOOKUP_OPTIMIZE END_COMMAND {
            hfst::xfst::xfst_->lookup_optimize(); CHECK;
       }
       | REMOVE_OPTIMIZATION END_COMMAND {
            hfst::xfst::xfst_->remove_optimization(); CHECK;
       }
       // ambiguous
       | AMBIGUOUS END_COMMAND {
            hxfsterror("unimplemetend ambiguous\n");
            return EXIT_FAILURE;
       }
       | EXTRACT_AMBIGUOUS END_COMMAND {
            hxfsterror("unimplemetend ambiguous\n");
            return EXIT_FAILURE;
       }
       | EXTRACT_UNAMBIGUOUS END_COMMAND {
            hxfsterror("unimplemetend ambiguous\n");
            return EXIT_FAILURE;
       }
       // define
       | DEFINE_ALIAS NAMETOKEN COMMAND_SEQUENCE END_COMMAND{
            hfst::xfst::xfst_->define_alias($2, $3);
            free($2);
            free($3); CHECK;
       }
       | DEFINE_ALIAS NAMETOKEN END_COMMAND NAMETOKEN_LIST END_SUB {
            hfst::xfst::xfst_->define_alias($2, $4);
            free($2);
            free($4); CHECK;
       }
       | LIST NAMETOKEN NAMETOKEN_LIST SEMICOLON END_COMMAND {
            hfst::xfst::xfst_->define_list($2, $3);
            free($2);
            free($3); CHECK;
       }
       | LIST NAMETOKEN RANGE END_COMMAND {
            hfst::xfst::xfst_->define_list($2, $3[0], $3[1]);
            free($2);
            free($3[0]);
            free($3[1]);
            free($3); CHECK;
       }
       | DEFINE_NAME {
            hfst::xfst::xfst_->define($1);
            free($1); CHECK;
       }
       | DEFINE_NAME REGEX {
            hfst::xfst::xfst_->define($1, $2);
            free($1);
            free($2); CHECK;
       }
       | DEFINE_FUNCTION REGEX {
            hfst::xfst::xfst_->define_function($1, $2);
            free($1);
            free($2); CHECK;
       }
       | UNDEFINE NAMETOKEN_LIST END_COMMAND {
            hfst::xfst::xfst_->undefine($2);
            free($2); CHECK;
       }
       | UNLIST NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->unlist($2);
            free($2); CHECK;
       }
       | NAME NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->name_net($2);
            free($2); CHECK;
       }
       | LOADD NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->load_definitions($2);
            free($2); CHECK;
       }
       // help
       | APROPOS END_COMMAND { 
            hfst::xfst::xfst_->apropos($1);
            free($1); CHECK;
       }
       | DESCRIBE END_COMMAND { 
            hfst::xfst::xfst_->describe($1); CHECK;
       }
       // stack
       | CLEAR END_COMMAND {
            hfst::xfst::xfst_->clear(); CHECK;
       }
       | POP END_COMMAND {
            hfst::xfst::xfst_->pop(); CHECK;
       }
       | PUSH_DEFINED NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->push($2);
            free($2); CHECK;
       }
       | PUSH_DEFINED END_COMMAND {
            hfst::xfst::xfst_->push(); CHECK;
       }
       | TURN END_COMMAND {
            hfst::xfst::xfst_->turn(); CHECK;
       }
       | ROTATE END_COMMAND {
            hfst::xfst::xfst_->rotate(); CHECK;
       }
       | LOADS REDIRECT_IN END_COMMAND {
            hfst::xfst::xfst_->load_stack($2);
            free($2); CHECK;
       }
       | LOADS NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->load_stack($2);
            free($2); CHECK;
       }
       | LOADS NAMETOKEN SEMICOLON END_COMMAND {
            hfst::xfst::xfst_->load_stack($2);
            free($2); CHECK;
       }
       // wrobble
       | COLLECT_EPSILON_LOOPS END_COMMAND {
            hfst::xfst::xfst_->collect_epsilon_loops(); CHECK;
       }
       | COMPACT_SIGMA END_COMMAND {
            hfst::xfst::xfst_->compact_sigma(); CHECK;
       }
       // flags
       | ELIMINATE_FLAG NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->eliminate_flag($2);
            free($2); CHECK;
       }
       | ELIMINATE_ALL END_COMMAND {
            hfst::xfst::xfst_->eliminate_flags(); CHECK;
       }
       // system
       | ECHO { 
            hfst::xfst::xfst_->echo($1);
            free($1); CHECK;
       }
       | QUIT { 
            hfst::xfst::xfst_->quit($1);
            free($1);
            return EXIT_SUCCESS;
       }
       | HFST {
            hfst::xfst::xfst_->hfst($1);
            free($1); CHECK;
       }
       | SOURCE NAMETOKEN END_COMMAND {
            hxfsterror("source not implemented yywrap\n");
            return EXIT_FAILURE;
       }
       | SYSTEM {
            hfst::xfst::xfst_->system($1);
            free($1); CHECK;
       }
       | VIEW END_COMMAND {
            hfst::xfst::xfst_->view_net(); CHECK;
            //hxfsterror("view not implemented\n");
            //return EXIT_FAILURE;
       }
       // vars
       | SET NAMETOKEN NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($3);
            if (i != -1)
              hfst::xfst::xfst_->set($2, i);
            else
              hfst::xfst::xfst_->set($2, $3);
            free($2);
            free($3); CHECK;
       }
       | SHOW NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->show($2);
            free($2); CHECK;
       }
       | SHOW_ALL END_COMMAND {
            hfst::xfst::xfst_->show(); CHECK;
       }
       | TWOSIDED_FLAGS END_COMMAND {
            hfst::xfst::xfst_->twosided_flags(); CHECK;
       }
       // tests
       | TEST_EQ END_COMMAND {
            hfst::xfst::xfst_->test_eq(); CHECK;
       }
       | TEST_FUNCT END_COMMAND {
            hfst::xfst::xfst_->test_funct(); CHECK;
       }
       | TEST_ID END_COMMAND {
            hfst::xfst::xfst_->test_id(); CHECK;
       }
       | TEST_INFINITELY_AMBIGUOUS {
            hfst::xfst::xfst_->test_infinitely_ambiguous(); CHECK;
       }
       | TEST_LOWER_BOUNDED END_COMMAND {
            hfst::xfst::xfst_->test_lower_bounded(); CHECK;
       }
       | TEST_LOWER_UNI END_COMMAND {
            hfst::xfst::xfst_->test_lower_uni(); CHECK;
       }
       | TEST_UPPER_BOUNDED END_COMMAND {
            hfst::xfst::xfst_->test_upper_bounded(); CHECK;
       }
       | TEST_UPPER_UNI END_COMMAND {
            hfst::xfst::xfst_->test_upper_uni(); CHECK;
       }
       | TEST_NONNULL END_COMMAND {
            hfst::xfst::xfst_->test_nonnull(); CHECK;
       }
       | TEST_NULL END_COMMAND {
            hfst::xfst::xfst_->test_null(); CHECK;
       }
       | TEST_OVERLAP END_COMMAND {
            hfst::xfst::xfst_->test_overlap(); CHECK;
       }
       | TEST_SUBLANGUAGE END_COMMAND {
            hfst::xfst::xfst_->test_sublanguage(); CHECK;
       }
       | TEST_UNAMBIGUOUS END_COMMAND {
            hfst::xfst::xfst_->test_unambiguous(); CHECK;
       }
       // assertions
       | ASSERT TEST_EQ END_COMMAND {
            hfst::xfst::xfst_->test_eq(true); CHECK;
       }
       | ASSERT TEST_FUNCT END_COMMAND {
            hfst::xfst::xfst_->test_funct(true); CHECK;
       }
       | ASSERT TEST_ID END_COMMAND {
            hfst::xfst::xfst_->test_id(true); CHECK;
       }
       | ASSERT TEST_LOWER_BOUNDED END_COMMAND {
            hfst::xfst::xfst_->test_lower_bounded(true); CHECK;
       }
       | ASSERT TEST_LOWER_UNI END_COMMAND {
            hfst::xfst::xfst_->test_lower_uni(true); CHECK;
       }
       | ASSERT TEST_UPPER_BOUNDED END_COMMAND {
            hfst::xfst::xfst_->test_upper_bounded(true); CHECK;
       }
       | ASSERT TEST_UPPER_UNI END_COMMAND {
            hfst::xfst::xfst_->test_upper_uni(true); CHECK;
       }
       | ASSERT TEST_NONNULL END_COMMAND {
            hfst::xfst::xfst_->test_nonnull(true); CHECK;
       }
       | ASSERT TEST_NULL END_COMMAND {
            hfst::xfst::xfst_->test_null(true); CHECK;
       }
       | ASSERT TEST_OVERLAP END_COMMAND {
            hfst::xfst::xfst_->test_overlap(true); CHECK;
       }
       | ASSERT TEST_SUBLANGUAGE END_COMMAND {
            hfst::xfst::xfst_->test_sublanguage(true); CHECK;
       }
       | ASSERT TEST_UNAMBIGUOUS END_COMMAND {
            hfst::xfst::xfst_->test_unambiguous(true); CHECK;
       }
       // substitutes
       | SUBSTITUTE_NAMED NAMETOKEN FOR NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->substitute_named($2, $4); // TODO!
            free($2);
            free($4); CHECK;
       }
       | SUBSTITUTE_LABEL LABEL_LIST FOR LABEL END_COMMAND {
            hfst::xfst::xfst_->substitute_label($2, $4);
            free($2);
            free($4); CHECK;
       }
       | SUBSTITUTE_SYMBOL QUOTED_NAMETOKEN_LIST FOR NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->substitute_symbol($2, $4);
            free($2);
            free($4); CHECK;
       }
       // prints
       | PRINT_ALIASES REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_aliases(&oss);
            oss.close(); CHECK;
       }
       | PRINT_ALIASES END_COMMAND {
            hfst::xfst::xfst_->print_aliases(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_ARCCOUNT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_arc_count(&oss);
            oss.close(); CHECK;
       }
       | PRINT_ARCCOUNT NAMETOKEN END_COMMAND {
            if (strcmp($2, "upper") && strcmp($2, "lower"))
            {
                hxfsterror("should be upper or lower");
                return EXIT_FAILURE;
            }
            hfst::xfst::xfst_->print_arc_count($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_ARCCOUNT END_COMMAND {
            hfst::xfst::xfst_->print_arc_count(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_DEFINED REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_defined(&oss);
            oss.close(); CHECK;
       }
       | PRINT_DEFINED END_COMMAND {
            hfst::xfst::xfst_->print_defined(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_DIR GLOB REDIRECT_OUT END_COMMAND {
            std::ofstream oss($3);
            hfst::xfst::xfst_->print_dir($2, &oss);
            oss.close();
            free($3); CHECK;
       }
       | PRINT_DIR GLOB END_COMMAND {
            hfst::xfst::xfst_->print_dir($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_DIR REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_dir("*", &oss);
            oss.close(); CHECK;
       }
       | PRINT_DIR END_COMMAND {
            hfst::xfst::xfst_->print_dir("*", &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_FILE_INFO REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_file_info(&oss);
            oss.close(); CHECK;
       }
       | PRINT_FILE_INFO END_COMMAND {
            hfst::xfst::xfst_->print_file_info(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_FLAGS REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_flags(&oss);
            oss.close(); CHECK;
       }
       | PRINT_FLAGS END_COMMAND {
            hfst::xfst::xfst_->print_flags(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_LABELS NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_labels($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_LABELS REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_labels(&oss);
            oss.close(); CHECK;
       }
       | PRINT_LABELS END_COMMAND {
            hfst::xfst::xfst_->print_labels(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_LABEL_COUNT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_label_count(&oss);
            oss.close(); CHECK;
       }
       | PRINT_LABEL_COUNT END_COMMAND {
            hfst::xfst::xfst_->print_label_count(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_LIST NAMETOKEN REDIRECT_OUT END_COMMAND {
            std::ofstream oss($3);
            hfst::xfst::xfst_->print_list($2, &oss);
            oss.close();
            free($2); CHECK;
       }
       | PRINT_LIST NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_list($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_LISTS REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_list(&oss);
            oss.close(); CHECK;
       }
       | PRINT_LISTS END_COMMAND {
            hfst::xfst::xfst_->print_list(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_LONGEST_STRING REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_longest_string(&oss);
            //hfst::xfst::xfst_fclose(f, $2); 
            oss.close();
            CHECK;
       }
       | PRINT_LONGEST_STRING END_COMMAND {
            //hfst::xfst::xfst_->print_longest_string(&hfst::xfst::xfst_->get_output_stream()); 
            hfst::xfst::xfst_->print_longest_string(&hfst::xfst::xfst_->get_output_stream()); 
            CHECK;
       }
       | PRINT_LONGEST_STRING_SIZE REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_longest_string_size(&oss);
            //hfst::xfst::xfst_fclose(f, $2); 
            oss.close();
            CHECK;
       }
       | PRINT_LONGEST_STRING_SIZE END_COMMAND {
            //hfst::xfst::xfst_->print_longest_string_size(&hfst::xfst::xfst_->get_output_stream()); 
            hfst::xfst::xfst_->print_longest_string_size(&hfst::xfst::xfst_->get_output_stream()); 
            CHECK;
       }
       | PRINT_NAME REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_name(&oss);
            oss.close(); CHECK;
       }
       | PRINT_NAME END_COMMAND {
            hfst::xfst::xfst_->print_name(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_SHORTEST_STRING REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_shortest_string(&oss);
            //hfst::xfst::xfst_fclose(f, $2);
            oss.close();
            CHECK;
       }
       | PRINT_SHORTEST_STRING END_COMMAND {
            //hfst::xfst::xfst_->print_shortest_string(&hfst::xfst::xfst_->get_output_stream()); 
            hfst::xfst::xfst_->print_shortest_string(&hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_SHORTEST_STRING_SIZE REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_shortest_string_size(&oss);
            //hfst::xfst::xfst_fclose(f, $2);
            oss.close(); 
            CHECK;
       }
       | PRINT_SHORTEST_STRING_SIZE END_COMMAND {
            //hfst::xfst::xfst_->print_shortest_string_size(&hfst::xfst::xfst_->get_output_stream()); 
            hfst::xfst::xfst_->print_shortest_string_size(&hfst::xfst::xfst_->get_output_stream()); 
            CHECK;
       }
       | PRINT_LOWER_WORDS NAMETOKEN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_lower_words($2, hfst::xfst::nametoken_to_number($3), &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_LOWER_WORDS NAMETOKEN NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($4, "w");
            std::ofstream oss($4);
            hfst::xfst::xfst_->print_lower_words($2, hfst::xfst::nametoken_to_number($3), &oss);
            free($2);
            //hfst::xfst::xfst_fclose(f, $4); 
            oss.close();
            CHECK;
       }
       | PRINT_LOWER_WORDS NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_lower_words(NULL, i, &hfst::xfst::xfst_->get_output_stream());
            else
              hfst::xfst::xfst_->print_lower_words($2, 0, &hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_LOWER_WORDS END_COMMAND {
            hfst::xfst::xfst_->print_lower_words(NULL, 0, &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_LOWER_WORDS NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($3);
            std::ofstream oss($3);
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_lower_words(NULL, i, &oss);
            else
              hfst::xfst::xfst_->print_lower_words($2, 0, &oss);
            //hfst::xfst::xfst_fclose(f, $3); 
            oss.close();
            CHECK;
       }
       | PRINT_LOWER_WORDS REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_lower_words(NULL, 0, &oss);
            //hfst::xfst::xfst_fclose(f, $2); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_LOWER NAMETOKEN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_random_lower($2, hfst::xfst::nametoken_to_number($3), &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_RANDOM_LOWER NAMETOKEN NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($4, "w");
            std::ofstream oss($4);
            hfst::xfst::xfst_->print_random_lower($2, hfst::xfst::nametoken_to_number($3), &oss);
            free($2);
            oss.close();
            //hfst::xfst::xfst_fclose(f, $4); 
            CHECK;
       }
       | PRINT_RANDOM_LOWER NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_random_lower(NULL, i, &hfst::xfst::xfst_->get_output_stream());
            else
              hfst::xfst::xfst_->print_random_lower($2, 15, &hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_RANDOM_LOWER END_COMMAND {
            hfst::xfst::xfst_->print_random_lower(NULL, 15, &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_RANDOM_LOWER NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($3);
            std::ofstream oss($3);
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_random_lower(NULL, i, &oss);
            else
              hfst::xfst::xfst_->print_random_lower($2, 15, &oss);
            //hfst::xfst::xfst_fclose(f, $3); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_LOWER REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_random_lower(NULL, 15, &oss);
            //hfst::xfst::xfst_fclose(f, $2); 
            oss.close();
            CHECK;
       }
       | PRINT_UPPER_WORDS NAMETOKEN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_upper_words($2, hfst::xfst::nametoken_to_number($3), &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_UPPER_WORDS NAMETOKEN NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($4, "w");
            std::ofstream oss($4);
            hfst::xfst::xfst_->print_upper_words($2, hfst::xfst::nametoken_to_number($3), &oss);
            free($2);
            //hfst::xfst::xfst_fclose(f, $4); 
            oss.close();
            CHECK;
       }
       | PRINT_UPPER_WORDS NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_upper_words(NULL, i, &hfst::xfst::xfst_->get_output_stream());
            else
              hfst::xfst::xfst_->print_upper_words($2, 0, &hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_UPPER_WORDS END_COMMAND {
            hfst::xfst::xfst_->print_upper_words(NULL, 0, &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_UPPER_WORDS NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($3);
            std::ofstream oss($3);
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_upper_words(NULL, i, &oss);
            else
              hfst::xfst::xfst_->print_upper_words($2, 0, &oss);
            //hfst::xfst::xfst_fclose(f, $3); 
            oss.close();
            CHECK;
       }
       | PRINT_UPPER_WORDS REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2); 
            hfst::xfst::xfst_->print_upper_words(NULL, 0, &oss);
            //hfst::xfst::xfst_fclose(f, $2); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_UPPER NAMETOKEN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_random_upper($2, hfst::xfst::nametoken_to_number($3), &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_RANDOM_UPPER NAMETOKEN NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($4, "w");
            std::ofstream oss($4);
            hfst::xfst::xfst_->print_random_upper($2, hfst::xfst::nametoken_to_number($3), &oss);
            free($2);
            //hfst::xfst::xfst_fclose(f, $4); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_UPPER NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_random_upper(NULL, i, &hfst::xfst::xfst_->get_output_stream());
            else
              hfst::xfst::xfst_->print_random_upper($2, 15, &hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_RANDOM_UPPER END_COMMAND {
            hfst::xfst::xfst_->print_random_upper(NULL, 15, &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_RANDOM_UPPER NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($3);
            std::ofstream oss($3);
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_random_upper(NULL, i, &oss);
            else
              hfst::xfst::xfst_->print_random_upper($2, 15, &oss);
            //hfst::xfst::xfst_fclose(f, $3); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_UPPER REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_random_upper(NULL, 15, &oss);
            //hfst::xfst::xfst_fclose(f, $2);
            oss.close();
            CHECK;
       }
       | PRINT_WORDS NAMETOKEN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_words($2, hfst::xfst::nametoken_to_number($3), &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_WORDS NAMETOKEN NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($4, "w");
            std::ofstream oss($4);
            hfst::xfst::xfst_->print_words($2, hfst::xfst::nametoken_to_number($3), &oss);
            free($2);
            //hfst::xfst::xfst_fclose(f, $4); 
            oss.close();
            CHECK;
       }
       | PRINT_WORDS NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_words(NULL, i, &hfst::xfst::xfst_->get_output_stream());
            else
              hfst::xfst::xfst_->print_words($2, 0, &hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_WORDS END_COMMAND {
            hfst::xfst::xfst_->print_words(NULL, 0, &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_WORDS NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($3);
            std::ofstream oss($3);
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_words(NULL, i, &oss);
            else
              hfst::xfst::xfst_->print_words($2, 0, &oss);
            //hfst::xfst::xfst_fclose(f, $3); 
            oss.close();
            CHECK;
       }
       | PRINT_WORDS REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_words(NULL, 0, &oss);
            oss.close();
            //hfst::xfst::xfst_fclose(f, $2); 
            CHECK;
       }
       | PRINT_RANDOM_WORDS NAMETOKEN NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_random_words($2, hfst::xfst::nametoken_to_number($3), &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_RANDOM_WORDS NAMETOKEN NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($4, "w");
            std::ofstream oss($4);
            hfst::xfst::xfst_->print_random_words($2, hfst::xfst::nametoken_to_number($3), &oss);
            free($2);
            //hfst::xfst::xfst_fclose(f, $4); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_WORDS NAMETOKEN END_COMMAND {
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_random_words(NULL, i, &hfst::xfst::xfst_->get_output_stream());
            else
              hfst::xfst::xfst_->print_random_words($2, 15, &hfst::xfst::xfst_->get_output_stream());
            CHECK;
       }
       | PRINT_RANDOM_WORDS END_COMMAND {
            hfst::xfst::xfst_->print_random_words(NULL, 15, &hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_RANDOM_WORDS NAMETOKEN REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($3);
            std::ofstream oss($3);
            int i = hfst::xfst::nametoken_to_number($2);
            if (i != -1)
              hfst::xfst::xfst_->print_random_words(NULL, i, &oss);
            else
              hfst::xfst::xfst_->print_random_words($2, 15, &oss);
            //hfst::xfst::xfst_fclose(f, $3); 
            oss.close();
            CHECK;
       }
       | PRINT_RANDOM_WORDS REDIRECT_OUT END_COMMAND {
            //std::ofstream oss($2);
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_random_words(NULL, 15, &oss);
            //hfst::xfst::xfst_fclose(f, $2); 
            oss.close();
            CHECK;
       }
       | PRINT NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_net($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_net(&oss);
            oss.close(); CHECK;
       }
       | PRINT END_COMMAND {
            hfst::xfst::xfst_->print_net(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_PROPS NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_properties($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_PROPS END_COMMAND {
            hfst::xfst::xfst_->print_properties(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_PROPS REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_properties(&oss);
            oss.close(); CHECK;
       }
       | PRINT_SIGMA NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_sigma($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_SIGMA REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_sigma(&oss);
            oss.close(); CHECK;
       }
       | PRINT_SIGMA END_COMMAND {
            hfst::xfst::xfst_->print_sigma(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_SIGMA_COUNT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_sigma_count(&oss);
            oss.close(); CHECK;
       }
       | PRINT_SIGMA_COUNT END_COMMAND {
            hfst::xfst::xfst_->print_sigma_count(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_SIGMA_WORD_COUNT NAMETOKEN END_COMMAND {
            if (strcmp($2, "upper") && strcmp($2, "lower"))
            {
                hxfsterror("must be upper or lower\n");
                return EXIT_FAILURE;
            }
            hfst::xfst::xfst_->print_sigma_word_count($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_SIGMA_WORD_COUNT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_sigma_word_count(&oss);
            oss.close(); CHECK;
       }
       | PRINT_SIGMA_WORD_COUNT END_COMMAND {
            hfst::xfst::xfst_->print_sigma_word_count(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_SIZE NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->print_size($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | PRINT_SIZE REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_size(&oss);
            oss.close(); CHECK;
       }
       | PRINT_SIZE END_COMMAND {
            hfst::xfst::xfst_->print_size(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_STACK REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_stack(&oss);
            oss.close(); CHECK;
       }
       | PRINT_STACK END_COMMAND {
            hfst::xfst::xfst_->print_stack(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | PRINT_LABELMAPS REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->print_labelmaps(&oss);
            oss.close(); CHECK;
       }
       // writes
       | SAVE_DOT NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->write_dot($2, &hfst::xfst::xfst_->get_output_stream());
            free($2); CHECK;
       }
       | SAVE_DOT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_dot(&oss);
            oss.close(); CHECK;
       }
       | SAVE_DOT END_COMMAND {
            hfst::xfst::xfst_->write_dot(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | SAVE_DEFINITION NAMETOKEN LEFT_PAREN REDIRECT_OUT END_COMMAND {
            hfst::xfst::xfst_->write_function($2, $4);
            free($2); CHECK;
       }
       | SAVE_DEFINITION NAMETOKEN LEFT_PAREN END_COMMAND {
            hfst::xfst::xfst_->write_function($2, 0);
            free($2); CHECK;
       }
       | SAVE_DEFINITION NAMETOKEN REDIRECT_OUT END_COMMAND {
            hfst::xfst::xfst_->write_definition($2, $3);
            free($2); CHECK;
       }
       | SAVE_DEFINITION NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->write_definition($2, 0);
            free($2); CHECK;
       }
       | SAVE_DEFINITIONS REDIRECT_OUT END_COMMAND {    
            hfst::xfst::xfst_->write_definitions($2); CHECK;
       }
       | SAVE_DEFINITIONS END_COMMAND {
            hfst::xfst::xfst_->write_definitions(0); CHECK;
       }
       | SAVE_STACK NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->write_stack($2);
            free($2); CHECK;
       }
       | SAVE_PROLOG REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_prolog(&oss);
            oss.close(); CHECK;
       }
       | SAVE_PROLOG NAMETOKEN END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_prolog(&oss);
            oss.close(); CHECK;
       }
       | SAVE_PROLOG END_COMMAND {
            hfst::xfst::xfst_->write_prolog(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | SAVE_SPACED REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_spaced(&oss);
            oss.close(); CHECK;
       }
       | SAVE_SPACED END_COMMAND {
            hfst::xfst::xfst_->write_spaced(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | SAVE_TEXT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_text(&oss);
            oss.close(); CHECK;
       }
       | SAVE_TEXT END_COMMAND {
            hfst::xfst::xfst_->write_text(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       // reads
       | READ_PROPS REDIRECT_IN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->read_props(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | READ_PROPS END_COMMAND {
            hfst::xfst::xfst_->read_props(stdin); CHECK;
       }
       | READ_PROLOG NAMETOKEN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->read_prolog(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | READ_PROLOG END_COMMAND {
            hfst::xfst::xfst_->read_prolog(stdin); CHECK;
       }
       | READ_REGEX REGEX {
            hfst::xfst::xfst_->read_regex($2);
            free($2); CHECK;
       }
       | READ_REGEX REDIRECT_IN END_COMMAND {
            FILE * f = hfst::xfst::xfst_->xfst_fopen($2, "r"); CHECK;
            hfst::xfst::xfst_->read_regex(f);
            hfst::xfst::xfst_->xfst_fclose(f, $2); CHECK;
       }
       | READ_REGEX NAMETOKEN_LIST SEMICOLON END_COMMAND {
            hfst::xfst::xfst_->read_regex($2);
            free($2); CHECK;
       }
       | READ_SPACED REDIRECT_IN END_COMMAND {
            hfst::xfst::xfst_->read_spaced_from_file($2);
            free($2); CHECK;
       }
       | READ_SPACED NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->read_spaced_from_file($2);
            free($2); CHECK;
       }
       | READ_SPACED NAMETOKEN_LIST CTRLD {
            hfst::xfst::xfst_->read_spaced($2);
            free($2); CHECK;
       }
       | READ_TEXT REDIRECT_IN END_COMMAND {
            hfst::xfst::xfst_->read_text_from_file($2);
            free($2); CHECK;
       }
       | READ_TEXT NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->read_text_from_file($2);
            free($2); CHECK;
       }
       | READ_TEXT NAMETOKEN_LIST CTRLD {
            hfst::xfst::xfst_->read_text($2);
            free($2); CHECK;
       }
       | READ_LEXC NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->read_lexc_from_file($2);
            free($2); CHECK;
       }
       | READ_LEXC NAMETOKEN SEMICOLON END_COMMAND {
            hfst::xfst::xfst_->read_lexc_from_file($2);
            free($2); CHECK;
       }
       | READ_LEXC NAMETOKEN_LIST CTRLD {
            hfst::xfst::xfst_->read_lexc_from_file(""); CHECK;
       }
       | READ_ATT NAMETOKEN END_COMMAND {
            hfst::xfst::xfst_->read_att_from_file($2);
            free($2); CHECK;
       }
       | WRITE_ATT END_COMMAND {
            hfst::xfst::xfst_->write_att(&hfst::xfst::xfst_->get_output_stream()); CHECK;
       }
       | WRITE_ATT REDIRECT_OUT END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_att(&oss);
            oss.close();
            free($2); CHECK;
       }
       | WRITE_ATT NAMETOKEN END_COMMAND {
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_att(&oss);
            oss.close();
            free($2); CHECK;
       }
       | WRITE_ATT NAMETOKEN NAMETOKEN NAMETOKEN END_COMMAND {
            // todo: handle input and output symbol tables
            std::ofstream oss($2);
            hfst::xfst::xfst_->write_att(&oss);
            oss.close();
            free($2); CHECK;
       }
       // net ops
       | CLEANUP END_COMMAND {
            hfst::xfst::xfst_->cleanup_net(); CHECK;
       }
       | COMPLETE END_COMMAND {
            hfst::xfst::xfst_->complete_net(); CHECK;
       }
       | COMPOSE END_COMMAND {
            hfst::xfst::xfst_->compose_net(); CHECK;
       }
       | CONCATENATE END_COMMAND {
            hfst::xfst::xfst_->concatenate_net(); CHECK;
       }
       | MINUS END_COMMAND {
            hfst::xfst::xfst_->minus_net(); CHECK;
       }
       | CROSSPRODUCT END_COMMAND {
            hfst::xfst::xfst_->crossproduct_net(); CHECK;
       }
       | MINIMIZE END_COMMAND {
            hfst::xfst::xfst_->minimize_net(); CHECK;
       }
       | DETERMINIZE END_COMMAND {
            hfst::xfst::xfst_->determinize_net(); CHECK;
       }
       | EPSILON_REMOVE END_COMMAND {
            hfst::xfst::xfst_->epsilon_remove_net(); CHECK;
       }
       | PRUNE_NET END_COMMAND {
            hfst::xfst::xfst_->prune_net(); CHECK;
       }
       | XFST_IGNORE END_COMMAND {
            hfst::xfst::xfst_->ignore_net(); CHECK;
       }
       | INTERSECT END_COMMAND {
            hfst::xfst::xfst_->intersect_net(); CHECK;
       }
       | INSPECT END_COMMAND {
            hfst::xfst::xfst_->inspect_net(); CHECK;
       }
       | INVERT END_COMMAND {
            hfst::xfst::xfst_->invert_net(); CHECK;
       }
       | LOWER_SIDE END_COMMAND {
            hfst::xfst::xfst_->lower_side_net(); CHECK;
       }
       | UPPER_SIDE END_COMMAND {
            hfst::xfst::xfst_->upper_side_net(); CHECK;
       }
       | NEGATE END_COMMAND {
            hfst::xfst::xfst_->negate_net(); CHECK;
       }
       | ONE_PLUS END_COMMAND {
            hfst::xfst::xfst_->one_plus_net(); CHECK;
       }
       | ZERO_PLUS END_COMMAND {
            hfst::xfst::xfst_->zero_plus_net(); CHECK;
       }
       | XFST_OPTIONAL END_COMMAND {
            hfst::xfst::xfst_->optional_net(); CHECK;
       }
       | REVERSE END_COMMAND {
            hfst::xfst::xfst_->reverse_net(); CHECK;
       }
       | SHUFFLE END_COMMAND {
            hfst::xfst::xfst_->shuffle_net(); CHECK;
       }
       | SIGMA END_COMMAND {
            hfst::xfst::xfst_->sigma_net(); CHECK;
       }
       | SORT END_COMMAND {
            hfst::xfst::xfst_->sort_net(); CHECK;
       }
       | SUBSTRING END_COMMAND {
            hfst::xfst::xfst_->substring_net(); CHECK;
       }
       | UNION END_COMMAND {
            hfst::xfst::xfst_->union_net(); CHECK;
       }
       | LABEL_NET END_COMMAND {
            hfst::xfst::xfst_->label_net(); CHECK;
       }
       | COMPILE_REPLACE_LOWER END_COMMAND {
            hfst::xfst::xfst_->compile_replace_lower_net(); CHECK;
       }
       | COMPILE_REPLACE_UPPER END_COMMAND {
            hfst::xfst::xfst_->compile_replace_upper_net(); CHECK;
       }
       | END_COMMAND {
            hfst::xfst::xfst_->prompt(); CHECK;
       }
       | NAMETOKEN END_COMMAND {
            if ( hfst::xfst::xfst_->unknown_command($1) != 0) 
              { 
                hxfsterror("Command not recognized.\n");
                YYABORT;
              }
       }
       ;

END_COMMAND: NEWLINE | ;

COMMAND_SEQUENCE: COMMAND_SEQUENCE NAMETOKEN {
                    $$ = static_cast<char*>(malloc(sizeof(char)*strlen($1)+strlen($2)+2));
                    char* r = $$;
                    char* s = $1;
                    while (*s != '\0')
                    {
                        *r = *s;
                        r++;
                        s++;
                    }
                    *r = ' ';
                    r++;
                    s = $2;
                    while (*s != '\0')
                    {
                        *r = *s;
                        r++;
                        s++;
                    }
                    *r = '\0';
                }
                | COMMAND_SEQUENCE SEMICOLON {
                    $$ = $1;
                }
                | NAMETOKEN {
                    $$ = $1;
                }
                ;

NAMETOKEN_LIST: NAMETOKEN_LIST NAMETOKEN {
                $$ = static_cast<char*>(malloc(sizeof(char)*strlen($1)+strlen($2)+2));
                char* s = $1;
                char* r = $$;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = ' ';
                r++;
                s = $2;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = '\0';
             }
             | NAMETOKEN {
                $$ = $1;
             }
             ;

QUOTED_NAMETOKEN_LIST: QUOTED_NAMETOKEN_LIST NAMETOKEN {
                $$ = static_cast<char*>(malloc(sizeof(char)*strlen($1)+strlen($2)+4));
                char* s = $1;
                char* r = $$;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = ' ';
                r++;
                s = $2;
                *r = '"';
                r++;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = '"';
                r++;
                *r = '\0';
             }
             | NAMETOKEN {
                $$ = static_cast<char*>(malloc(sizeof(char)*strlen($1)+3));
                char* s = $1;
                char* r = $$;
                *r = '"';
                r++;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = '"';
                r++;
                *r = '\0';
                free($1);
             }
             ;

LABEL: NAMETOKEN COLON NAMETOKEN {
                $$ = strdup((std::string($1) + std::string(":") + std::string($3)).c_str());
                }
                | NAMETOKEN {
                $$ = $1;
                }
                ;

LABEL_LIST: LABEL_LIST LABEL {
                $$ = static_cast<char*>(malloc(sizeof(char)*strlen($1)+strlen($2)+2));
                char* s = $1;
                char* r = $$;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = ' ';
                r++;
                s = $2;
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = '\0';
             }
             | LABEL {
                $$ = $1;
             }
             ;
%%

// oblig. declarations
extern FILE* hxfstin;
int hxfstparse(void);

// gah, bison/flex error mechanism here
void
hxfsterror(const char* text)
{ 
    hfst::xfst::xfst_->error() << text << std::endl;
    hfst::xfst::xfst_->flush(&hfst::xfst::xfst_->error());
    //fprintf(stderr,  "%s\n", text);
}


// vim: set ft=yacc:
