%option 8Bit batch yylineno noyywrap nounput prefix="pmatch"

%{


#include <string.h>

#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstXeroxRules.h"

#include "pmatch_utils.h"
#include "pmatch_parse.hh"


#undef YY_INPUT
#define YY_INPUT(buf, retval, maxlen)   (retval = hfst::pmatch::getinput(buf, maxlen))

extern
void pmatcherror(char *text);

%}

/* c.f. Unicode Standard 5.1 D92 Table 3-7 */
U1 [\x20-\x7e]
U2 [\xc2-\xdf][\x80-\xbf]
U31 \xe0[\xa0-\xbf][\x80-\xbf]
U32 [\xe1-\xec][\x80-\xbf][\x80-\xbf]
U33 \xed[\x80-\x9f][\x80-\xbf]
U34 [\xee-\xef][\x80-\xbf][\x80-\xbf]
U41 \xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]
U42 [\xf1-\xf3][\x80-\xbf][\x80-\xbf][\x80-\xbf]
U43 \xf4[\x80-\x8f][\x80-\xbf][\x80-\xbf]
/* non US-ASCII */
U8H {U43}|{U42}|{U41}|{U34}|{U33}|{U32}|{U31}|{U2}
/* any UTF-8 */
U8C {U8H}|{U1}
/* Escaped */
EC "%"{U8C}

/* any ASCII */
A7 [\x00-\x7e]
/* special meaning in pmatch */
A7RESTRICTED [- |<>%^:;@0~\\&?$+*/_(){}\]\[-]
/* non-restricted ASCII */
A7UNRESTRICTED [\x21-\x7e]{-}[- |<>%^:;,@~\\&?$+*/(){}\]\[]

WEIGHT [0-9]+(\.[0-9]+)?

/* token character */
NAME_CH {A7UNRESTRICTED}|{U8H}|{EC}
UINTEGER [1-9][0-9]*
INTEGER -?[1-9][0-9]*
WSP [\t ]
LWSP [\t\r\n ]
%%

[Dd]"efine" {
    return DEFINE;
}

"regex" {
return REGEX;
}

"DefIns" {
    return DEFINS;
}

"DefFun" {
    return DEFFUN;
}

"Alpha" {
    return ALPHA;
}

"UppercaseAlpha" {
    return UPPERALPHA;
}

"LowercaseAlpha" {
    return LOWERALPHA;
}

"Num" {
    return NUM;
}

"Punct" {
    return PUNCT;
}

"Whitespace" {
    return WHITESPACE;
}

"OptCap(" {
    return OPTCAP_LEFT;
}

"ToLower(" {
    return TOLOWER_LEFT;
}

"ToUpper(" {
    return TOUPPER_LEFT;
}

"Ins(" {
    return INS_LEFT;
}

"Define(" {
    return DEFINE_LEFT;
}

"EndTag(" {
    return ENDTAG_LEFT;
}

"LC(" {
    return LC_LEFT;
}

"RC(" {
    return RC_LEFT;
}

"NLC(" {
    return NLC_LEFT;
}

"NRC(" {
    return NRC_LEFT;
}

"OR(" {
    return OR_LEFT;
}

"AND(" {
    return AND_LEFT;
}

"Map(" {
    return MAP_LEFT;
}

"~"   { return COMPLEMENT; }
"\\"  { return TERM_COMPLEMENT; }
"&"   { return INTERSECTION; }
"-"   { return MINUS; }

"$."  { return CONTAINMENT_ONCE; }
"$?"  { return CONTAINMENT_OPT; }
"$"   { return CONTAINMENT; }

"+"   { return PLUS; }
"*"   { return STAR; }

"./." { return IGNORE_INTERNALLY; }
"/"   { return IGNORING; }

"|"   { return UNION; }

"<>"  { return SHUFFLE; }
"<"   { return BEFORE; }
">"   { return AFTER; }

".o." { return COMPOSITION; }
".O." { return LENIENT_COMPOSITION; }
".x." { return CROSS_PRODUCT; }
".P." { return UPPER_PRIORITY_UNION; }
".p." { return LOWER_PRIORITY_UNION; }
".-u." { return UPPER_MINUS; }
".-l." { return LOWER_MINUS; }

"`[[" { return SUBSTITUTE_LEFT; }

"\\<=" { return LEFT_RESTRICTION; }
"<=>" { return LEFT_RIGHT_ARROW; }
"<=" { return LEFT_ARROW; }
"=>" { return RIGHT_ARROW; }
"->" { return REPLACE_RIGHT; }
"(->)" { return OPTIONAL_REPLACE_RIGHT; }
"<-" { return REPLACE_LEFT; }
"(<-)" { return OPTIONAL_REPLACE_LEFT; }
"<->" { return REPLACE_LEFT_RIGHT; }
"(<->)" { return OPTIONAL_REPLACE_LEFT_RIGHT; }

"@->" { return LTR_LONGEST_MATCH; }
"@>" { return LTR_SHORTEST_MATCH; }
"->@" { return RTL_LONGEST_MATCH; }
">@" { return RTL_SHORTEST_MATCH; }

"||" { return REPLACE_CONTEXT_UU; }
"//" { return REPLACE_CONTEXT_LU; }
"\\\\" { return REPLACE_CONTEXT_UL; }
"\\//" { return REPLACE_CONTEXT_LL; }
"_"+ { return CENTER_MARKER; }
"..."+ { return MARKUP_MARKER; }

"\\\\\\" { return LEFT_QUOTIENT; }

"^"{UINTEGER}","{UINTEGER} { 
    pmatchlval.values = hfst::pmatch::get_n_to_k(pmatchtext);
    return CATENATE_N_TO_K;
}

"^{"{UINTEGER}","{UINTEGER}"}" {
    pmatchlval.values = hfst::pmatch::get_n_to_k(pmatchtext);
    return CATENATE_N_TO_K;
}

"^>"{UINTEGER} { 
    pmatchlval.value = strtol(pmatchtext + 2, 0, 10);
    return CATENATE_N_PLUS; 
}

"^<"{UINTEGER} { 
    pmatchlval.value = strtol(pmatchtext + 2, 0, 10);
    return CATENATE_N_MINUS;
}

"^"{UINTEGER}                  { 
    pmatchlval.value = strtol(pmatchtext + 1, 0, 10);
    return CATENATE_N;
}

".r" { return REVERSE; }
".i" { return INVERT; }
".u" { return UPPER; }
".l" { return LOWER; }

"@bin\""[^""]+"\""|"@\""[^""]+"\"" { 
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '"');
    return READ_BIN;
}

"@txt\""[^""]+"\"" {
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '"');
    return READ_TEXT;
}

"@stxt\""[^""]+"\"" {
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '"');
    return READ_SPACED;
}

"@pl\""[^""]+"\"" {
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '"');
    return READ_PROLOG;
}

"@re\""[^""]+"\"" {
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '"');
    return READ_RE;
}

"@lexc\""[^""]+"\"" {
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '"');
    return READ_LEXC;
}

"[." { return LEFT_BRACKET_DOTTED; }
".]" { return RIGHT_BRACKET_DOTTED; }
"[" { return LEFT_BRACKET; }
"]" { return RIGHT_BRACKET; }
"(" { return LEFT_PARENTHESIS; }
")" { return RIGHT_PARENTHESIS; }

{LWSP}":"{LWSP} { return PAIR_SEPARATOR_SOLE; }
^":"$ { return PAIR_SEPARATOR_SOLE; }
{LWSP}":" { return PAIR_SEPARATOR_WO_LEFT; }
":"{LWSP} { return PAIR_SEPARATOR_WO_RIGHT; }
":" { return PAIR_SEPARATOR; }

"::"{WEIGHT} {
    pmatchlval.weight = hfst::pmatch::get_weight(pmatchtext + 2);
    return WEIGHT;
}
"{"([^}]|"\\}")+"}" {
    pmatchlval.label = hfst::pmatch::get_escaped_delimited(pmatchtext, '{', '}');
    return CURLY_LITERAL;
}

"\""([^"\""]|"\\\"")+"\"" {
    pmatchlval.label = hfst::pmatch::parse_quoted(pmatchtext); 
    return QUOTED_LITERAL;
}

",," { return COMMACOMMA; }
"," { return COMMA; }

"\"\"" { return EPSILON_TOKEN; }
"[]" { return EPSILON_TOKEN; }
"0" { return EPSILON_TOKEN; }
"?" { return ANY_TOKEN; }
"#"|".#." { return BOUNDARY_MARKER; }

{EC} {
    pmatchlval.label = hfst::pmatch::strip_percents(pmatchtext);
    return QUOTED_LITERAL;
}

{NAME_CH}+ {
    pmatchlval.label = hfst::pmatch::strip_percents(pmatchtext);
    return SYMBOL;
}

{NAME_CH}+"(" {
    char * label = (char *) malloc(strlen(pmatchtext));;
    strncpy(label, pmatchtext, strlen(pmatchtext));
    label[strlen(pmatchtext) - 1] = '\0';
    pmatchlval.label = hfst::pmatch::strip_percents(label);
    free(label);
    return SYMBOL_WITH_LEFT_PAREN;
}

";"{WSP}*{WEIGHT} {
    pmatchlval.weight = hfst::pmatch::get_weight(pmatchtext + 2);
    return END_OF_WEIGHTED_EXPRESSION;
}

";" { 
    return END_OF_EXPRESSION;
}

{LWSP}* { /* ignorable whitespace */ }

("!")[^\n]*$ { /* ignore comments */ }

. { 
    return LEXER_ERROR;
}

%%
