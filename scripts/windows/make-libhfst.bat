SET debug_compile=
SET debug_link=

if "%1%"=="/DEBUG" SET debug_compile=/Zi /O2 /bigobj /MDd
if "%1%"=="/DEBUG" SET debug_link=/DEBUG /release

copy ..\..\back-ends\foma\libfoma.* .
copy ..\..\back-ends\openfstwin\src\lib\openfst.* .
cl %debug_compile% /EHsc /LD /Felibhfst.dll ^
/D HAVE_FOMA /D HAVE_OPENFST /D HFSTEXPORT /D_MSC_VER /DWINDOWS /DWIN32 ^
/I..\..\libhfst\src /I..\..\back-ends\foma /I..\..\back-ends /I..\..\back-ends\openfstwin\src\include /I ..\.. ^
/Iparsers /I..\.. /I..\..\libhfst\src /I..\..\libhfst\src\parsers /I..\..\back-ends\foma /I..\..\back-ends /I..\..\back-ends\openfstwin\src\include ^
HfstApply.cpp ^
HfstInputStream.cpp ^
HfstTransducer.cpp ^
HfstOutputStream.cpp ^
HfstRules.cpp ^
HfstXeroxRules.cpp ^
HfstDataTypes.cpp ^
HfstSymbolDefs.cpp ^
HfstTokenizer.cpp ^
HfstFlagDiacritics.cpp ^
HfstExceptionDefs.cpp ^
HarmonizeUnknownAndIdentitySymbols.cpp ^
HfstLookupFlagDiacritics.cpp ^
HfstEpsilonHandler.cpp ^
implementations\HfstTransitionGraph.cpp ^
implementations\ConvertTransducerFormat.cpp ^
implementations\HfstTropicalTransducerTransitionData.cpp ^
implementations\ConvertTropicalWeightTransducer.cpp ^
implementations\ConvertLogWeightTransducer.cpp ^
implementations\ConvertFomaTransducer.cpp ^
implementations\ConvertOlTransducer.cpp ^
implementations\TropicalWeightTransducer.cpp ^
implementations\LogWeightTransducer.cpp ^
implementations\FomaTransducer.cpp ^
implementations\HfstOlTransducer.cpp ^
implementations\compose_intersect\ComposeIntersectRulePair.cpp ^
implementations\compose_intersect\ComposeIntersectLexicon.cpp ^
implementations\compose_intersect\ComposeIntersectRule.cpp ^
implementations\compose_intersect\ComposeIntersectFst.cpp ^
implementations\compose_intersect\ComposeIntersectUtilities.cpp ^
implementations\optimized-lookup\transducer.cpp ^
implementations\optimized-lookup\convert.cpp ^
implementations\optimized-lookup\ospell.cpp ^
implementations\optimized-lookup\pmatch.cpp ^
implementations\optimized-lookup\find_epsilon_loops.cpp ^
parsers\xre_lex.cpp ^
parsers\xre_parse.cpp ^
parsers\pmatch_parse.cpp ^
parsers\pmatch_lex.cpp ^
parsers\lexc-parser.cpp ^
parsers\lexc-lexer.cpp ^
parsers\LexcCompiler.cpp ^
parsers\PmatchCompiler.cpp ^
parsers\XreCompiler.cpp ^
parsers\lexc-utils.cpp ^
parsers\pmatch_utils.cpp ^
parsers\xre_utils.cpp /link %debug_link% openfst.lib libfoma.lib
