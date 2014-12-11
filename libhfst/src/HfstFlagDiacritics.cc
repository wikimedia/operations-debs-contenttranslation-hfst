#include "HfstFlagDiacritics.h"

#ifndef MAIN_TEST

namespace hfst {

bool FdOperation::is_diacritic(const std::string& diacritic_string)
{
  // All diacritics have form @[A-Z][.][A-Z]+([.][A-Z]+)?@
  if (diacritic_string.size() < 5)
    { return false; }
  if (diacritic_string.at(2) != '.')
    { return false; }
  // These two checks probably always succeed...
  if (diacritic_string.at(0) != '@')
    { return false; }
  if (diacritic_string.at(diacritic_string.size()-1) != '@')
    { return false; }
  switch (diacritic_string.at(1))
    {
    case 'P':
      break;
    case 'N':
      break;
    case 'D':
      break;
    case 'R':
      break;
    case 'C':
      break;
    case 'U':
      break;
    default:
      return false;
    }
  if (diacritic_string.find_last_of('.') == 2)
    {
      if ((diacritic_string.at(1) != 'R') and
          (diacritic_string.at(1) != 'D') and
          (diacritic_string.at(1) != 'C'))
      { return false; }
    }
  return true;
}
  
  std::string FdOperation::get_operator(const std::string& diacritic)
  { 
    // The operator is the second char.
    return diacritic.substr(1,1); 
  }

  std::string FdOperation::get_feature(const std::string& diacritic)
  {
    // The feature name starts after the '@', '.' and operator chars.
    size_t feature_start = 3;

    // The feature name ends at the '.' char after the feature name star pos.
    size_t feature_past  = diacritic.find('.',3);

    return diacritic.substr(feature_start, feature_past - feature_start);
  }

  std::string FdOperation::get_value(const std::string& diacritic)
  {
    // The value starts after the second '.' char.
    size_t value_start = diacritic.find('.',diacritic.find('.') + 1) + 1;

    // The value ends at the last char.
    size_t value_past  = diacritic.size() - 1;

    return diacritic.substr(value_start,value_past - value_start);
  }

  bool FdOperation::has_value(const std::string& flag_diacritic)
  { 
    return flag_diacritic.find('.',flag_diacritic.find('.') + 1) != 
      std::string::npos;
  }

std::string::size_type FdOperation::find_diacritic
(const std::string& diacritic_str, 
 std::string::size_type& length)
{
  std::string::size_type start = diacritic_str.find('@');
  if(start != std::string::npos)
  {
    std::string::size_type end = diacritic_str.find('@', start+1);
    if(end != std::string::npos)
    {
      if(is_diacritic(diacritic_str.substr(start, end-start)))
      {
        length = end-start;
        return start;
      }
    }
  }
  return std::string::npos;

}

}

#else // MAIN_TEST was defined

#include <iostream>
#include <cassert>

using namespace hfst;

int main(int argc, char * argv[])
{
    std::cout << "Unit tests for " __FILE__ ":" << std::endl;

    assert(FdOperation::is_diacritic("@D.NeedNoun.ON@"));
    assert(FdOperation::get_operator("@D.NeedNoun.ON@") == "D");
    assert(FdOperation::get_feature("@D.NeedNoun.ON@") == "NeedNoun");
    assert(FdOperation::get_value("@D.NeedNoun.ON@") == "ON");
    assert(FdOperation::has_value("@D.NeedNoun.ON@"));
    assert(not FdOperation::has_value("@C.NeedNoun@"));

    std::cout << "ok" << std::endl;
    return 0;
}

#endif // MAIN_TEST
