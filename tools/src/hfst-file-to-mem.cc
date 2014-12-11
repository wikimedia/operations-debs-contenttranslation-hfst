#include <stdio.h>
#include <cstring>
#include "hfst-commandline.h"
#include <cstdlib>

//#include <stdbool.h>
//#include "../../back-ends/foma/fomalib.h" // todo: find the exact header where xxmalloc is defined

char * hfst_stdin_to_mem()
{
  size_t maxbytes = 1000000;
  size_t numbytes = 0;
  // fix: slow
  char * buffer = (char*)malloc((maxbytes) * sizeof(char));
  if(buffer == NULL)
    {
      error(EXIT_FAILURE, 0, "Error allocating memory to read file '<stdin>'\n");
      return NULL;
    }

  while(true) 
    { 
      *(buffer + numbytes) = fgetc(stdin);
      if (feof(stdin))
        {
          *(buffer + numbytes) = '\0';
          break;
        }
      numbytes++;
      if (numbytes >= maxbytes)
        {
          error(EXIT_FAILURE, 0, "Error reading file '<stdin>' to memory, not enough memory\n");
          return NULL;
        }
    }
  return buffer;
}

// Based on a function in foma written by Mans Hulden.                                       
// Read the file 'filename' to memory and return a pointer to it.                            
// Filename "<stdin>" uses stdin for reading.                                              
// Returns NULL if file cannot be opened or read or memory cannot be allocated.              

char * hfst_file_to_mem(const char *filename) {

  if (strcmp(filename, "<stdin>") == 0)
    {
      return hfst_stdin_to_mem();
    }

  FILE   *infile;
  size_t  numbytes;
  char   *buffer;
  infile = fopen(filename, "rb");
  if(infile == NULL)
    {
      error(EXIT_FAILURE, 0, "Error opening file '%s'\n", filename);
      return NULL;
    }
  fseek(infile, 0L, SEEK_END);
  numbytes = ftell(infile);
  fseek(infile, 0L, SEEK_SET);

  buffer = (char*)malloc((numbytes+1) * sizeof(char));
  if(buffer == NULL)
    {
      error(EXIT_FAILURE, 0, "Error allocating memory to read file '%s'\n", filename);
      return NULL;
    }
  if (fread(buffer, sizeof(char), numbytes, infile) != numbytes)
    {
      error(EXIT_FAILURE, 0, "Error reading file '%s' to memory\n", filename);
      return NULL;
    }
  fclose(infile);
  *(buffer+numbytes)='\0';
  return(buffer);
}
