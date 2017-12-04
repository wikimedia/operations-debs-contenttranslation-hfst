namespace hfst {
  namespace xfst {

    typedef std::map<std::string, hfst::xfst::XfstCommand> Name2Cmd;
    Name2Cmd name2cmd;
    typedef std::map<hfst::xfst::XfstCommand, std::vector<std::string> > Cmd2Names;
    Cmd2Names cmd2names;

    typedef std::set<hfst::xfst::XfstCommand> XfstCommandSet;
    typedef std::map<std::string, XfstCommandSet > Txt2Cmds;
    Txt2Cmds txt2cmds;

    XfstCommandSet get_commands(const std::string & name)
      {
        XfstCommandSet retval;

        Name2Cmd::const_iterator name2cmd_it = name2cmd.find(name);
        Txt2Cmds::const_iterator txt2cmds_it = txt2cmds.find(name);

        if (name2cmd_it != name2cmd.end())
          {
            retval.insert(name2cmd_it->second);
          }
        if (txt2cmds_it != txt2cmds.end())
          {
            XfstCommandSet commands = txt2cmds_it->second;
            for (XfstCommandSet::const_iterator it = commands.begin();
                 it != commands.end(); it++)
              {
                retval.insert(*it);
              }
          }
        return retval;
      }

    void xfst_mapping(XfstCommand command, const char * names_)
    {
      char * names = strdup(names_);
      char * names_begin = names;
      char * name = names;
      while (true)
        {
          if (*names == '\0')
            {
              //fprintf(stderr, "adding name: '%s'\n", name);
              cmd2names[command].push_back(std::string(name));
              name2cmd[std::string(name)] = command;
              break;
            }
          if (*names == ',')
            {
              *names = '\0';
              names++;
              *names = '\0';
              //fprintf(stderr, "adding name: '%s'\n", name);
              cmd2names[command].push_back(std::string(name));
              name2cmd[std::string(name)] = command;
              names++;
              name = names;
            }
          else
            {
              names++;
            }
        }
      free(names_begin);
    }

    void init_name2cmd()
    {
      // Used for cases like "apply" -> "apply [up|down|med]"
    std::set<hfst::xfst::XfstCommand> cmdset;

    xfst_mapping(ADD_PROPS_CMD, "add properties, add");
    xfst_mapping(APPLY_UP_CMD, "apply up, up");
    xfst_mapping(APPLY_DOWN_CMD, "apply down, down");
    xfst_mapping(APPLY_DOWN_CMD, "apply med, med");

    // "apply"
    cmdset.insert(APPLY_UP_CMD);
    cmdset.insert(APPLY_DOWN_CMD);
    cmdset.insert(APPLY_MED_CMD);
    txt2cmds["apply"] = cmdset;

    xfst_mapping(AMBIGUOUS_CMD, "ambiguous upper, ambiguous");
    xfst_mapping(DEFINE_ALIAS_CMD, "alias");
    xfst_mapping(APROPOS_CMD, "apropos");
    xfst_mapping(CLEANUP_CMD, "cleanup net, cleanup");
    xfst_mapping(CLEAR_CMD, "clear stack, clear");
    xfst_mapping(COLLECT_EPSILON_LOOPS_CMD, "collect epsilon-loops, epsilon-loops");
    xfst_mapping(COMPACT_SIGMA_CMD, "compact sigma");
    xfst_mapping(COMPILE_REPLACE_LOWER_CMD, "compile-replace lower, com-rep lower");
    xfst_mapping(COMPILE_REPLACE_UPPER_CMD, "compile-replace upper, com-rep upper");

    // "compile-replace", "com-rep"
    cmdset.clear();
    cmdset.insert(COMPILE_REPLACE_LOWER_CMD);
    cmdset.insert(COMPILE_REPLACE_UPPER_CMD);
    txt2cmds["compile-replace"] = cmdset;
    txt2cmds["com-rep"] = cmdset;

    xfst_mapping(COMPLETE_CMD, "complete net, complete");
    xfst_mapping(COMPOSE_CMD, "compose net, compose");
    xfst_mapping(CONCATENATE_CMD, "concatenate net, concatenate");
    xfst_mapping(LOOKUP_OPTIMIZE_CMD, "lookup-optimize, lookup-optimise");
    xfst_mapping(REMOVE_OPTIMIZATION_CMD, "remove-optimization, remove-optimisation");
    xfst_mapping(CROSSPRODUCT_CMD, "crossproduct net, crossproduct");
    xfst_mapping(DEFINE_CMD, "define");
    xfst_mapping(DETERMINIZE_CMD, "determinize net, determinize, determinize net, determinise");
    xfst_mapping(ECHO_CMD, "echo");
    xfst_mapping(EDIT_PROPS_CMD, "edit properties, edit");
    xfst_mapping(ELIMINATE_FLAG_CMD, "eliminate flag");
    xfst_mapping(ELIMINATE_ALL_CMD, "eliminate flags");

    // "eliminate"
    cmdset.clear();
    cmdset.insert(ELIMINATE_FLAG_CMD);
    cmdset.insert(ELIMINATE_ALL_CMD);
    txt2cmds["eliminate"] = cmdset;

    xfst_mapping(EPSILON_REMOVE_CMD, "epsilon-remove net, epsilon-remove");
    xfst_mapping(EXTRACT_AMBIGUOUS_CMD, "extract ambiguous");
    xfst_mapping(EXTRACT_UNAMBIGUOUS_CMD, "extract unambiguous");

    // "extract"
    cmdset.clear();
    cmdset.insert(EXTRACT_AMBIGUOUS_CMD);
    cmdset.insert(EXTRACT_UNAMBIGUOUS_CMD);
    txt2cmds["extract"] = cmdset;

    xfst_mapping(DESCRIBE_CMD, "help");
    xfst_mapping(LICENCE_CMD, "help licence, help license");
    xfst_mapping(WARRANTY_CMD, "help warranty");

    // "help"
    cmdset.clear();
    cmdset.insert(DESCRIBE_CMD);
    cmdset.insert(LICENCE_CMD);
    cmdset.insert(WARRANTY_CMD);
    txt2cmds["help"] = cmdset;

    xfst_mapping(HFST_CMD, "hfst");
    xfst_mapping(IGNORE_CMD, "ignore net, ignore");
    xfst_mapping(INTERSECT_CMD, "intersect net, intersect");
    xfst_mapping(INTERSECT_CMD, "conjunct");
    xfst_mapping(INSPECT_CMD, "inspect, inspect net");
    xfst_mapping(INVERT_CMD, "invert net, invert");
    xfst_mapping(LABEL_CMD, "label net");
    xfst_mapping(LIST_CMD, "list");
    xfst_mapping(LOADD_CMD, "load defined, loadd");
    xfst_mapping(LOADS_CMD, "load, load stack");
    xfst_mapping(LOWER_SIDE_CMD, "lower-side net, lower-side");
    xfst_mapping(MINIMIZE_CMD, "minimize net, minimize, minimise");
    xfst_mapping(MINUS_CMD, "minus net, minus, subtract");
    xfst_mapping(NAME_CMD, "name net, name");
    xfst_mapping(NEGATE_CMD, "negate net, negate");
    xfst_mapping(ONE_PLUS_CMD, "one-plus net, one-plus");
    xfst_mapping(POP_CMD, "pop, pop stack");
    xfst_mapping(PRINT_ALIASES_CMD, "print aliases, aliases");
    xfst_mapping(PRINT_ARCCOUNT_CMD, "print arc-tally, arc-tally");
    xfst_mapping(PRINT_DEFINED_CMD, "print defined, pdefined");
    xfst_mapping(SAVE_DEFINITIONS_CMD, "write definition, wdef, write definitions, wdefs");
    xfst_mapping(PRINT_DIR_CMD, "print directory, directory");
    xfst_mapping(SAVE_DOT_CMD, "write dot, wdot, dot");
    xfst_mapping(WRITE_ATT_CMD, "write att, att");
    xfst_mapping(PRINT_FILE_INFO_CMD, "print file-info, file-info");
    xfst_mapping(PRINT_FLAGS_CMD, "print flags, flags");
    xfst_mapping(PRINT_LABELS_CMD, "print labels, labels");
    xfst_mapping(PRINT_LABELMAPS_CMD, "print label-maps, label-maps");
    xfst_mapping(PRINT_LABEL_COUNT_CMD, "print label-tally, label-tally");
    xfst_mapping(PRINT_LIST_CMD, "print list");
    xfst_mapping(PRINT_LISTS_CMD, "print lists");
    xfst_mapping(PRINT_LONGEST_STRING_CMD, "print longest-string, longest-string, pls");
    xfst_mapping(PRINT_LONGEST_STRING_SIZE_CMD, "print longest-string-size, longest-string-size, plz");
    xfst_mapping(PRINT_LOWER_WORDS_CMD, "print lower-words, lower-words");
    xfst_mapping(PRINT_NAME_CMD, "print name, pname");
    xfst_mapping(PRINT_CMD, "print net");
    xfst_mapping(PRINT_PROPS_CMD, "print properties, print props, write properties, write props");
    xfst_mapping(PRINT_RANDOM_LOWER_CMD, "print random-lower, random-lower");
    xfst_mapping(PRINT_RANDOM_UPPER_CMD, "print random-upper, random-upper");
    xfst_mapping(PRINT_RANDOM_WORDS_CMD, "print random-words, random-words");
    xfst_mapping(PRINT_SHORTEST_STRING_SIZE_CMD, "print shortest-string-size, print shortest-string-length, "
                 "shortest-string-size, shortest-string-length, psz");
    xfst_mapping(PRINT_SHORTEST_STRING_CMD, "print shortest-string, shortest-string, pss");
    xfst_mapping(PRINT_SIGMA_CMD, "print sigma, sigma");
    xfst_mapping(PRINT_SIGMA_COUNT_CMD, "print sigma-tally, sigma-tally, sitally, print sigma-word-tally");
    xfst_mapping(PRINT_SIZE_CMD, "print size, size");
    xfst_mapping(PRINT_STACK_CMD, "print stack, stack");
    xfst_mapping(PRINT_UPPER_WORDS_CMD, "print upper-words, upper-words");
    xfst_mapping(PRINT_WORDS_CMD, "print words, words");

    // "print"
    cmdset.clear();
    cmdset.insert(PRINT_ALIASES_CMD);
    cmdset.insert(PRINT_ARCCOUNT_CMD);
    cmdset.insert(PRINT_DEFINED_CMD);
    cmdset.insert(PRINT_DIR_CMD);
    cmdset.insert(PRINT_FILE_INFO_CMD);
    cmdset.insert(PRINT_FLAGS_CMD);
    cmdset.insert(PRINT_LABELS_CMD);
    cmdset.insert(PRINT_LABELMAPS_CMD);
    cmdset.insert(PRINT_LABEL_COUNT_CMD);
    cmdset.insert(PRINT_LIST_CMD);
    cmdset.insert(PRINT_LISTS_CMD);
    cmdset.insert(PRINT_LONGEST_STRING_CMD);
    cmdset.insert(PRINT_LONGEST_STRING_SIZE_CMD);
    cmdset.insert(PRINT_LOWER_WORDS_CMD);
    cmdset.insert(PRINT_NAME_CMD);
    cmdset.insert(PRINT_CMD);
    cmdset.insert(PRINT_PROPS_CMD);
    cmdset.insert(PRINT_RANDOM_LOWER_CMD);
    cmdset.insert(PRINT_RANDOM_UPPER_CMD);
    cmdset.insert(PRINT_RANDOM_WORDS_CMD);
    cmdset.insert(PRINT_SHORTEST_STRING_SIZE_CMD);
    cmdset.insert(PRINT_SHORTEST_STRING_CMD);
    cmdset.insert(PRINT_SIGMA_CMD);
    cmdset.insert(PRINT_SIGMA_COUNT_CMD);
    cmdset.insert(PRINT_SIGMA_WORD_COUNT_CMD);
    cmdset.insert(PRINT_SIZE_CMD);
    cmdset.insert(PRINT_STACK_CMD);
    cmdset.insert(PRINT_UPPER_WORDS_CMD);
    cmdset.insert(PRINT_WORDS_CMD);
    txt2cmds["print"] = cmdset;

    // "write"
    cmdset.clear();
    cmdset.insert(SAVE_DEFINITIONS_CMD);
    cmdset.insert(SAVE_DEFINITIONS_CMD);
    cmdset.insert(SAVE_DOT_CMD);
    cmdset.insert(WRITE_ATT_CMD);
    cmdset.insert(PRINT_PROPS_CMD);
    cmdset.insert(PRINT_PROPS_CMD);
    cmdset.insert(SAVE_PROLOG_CMD);
    cmdset.insert(SAVE_SPACED_CMD);
    cmdset.insert(SAVE_TEXT_CMD);
    txt2cmds["write"] = cmdset;

    xfst_mapping(PRUNE_NET_CMD, "prune net, prune");
    xfst_mapping(PUSH_DEFINED_CMD, "push, push defined");
    xfst_mapping(QUIT_CMD, "quit, exit, bye, stop, hyvästi, au revoir, näkemiin, viszlát, auf wiedersehen, has"
                 "ta la vista, arrivederci, ongdodongo");
    xfst_mapping(READ_LEXC_CMD, "lexc, read lexc");
    xfst_mapping(READ_ATT_CMD, "att, read att");
    xfst_mapping(READ_PROPS_CMD, "read properties, rprops");
    xfst_mapping(READ_PROLOG_CMD, "read prolog, rpl");
    xfst_mapping(READ_REGEX_CMD, "regex, read regex");
    xfst_mapping(READ_SPACED_CMD, "rs, read spaced-text");
    xfst_mapping(READ_TEXT_CMD, "rt, read text");

    // "read"
    cmdset.clear();
    cmdset.insert(READ_LEXC_CMD);
    cmdset.insert(READ_ATT_CMD);
    cmdset.insert(READ_PROPS_CMD);
    cmdset.insert(READ_PROLOG_CMD);
    cmdset.insert(READ_REGEX_CMD);
    cmdset.insert(READ_SPACED_CMD);
    cmdset.insert(READ_TEXT_CMD);
    txt2cmds["read"] = cmdset;

    // "save"
    cmdset.clear();
    cmdset.insert(SAVE_DEFINITIONS_CMD);
    cmdset.insert(SAVE_STACK_CMD);
    txt2cmds["save"] = cmdset;

    // "sort"
    cmdset.clear();
    cmdset.insert(SORT_IN_CMD);
    cmdset.insert(SORT_OUT_CMD);
    cmdset.insert(SORT_NET_CMD);
    txt2cmds["sort"] = cmdset;

    // "substitute"
    cmdset.clear();
    cmdset.insert(SUBSTITUTE_NAMED_CMD);
    cmdset.insert(SUBSTITUTE_LABEL_CMD);
    cmdset.insert(SUBSTITUTE_SYMBOL_CMD);
    txt2cmds["substitute"] = cmdset;

    // "test"
    cmdset.clear();
    cmdset.insert(TEST_EQ_CMD);
    cmdset.insert(TEST_FUNCT_CMD);
    cmdset.insert(TEST_ID_CMD);
    cmdset.insert(TEST_LOWER_BOUNDED_CMD);
    cmdset.insert(TEST_LOWER_UNI_CMD);
    cmdset.insert(TEST_NONNULL_CMD);
    cmdset.insert(TEST_NULL_CMD);
    cmdset.insert(TEST_OVERLAP_CMD);
    cmdset.insert(TEST_SUBLANGUAGE_CMD);
    cmdset.insert(TEST_UPPER_BOUNDED_CMD);
    cmdset.insert(TEST_UPPER_UNI_CMD);
    cmdset.insert(TEST_UNAMBIGUOUS_CMD);
    txt2cmds["test"] = cmdset;

    xfst_mapping(REVERSE_CMD, "reverse net, reverse");
    xfst_mapping(ROTATE_CMD, "rotate, rotate stack");
    xfst_mapping(SAVE_DEFINITIONS_CMD, "save defined, saved");
    xfst_mapping(SAVE_STACK_CMD, "save stack, save, ss");
    xfst_mapping(SET_CMD, "set");
    xfst_mapping(SHOW_ALL_CMD, "show variables");
    xfst_mapping(SHOW_CMD, "show variable, show");
    xfst_mapping(SHUFFLE_CMD, "shuffle net, shuffle");
    xfst_mapping(SIGMA_CMD, "sigma net");
    xfst_mapping(SORT_NET_CMD, "sort net, sort");
    xfst_mapping(SORT_IN_CMD, "sort in");
    xfst_mapping(SORT_OUT_CMD, "sort out");
    xfst_mapping(SOURCE_CMD, "source");
    xfst_mapping(SUBSTITUTE_NAMED_CMD, "substitute defined");
    xfst_mapping(FOR_CMD, "for");
    xfst_mapping(SUBSTITUTE_LABEL_CMD, "substitute label");
    xfst_mapping(SUBSTITUTE_SYMBOL_CMD, "substitute symbol");
    xfst_mapping(SUBSTRING_CMD, "substring net, substring");
    xfst_mapping(SYSTEM_CMD, "system");
    xfst_mapping(TEST_EQ_CMD, "test equivalent, equivalent, te");
    xfst_mapping(TEST_FUNCT_CMD, "test functional, functional, tf");
    xfst_mapping(TEST_ID_CMD, "test identity, identity, ti");
    xfst_mapping(TEST_LOWER_BOUNDED_CMD, "test lower-bounded, lower-bounded, tlb");
    xfst_mapping(TEST_LOWER_UNI_CMD, "test lower-universal, lower-universal, tlu");
    xfst_mapping(TEST_NONNULL_CMD, "test non-null, tnn");
    xfst_mapping(TEST_NULL_CMD, "test null, tnu");
    xfst_mapping(TEST_OVERLAP_CMD, "test overlap, overlap, to");
    xfst_mapping(TEST_SUBLANGUAGE_CMD, "test sublanguage, sublanguage, ts");
    xfst_mapping(TEST_UPPER_BOUNDED_CMD, "test upper-bounded, upper-bounded, tub");
    xfst_mapping(TEST_UPPER_UNI_CMD, "test upper-universal, upper-universal, tuu");
    xfst_mapping(TEST_UNAMBIGUOUS_CMD, "test unambiguous");
    xfst_mapping(TURN_CMD, "turn, turn stack");
    xfst_mapping(TWOSIDED_FLAGS_CMD, "twosided flag-diacritics, tfd");
    xfst_mapping(UNDEFINE_CMD, "undefine");
    xfst_mapping(UNLIST_CMD, "unlist");
    xfst_mapping(UNION_CMD, "union net, union, disjunct");
    xfst_mapping(UPPER_SIDE_CMD, "upper-side net, upper-side");
    xfst_mapping(VIEW_CMD, "view net");
    xfst_mapping(SAVE_PROLOG_CMD, "wpl, write prolog, wspaced-text");
    xfst_mapping(SAVE_SPACED_CMD, "write spaced-text");
    xfst_mapping(SAVE_TEXT_CMD, "wt, write text");
    xfst_mapping(ZERO_PLUS_CMD, "zero-plus net, zero-plus");
    
    }
  }
}
