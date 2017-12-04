// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

//! @file xfst-utils.cc
//!
//! @brief Implementation of some string handling in HFST xfst.
//!
//! @author Tommi A. Pirinen

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string>
#include <vector>
#include <sstream>

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>

#include <errno.h>

#ifdef YACC_USE_PARSER_H_EXTENSION
  #include "xfst-parser.h"
#else
  #include "xfst-parser.hh"
#endif

#include "xfst-utils.h"

// for hfst::size_t_to_int
#ifndef HAVE_GETLINE
  #include "HfstDataTypes.h"
#endif // HAVE_GETLINE

using std::string;

// flex stuffa
extern int hxfstlineno;
extern char* hxfsttext;
extern YYLTYPE hxfstlloc;

namespace hfst { namespace xfst {

#ifndef HAVE_GETLINE
    ssize_t
    getline(char** s, size_t* n, FILE* f)
      {
        *s = static_cast<char*>(calloc(sizeof(char),*n));
        char* r = fgets(*s, hfst::size_t_to_int(*n), f);
        if (r == 0)
          {
            //fprintf(stderr, "unable to read in substitute getline\n");
            return -1;
          }
        return *n;
      }
#endif

char*
strdup_token_part()
{
    char *error_token = (char*)malloc(sizeof(char)*strlen(hxfsttext)+100);
    char* maybelbr = strchr(hxfsttext, '\n');
    if (maybelbr != NULL)
    {
        char* beforelbr = (char*)malloc(sizeof(char)*strlen(hxfsttext)+1);
        (void)memcpy(beforelbr, hxfsttext, maybelbr-hxfsttext);
        beforelbr[maybelbr-hxfsttext] = '\0';
        (void)sprintf(error_token, "[near: `%s\\n']", beforelbr);
        free(beforelbr);
    }
    else if (strlen(hxfsttext) < 80)
    {
        (void)sprintf(error_token, "[near: `%s']", hxfsttext);
    }
    else
    {
        (void)sprintf(error_token, "[near: `%30s...' (truncated)]",
                      hxfsttext);
    }
    return error_token;
}

    /*char*
strip_percents(const char* s, bool do_zeros)
{
    char* rv = (char*)malloc(sizeof(char)*strlen(s)*6+1);
    char* p = rv;
    const char* c = s;
    bool escaping = false;
    while (*c != '\0')
    {
        if (escaping)
        {
            if (*c != '0')
            {
                *p = *c;
            }
            else
            {
                *p = '@';
                p++;
                *p = 'Z';
                p++;
                *p = 'E';
                p++;
                *p = 'R';
                p++;
                *p = 'O';
                p++;
                *p = '@';
            }
            escaping = false;
            ++p;
            ++c;
        }
        else if (*c == '%')
        {
            escaping = true;
            ++c;
        }
        else if (do_zeros && (*c == '0'))
        {
            *p = '@';
            p++;
            *p = '0';
            p++;
            *p = '@';
            p++;
            c++;
        }
        else
        {
            *p = *c;
            ++p;
            ++c;
        }
    }
    *p = '\0';
    if (escaping)
    {
        fprintf(stderr, "Stray escape char %% in %s\n", s);
        return NULL;
    }
    return rv;
    }*/

char*
strstrip(const char* s)
{
    char* rv = (char*)malloc(sizeof(char)*strlen(s)+1);

    if (*s == '\0') // empty string is a spcial case
    {
      *rv = '\0';
      return rv;
    }

    char* p = rv;
    while (isspace(*s))
    {
        ++s;
    }
    while (*s != '\0')
    {
        *p = *s;
        ++p;
        ++s;
    }
    *p = '\0';
    --p;
    while (isspace(*p))
    {
        *p = '\0';
        --p;
    }
    return rv;
}

    int nametoken_to_number(const char * token)
    {
      std::string tokenstr(token);
      std::stringstream str(tokenstr);
      unsigned int x;
      str >> x;
      if (!str)
        return -1;
      return (int)x;
    }

char*
strdup_nonconst_part(const char* token, const char* prefix,
                          const char* suffix, bool strip)
{
    size_t prefix_len = 0;
    size_t suffix_len = 0;
    size_t varpart_len = 0;
    size_t token_len = strlen(token);
    char* token_part = (char*)malloc(sizeof(char) * token_len + 1);
    if (prefix)
    {
        prefix_len = strlen(prefix);
    }
    if (suffix)
    {
        suffix_len = strlen(suffix);
    }
    varpart_len = strlen(token) - prefix_len - suffix_len;
    assert(varpart_len <= token_len);
    assert(prefix != NULL);
    assert(strncmp(token, prefix, prefix_len) == 0);
    assert(suffix != NULL);
    assert(strncmp(token + prefix_len + varpart_len, suffix, suffix_len) == 0);
    (void)memcpy(token_part, token + prefix_len, varpart_len);
    token_part[varpart_len] = '\0';
    if (strip)
    {
        char* tmp = strstrip(token_part);
        free(token_part);
        token_part = tmp;
    }
    return token_part;
}


} }

// vim: set ft=cpp.doxygen:

