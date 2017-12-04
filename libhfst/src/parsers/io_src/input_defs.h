//! @file input_defs.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Redefinition of the Bison @a YY_INPUT macro.
//!
//! In order to allow better error messages, the @a YY_INPUT macro needs to
//! be redefined.
//!
//! The new @a YY_INPUT macro uses @a InputReader to read one character at
//! a time.

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, version 3 of the Licence.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef INPUT_DEFS_H
#define INPUT_DEFS_H

#include "InputReader.h"

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

extern InputReader input_reader;
#undef YY_INPUT
#define YY_INPUT( buf, result, max_size ) { \
char c = input_reader.input(); \
if (c == 0) { \
result = YY_NULL; \
} \
 else { \
buf[0] = c; \
result = 1; \
} \
}

#endif // INPUT_DEFS_H
