#ifdef WINDOWS
#include <windows.h>
#include <string>
namespace hfst 
{
  std::string wide_string_to_string(const std::wstring & wstr)
    {
      int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
      std::string str( size_needed, 0 );
      WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
      return str;
    }
}
#endif
