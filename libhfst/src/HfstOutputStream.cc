//       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <string>

using std::string;

#include "HfstTransducer.h"
#include "HfstOutputStream.h"

#ifndef MAIN_TEST

namespace hfst
{
  HfstOutputStream::HfstOutputStream(ImplementationType type, bool hfst_format):
    type(type), hfst_format(hfst_format), is_open(false)
  { 
    if (not HfstTransducer::is_implementation_type_available(type)) {
      HFST_THROW(ImplementationTypeNotAvailableException);
    }

    switch(type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        implementation.sfst = 
          new hfst::implementations::SfstOutputStream();
        break;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        implementation.tropical_ofst = 
          new hfst::implementations::TropicalWeightOutputStream(hfst_format);
        break;
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        implementation.log_ofst = 
          new hfst::implementations::LogWeightOutputStream();
        break;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        implementation.foma = 
          new hfst::implementations::FomaOutputStream();
        break;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        implementation.my_transducer_library = 
          new hfst::implementations::MyTransducerLibraryOutputStream(hfst_format);
        break;
#endif
      case HFST_OL_TYPE:
        implementation.hfst_ol =
          new hfst::implementations::HfstOlOutputStream(false);
        break;
      case HFST_OLW_TYPE:
        implementation.hfst_ol =
          new hfst::implementations::HfstOlOutputStream(true);
        break;
      default:
        HFST_THROW(SpecifiedTypeRequiredException);
        break;
      }
    this->is_open=true;
  }
  // FIXME: HfstOutputStream takes a string parameter, 
  //        HfstInputStream a const char*
  HfstOutputStream::HfstOutputStream
  (const std::string &filename,ImplementationType type, bool hfst_format):
    type(type), hfst_format(hfst_format), is_open(false)
  { 
    if (not HfstTransducer::is_implementation_type_available(type)) {
      HFST_THROW(ImplementationTypeNotAvailableException);
    }

    switch(type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        implementation.sfst = 
          new hfst::implementations::SfstOutputStream(filename);
        break;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        // FIXME: this should be done in TropicalWeight layer
        if (filename.compare("") == 0) 
          implementation.tropical_ofst = 
            new hfst::implementations::TropicalWeightOutputStream(hfst_format);
        else
          implementation.tropical_ofst = 
            new hfst::implementations::TropicalWeightOutputStream
            (filename, hfst_format);
        break;
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        implementation.log_ofst = 
          new hfst::implementations::LogWeightOutputStream(filename);
        break;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        implementation.foma = 
          new hfst::implementations::FomaOutputStream(filename);
        break;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        implementation.my_transducer_library =
          new hfst::implementations::MyTransducerLibraryOutputStream(filename, hfst_format);
        break;
#endif
      case HFST_OL_TYPE:
        implementation.hfst_ol =
          new hfst::implementations::HfstOlOutputStream(filename, false);
        break;
      case HFST_OLW_TYPE:
        implementation.hfst_ol =
          new hfst::implementations::HfstOlOutputStream(filename.c_str(), true);
        break;
      default:
        HFST_THROW(SpecifiedTypeRequiredException);
        break;
      }
    this->is_open=true;
  }
  
  HfstOutputStream::~HfstOutputStream(void)
  {
    switch (type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        delete implementation.sfst;
        break;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        delete implementation.tropical_ofst;
        break;
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        delete implementation.log_ofst;
        break;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        delete implementation.foma;
        break;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        delete implementation.my_transducer_library;
        break;
#endif
      case HFST_OL_TYPE:
      case HFST_OLW_TYPE:
        delete implementation.hfst_ol;
        break;
      default:
        assert(false);
      }
  }

  void HfstOutputStream::append(std::vector<char> &str, const std::string &s)
  {
    for (unsigned int i=0; i<s.length(); i++)
      str.push_back(s[i]);
    str.push_back('\0');
  }

  void HfstOutputStream::write(const std::string &s)
  {
    for (unsigned int i=0; i<s.length(); i++)
      write(s[i]);
  }

  void HfstOutputStream::write(const std::vector<char> &s)
  {
    for (unsigned int i=0; i<s.size(); i++)
      write(s[i]);
  }

  void HfstOutputStream::write(const char &c)
  {
    switch(type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        implementation.sfst->write(c);
        break;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        implementation.tropical_ofst->write(c);
        break;
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        implementation.log_ofst->write(c);
        break;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        implementation.foma->write(c);
        break;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        implementation.my_transducer_library->write(c);
        break;
#endif
        // we always have HFST_OL, right?
      case HFST_OL_TYPE:
      case HFST_OLW_TYPE:
        implementation.hfst_ol->write(c);
        break;
        
      default:
        assert(false);
      }
  }

  void HfstOutputStream::append_hfst_header_data(std::vector<char> &header)
  {
    append(header, "version");
    append(header, "3.3");
    append(header, "type");

    std::string type_value;

    switch(type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        type_value=std::string("SFST");
        break;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        type_value=std::string("TROPICAL_OPENFST");
        break;
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        type_value=std::string("LOG_OPENFST");
        break;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        type_value=std::string("FOMA");
        break;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        type_value=std::string("MY_TRANSDUCER_LIBRARY");
        break;
#endif
      case HFST_OL_TYPE:
        type_value=std::string("HFST_OL");
        break;
      case HFST_OLW_TYPE:
        type_value=std::string("HFST_OLW");
        break;
      default:
        assert(false);
      }

    append(header, type_value);
  }

#if HAVE_SFST
void
HfstOutputStream::append_implementation_specific_header_data(std::vector<char>&
                                                             header,
                                                             HfstTransducer&
                                                             transducer)
#else
void 
HfstOutputStream::append_implementation_specific_header_data(std::vector<char>&,
                                                             HfstTransducer&)
#endif
  {
    switch(type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        implementation.sfst->append_implementation_specific_header_data
          (header, transducer.implementation.sfst);
        break;
#endif
      default:
        break;
      }
  }

  HfstOutputStream &HfstOutputStream::redirect (HfstTransducer &transducer)
  {
    return this->operator<<(transducer);
  }

  HfstOutputStream &HfstOutputStream::operator<< (HfstTransducer &transducer)
  {
    if (not this->is_open) {
      HFST_THROW(StreamIsClosedException);
    }
      

    if (type != transducer.type)
      {
        HFST_THROW_MESSAGE(TransducerTypeMismatchException, 
                           "operator<<: "
                           "HfstOutputStream and HfstTransducer do not "
                           "have the same type");
      }

    /* Write the HFST header. The header has the following structure:
       
       - the first four chars identify an HFST header:  "HFST"
       - the fifth char is a separator:                 "\0"
       - the sixth and seventh char tell the length of the rest of the header
         (beginning after the eighth char)
       - the eighth char is a separator and is not counted 
         to the header length: "\0"
       - the rest of the header consists of pairs of attributes and their values
         that are each separated by a char "\0"

       An example:

       "HFST\0"
       "\0\x1c\0"
       "version\0"  "3.0\0"
       "type\0"     "FOMA\0"
       "name\0"     "\0"
       
       This is the header of a version 3.0 HFST transducer whose implementation 
       type is foma and whose name is not defined, i.e. is the empty string "". 
       The two bytes "\0\x1c" that form the length field tell that the length of
       the rest of the header (i.e. the sequence of bytes
       "version\03.0\0type\0FOMA\0name\0\0") is 0 * 256 + 28 * 1 = 28 bytes.

       HFST version 3.0 header must contain at least the attributes 'version', 
       'type' and 'name' and their values. Implementation-specific attributes
       can follow after these obligatory attributes.
     */
    if (hfst_format) {
      const int MAX_HEADER_LENGTH=65535;

      // collect the header data here
      std::vector<char> header;
      append_hfst_header_data(header); // attributes "version" and "type"
      for (std::map<string,string>::const_iterator prop =
               transducer.props.begin();
           prop != transducer.props.end();
           ++prop)
        {
          if ((prop->first == "type") || (prop->first == "version"))
            {
              // special hanling above
              continue;
            }
          append(header, prop->first);
          append(header, prop->second);
        }

      append_implementation_specific_header_data(header, transducer);

      // write the field that identifies the header as an HFST header
      write("HFST");
      write('\0');

      // write header length using two bytes
      int header_length = (int)header.size();
      if (header_length > MAX_HEADER_LENGTH) {
        fprintf(stderr, "ERROR: transducer header is too long\n");
        exit(1);
      }

      char first_byte = *((char*)(&header_length));
      char second_byte = *((char*)(&header_length)+1);
      write(first_byte);
      write(second_byte);
      write('\0');

      // write the rest of the header
      write(header);
    } // if (hfst_format)

    switch (type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        implementation.sfst->write_transducer
          (transducer.implementation.sfst);
        return *this;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        implementation.tropical_ofst->write_transducer
          (transducer.implementation.tropical_ofst);
        return *this;    
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        implementation.log_ofst->write_transducer
          (transducer.implementation.log_ofst);
        return *this;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        implementation.foma->write_transducer
          (transducer.implementation.foma);
        return *this;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        implementation.my_transducer_library->write_transducer
          (transducer.implementation.my_transducer_library);
#endif
      case HFST_OL_TYPE:
      case HFST_OLW_TYPE:
        implementation.hfst_ol->write_transducer
          (transducer.implementation.hfst_ol);
        return *this;
      default:
        assert(false);
        return *this;
      }
  }

  void HfstOutputStream::close(void) {
    switch (type)
      {
#if HAVE_SFST
      case SFST_TYPE:
        implementation.sfst->close();
        break;
#endif
#if HAVE_OPENFST
      case TROPICAL_OPENFST_TYPE:
        implementation.tropical_ofst->close();
        break;
#if HAVE_OPENFST_LOG
      case LOG_OPENFST_TYPE:
        implementation.log_ofst->close();
        break;
#endif
#endif
#if HAVE_FOMA
      case FOMA_TYPE:
        implementation.foma->close();
        break;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
      case MY_TRANSDUCER_LIBRARY_TYPE:
        implementation.my_transducer_library->close();
        break;
#endif
      case HFST_OL_TYPE:
      case HFST_OLW_TYPE:
        implementation.hfst_ol->close();
        break;
      default:
        assert(false);
      }
    this->is_open=false;
  }

}

#else // MAIN_TEST was defined

#include <iostream>

int main(int argc, char * argv[])
{
    std::cout << "Unit tests for " __FILE__ ":" << std::endl;
    
    std::cout << "ok" << std::endl;
    return 0;
}

#endif // MAIN_TEST
