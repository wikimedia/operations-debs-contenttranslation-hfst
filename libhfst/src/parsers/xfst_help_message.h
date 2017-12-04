// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

namespace hfst
{
namespace xfst
{

typedef std::vector<std::string> StringVector;

// find help message for a certain command
#define HELP_MODE_ONE_COMMAND 0
// get all commands and their help messages
#define HELP_MODE_ALL_COMMANDS 1
// get all command-help message pairs, where a certain word is found
#define HELP_MODE_APROPOS 2

// Convert \a str to upper case.
 std::string to_upper_case(const std::string & str);

// Whether \a c is a punctuation character.
 bool is_punctuation_char(char c);

// Whether word \a str_ is found in text \a text_.
// Punctuation characters and upper/lower case are handled in this function.
 bool word_found_in_text(const std::string & str_, const std::string & text_);


// Convert the list of names separated by commas \a namelist into a vector of names.
 StringVector namelist_to_name_vector(const std::string & namelist);
    
// Append help message for command known by names in \a namelist, taking arguments
// listed in \a arguments, and described by \a description to \a message.
// \a all_names defines whether all names in \a namelist are included or just the first one.
void append_help_message(const std::string & namelist, const std::string & arguments,
                         const std::string & description, std::string & message, bool all_names = true);

 bool text_matches_some_name(const std::string & text, const std::string & namelist);

    bool get_help_message(const std::string & text, std::string & message, int help_mode, bool skip_ambiguous_cases=false);

bool handle_ambiguous_case(const std::string & name, const std::string & namelist,
                           const std::string & text, std::string & message, int help_mode);

// If \a text matches (depending on \a help_mode) a command known by names
// listed in \a names, taking arguments \a arguments, described by \a description,
// add help message for the command to \a message. \a all_names defines whether
// all names in \a names are included or just the first one.
// Return whether the search should continue (depends on \a help_mode).
bool handle_case(const std::string & names, const std::string & arguments,
                 const std::string & description, const std::string & text,
                 std::string & message, int help_mode, bool all_names=true);

// Generate help message(s) for command(s) named \a text and append the help message(s)
// to \a message. \a help_mode defines whether we are generating help messages for \a text,
// all commands (in that case, \a message is ignored) or for commands that contain or
// whose help messages contain the word \a text. \a skip_ambiguous_cases defines whether
// ambiguous cases where \a text matches more than one command are ignored.
// @return Whether the help message could be generated.
    bool get_help_message(const std::string & text, std::string & message, int help_mode,
                          bool skip_ambiguous_cases);

}
}
