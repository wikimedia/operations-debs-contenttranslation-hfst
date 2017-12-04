================================
 HFST: Metadata header registry
================================

The HFST3 metadata headers are metadata contained in HFST3 transducer container
files. The HFST3 transducer format is a container format for FST files akin to
AVI and MKV for videos, OGG for sounds etc. The HFST3 files can contain any
FST binary data with minimal extra data. HFST3 library and applications will of
course be able to read only the FST formats that are included in the library as
backends (codecs, to follow the media file analogy).

This document lists the field names that can be used in HFST3 metadata headers.
The fields listed here are exhaustive list of names that currently have effect
on processing of the automata. Note that using a name not specified here does
not guarantee that it will not be used in future versions; if you wish to add
private extensions you should prefix the names with *X-*.

The names and values of the headers *should* be case-sensitive, so version
header *may* not match Version header. There will, however, never be two
headers with only case differences in names, so implementations *may* use
heuristics to use Version header values as version iff no lower-case variant
exists

HFST core headers from 3.0 version
----------------------------------

These are the headers that were present in the initial release of HFST 3 and
are supported by all HFST software. The headers type and version *must* exist
in any HFST transducer that contains HFST3 magic bytes in the beginning. The
header name can be omitted, in that case tools will use the filename, if
available, to represent the transducer in user interfaces. Note, that the first
metadata header in all files *should* be the version header, so incompatible
parsers can quit parsing as soon as possible without breaking.

name
  The user-readable name for the automata used in user interfaces
  instead of the file name, if available. Example: *The Finnish
  hyphenator of Omorfi dictionary*. A missing name header means
  *filename[index]* is used to represent the automaton.
type
  The identifier of the format for the transducer binary stored in the
  file. The values of type header are written in all capitals. This is
  used by library to decide which library will parse the contained
  automata. Example: *TROPICAL_OPENFST*.
version
  Minimum ersion of HFST required to parse all data in the headers or
  the contents of the transducer data. The value 3.0 indicates that
  only 3.0 headers will be used. The value 3.3 allows any downwards
  compatible header to be used. Version value 4.0 or greater will
  prevent library versions 3 to use the file. Example: *3.0*

Optional headers in 3.3 version
-------------------------------

These headers were introduced in version 3.3 of the library and header format.
The headers in this list are not required in automata files but may be necessary
for specific tools to function correctly.


character-encoding
  The encoding used for characters in file. The value must
  be *utf-8*, since use of other character encodings is not
  considered good practice at the time. This is used by
  corpus processing tools to determine if they can safely
  allow the use of automaton or require user for conversion.
commandline-definition
  The possible reconstruction of commands used to create current transducer.
  This can be only as accurate as command-line reconstructions can be, i.e.
  things that are parsed by shell but won't be passed to the program, such as
  pipes and redirections, can only be guessed. Example:
  *hfst-lexc lexicon.lexc -o lexicon.hfst && hfst-twolc rules.twolc -o
  rules.hfst; hfst-compose-intersect lexicon.hfst rules.hfst*.
compression
  The compression scheme used for automaton data. The
  automata in the file can be compressed using any of
  available algorithms. It should be noted that compressed
  automata cannot be used as freely as uncompressed ones and
  their use requires extra libraries. Some compression
  schemes may not be usable in standard streams at all. This
  is used by library to uncompress the data before passing
  it to respective libraries for reading.
  Example: *gzip*.
content-version
  Version of automaton. The version may be used by
  corpora tools to determine which of multiple automatons
  with same purpose and name to use. The version *should* be
  in similar full-stop separated version vector format as is
  used with most software. Not to be confused with *version* header, which
  defines the version of libhfst where current header format was introduced.
  Example: *2.6.38.1*.
copyright
  The copyright holder of the transducer data as whole. The
  existence or absence of this header has no effects to
  copyrights as rendered by Berne convention, it is only
  for informative purposes. Example: *(c) 2011, University
  of Helsinki*.
dcmi-text
  DCMI Text encoded *Dublin Core* metadata. Most of
  arbitrary and useless metadata belongs under this
  section, that is governed by external standard. DCMI compatible tools may
  present this data to end users. Example::
    
    DescriptionSet (
       Description (
          Statement (
              PropertyURI ( dcterms:title )
              LiteralValueString ( "English morphological analyser" )
          )
       )
    )
formulaic-definition
  A description of automaton using tight formula notation.
gpg-signature
  GPG signature of the transducer data.
gpg-encryption
  GPG encryption key used to decrypt the transducer data.
md5sum
  MD5 check sum of the transducer data. This may be used by
  tools to verify transducer integrity. Should only be used
  on systems that are unable to calculate more reliable
  checksums. Example: **
language
  The natural language that automata encodes in BCP 47
  format. This is used by corpora processing tools to select
  suitable automata. The value *und* is used for undefined
  and *qtz* for non-linguistic data, such as rules and
  other automata.  Example: *fi*.
last-modified
  Date of creation for the automata. Date *should* use
  specific ISO 8901 format, that corresponds *strftime(3)*
  specification *%Y-%m-%dZ%H:%M:%S*. Example:
  *2011-08-24Z19:25:21*
length
  Size of automaton in octets. This is the number of octets
  to read from file from the end of headers to the beginning
  of next automaton header or EOF. This may be used by the
  library to read whole automaton data to a buffer. Example:
  *314592*.
licence
  The licence that applies to use of transducer data. The
  existence or absence of this header has no effects to
  copyrights as rendered by Berne convention, it is only
  for informative purposes. Example: *GNU GPLv3*.
purpose
  The automaton's primary use. The corpora and writers'
  tools use this to enumerate available functionalities.
  Currently supported values are: *analysis*, *generation*,
  *error model*, *hyphenation*, *phonological rules*,
  *spell-checking*.
revision
  A revision identifier of version controlling system.
  This can be used by human reader to reproduce the
  automaton from publicly avaible version controlling
  system. Example: *73624* (from SVN).
shasum
  SHA check sum of the transducer data. This can be used
  to verify transducer integrity. Example:
  *4a7f4849457500fe27585515f6d99924dbf99121*.
xfst-definition
  Xerox regular expression defining the automata. Does not
  accurately reproduce the original formula in Xerox's
  implementation. Xfst's name *DEFINITION*. Example:
  *a ;*
xfst-toolversions
  Versions of tools used to build the automata. Xfst's name
  *TOOLVERSIONS*. Example:
  *( ( hfst-xfst 0.1 ) ( libhfst 3.4 ) )*.

.. vim: set ft=rst:
