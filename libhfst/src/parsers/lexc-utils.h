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

namespace hfst { namespace lexc {

const char LEXC_JOINER_START[] = "$_LEXC_JOINER.";
const char LEXC_JOINER_END[] = "_$";
const char LEXC_FLAG_LEFT_START[] = "$R.LEXNAME.";
const char LEXC_FLAG_RIGHT_START[] = "$P.LEXNAME.";
const char LEXC_FLAG_END[] = "$";
const char LEXC_DFN_START[] = "@_LEXC_DEFINITION.";
const char LEXC_DFN_END[] = "_@";
const char REG_EX_START[] = "$_REG.";
const char REG_EX_END[] = "_$";

// RECODE LEXC STYLE

//! @brief Strips lexc style percent escaping from a string.
//!
//! E.g. like stripslashes() in PHP. 
std::string& stripPercents(std::string& s);

//! @brief Percent encode critical characters in raw string for lexc.
std::string& addPercents(std::string& s);

//! @brief Find flag representation of given joiner name string.
std::string& flagJoinerEncode(std::string& s, bool left);

//! @brief Find inner representation of given joiner name string.
std::string& joinerEncode(std::string& s);

//! @brief Format inner representation of joiner string in readable format as
//! it was in lexc source.
std::string& joinerDecode(std::string& s);

//! @brief Find inner representation for regex map key of given joiner name string.
std::string& regExpresionEncode(std::string& s);

//! @brief Format inner representation of joiner string in readable format as
//! it was in lexc source.
std::string& regExpresionDecode(std::string& s);

//! @brief Replaces @ZERO@ with "0" in a string
std::string replace_zero(const std::string s);

// FLEX HANDLING

//! @brief Set filename used for position messages.
void set_infile_name(const char* s);

//! @brief Initialise memory of file positions to zeros.
//!
//! Sets all members of current yylloc structure to zeros.
void token_reset_positions();

//! @brief Keep memory of positions of last parsed tokens for error messages.
//!
//! Counts length, height and width of the given token. Update yylloc structure
//! provided by lex and yacc, for location data.
void token_update_positions(const char* token);

//! @brief writes token positions in standard format.
char* strdup_token_positions();

//! @brief create some sensible representation of current token.
char* strdup_token_part();
//! @brief Strips percent escaping and strdups
char* strip_percents(const char* s, bool do_zeros);

//! @brief Strips initial and final white space and strdups
char* strstrip(const char* s);

//! @brief extracts the variable substring part from token.
//! Omits constant string prefix, suffix and optionally strips spaces.
char* strdup_nonconst_part(const char* token, 
                           const char* prefix,
                           const char* suffix,
                           bool strip);

// help flex/yacc with meaningful error messages
//! @brief print error_at_line style error message for current token
void error_at_current_token(int status, int errnum, const char* format);


} }
// vim: set ft=cpp.doxygen:
#endif // GUARD_lexc_utils_h
