======================================================================
 Xerox flag diacritics and their support in HFST library and software
======================================================================

Flag diacritics are a scheme of marking long distance dependencies in FSTs,
detailed e.g. in [BEE98]_ and [BEE03]_. The flag diacritics are identified in
transducer as arcs of form @X.NAME@ or @X.NAME.VALUE@, where X is operation
identified by one of P, N, C, U, R or D. NAME and VALUE are arbitrary strings,
possibly originally limited to ASCII symbols. Their interpretation for automata
operations is to act as epsilons, excepting pathwise interpretation of automata
where invalid combination of flags on the path invalidates whole path.

The support for flag diacritics needs to be explicitly coded for many
operations. It is currently supported in intersecting composition (tool and
library function) and composition (tool), and only when flag diacritics are on
the left hand side transducer. It is also fully supported in all lookup tools,
and library functions, and all lookup related tools, such as diff-test. The
flag diacritics are not currently supported in any other programs, such as
fst2strings.



.. [BEE98] *Constraining separated morphotactic dependencies in
    finite-state grammars*, Kenneth R. Beesley.
.. [BEE03] *Finite State Morphology*, Kenneth R. Beesley, Lauri Karttunen
