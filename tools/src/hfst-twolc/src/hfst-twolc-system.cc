//
// An alternative for the tool hfst-twolc.sh.
// Uses system calls instead of shell commands.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(int argc, char* argv[]) {

  char command [1000];
  std::string arguments;
  for(int i = 1; i < argc; i++) {
    arguments.append(std::string(argv[i]));
    arguments.append(std::string(" "));
  }

  (void)sprintf(command, 
                "htwolcpre1.exe %s | "
                "htwolcpre2.exe %s | "
                "htwolcpre3.exe %s", 
                arguments.c_str(), 
                arguments.c_str(), 
                arguments.c_str());

  int retval = system(command);
  if (retval != 0)
    return 1;
  return 0;

}
