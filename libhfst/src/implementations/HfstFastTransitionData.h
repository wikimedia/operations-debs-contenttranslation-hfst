
namespace hfst {

  namespace implementations {

    /** @brief One implementation of template class C in HfstTransition. 

        An HfstFastTransitionData has an input number and an output number
    of type SymbolType (an unsigned int) and a weight of type WeightType 
    (a float).
    */

    class HfstFastTransitionData {
    public:
      /** @brief The input and output symbol type. */
      typedef unsigned int SymbolType;
      /** @brief The weight type. */
      typedef float WeightType;
      /** @brief A set of symbols. */
      typedef std::set<SymbolType> SymbolTypeSet;

    private:
      /* The actual transition data */
      SymbolType input_number;
      SymbolType output_number;
      WeightType weight;

    public:
      
      /** @brief Create an HfstFastTransitionData with 
      input and output numbers and weight zero. */
    HfstFastTransitionData(): 
      input_number(0), output_number(0), weight(0) {}
      
      /** @brief Create a deep copy of HfstFastTransitionData 
          \a data. */
      HfstFastTransitionData
        (const HfstFastTransitionData &data) {
        input_number = data.input_number;
        output_number = data.output_number;
        weight = data.weight;
      }

      /** @brief Create an HfstFastTransitionData with 
          input number \a inumber, output number \a onumber 
          and weight \a weight. */
      HfstFastTransitionData(SymbolType inumber,
                 SymbolType onumber,
                 WeightType weight) {
        input_number = inumber;
        output_number = onumber;
        this->weight = weight;
      }

      /** @brief Get the input symbol. */
      SymbolType get_input_symbol() const {
        return input_number;
      }

      /** @brief Get the output symbol. */
      SymbolType get_output_symbol() const {
        return output_number;
      }

      /** @brief Get the weight. */
      WeightType get_weight() const {
        return weight;
      }

      static SymbolType get_epsilon()
      {
    return 0;
      }

      static SymbolType get_unknown()
      {
    return 1;
      }

      static SymbolType get_identity()
      {
    return 2;
      }

      /* Are these needed? */
      static bool is_epsilon(const SymbolType &s) {
    return s == 0;
      }
      static bool is_unknown(const SymbolType &s) {
    return s == 1;
      }
      static bool is_identity(const SymbolType &s) {
    return s == 2;
      }
      static bool is_valid_symbol(const SymbolType &s) {
    (void)s;
    return true;
      }

      /* Get a marker symbol. Equivalent to (biggest number in sts + 1). */
      static SymbolType get_marker(const SymbolTypeSet &sts) {
    SymbolType marker=0;
    for (SymbolTypeSet::const_iterator it = sts.begin();
         it != sts.end(); it++) {
      if (marker < *it) {
        marker = *it;
      }
    }
    return marker++;
      }

      /** @brief Whether this transition is less than transition 
          \a another. 
      */
      bool operator<(const HfstFastTransitionData &another) 
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

      void operator=(const HfstFastTransitionData &another)
    {
      input_number = another.input_number;
      output_number = another.output_number;
      weight = another.weight;
    }

      friend class ComposeIntersectFst;
      friend class ComposeIntersectLexicon;
      friend class ComposeIntersectRule;
      friend class ComposeIntersectRulePair;
      
    };


    /*    std::ostream& operator<<(std::ostream &out, 
                 const HfstFastTransitionData &tr)
      {
    return out << tr.get_input_symbol() << '\t' 
           << tr.get_output_symbol() << '\t' 
           << tr.get_weight();
           }*/

  } // namespace implementations

} // namespace hfst



