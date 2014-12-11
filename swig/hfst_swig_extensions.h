#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include "HfstDataTypes.h"
#include "HfstTransducer.h"
#include "HfstFlagDiacritics.h"
#include "implementations/optimized-lookup/pmatch.h"

// NO EFFECT in Swig...
// Make sure that all standard streams are in binary mode.
// Line feed and carriage return characters are not handled correctly
// in text mode.
//#include <fcntl.h>
//int _CRT_fmode = _O_BINARY;


typedef std::vector<std::pair <float, std::vector<std::string> > >
OneLevelPathVector;

typedef std::vector<std::pair <float, std::vector<std::pair<std::string, std::string> > > >
TwoLevelPathVector;

typedef std::vector<std::pair <std::string, float> > StringFloatVector;

class HfstPath {
 public:
  float weight;
  std::string input;
  std::string output;
  HfstPath() {
    weight = 0;
    input = std::string("");
    output = std::string("");
  };
  HfstPath(const HfstPath &path) {
    weight = path.weight;
    input = path.input;
    output = path.output;
  };
  HfstPath(float weight_, std::string &input_, std::string &output_) {
    weight = weight_;
    input = input_;
    output = output_;
  };
  ~HfstPath() {};
  void operator=(const HfstPath &path) {
    weight = path.weight;
    input = path.input;
    output = path.output;
  };
};

typedef std::vector<HfstPath> HfstPathVector;

namespace hfst {

  HfstTransducer ptrvalue(const HfstTransducer * t) {
    return *t;
  }

  HfstTwoLevelPaths extract_paths(const HfstTransducer &t, int max_num=-1, int cycles=-1)
  {
    HfstTwoLevelPaths result;
    t.extract_paths(result, max_num, cycles);
    return result;
  }

  HfstTwoLevelPaths extract_paths_fd(const HfstTransducer &t, int max_num=-1, int cycles=-1, bool filter_fd=false)
  {
    HfstTwoLevelPaths result;
    t.extract_paths_fd(result, max_num, cycles, filter_fd);
    return result;
  }

  OneLevelPathVector vectorize(HfstOneLevelPaths * holps)
  {
    std::vector<std::pair <float, std::vector<std::string> > > retval;
    for (HfstOneLevelPaths::const_iterator it = holps->begin();
         it != holps->end(); ++it) {
      retval.push_back(*it);
    }
    return retval;
  }
  
  TwoLevelPathVector vectorize(HfstTwoLevelPaths htlps)
  {
    std::vector<std::pair <float, std::vector<std::pair<std::string, std::string > > > > retval;
    for (HfstTwoLevelPaths::const_iterator it = htlps.begin();
         it != htlps.end(); ++it) {
      retval.push_back(*it);
    }
    return retval;
  }

  OneLevelPathVector purge_flags(OneLevelPathVector olpv)
  {
    OneLevelPathVector retval;
    for (OneLevelPathVector::const_iterator it = olpv.begin(); it != olpv.end();
         ++it) {
      std::vector<std::string> temp;
      for (std::vector<std::string>::const_iterator str_it =
             it->second.begin(); str_it != it->second.end(); ++str_it) {
        if (!FdOperation::is_diacritic(*str_it)) {
          temp.push_back(*str_it);
        }
      }
      retval.push_back(std::pair<float, std::vector<std::string> >(it->first, temp));
    }
    return retval;
  }

  TwoLevelPathVector purge_flags(TwoLevelPathVector tlpv)
  {
    TwoLevelPathVector retval;
    for (TwoLevelPathVector::const_iterator it = tlpv.begin(); it != tlpv.end();
         ++it) {
      std::vector<std::pair<std::string, std::string> > temp;
      for (std::vector<std::pair<std::string, std::string> >::const_iterator pair_it =
             it->second.begin(); pair_it != it->second.end(); ++pair_it) {
        if (!FdOperation::is_diacritic(pair_it->first)) {
          temp.push_back(*pair_it);
        }
      }
      retval.push_back(std::pair<float, std::vector<std::pair<std::string, std::string> > >(it->first, temp));
    }
    return retval;
  }
  
  HfstPathVector detokenize_vector(OneLevelPathVector olpv)
  {
    HfstPathVector retval;
    for (OneLevelPathVector::const_iterator it = olpv.begin(); it != olpv.end();
         ++it) {
      std::string temp;
      for (std::vector<std::string>::const_iterator str_it =
             it->second.begin(); str_it != it->second.end(); ++str_it) {
        temp.append(*str_it);
      }
      retval.push_back(HfstPath(it->first, temp, temp));
    }
    return retval;
  }

  HfstPathVector detokenize_vector(TwoLevelPathVector tlpv)
  {
    HfstPathVector retval;
    for (TwoLevelPathVector::const_iterator it = tlpv.begin(); it != tlpv.end();
         ++it) {
      std::string temp_in;
      std::string temp_out;
      for (std::vector<std::pair<std::string, std::string> >::const_iterator pair_it =
             it->second.begin(); pair_it != it->second.end(); ++pair_it) {
        temp_in.append(pair_it->first);
        temp_out.append(pair_it->second);
      }
      retval.push_back(HfstPath(it->first, temp_in, temp_out));
    }
    return retval;
  }
  
  HfstPathVector detokenize_paths(HfstOneLevelPaths * holps)
  {
    return detokenize_vector(vectorize(holps));
  }

  HfstPathVector detokenize_paths(HfstTwoLevelPaths htlps)
  {
    return detokenize_vector(vectorize(htlps));
  }

  HfstPathVector detokenize_and_purge_paths(HfstOneLevelPaths * holps)
  {
    return detokenize_vector(purge_flags(vectorize(holps)));
  }

  HfstPathVector detokenize_and_purge_paths(HfstTwoLevelPaths htlps)
  {
    return detokenize_vector(purge_flags(vectorize(htlps)));
  }

}

hfst_ol::PmatchContainer & load_pmatch(std::string filename)
{
    std::ifstream instream(filename.c_str());
    return * (new hfst_ol::PmatchContainer(instream));
}
