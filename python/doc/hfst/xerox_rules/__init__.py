## @package hfst.xerox_rules
# Xerox-type replace rules.

## Type of Xerox-type replace rules.
class ReplaceType:
    ## Match contexts of replace rules on input level.
    REPL_UP = libhfst.REPL_UP
    ## Match contexts of replace rules on output level.
    REPL_DOWN = libhfst.REPL_DOWN
    ## Match left context of replace rules on output level and right context on input level.
    REPL_LEFT = libhfst.REPL_LEFT
    ## Match left context of replace rules on input level and right context on output level.
    REPL_RIGHT = libhfst.REPL_RIGHT
        
## A rule that contains mapping and context and replace type (if any).
# If rule is A -> B || L _ R , than mapping is cross product of transducers A and B,
# context is pair of transducers L and R, and replType is enum REPL_UP.
class Rule:
        ## Rule that performs mappings defined in \a mapping in every context.
        # @param mapping HfstTransducerPairVector
        def __init__(self, mapping):
                pass
        ## Rule that performs mappings defined in \a mapping in contexts \a context. \a type defines how contexts are matched.
        # @param mapping HfstTransducerPairVector
        # @param context HfstTransducerPairVector
        # @param type ReplType
        def __init__(self, mapping, context, type):
                pass
        ## Copy Rule.
        # @param rule Rule
        def __init__(self, rule):
                pass
        ## Default constructor needed for SWIG.
        def __init__(self):
                pass
        ## Get mappings defined in Rule.
        # @return HfstTransducerPairVector 
        def get_mapping(self):
                pass
        ## Get contexts defined in Rule.
        # @return HfstTransducerPairVector
        def get_context():
                pass
        ## Get replace type defined in Rule.
        # @return ReplaceType
        def get_replType():
                pass
        ## Encode flag diacritics.
        def encodeFlags():
                pass
        # friend std::ostream& operator<<(std::ostream &out, const Rule &r);

## replace up, left, right, down
# @param rule (Rule, HfstRuleVector)
# @param optional (Bool)
def replace(rule, optional):
        pass
## replace up, left, right, down
# @param rule (Rule, HfstRuleVector)
# @param optional (Bool)
def replace_left(rule, optional):
        pass
## left to right
# @param rule (Rule, HfstRuleVector)
def replace_leftmost_longest_match(rule):
        pass
## right to left
# @param rule (Rule, HfstRuleVector)
def replace_rightmost_longest_match(rule):
        pass
## todo
# @param rule (Rule, HfstRuleVector)
def replace_leftmost_shortest_match(rule):
        pass
## todo
# @param rule (Rule, HfstRuleVector)
def replace_rightmost_shortest_match(rule):
        pass
## replace up, left, right, down
# @param rule (Rule, HfstRuleVector)
# @param optional (Bool)
def replace_epenthesis(rule, optional):
        pass
## Restriction function "=>"
# @param automaton (HfstTransducer)
# @param context (HfstTransducerPairVector)
def restriction(automaton, context):
        pass
## todo
# @param left (HfstTransducer)
# @param right (HfstTransducer)
def before(left, right):
        pass
## todo
# @param left (HfstTransducer)
# @param right (HfstTransducer)
def after(left, right):
        pass
