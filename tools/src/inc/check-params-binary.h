    if (firstNamed && secondNamed)
      {
        if ((argc - optind) > 0) // hfst-tool file1 file2 file3
          {
            error(EXIT_FAILURE, 0,
              "No more than two transducer files may be given");
          }
      }
    else if (!firstNamed && !secondNamed)
      {
        // neither input given in options:
        if ((argc - optind) == 2) // hfst-tool file1 file2
          {
            firstfilename = hfst_strdup(argv[optind]);
            firstfile = hfst_fopen(firstfilename, "r");
            secondfilename = hfst_strdup(argv[optind+1]);
            secondfile = hfst_fopen(secondfilename, "r");
            is_input_stdin = false;
          }
        else if ((argc - optind) == 1) // hfst-tool file2 < file1
          {
            secondfilename = hfst_strdup(argv[optind]);
            secondfile = hfst_fopen(secondfilename, "r");
            firstfilename = hfst_strdup("<stdin>");
            firstfile = stdin;
            is_input_stdin = true;
          }
        else if ((argc - optind) > 2)
          {
            error(EXIT_FAILURE, 0,
                  "no more than two transducer filenames may be given");
          }
        else // hfst-tool < file1
          {
	    error(EXIT_FAILURE, 0,
		  "at least one input must be from a named file");
          }
    }
    else if (!firstNamed) //
    {
        if ((argc - optind) == 1) // hfst-tool file1 -2 file2
        {
            firstfilename = hfst_strdup(argv[optind]);
            firstfile = hfst_fopen(firstfilename, "r");
            is_input_stdin = false;
        }
        else if ((argc - optind) == 0) // hfst-tool -2 file2 < file1
        {
            firstfilename = hfst_strdup("<stdin>");
            firstfile = stdin;
            is_input_stdin = true;
        }
        else // hfst-tool -2 file2 file1 file3
          {
            error(EXIT_FAILURE, 0,
                  "no more than two transducer filenames may be given");
          }
    }
    else if (!secondNamed)
    {
        if ((argc - optind) == 1) // hfst-tool file2 -1 file1
        {
            secondfilename = hfst_strdup(argv[optind]);
            secondfile = hfst_fopen(secondfilename, "r");
            is_input_stdin = false;
        }
        else if ((argc - optind) == 0) // hfst-tool -1 file1 < file2
        {
            secondfilename = hfst_strdup("<stdin>");
            secondfile = stdin;
            is_input_stdin = true;
        }
        else // hfst-tool -1 file1 file2 file3
          {
            error(EXIT_FAILURE, 0,
                  "no more than two transducer filenames may be given");
          }
    }
    else // hfst-tool < file1
    {
      error(EXIT_FAILURE, 0,
	    "at least one transducer filename must be given");
    }

