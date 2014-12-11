#ifndef _FLAG_DIACRITICS_H_
#define _FLAG_DIACRITICS_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <utility>

/** @file HfstFlagDiacritics.h
    \brief Class declarations for flag diacritic handling. */

namespace hfst {

enum FdOperator {Pop, Nop, Rop, Dop, Cop, Uop};

typedef unsigned short FdFeature;
typedef short FdValue;

class FdOperation
{
private:
    FdOperator op;
    FdFeature feature;
    FdValue value;
    std::string name;
public:
    FdOperation
      (FdOperator op, FdFeature feat, FdValue val, const std::string& str):
    op(op), feature(feat), value(val), name(str) {}
    
    FdOperator Operator(void) const { return op; }
    FdFeature Feature(void) const { return feature; }
    FdValue Value(void) const { return value; }
    std::string Name(void) const { return name; }
    
    static FdOperator char_to_operator(char c)
        {
            switch (c) {
            case 'P': return Pop;
            case 'N': return Nop;
            case 'R': return Rop;
            case 'D': return Dop;
            case 'C': return Cop;
            case 'U': return Uop;
            default:
                throw;
            }
        }

    static bool is_diacritic(const std::string& diacritic_str);
    static std::string::size_type find_diacritic
      (const std::string& diacritic_str,
       std::string::size_type& length);

    static std::string get_operator(const std::string& diacritic);
    static std::string get_feature(const std::string& diacritic);
    static std::string get_value(const std::string& diacritic);
    static bool has_value(const std::string& diacritic); 
};

template<class T> class FdState;
  
/** \brief A collection of the flag diacritics from a symbol table indexed
    by keys of type \a T
*/
template<class T>
class FdTable
{
private:
    // Used for generating IDs that stand in for feature and value strings
    std::map<std::string, FdFeature> feature_map;
    std::map<std::string, FdValue> value_map;
    
    std::map<T, FdOperation> operations;
    std::map<std::string, T> symbol_map;
public:
    FdTable(): feature_map(), value_map()
        { value_map[std::string()] = 0; } // empty value = neutral
    
    void define_diacritic(T symbol, const std::string& str)
        {
            if(!FdOperation::is_diacritic(str))
                throw;
      
            FdOperator op = FdOperation::char_to_operator(str.at(1));
            std::string feat;
            std::string val;
      
            // Third character is always the first fullstop.
            size_t first_full_stop_pos = 2;
            // Find the second full stop, if there is one.
            size_t second_full_stop_pos = str.find('.',first_full_stop_pos+1);
            size_t last_char_pos = str.size() - 1;
            if(second_full_stop_pos == std::string::npos)
            {
                assert(op == Cop || op == Dop || op == Rop);
                feat = str.substr(first_full_stop_pos+1, 
                                  last_char_pos-first_full_stop_pos-1);
            }
            else
            {
                feat = str.substr(first_full_stop_pos+1, 
                                  second_full_stop_pos-first_full_stop_pos-1);
                val = str.substr(second_full_stop_pos+1, 
                                 last_char_pos-second_full_stop_pos-1);
            }
      
            if(feature_map.count(feat) == 0)
            {
                FdFeature next = feature_map.size();
                feature_map[feat] = next;
            }
            if(value_map.count(val) == 0)
            {
                FdValue next = value_map.size()+1;
                value_map[val] = next;
            }
      
            operations.insert
              (std::pair<T,FdOperation>
               (symbol, 
                FdOperation(op, feature_map[feat], value_map[val], str)));
            symbol_map.insert(std::pair<std::string,T>(str, symbol));
        }
    
    FdFeature num_features() const { return feature_map.size(); }
    bool is_diacritic(T symbol) const
        { return operations.find(symbol) != operations.end(); }
      
    const FdOperation* get_operation(T symbol) const
        {
          // for some reason this fails to compile???
          //std::map<T,FdOperation>::const_iterator i 
          //  = operations.find(symbol);
          //return (i==operations.end()) ? NULL : &(i->second);
        
          return (operations.find(symbol)==operations.end()) ? NULL : 
            &(operations.find(symbol)->second);
        }
    const FdOperation* get_operation(const std::string& symbol) const
        {
            return (symbol_map.find(symbol)==symbol_map.end()) ? NULL : 
              get_operation(symbol_map.find(symbol)->second);
        }
    
    bool is_valid_string(const std::vector<T>& symbols) const
        {
            FdState<T> state(*this);
      
            for(size_t i=0; i<symbols.size(); i++)
            {
                if(!state.apply_operation(symbols[i]))
                    break;
            }
            return !state.fails();
        }
    
    bool is_valid_string(const std::string& str) const
        {
            FdState<T> state(*this);
            std::string remaining(str);
            std::string::size_type length;
      
            while(true)
            {
                std::string::size_type next_diacritic_pos 
                  = FdOperation::find_diacritic(remaining, length);
                if(next_diacritic_pos == std::string::npos) // fixed
                    break;
        
                std::string diacritic = remaining.substr(0, length);
                if(!state.apply_operation(diacritic))
                    break;
                remaining = remaining.substr(length);
            }
            return !state.fails();
        }
};

/** \brief Contains the values of each of the flag diacritic features from a
    table. It allows for evaluating a series of diacritic operations
*/
template<class T>
class FdState
{
private:
    const FdTable<T>* table;
    
    // This is indexed with values of type FdFeature
    typename std::vector<FdValue> values;
    T num_features;
    
    bool error_flag;
public:
    FdState(const FdTable<T>& t):
    table(&t), values(table->num_features()),
    num_features(table->num_features()), error_flag(false)
        {}

    FdState():
    table(NULL), values(), num_features(0), error_flag(false)
    {}

    const FdTable<T>& get_table() const {return *table;}

    const std::vector<FdValue> & get_values(void) const
    { return values; }

    void assign_values(std::vector<FdValue> const & vals)
    {
        values = vals;
        if (values.size() != num_features) {
            error_flag = true;
        }
    }

    bool apply_operation(T symbol)
        {
            const FdOperation* op = table->get_operation(symbol);
            if(op)
                return apply_operation(*op);
            return true; // if the symbol isn't a diacritic
        }    
    bool apply_operation(const FdOperation& op)
        {
            switch(op.Operator()) {
            case Pop: // positive set
                values[op.Feature()] = op.Value();
                return true;
          
            case Nop: // negative set (literally, in this implementation)
                values[op.Feature()] = -1*op.Value();
                return true;
          
            case Rop: // require
                if (op.Value() == 0) // empty require
                    return (values[op.Feature()] != 0);
                else // nonempty require
                    return (values[op.Feature()] == op.Value());
            
            case Dop: // disallow
                if (op.Value() == 0) // empty disallow
                    return (values[op.Feature()] == 0);
                else // nonempty disallow
                    return (values[op.Feature()] != op.Value());
            
            case Cop: // clear
                values[op.Feature()] = 0;
                return true;
          
            case Uop: // unification
              if(values[op.Feature()] == 0 || /* if the feature is unset or */
                 values[op.Feature()] == op.Value() || /* the feature is at 
                                                          this value already 
                                                          or */
                 (values[op.Feature()] < 0 &&
                  (values[op.Feature()]*(-1) != op.Value())) /* the feature is 
                                                              negatively set 
                                                              to something 
                                                              else */
                 )
                {
                    values[op.Feature()] = op.Value();
                    return true;
                }
                return false;
            }
            throw; // for the compiler's peace of mind
        }
    bool apply_operation(const std::string& symbol)
        {
            const FdOperation* op = table->get_operation(symbol);
            if(op)
                return apply_operation(*op);
            return true;
        }
    
    bool fails() const {return error_flag;}
    void reset()
        {
            error_flag = false;
            values.clear();
            values.insert(values.begin(), table->num_features(), 0);
        }
};

}
#endif
