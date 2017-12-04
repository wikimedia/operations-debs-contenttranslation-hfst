#ifdef WINDOWS
#pragma warning(disable: 4161)
#pragma warning(disable: 4103)
#include <windows.h>
#include <string>

#include <cstdarg>
#include <cstdio>
#include "HfstDataTypes.h"

#include <iostream> // for debugging

namespace hfst
{
  int hfst_fprintf_console(FILE * stream, const char * format, ...)
  {
    va_list args;
    va_start(args, format);

    if ((stream == stdout || stream == stderr))
      {
        char buffer [1024];
        int r = vsprintf(buffer, format, args);
        va_end(args);
        if (r < 0)
          return r;
        HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stream == stderr)
          stdHandle = GetStdHandle(STD_ERROR_HANDLE);

        std::string pstr(buffer);
        DWORD numWritten = 0;
        int wchars_num =
          MultiByteToWideChar(CP_UTF8 , 0 , pstr.c_str() , -1, NULL , 0 );
        wchar_t* wstr = new wchar_t[wchars_num];
        MultiByteToWideChar(CP_UTF8 , 0 ,
                            pstr.c_str() , -1, wstr , wchars_num );
        int retval = WriteConsoleW(stdHandle, wstr, wchars_num-1, &numWritten, NULL);
        delete[] wstr;

        return retval;
      }
    else
      {
        int retval = vfprintf(stream, format, args);
        va_end(args);
        return retval;
      }
  }

  bool get_line_from_console(std::string & str, size_t buffer_size, bool keep_newline /* = false*/)
  {
    bool DEBUG = false;
    SetConsoleCP(65001);
    const HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
    WCHAR * buffer = new WCHAR [buffer_size];
    DWORD numRead = 0;
    if (ReadConsoleW(stdIn, buffer, hfst::size_t_to_uint(buffer_size/4), &numRead, NULL))
      {
        if (DEBUG) { std::cerr << "get_line_from_console: numRead is " << numRead << std::endl; }
        
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, buffer, (int)numRead, NULL, 0, NULL, NULL);
        if (DEBUG) { std::cerr << "conversions: size_needed is " << size_needed << std::endl; }
        CHAR * strbuf = new CHAR [size_needed];
        WideCharToMultiByte(CP_UTF8, 0, buffer, (int)numRead, strbuf, size_needed, NULL, NULL);
        delete buffer;
        strbuf[size_needed] = 0; // NULL-terminate the buffer
        str = std::string(strbuf);
        
        if (DEBUG) { std::cerr << "get_line_from_console: size of str is now (1) " << str.size() << std::endl; }
        
        if (str[0] == (char)26 || str[0] == (char)4) // control+Z, control+D
          return false;

        // Get rid of carriage returns and newlines.

        if (str.size() == 0)
          return true;

        // Get rid of carriage return
        if (str.size() > 1)
          {
            if (str[str.size()-2] == '\r')
              str.erase(str.size()-2, 1);
          }

        if (str[str.size()-1] != '\n')
          return true;

        if (keep_newline)
          return true;

        str.erase(str.size()-1);
        return true;
        
        if (DEBUG) { std::cerr << "get_line_from_console: size of str is now (2) " << str.size() << std::endl; }
        return true;
      }
    return false;
  }

  void set_console_cp_to_utf8()
  {
    SetConsoleCP(65001);
  }

} // namespace hfst

#endif // WINDOWS
