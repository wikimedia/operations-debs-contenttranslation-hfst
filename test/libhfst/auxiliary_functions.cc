const bool VERBOSE=true;

void verbose_print(const char *msg,
           hfst::ImplementationType type=hfst::ERROR_TYPE) {
  if (VERBOSE) {
    fprintf(stderr, "Testing:\t%s", msg);
    fprintf(stderr, " for type ");
    switch (type)
      {
      case hfst::SFST_TYPE:
    fprintf(stderr, "SFST_TYPE");
    break;
      case hfst::TROPICAL_OPENFST_TYPE:
    fprintf(stderr, "TROPICAL_OPENFST_TYPE");
    break;
      case hfst::LOG_OPENFST_TYPE:
    fprintf(stderr, "LOG_OPENFST_TYPE");
    break;
      case hfst::FOMA_TYPE:
    fprintf(stderr, "FOMA_TYPE");
    break;
      case hfst::HFST_OL_TYPE:
    fprintf(stderr, "HFST_OL_TYPE");
    break;
      case hfst::HFST_OLW_TYPE:
    fprintf(stderr, "HFST_OLW_TYPE");
    break;
      default:
    fprintf(stderr, "(type undefined)");
    break;
      }
    fprintf(stderr, "...\n");
  }
}

unsigned char get_bin(size_t fact_128, size_t fact_64, size_t fact_32,
              size_t fact_16 , size_t fact_8 , size_t fact_4 ,
              size_t fact_2  , size_t fact_1)
{
  return
    fact_128*128 + fact_64*64 + fact_32*32 + fact_16*16 + fact_8*8 +
    fact_4*4 + fact_2*2+ fact_1*1;
}
