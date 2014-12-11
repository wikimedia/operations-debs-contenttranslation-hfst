#include <string>
#include <map>
#include <set>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include "../HfstExceptionDefs.h"

namespace hfst {

  namespace implementations {

    struct string_comparison {
      bool operator() (const std::string &str1, const std::string &str2) const {
        return (str1.compare(str2) < 0);
      }
    };
    
    /** @brief One implementation of template class C in 
        HfstTransition. 
        
        A HfstTropicalTransducerTransitionData has an input symbol and an 
        output symbol of type SymbolType (string) and a weight of type 
        WeightType (float).

        \internal Actually a HfstTropicalTransducerTransitionData has an 
        input and an output number of type unsigned int, but this 
        implementation is hidden from the user.
        The class has two static maps and functions that take care of conversion
        between strings and internal numbers.
        
        @see HfstTransition HfstBasicTransition */
    class HfstTropicalTransducerTransitionData {
    public:
      /** @brief The input and output symbol type. */
      typedef std::string SymbolType;
      /** @brief The weight type. */
      typedef float WeightType;
      /** @brief A set of symbols. */
      typedef std::set<SymbolType> SymbolTypeSet;
      
      typedef std::vector<SymbolType> 
        Number2SymbolVector;
      typedef std::map<SymbolType, unsigned int, string_comparison> 
        Symbol2NumberMap;

      static SymbolType get_epsilon()
      {
        return SymbolType("@_EPSILON_SYMBOL_@");
      }
      
      static SymbolType get_unknown()
      {
        return SymbolType("@_UNKNOWN_SYMBOL_@");
      }
      
      static SymbolType get_identity()
      {
        return SymbolType("@_IDENTITY_SYMBOL_@");
      }
      
    public: /* FIXME: Should be private. */
      /* Maps that contain information of the mappings between strings 
         and numbers */
      static Number2SymbolVector number2symbol_map;
      static Symbol2NumberMap symbol2number_map;
      /* The biggest number in use. */
      static unsigned int max_number;

      /* Get the biggest number used to represent a symbol. */
      static unsigned int get_max_number() {
        return max_number;
      }

      /* 
         Get a vector that defines how numbers of a transducer must
         be changed, i.e. harmonized, so that it follows the same 
         number-to-string encoding as all transducers that use the datatype
         HfstTropicalTransducerTransitionData.

         \a symbols defines how numbers are mapped to strings in the
         original transducer so that each index in \a symbols 
         is the number that corresponds to the string at that index.
         An empty string at an index means that the index is not
         used in the original transducer.

         The result is a vector whose each index is the number that
         must be replaced by the number at that index when a
         transducer is harmonized. If an index is not used in the
         transducer, the result will contain a zero at that index.
      */
      static std::vector<unsigned int> get_harmonization_vector
        (const std::vector<SymbolType> &symbols)
      {
        std::vector<unsigned int> harmv;
        harmv.reserve(symbols.size());
        harmv.resize(symbols.size(), 0);
        for (unsigned int i=0; i<symbols.size(); i++)
          {
            if (symbols.at(i) != "")
              harmv.at(i) = get_number(symbols.at(i));
          }
        return harmv;
      }

      static std::vector<unsigned int> get_reverse_harmonization_vector
        (const std::map<SymbolType, unsigned int> &symbols)
      {
        std::vector<unsigned int> harmv;
        harmv.reserve(max_number+1);
        harmv.resize(max_number+1, 0);
        for (unsigned int i=0; i<harmv.size(); i++)
          {
            std::map<SymbolType, unsigned int>::const_iterator it
              = symbols.find(get_symbol(i));
            if (it != symbols.end())
              harmv.at(i) = it->second;
          }
        return harmv;
      }

    protected:
      /* Get the symbol that is mapped as \a number */
      static const std::string &get_symbol(unsigned int number) 
      { 
        if (number >= number2symbol_map.size()) {
          std::string message("HfstTropicalTransducerTransitionData: "
                              "number ");
          std::ostringstream oss;
          oss << number;
          message.append(oss.str());
          message.append(" is not mapped to any symbol");
          HFST_THROW_MESSAGE
            (HfstFatalException, message);
        }
        return number2symbol_map[number];
      }

      /* Get the number that is used to represent \a symbol */
      static unsigned int get_number(const std::string &symbol) 
      {
        if(symbol == "") { // FAIL
          Symbol2NumberMap::iterator it = symbol2number_map.find(symbol);
          if (it == symbol2number_map.end()) {
            std::cerr << "ERROR: No number for the empty symbol\n" 
                      << std::endl;
          }
          else {
            std::cerr << "ERROR: The empty symbol corresdponds to number " 
                      << it->second << std::endl;
          }
          assert(false);
        }
        
        Symbol2NumberMap::iterator it = symbol2number_map.find(symbol);
        if (it == symbol2number_map.end()) 
          {
            max_number++;
            symbol2number_map[symbol] = max_number;
            number2symbol_map.push_back(symbol);            
            return max_number;
          }
        return it->second;
      }

      //private: TEST
    public:
      /* The actual transition data */
      unsigned int input_number;
      unsigned int output_number;
      WeightType weight;

    public:
      void print_transition_data() 
      {
    fprintf(stderr, "%i:%i %f\n", 
        input_number, output_number, weight);
      }

    public:

      /** @brief Create a HfstTropicalTransducerTransitionData with 
          epsilon input and output strings and weight zero. */
    HfstTropicalTransducerTransitionData(): 
      input_number(0), output_number(0), weight(0) {}
      
      /** @brief Create a deep copy of HfstTropicalTransducerTransitionData 
          \a data. */
      HfstTropicalTransducerTransitionData
        (const HfstTropicalTransducerTransitionData &data) {
        input_number = data.input_number;
        output_number = data.output_number;
        weight = data.weight;
      }

      /** @brief Create a HfstTropicalTransducerTransitionData with 
          input symbol \a isymbol, output symbol \a osymbol 
          and weight \a weight. */
      HfstTropicalTransducerTransitionData(SymbolType isymbol,
                       SymbolType osymbol,
                       WeightType weight) {
    if (isymbol == "" || osymbol == "")
      HFST_THROW_MESSAGE
        (EmptyStringException,
         "HfstTropicalTransducerTransitionData"
         "(SymbolType, SymbolType, WeightType)");
    
        input_number = get_number(isymbol);
        output_number = get_number(osymbol);
        this->weight = weight;
      }

      HfstTropicalTransducerTransitionData
        (unsigned int inumber,
         unsigned int onumber,
         WeightType weight) {
        input_number = inumber;
        output_number = onumber;
        this->weight = weight;
      }

      /** @brief Get the input symbol. */
      const SymbolType &get_input_symbol() const {
        return get_symbol(input_number);
      }

      /** @brief Get the output symbol. */
      const SymbolType &get_output_symbol() const {
        return get_symbol(output_number);
      }

      unsigned int get_input_number() const {
        return input_number;
      }

      unsigned int get_output_number() const {
        return output_number;
      }
      
      /** @brief Get the weight. */
      WeightType get_weight() const {
        return weight;
      }

      /* Are these needed? */
      static bool is_epsilon(const SymbolType &symbol) {
        return (symbol.compare("@_EPSILON_SYMBOL_@") == 0);
      }
      static bool is_unknown(const SymbolType &symbol) {
        return (symbol.compare("@_UNKNOWN_SYMBOL_@") == 0);
      }
      static bool is_identity(const SymbolType &symbol) {
        return (symbol.compare("@_IDENTITY_SYMBOL_@") == 0);
      }
      static bool is_valid_symbol(const SymbolType &symbol) {
        if (symbol == "")
          return false;
        return true;
      }

      static SymbolType get_marker(const SymbolTypeSet &sts) {
        (void)sts;
        return SymbolType("@_MARKER_SYMBOL_@");
      }

      /** @brief Whether this transition is less than transition 
          \a another. 
          
          /internal is it too slow if string comparison is used instead?
      */
      bool operator<(const HfstTropicalTransducerTransitionData &another) 
        const {
        if (input_number < another.input_number )
          return true;
        if (input_number > another.input_number)
          return false;
        if (output_number < another.output_number)
          return true;
        if (output_number > another.output_number)
          return false;
        return (weight < another.weight);
      }

      // same as operator< but weight is ignored
      bool less_than_ignore_weight(const HfstTropicalTransducerTransitionData &another) 
        const {
        if (input_number < another.input_number )
          return true;
        if (input_number > another.input_number)
          return false;
        if (output_number < another.output_number)
          return true;
        if (output_number > another.output_number)
          return false;
        return false;
      }
      
      void operator=(const HfstTropicalTransducerTransitionData &another)
        {
          input_number = another.input_number;
          output_number = another.output_number;
          weight = another.weight;
        }
      
      friend class Number2SymbolVectorInitializer;
      friend class Symbol2NumberMapInitializer;

      friend class ComposeIntersectFst;
      friend class ComposeIntersectLexicon;
      friend class ComposeIntersectRule;
      friend class ComposeIntersectRulePair;
      template <class C> friend class HfstTransitionGraph;

    };

    // Initialization of static members in class 
    // HfstTropicalTransducerTransitionData..
    class Number2SymbolVectorInitializer {
    public:
      Number2SymbolVectorInitializer
        (HfstTropicalTransducerTransitionData::Number2SymbolVector &vect) {
        vect.push_back(std::string("@_EPSILON_SYMBOL_@"));
        vect.push_back(std::string("@_UNKNOWN_SYMBOL_@"));
        vect.push_back(std::string("@_IDENTITY_SYMBOL_@"));
      }
    };

    class Symbol2NumberMapInitializer {
    public:
      Symbol2NumberMapInitializer
        (HfstTropicalTransducerTransitionData::Symbol2NumberMap &map) {
        map["@_EPSILON_SYMBOL_@"] = 0;
        map["@_UNKNOWN_SYMBOL_@"] = 1;
        map["@_IDENTITY_SYMBOL_@"] = 2;
      }
    };

  } // namespace implementations

} // namespace hfst
