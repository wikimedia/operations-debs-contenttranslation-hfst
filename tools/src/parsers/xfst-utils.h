//! @file lexc-utils.h
//!
//! @brief Various string handling methods for HFST lexc.
//! 
//! @author Tommi A. Pirinen


//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, version 3 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GUARD_lexc_utils_h
#define GUARD_lexc_utils_h
#if HAVE_CONFIG_H
#  include <config.h>
#endif
#include <string>

namespace hfst { namespace xfst {

#ifndef HAVE_GETLINE
#   define MAX_LINE_SIZE 12345678
ssize_t getline(char** line, size_t* n, FILE* f);
#endif

//! @brief Open file and print XFSTish stuff
FILE* xfst_fopen(const char* path, const char* mode);
//! @brief Close \a file that has \a name.
 void xfst_fclose(FILE * file, const char * name);
//! @brief Strips initial and final white space and strdups
char* strstrip(const char* s);

 int nametoken_to_number(const char * token);

//! @brief extracts the variable substring part from token.
//! Omits constant string prefix, suffix and optionally strips spaces.
char* strdup_nonconst_part(const char* token, 
                           const char* prefix,
                           const char* suffix,
                           bool strip);

} }
// vim: set ft=cpp.doxygen:
#endif // GUARD_lexc_utils_h
