#ifndef __AUTOMATE_RECOGNIZER__
#define __AUTOMATE_RECOGNIZER__

#include "../hybride_automata/grammar.hpp"

using namespace std;
using namespace automate;

namespace recognizer{
  class Token{
  public:
    DBM initial_values;
    DBM current_values;
    DBM final_values;
    vector<pair<bool,unordered_set<string>>> variables;

  //--------------------------------------------------------------------------//
  //---------------------------Constructor------------------------------------//
  //--------------------------------------------------------------------------//
    Token(Automate* automate);
    Token(Token const& token);
    Token(DBM initial_v,DBM current_v,DBM final_v,
          vector<pair<bool,unordered_set<string>>> & memory);
    Token(DBM clocks_v,
          vector<pair<bool,unordered_set<string>>> & memory);
    ~Token();

  //--------------------------------------------------------------------------//
  //--------------------------------Methods-----------------------------------//
  //--------------------------------------------------------------------------//
    bool operator<=(Token const& tok2) const;
    void increment(double time_elapse);

    static bool included(Token const& tok, list<Token> const& list){
      for(Token const& elmt : list){
        if(tok <= elmt){
          return true;
        }
      }
      return false;
    }

    static Token validate(Token tok){
      tok.validate;
      return tok;
    }
    
    string to_string() const;
  };

  class Checker{
  public:
    Automate* modele;
    map<State*,list<Token>> map_tokens;
    Checker(Automate* modele_automate);
    ~Checker();

    bool check();

    void propagate(bool incremented);
    void input(double time_elapse);
    void input(string event);

    void print_state(string str);
  };
}

#endif
