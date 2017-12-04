
/*******************************************************************/
/*                                                                 */
/*     File: utf8.h                                                */
/*   Author: Helmut Schmid                                         */
/*  Purpose:                                                       */
/*  Created: Mon Sep  5 17:49:16 2005                              */
/* Modified: Mon Apr  7 08:26:39 2008 (schmid)                     */
/*                                                                 */
/*******************************************************************/

#ifndef _SFST_UTF8_H_
#define _SFST_UTF8_H_

/* @file HfstUtf8.h
   \brief Functions for handling utf-8 strings. */

namespace sfst_utf8 {
  
  unsigned int utf8toint( char *s );
  unsigned int utf8toint( char **s );
  char *int2utf8( unsigned int );
  
}
#endif
