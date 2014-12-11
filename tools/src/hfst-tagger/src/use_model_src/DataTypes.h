#ifndef HEADER_DataTypes_h
#define HEADER_DataTypes_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_TR1_UNORDERED_MAP
 #include <tr1/unordered_map>
#else
 #include <unordered_map>
#endif

#include <string>
#include <vector>

typedef int State;
typedef int Symbol;
typedef float Weight;

struct TransitionData
{
  Weight weight;
  State  target;
};

#ifdef USE_TR1_UNORDERED_MAP
 typedef std::tr1::unordered_map<std::string,Symbol> Symbol2NumberMap;
#else
 typedef std::unordered_map<std::string,Symbol> Symbol2NumberMap;
#endif

typedef std::vector<std::string>               Number2SymbolMap;

typedef std::vector<Weight> StateFinalWeightMap;

#ifdef USE_TR1_UNORDERED_MAP
 typedef std::tr1::unordered_map<Symbol,TransitionData> Symbol2TransitionDataMap;
#else
 typedef std::unordered_map<Symbol,TransitionData> Symbol2TransitionDataMap;
#endif

typedef std::vector<Symbol2TransitionDataMap>     TransitionMap;

typedef std::pair<size_t,Weight> IdWeightPair;

#ifdef USE_TR1_UNORDERED_MAP
 typedef std::tr1::unordered_map<std::string,IdWeightPair> StringWeightMap;
 typedef std::tr1::unordered_map<std::string,float> ProbabilityMap;
#else
 typedef std::unordered_map<std::string,IdWeightPair> StringWeightMap;
 typedef std::unordered_map<std::string,float> ProbabilityMap;
#endif

#define DEFAULT_SYMBOL "<NONE>"
#define DEFAULT 1

class InvalidState
{};

class InvalidKey
{};

class BrokenLexicalModel
{};

typedef std::pair<std::string,std::string> StringPair;
typedef std::pair<std::string,std::string> SymbolPair;
typedef std::vector<StringPair> StringPairVector;
typedef std::vector<Symbol> SymbolVector;

typedef std::pair<Weight,StringPairVector> WeightedStringPairVector;
typedef std::pair<Weight,SymbolVector> WeightedSymbolVector;

typedef std::pair<Weight,std::string> WeightedString;
typedef std::vector<WeightedString> WeightedStringVector;

#endif // HEADER_DataTypes_h
