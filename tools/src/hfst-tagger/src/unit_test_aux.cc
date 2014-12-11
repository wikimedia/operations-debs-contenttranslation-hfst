#include "unit_test_aux.h"

#include <iostream>
#include <cstdlib>

void fail_test(const char * file,int line_number)
{
  std::cerr << "Test in file " << file << " fails on line "
	    << line_number << std::endl;

  exit(1);
}
