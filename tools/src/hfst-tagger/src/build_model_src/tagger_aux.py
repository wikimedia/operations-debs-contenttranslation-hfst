# @file tagger_aux.py
#
# @author Miikka Silfverberg
#
# @brief Auxiliary functions for computing statistics from a POS
# tagger training file.

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, version 3 of the Licence.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

import math
import collections
import string
import sys
import re

valid_pattern_str = \
"^(((NONE)|(WORD)) ((NONE)|(TAG)) )*((NONE)|(WORD)) ((NONE)|(TAG))$"

class InvalidPattern(Exception):
    def __init__(self):
        super(InvalidPattern, self).__init__()

class InvalidConfigLine(Exception):
    def __init__(self):
        super(InvalidConfigLine, self).__init__()

class ReachesSequenceEnd(Exception):
    def __init__(self):
        super(ReachesSequenceEnd, self).__init__()

class SequenceSimplifier:

    def __init__(self,pattern):

        for line in pattern:
            if len(line) != 2 or (not line[0] in [0,1]) or \
                    (not line[1] in [0,1]):    
                raise InvalidPattern()

        self.pattern = pattern
            
    def simplify(self,i,sequence):

        if i + len(self.pattern) >= len(sequence):
            raise ReachesSequenceEnd()

        simplified_subsequence = []

        for pair in self.pattern:
            simplified_entry = ["<NONE>","<NONE>"]
            
            if pair[0] == 1:
                simplified_entry[0] = sequence[i][0]

            if pair[1] == 1:
                simplified_entry[1] = sequence[i][1]

            simplified_subsequence.append(tuple(simplified_entry))

            i += 1

        return tuple(simplified_subsequence)

class Pattern:
    def __init__(self,numerator, denominator, name):
        self.numerator   = numerator
        self.denominator = denominator
        self.name        = name
        self.order       = len(numerator.pattern) - 1 

# Read statistics patterns from file config_file_name.
def read_config_file(config_file_name):
    config_file = open(config_file_name)
    
    config_data = config_file.read().split("\n")

    patterns = []

    for line in config_data:
        if line == "":
            continue
        patterns.append(parse_config_line(line))

    return patterns

def parse_config_pattern(pattern_str):
    
    if re.match(valid_pattern_str,pattern_str) == None:
        raise InvalidConfigLine()

    field_strings = pattern_str.split(" ")

    pattern = []

    i = 0

    while i < len(field_strings) - 1:
        word_string = field_strings[i]
        tag_string = field_strings[i+1]

        pattern.append([(lambda x: x == "WORD" and 1 or 0)(word_string),
                        (lambda x: x == "TAG"  and 1 or 0)(tag_string)])
        i += 2

    return SequenceSimplifier(pattern)

def parse_config_line(line):
    fields = re.split("\t+",line)

    if len(fields) != 4:
        raise InvalidConfigLine()

    name                    = fields[0]
    numerator_pattern_str   = fields[1]
    denominator_pattern_str = fields[2]
    weigth_str              = fields[3]

    numerator_simplifier   = parse_config_pattern(numerator_pattern_str)
    denominator_simplifier = parse_config_pattern(denominator_pattern_str)

    return Pattern(numerator_simplifier, denominator_simplifier, name)
                              
# Unless line is a utf-8 encoded line of number_of_fields tab
# separated fields, raise an exception.
def check_line(line,number_of_fields):

    line_copy = line

    try:
        line_copy.decode("utf-8")

    except UnicodeDecodeError:
        raise Exception("Invalid utf-8 encoding on line")

    if len(line_copy.split("\t")) != number_of_fields:
        raise Exception("Wrong number of fields on line")

# Return tropical penalty corresponding to the probability
# suffix_and_tag_count/suffix_count.
def get_penalty(suffix_and_tag_count, suffix_count):

    return math.log(suffix_count) - math.log(suffix_and_tag_count)


def verbose_print(message, is_verbose):
    if is_verbose:
        sys.stderr.write(message + "\n")

# Return the utf-8 string str reversed. utf-8 symbols are not
# internally reversed.
def reverse(str):    
    return str.decode("utf-8")[::-1]

# Return a map for counting pairs e.g. word form and tag pairs.
def get_object_counter():
    return collections.defaultdict(lambda : 0.0)

# Return a map for counting objects, e.g. word forms.
def get_pair_counter():
    return collections.defaultdict(lambda : get_object_counter())

# Return a mapping from pairs in pair_counter to their conditional
# probability given the second member of the pair. The counts of pairs
# are given by pair_counter and the counts of the members by
# object_counter.
def get_conditional_penalty_map(pair_counter, object_counter):

    penalty_map = {}

    for first_member, second_member_dict in pair_counter.iteritems():

        for second_member, pair_count in second_member_dict.iteritems():
            penalty = get_penalty(pair_count, object_counter[second_member])
            penalty_map[(first_member, second_member)] = penalty

    return penalty_map

# return a mapping from objects to their probabilities. The count of
# each object type is given by object_counter and the total number of
# objects is total_count.
def get_penalty_map(object_counter, total_count):

    penalty_map = {}

    for object, count in object_counter.iteritems():

        penalty = get_penalty(count, total_count)
        penalty_map[object] = penalty

    return penalty_map

def print_conditional_penalties(pair_counter, object_counter, 
                                appended_suffix,
                                invert_fields,
                                print_maximum_penalty):

    penalty_map = get_conditional_penalty_map(pair_counter, object_counter) 

    if print_maximum_penalty:
        max_object_count = 0
        
        for count in object_counter.itervalues():
            max_object_count = max(max_object_count, count)

        print "PENALTY_WEIGHT=" + str(get_penalty(1, max_object_count + 1))

    for pair, penalty in penalty_map.iteritems():
        if type(pair[0]) == type(u"") or type(pair[0]) == type(""):

            p = list(pair)
            
            try:
                p[0] = p[0].decode("utf-8")
            except UnicodeEncodeError:
                pass
            
            try:
                p[1] = p[1].decode("utf-8")
            except UnicodeEncodeError:
                pass
            

            if not invert_fields:
                s = string.join([p[0] + appended_suffix, 
                                 p[1], 
                                 str(penalty)],"\t")
                print s.encode("utf-8")
            else:
                
                s = string.join([p[1] + appended_suffix, 
                                 p[0], 
                                 str(penalty)],"\t")
                print s.encode("utf-8")
        else:
            for entry in pair[0]:
                e = list(entry)
                
                try:
                    e[0] = e[0].decode("utf-8")
                except UnicodeEncodeError:
                    pass

                try:
                    e[1] = e[1].decode("utf-8")
                except UnicodeEncodeError:
                    pass
                
                s = e[0] + "\t" + e[1] + "\t"
                print s.encode("utf-8"),

            print penalty

def print_penalties(object_counter, total_count, appended_suffix):

    penalty_map = get_penalty_map(object_counter, total_count) 

    for object, penalty in penalty_map.iteritems():
        
        o = object
        try:
            o = o.decode("utf-8")
        except UnicodeEncodeError:
            pass

        s = o + appended_suffix + "T\t" + str(penalty)

        print s.encode("utf-8")
