#ifdef WINDOWS
#include <string>
namespace hfst 
{
  std::string wide_string_to_string(const std::wstring & wstr);
}
#endif
