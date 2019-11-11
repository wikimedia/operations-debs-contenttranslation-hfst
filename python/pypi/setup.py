#!/usr/bin/python3

"""
Setup for creating PIP packages for HFST Python bindings.

Before running setup, recursively copy directories 'libhfst/src'
and 'back-ends' from HFST C++ source code under the directory where
setup is run (on linux and OS X with copy-files.sh and on windows with
copy-files-win.sh). Make sure that the following C++ files 
from 'libhfst/src/parsers' have been generated from flex/yacc files
before copying (on linux and OS X by running 'make' and on windows
with 'compile-parsers-win.sh' located in 'libhfst/src/parsers'):

  lexc-lexer.cc pmatch_lex.cc xfst-lexer.cc xre_lex.cc sfst-scanner.cc
  lexc-parser.cc pmatch_parse.cc xfst-parser.cc xre_parse.cc sfst-compiler.cc
  lexc-parser.hh pmatch_parse.hh xfst-parser.hh xre_parse.hh sfst-compiler.hh

Compiling the extensions requires python, swig and a C++ compiler,
all located on a directory listed on system PATH. On linux and OS X,
readline and getline must be available.

The setup script has been tested on linux with gcc 5.4.0, swig 3.0.12 and
python 3.5 and on windows with swig 3.0.5 and msvc 10.0 (with python 3.4)
and msvc 14.0 (with python 3.5 and 3.6).

"""

from setuptools import setup, Extension
from sys import argv, platform


# ----- README -----

def readme():
    with open('README.rst') as f:
        return f.read()


# ----- SETUP OPTION HANDLING -----

# If hfst-specific option is found in sys.argv, remove it and return True. Else, return False.
def hfst_specific_option(option):
    if option in argv:
        index = argv.index(option)
        argv.pop(index)
        return True
    else:
        return False


# ----- C++ STANDARD  -----

# Use C++ standard C++11 unless compiling for Python 2.7 for Windows (requires msvc 2008 which does not support C++11)
# or for OS X (C++11 requires libc++ instead of libstdc++ and minimum version requirement 10.7 instead of 10.6).
CPP_STD_11=True
from sys import version_info
if (platform == "darwin") or (platform == "win32" and version_info[0] == 2):
    CPP_STD_11=False
# Override default behaviour, if requested.
if hfst_specific_option('--with-c++11'):
    CPP_STD_11=True
if hfst_specific_option('--without-c++11'):
    CPP_STD_11=False

# By default, use the C++ version of foma backend. C++11 requires option -std=c++0x to be set for C/C++ compiler
# (this cannot de defined for each file separately) and some compilers refuse to compile C with that option.
CPP_FOMA=True
if hfst_specific_option('--with-c++-foma'):
    CPP_FOMA=True
if hfst_specific_option('--with-c-foma'):
    CPP_FOMA=False

# Experimental...
if platform == "darwin" and CPP_STD_11:
    import os
    os.environ["_PYTHON_HOST_PLATFORM"] = 'macosx-10.7-x86_64'


# ----- SWIG CONFIGURATION -----

# HFST C++ headers needed by swig when creating the python/c++ interface
swig_include_dir = "libhfst/src/"
# Generate wrapper for C++
ext_swig_opts = ["-c++", "-I" + swig_include_dir, "-Wall"]
# for python3.3 and python3.4 on windows, add SDK include directory
if platform == "win32" and version_info[0] == 3 and (version_info[1] == 3 or version_info[1] == 4):
    ext_swig_opts.extend(["-IC:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.0A\\Include"])
# By default, we have a pre-swig-generated wrapper
ext_source = ["libhfst_wrap.cpp"]
if hfst_specific_option('--generate-wrapper'):
    ext_source = ["libhfst.i"]

# ----- LINKER ARGUMENTS -----

# Readline is needed for hfst.start_xfst(). On windows the shell where HFST
# python bindings are run from has its own readline which will do.
include_readline=False
include_getline=False
if platform == "linux" or platform == "linux2" or platform == "darwin":
    include_readline=True
    include_getline=True
if hfst_specific_option('--no-readline'):
    include_readline=False
ext_extra_link_args = []
if include_readline:
    ext_extra_link_args = ['-lreadline']
# Experimental...
if platform == "darwin" and CPP_STD_11:
    ext_extra_link_args.extend(['-mmacosx-version-min=10.7'])


# ----- INCLUDE DIRECTORIES -----

# HFST headers needed when compiling the actual c++ extension
ext_include_dirs = [".", "libhfst/src/", "back-ends/foma", "back-ends",
                    "parsers", "libhfst/src/parsers"]
if platform == "win32":
    ext_include_dirs.append("back-ends/openfstwin/src/include")
else:
    ext_include_dirs.append("back-ends/openfst/src/include")


# ----- CONFIGURATION -----

# Include foma implementation for OS X only when c++11 is disabled.
include_foma_backend=True
if platform == "linux" or platform == "linux2" or platform == "win32" or (platform == "darwin" and not CPP_STD_11):
    include_foma_backend=True
ext_define_macros = []
if include_foma_backend:
    ext_define_macros.append(('HAVE_FOMA', None))

# Openfst backend is always enabled
ext_define_macros.append(('HAVE_OPENFST', None))
ext_define_macros.append(('HAVE_OPENFST_LOG', None))

if include_readline:
    ext_define_macros.append(('HAVE_READLINE', None))
if include_getline:
    ext_define_macros.append(('HAVE_GETLINE', None))

# msvc-specific macros.
if platform == "win32":
    # MSC_VER_ should already be defined
    for macro in ["HFSTEXPORT", "OPENFSTEXPORT", "WINDOWS", "WIN32", "_CRT_SECURE_NO_WARNINGS"]:
        ext_define_macros.append((macro, None))

# If C++11 is not supported, what features will be disabled and where unordered map and set are found.
if (not CPP_STD_11):
    # Disable c++11 features.
    ext_define_macros.append(('NO_CPLUSPLUS_11', None))
    # Unordered containers are in namespace std::tr1.
    ext_define_macros.append(('USE_TR1_UNORDERED_MAP_AND_SET', None))
    # On windows, the header files are not located in directory tr1
    # although the namespace is std::tr1.
    if not platform == "win32":
        ext_define_macros.append(('INCLUDE_TR1_UNORDERED_MAP_AND_SET', None))


# ----- COMPILATION OPTIONS -----

ext_extra_compile_args = []
if platform == "linux" or platform == "linux2" or platform == "darwin":
    ext_extra_compile_args = ["-Wno-sign-compare", "-Wno-strict-prototypes"]
    # C++11 standard does not need to be specifically requested for msvc compilers.
    if CPP_STD_11:
        ext_extra_compile_args.extend(["-std=c++0x"])
# Experimental...
if platform == "darwin" and CPP_STD_11:
    ext_extra_compile_args.extend(["-stdlib=libc++", "-mmacosx-version-min=10.7"])
# define error handling mechanism on windows
if platform == "win32":
    ext_extra_compile_args = ["/EHsc"]


# ----- C++ SOURCE FILES -----

# C++ source files have 'cpp' extension
cpp = ".cpp"

# on windows, openfst back-end is in directory 'openfstwin'
openfstdir = "openfst"
if platform == "win32":
    openfstdir = "openfstwin"

# foma source file extension (C++ by default)
fe = cpp
if not CPP_FOMA:
    fe = ".c"

# all c++ extension source files
libhfst_source_files = ["libhfst/src/parsers/XfstCompiler" + cpp,
                        "libhfst/src/HfstApply" + cpp,
                        "libhfst/src/HfstInputStream" + cpp,
                        "libhfst/src/HfstTransducer" + cpp,
                        "libhfst/src/HfstOutputStream" + cpp,
                        "libhfst/src/HfstRules" + cpp,
                        "libhfst/src/HfstXeroxRules" + cpp,
                        "libhfst/src/HfstDataTypes" + cpp,
                        "libhfst/src/HfstSymbolDefs" + cpp,
                        "libhfst/src/HfstTokenizer" + cpp,
                        "libhfst/src/HfstFlagDiacritics" + cpp,
                        "libhfst/src/HfstExceptionDefs" + cpp,
                        "libhfst/src/HarmonizeUnknownAndIdentitySymbols" + cpp,
                        "libhfst/src/HfstLookupFlagDiacritics" + cpp,
                        "libhfst/src/HfstEpsilonHandler" + cpp,
                        "libhfst/src/HfstStrings2FstTokenizer" + cpp,
                        "libhfst/src/HfstPrintDot" + cpp,
                        "libhfst/src/HfstPrintPCKimmo" + cpp,
                        "libhfst/src/hfst-string-conversions" + cpp,
                        "libhfst/src/string-utils" + cpp,
                        "libhfst/src/implementations/HfstBasicTransducer" + cpp,
                        "libhfst/src/implementations/HfstBasicTransition" + cpp,
                        "libhfst/src/implementations/ConvertTransducerFormat" + cpp,
                        "libhfst/src/implementations/HfstTropicalTransducerTransitionData" + cpp,
                        "libhfst/src/implementations/ConvertTropicalWeightTransducer" + cpp,
                        "libhfst/src/implementations/ConvertLogWeightTransducer" + cpp,
                        "libhfst/src/implementations/ConvertFomaTransducer" + cpp,
                        "libhfst/src/implementations/ConvertOlTransducer" + cpp,
                        "libhfst/src/implementations/TropicalWeightTransducer" + cpp,
                        "libhfst/src/implementations/LogWeightTransducer" + cpp,
                        "libhfst/src/implementations/FomaTransducer" + cpp,
                        "libhfst/src/implementations/HfstOlTransducer" + cpp,
                        "libhfst/src/implementations/compose_intersect/ComposeIntersectRulePair" + cpp,
                        "libhfst/src/implementations/compose_intersect/ComposeIntersectLexicon" + cpp,
                        "libhfst/src/implementations/compose_intersect/ComposeIntersectRule" + cpp,
                        "libhfst/src/implementations/compose_intersect/ComposeIntersectFst" + cpp,
                        "libhfst/src/implementations/compose_intersect/ComposeIntersectUtilities" + cpp,
                        "libhfst/src/implementations/optimized-lookup/transducer" + cpp,
                        "libhfst/src/implementations/optimized-lookup/convert" + cpp,
                        "libhfst/src/implementations/optimized-lookup/ospell" + cpp,
                        "libhfst/src/implementations/optimized-lookup/pmatch" + cpp,
                        "libhfst/src/implementations/optimized-lookup/pmatch_tokenize" + cpp,
                        "libhfst/src/implementations/optimized-lookup/find_epsilon_loops" + cpp,
                        "libhfst/src/parsers/xre_lex" + cpp,
                        "libhfst/src/parsers/xre_parse" + cpp,
                        "libhfst/src/parsers/pmatch_parse" + cpp,
                        "libhfst/src/parsers/pmatch_lex" + cpp,
                        "libhfst/src/parsers/lexc-parser" + cpp,
                        "libhfst/src/parsers/lexc-lexer" + cpp,
                        "libhfst/src/parsers/xfst-parser" + cpp,
                        "libhfst/src/parsers/xfst-lexer" + cpp,
                        "libhfst/src/parsers/LexcCompiler" + cpp,
                        "libhfst/src/parsers/PmatchCompiler" + cpp,
                        "libhfst/src/parsers/XreCompiler" + cpp,
                        "libhfst/src/parsers/lexc-utils" + cpp,
                        "libhfst/src/parsers/pmatch_utils" + cpp,
                        "libhfst/src/parsers/xre_utils" + cpp,
                        "libhfst/src/parsers/xfst-utils" + cpp,
                        "libhfst/src/parsers/xfst_help_message" + cpp,
                        "libhfst/src/parsers/sfst-scanner" + cpp,
                        "libhfst/src/parsers/sfst-compiler" + cpp,
                        "libhfst/src/parsers/SfstCompiler" + cpp,
                        "libhfst/src/parsers/SfstAlphabet" + cpp,
                        "libhfst/src/parsers/SfstBasic" + cpp,
                        "libhfst/src/parsers/SfstUtf8" + cpp,
                        "libhfst/src/parsers/htwolcpre1-lexer" + cpp,
                        "libhfst/src/parsers/htwolcpre2-lexer" + cpp,
                        "libhfst/src/parsers/htwolcpre3-lexer" + cpp,
                        "libhfst/src/parsers/htwolcpre1-parser" + cpp,
                        "libhfst/src/parsers/htwolcpre2-parser" + cpp,
                        "libhfst/src/parsers/htwolcpre3-parser" + cpp,
                        "libhfst/src/parsers/TwolcCompiler" + cpp,
                        "libhfst/src/parsers/io_src/InputReader" + cpp,
                        "libhfst/src/parsers/string_src/string_manipulation" + cpp,
                        "libhfst/src/parsers/variable_src/RuleSymbolVector" + cpp,
                        "libhfst/src/parsers/variable_src/RuleVariables" + cpp,
                        "libhfst/src/parsers/variable_src/RuleVariablesConstIterator" + cpp,
                        "libhfst/src/parsers/variable_src/VariableValues" + cpp,
                        "libhfst/src/parsers/rule_src/ConflictResolvingLeftArrowRule" + cpp,
                        "libhfst/src/parsers/rule_src/ConflictResolvingRightArrowRule" + cpp,
                        "libhfst/src/parsers/rule_src/LeftArrowRule" + cpp,
                        "libhfst/src/parsers/rule_src/LeftArrowRuleContainer" + cpp,
                        "libhfst/src/parsers/rule_src/LeftRestrictionArrowRule" + cpp,
                        "libhfst/src/parsers/rule_src/OtherSymbolTransducer" + cpp,
                        "libhfst/src/parsers/rule_src/RightArrowRule" + cpp,
                        "libhfst/src/parsers/rule_src/RightArrowRuleContainer" + cpp,
                        "libhfst/src/parsers/rule_src/Rule" + cpp,
                        "libhfst/src/parsers/rule_src/RuleContainer" + cpp,
                        "libhfst/src/parsers/rule_src/TwolCGrammar" + cpp,
                        "libhfst/src/parsers/alphabet_src/Alphabet" + cpp ]

foma_source_files = [ "back-ends/foma/int_stack" + fe,
                      "back-ends/foma/define" + fe,
                      "back-ends/foma/determinize" + fe,
                      "back-ends/foma/apply" + fe,
                      "back-ends/foma/rewrite" + fe,
                      "back-ends/foma/topsort" + fe,
                      "back-ends/foma/flags" + fe,
                      "back-ends/foma/minimize" + fe,
                      "back-ends/foma/reverse" + fe,
                      "back-ends/foma/extract" + fe,
                      "back-ends/foma/sigma" + fe,
                      "back-ends/foma/structures" + fe,
                      "back-ends/foma/constructions" + fe,
                      "back-ends/foma/coaccessible" + fe,
                      "back-ends/foma/io" + fe,
                      "back-ends/foma/utf8" + fe,
                      "back-ends/foma/spelling" + fe,
                      "back-ends/foma/dynarray" + fe,
                      "back-ends/foma/mem" + fe,
                      "back-ends/foma/stringhash" + fe,
                      "back-ends/foma/trie" + fe,
                      "back-ends/foma/lex.yy" + fe,
                      "back-ends/foma/regex" + fe ]

openfst_source_files =  [ "back-ends/" + openfstdir + "/src/lib/compat" + cpp,
                          "back-ends/" + openfstdir + "/src/lib/flags" + cpp,
                          "back-ends/" + openfstdir + "/src/lib/fst" + cpp,
                          "back-ends/" + openfstdir + "/src/lib/properties" + cpp,
                          "back-ends/" + openfstdir + "/src/lib/symbol-table" + cpp,
                          "back-ends/" + openfstdir + "/src/lib/symbol-table-ops" + cpp,
                          "back-ends/" + openfstdir + "/src/lib/util" + cpp ]

libhfst_source_files = libhfst_source_files + openfst_source_files

if include_foma_backend:
    libhfst_source_files = libhfst_source_files + foma_source_files

ext_package_data = {}
if (platform == "win32"):
    if (version_info[0] == 2 and version_info[1] > 6):
        package_data = {'hfst': ['MSVCP90.DLL', 'MSVCR90.DLL']}
    elif (version_info[0] == 3 and version_info[1] > 4):
        package_data = {'hfst': ['MSVCP140.DLL', 'VCRUNTIME140.DLL']}
    else:
        pass

# (Is this needed?)
# foma_object_files = []
# (compile foma backend separately)
# for file in back-ends/foma/*.c; do clang -fPIC -std=c99 -arch i386 -arch x86_64 -mmacosx-version-min=10.7 -DHAVE_FOMA -c $file ; done
# if platform == "darwin":
#     for file in foma_source_files:
#         foma_object_files.append(file.replace('back-ends/foma/','').replace('.c','.o'))
# in Extension: extra_objects = foma_object_files


# ----- The HFST C++ EXTENSION -----

libhfst_module = Extension('_libhfst',
                           language = "c++",
                           sources = ext_source + libhfst_source_files,
                           swig_opts = ext_swig_opts,
                           include_dirs = ext_include_dirs,
                           define_macros = ext_define_macros,
                           extra_link_args = ext_extra_link_args,
                           extra_compile_args = ext_extra_compile_args
                           )

setup(name = 'hfst',
      version = '3.15.1.0_beta',
      author = 'HFST team',
      author_email = 'hfst-bugs@helsinki.fi',
      url = 'http://hfst.github.io/',
      description = 'Python interface for HFST',
      long_description = readme(),
      license = 'GNU GPL3',
      ext_modules = [libhfst_module],
      py_modules = ["libhfst"],
      packages = ["hfst", "hfst.exceptions", "hfst.sfst_rules", "hfst.xerox_rules"],
      package_data = ext_package_data,
      data_files = []
      )
