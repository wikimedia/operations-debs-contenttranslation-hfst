//! @file CommandLine.cc

#include "CommandLine.h"

void CommandLine::print_version(void)
{
  // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dversion
  std::cerr << std::endl << PROGRAM_NAME << " " << 0 << " (" 
        << PACKAGE_STRING << ")" << std::endl
        << "Copyright (C) 2010 University of Helsinki," << std::endl
        << "License GPLv3: GNU GPL version 3 " << std::endl
        << "<http://gnu.org/licenses/gpl.html>" << std::endl
        << "This is free software: you are free to change and " 
        << std::endl
        << "redistribute it." << std::endl
        << "There is NO WARRANTY, to the extent permitted by law." 
        << std::endl << std::endl;
}

void CommandLine::print_usage(void)
{
  std::cerr << std::endl
        << "Usage: " << PROGRAM_NAME << " [OPTIONS...] INFILE" 
        << std::endl 
        << "Usage: " << PROGRAM_NAME << " [OPTIONS...] -i INFILE" 
        << std::endl 
        << "Usage: " << PROGRAM_NAME << " [OPTIONS...] --input=INFILE" 
        << std::endl 
        << "Usage: cat INFILE | " << PROGRAM_NAME << " [OPTIONS...]" 
        << std::endl
        << "An input file has to be given either using the option -i or"
        << std::endl
        << "--input, as the last commandline argument or from STDIN."
        << std::endl << std::endl;
}

void CommandLine::print_help(void)
{
  print_usage();
  std::cerr << std::endl
        << "Read a twolc grammar, compile it and store it. If INFILE is "
        << std::endl
        << "missing, the grammar is read from STDIN. If there is no output"
        << std::endl
        << "file given using -o or --output, the compiled grammar is"
        << std::endl
        << "written to STDOUT." << std::endl << std::endl;

  std::cerr << "Common options:\n"
        << "  -h, --help               Print help message" << std::endl  
        << "  -V, --version            Print version info" << std::endl 
        << "  -u, --usage              Print usage"  << std::endl
        << "  -v, --verbose            Print verbosely while processing"
        << std::endl
        << "  -q, --quiet              Do not print output" << std::endl
        << "  -s, --silent             Alias of --quiet"    << std::endl;

  std::cerr << "Input/Output options:" << std::endl
        << "  -i, --input=INFILE       Read input transducer from INFILE"
        << std::endl
        << "  -o, --output=OUTFILE     Write output transducer to OUTFILE"
        << std::endl;

  std::cerr << "TwolC grammar options:" << std::endl
        << "  -R, --resolve            Resolve left-arrow conflicts." 
        << std::endl
        << "  -D, --dont-resolve-right Don't resolve right-arrow conflicts." 
        << std::endl
        << "  -f, --format=FORMAT      Store result in format FORMAT." 
        << std::endl << std::endl;
  
  std::cerr << "Format may be one of openfst-log, openfst-tropical, foma or sfst."
        << std::endl << std::endl;

  std::cerr << "By default format is openfst-tropical. By default right arrow "
            << std::endl 
            << "conflicts are resolved and left arrow conflicts are not resolved."
            << std::endl << std::endl;
}

int CommandLine::parse_options(int argc, char** argv)
{
  bool resolve_left = false;
  bool resolve_right = true;
  bool verbose = false;
  bool silent = false;
  char * outfilename = NULL;
  bool outputNamed = false;
  bool inputNamed = false;
  bool isDebug = false; 
  char * infilename = NULL;
  char * debug_file_name = NULL;
  ImplementationType form = hfst::TROPICAL_OPENFST_TYPE;

  // use of this function requires options are settable on global scope
  while (true)
    {
      static const struct option long_options[] =
        {
      {"help", no_argument, 0, 'h'},    
      {"version", no_argument, 0, 'V'}, 
      {"verbose", no_argument, 0, 'v'}, 
      {"quiet", no_argument, 0, 'q'},   
      {"silent", no_argument, 0, 's'},  
      {"usage", no_argument, 0, 'u'},
      {"input", required_argument, 0, 'i'}, 
      {"output", required_argument, 0, 'o'},
      {"resolve-left",no_argument, 0, 'R'},
      {"dont-resolve-right",no_argument, 0, 'D'},
      {"debug_file",required_argument, 0, 'd'},
      {"format",required_argument, 0, 'f'},
      {0,0,0,0}
        };
      int option_index = 0;
      // add tool-specific options here 
      char c = getopt_long(argc, argv, 
               ":hVvqsu" "i:o:" "RDi:d:f:",
               long_options, &option_index);
      if (-1 == c)
        {
      break;
        }
      
      switch (c)
        {
    case 'h':
      help = true;
      break;
    case 'V':
      version = true;
      break;
    case 'u':
      usage = true;
      break;
    case 'v':
      verbose = true;
      break;
    case 'q':
      silent = true;
      break;
    case 's':
      silent = true;
      break;
    case 'R':
      resolve_left = true;
      break;
    case 'D':
      resolve_right = false;
      break;
    case 'i':
      inputNamed = true;
      infilename = hfst_strdup(optarg);
      break;
    case 'd':
      isDebug = true;
      debug_file_name = hfst_strdup(optarg);
      break;
    case 'o':
      outputNamed = true;
      outfilename = hfst_strdup(optarg);
      break;
    case 'f':
      if (std::string("tropical-weight") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      if (std::string("tropical") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      if (std::string("log") == optarg)
        { form = hfst::LOG_OPENFST_TYPE; }
      else if (std::string("tropical-openfst") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      else if (std::string("openfst-tropical") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      else if (std::string("log-weight") == optarg)
        { form = hfst::LOG_OPENFST_TYPE; }
      else if (std::string("log-openfst") == optarg)
        { form = hfst::LOG_OPENFST_TYPE; }
      else if (std::string("openfst-log") == optarg)
        { form = hfst::LOG_OPENFST_TYPE; }
      else if (std::string("openfst") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      else if (std::string("weighted") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      else if (std::string("weight") == optarg)
        { form = hfst::TROPICAL_OPENFST_TYPE; }
      else if (std::string("sfst") == optarg)
        { form = hfst::SFST_TYPE; }
      else if (std::string("foma") == optarg)
        { form = hfst::FOMA_TYPE; }
      else if (std::string("unweighted") == optarg)
        { form = hfst::FOMA_TYPE; }
      else
        { 
          std::cerr << "Unknown format \"" << optarg << "\"."
            << "Try running with option -h or --help."
            << std::endl;
          exit(1);
        }
      break;
    case ':':
      std::cerr << "Missing argument for -" << (char)optopt 
            << ". Try using --help." 
            << std::endl;
      exit(1);
    default:
      std::cerr << "Unknown commandline option: -" << (char)optopt
            << ". Try using --help." 
            << std::endl;
      exit(1);
        }
      
    }

  if (! inputNamed)
    {
      if ((argc - optind) == 1)
    { 
      inputNamed = true;
      infilename = hfst_strdup(argv[optind]); 
    }
      else if ((argc - optind) > 1)
    { 
      std::cerr << "no more than one input rule file may be given" 
            << std::endl; 
      exit(1);
    }
    }
  else 
    {
      if ((argc - optind) > 0)
    { 
      std::cerr << "no more than one input rule file may be given" 
            << std::endl; 
      exit(1);
    }

    }
  
  this->be_verbose = verbose;
  this->be_quiet = silent;
  this->has_input_file = inputNamed;
  this->has_output_file = outputNamed;
  this->resolve_left_conflicts = resolve_left;
  this->resolve_right_conflicts = resolve_right;
  if (this->has_input_file)
    { this->input_file_name = infilename; }
  if (this->has_output_file)
    { this->output_file_name = outfilename; }
  this->format = form;
  this->help = help;
  this->usage = usage;
  this->version = version;
  free(infilename);
  free(outfilename);

  if (isDebug)
    {
      this->has_debug_file = true;
      this->has_input_file = true;
      this->input_file_name = debug_file_name;
    }

  return EXIT_CONTINUE;
}

CommandLine::CommandLine(int argc,char * argv[]):
  be_verbose(false),
  be_quiet(false),
  has_input_file(false),
  input_file(NULL),
  has_output_file(false),
  output_file(NULL),
  resolve_left_conflicts(false),
  resolve_right_conflicts(true),
  help(false),
  version(false),
  usage(false),
  has_debug_file(false)
{ parse_options(argc,argv); }

CommandLine::~CommandLine(void)
{
  delete input_file;
  delete output_file;
}

std::istream &CommandLine::set_input_file(void)
{
  if (has_input_file)
    {
      input_file = new std::ifstream(input_file_name.c_str());
      if (! input_file->good())
    { 
      std::cerr << "File " << input_file_name << " could not be opened!"
            << std::endl;
      std::cout << "__HFST_TWOLC_DIE";
      exit(1);
    }
      return *input_file;
    }
  return std::cin;
}

std::ostream &CommandLine::set_output_file(void)
{
  if (has_output_file)
    {
      output_file = new std::ofstream(output_file_name.c_str());
      if (! output_file->good())
    { 
      std::cerr << "File " << output_file_name << " could not be opened!"
            << std::endl;
      std::cout << "__HFST_TWOLC_DIE";
      exit(1);      
    }
      return *output_file;
    }
  return std::cout;
}

std::ostream &set_output_file(void);

#ifdef TEST_COMMAND_LINE
std::ostream &operator<<(std::ostream &out,const CommandLine &command_line)
{
  out 
    << "VERBOSE:\t"       << command_line.be_verbose << std::endl
    << "QUIET:\t\t"       << command_line.be_quiet << std::endl
    << "INFILE EXIST:\t"  << command_line.has_input_file << std::endl
    << "INFILE:\t\t"      << command_line.input_file_name << std::endl
    << "OUTFILE EXIST:\t" << command_line.has_output_file << std::endl
    << "OUTFILE:\t"       << command_line.output_file_name << std::endl
    << "FORMAT:\t\t"      << command_line.format << std::endl
    << "RESOLVE:\t"       << command_line.resolve_conflicts << std::endl;
  return out;
}

int main(int argc, char * argv[]) 
{
  CommandLine command_line(argc,argv);
  std::cout << command_line << std::endl;
}
#endif
