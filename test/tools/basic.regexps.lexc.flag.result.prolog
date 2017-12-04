network(NO_NAME_1).
arc(NO_NAME_1, 0, 1, "@P.LEXNAME.Root@").
arc(NO_NAME_1, 1, 2, "@R.LEXNAME.Root@").
arc(NO_NAME_1, 2, 3, "a":"C").
arc(NO_NAME_1, 2, 4, "a":"B").
arc(NO_NAME_1, 3, 10, "@P.LEXNAME.BAZ@").
arc(NO_NAME_1, 4, 5, "@P.LEXNAME.BAR@").
arc(NO_NAME_1, 5, 6, "@R.LEXNAME.BAR@").
arc(NO_NAME_1, 6, 7, "a":"b").
arc(NO_NAME_1, 7, 8, "@P.LEXNAME.#@").
arc(NO_NAME_1, 8, 9, "@R.LEXNAME.#@").
arc(NO_NAME_1, 10, 11, "@R.LEXNAME.BAZ@").
arc(NO_NAME_1, 11, 7, "a":"c").
final(NO_NAME_1, 9).
