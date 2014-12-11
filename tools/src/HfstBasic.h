#ifndef _HFST_BASIC_H_
#define _HFST_BASIC_H_

#include <stdio.h>

/* @file HfstBasic.h
   \brief Basic functions for string handling. */

namespace hfst {
namespace basic {

  extern bool Switch_Bytes;

  char* fst_strdup(const char* pString);
  int read_string( char *buffer, int size, FILE *file );
  size_t read_num( void *p, size_t size, FILE *file );

}
}
#endif
