#include <string>
#include <iostream>
#include <fstream>
#include "../time_automata/toDot.hpp"
#include "../time_automata/grammar.hpp"
#include "parsingDriver.hpp"

using namespace std;
using namespace automate;

int main(int argc, char *argv[]){
  if(argc < 2){
    cout << "Nombre d'argument incorrecte : <fichier .regex> <sortie .dot>\n";
  }
  regex_driver parser;
  automate::Automate*input_autom = nullptr;
  int res = parser.parse (&input_autom, argv[1]);
  if(res != 0){
    if(input_autom != nullptr){
      delete input_autom;
    }
    return 1;
  }

  cout << "Value returned by parse : " << res <<"\n";
  cout << "Number of state : " << input_autom->states.size() << "\nStates names : \n";
  for(automate::State st : input_autom->states){
    cout << "\t" << st.id << "\n";
  }
  cout << "clocks names : \n";
  for(automate::Clock * cl : input_autom->clocks)
    cout << "\t"<< cl->name << " : " << cl->getId() << "\n";
  cout << "List of edges : " << input_autom->transitions.size() << "\n";
  for(automate::State & st : input_autom->states){
    for(automate::Transition & trans : input_autom->transitions[&st]){
      cout << "\t" << trans.origine->id << "->" << trans.destination->id << "\n";
      cout << "\t\tThe clocks_constraints DBM :" <<"\n";
      for(int i=0; i<trans.clocks_constraints.length;i++){
        cout << "\t\t\t";
        for(int j=0; j<trans.clocks_constraints.length;j++){
          double value = trans.clocks_constraints.matrice[i][j].value;
          cout << "(";
          if(value == numeric_limits<double>::max())
            cout<< "inf";
          else
            cout << value;
          cout << "," << trans.clocks_constraints.matrice[i][j].inclusion <<")";
          cout << "\t";
        }
        cout << "\n";
      }
      cout << "\t\t" << "Clocks to reset : ";
      for(Clock* clk : trans.clocks_to_reset){
        cout  << clk->name <<" ";
      }
      cout << "\n";
    }
  }

 if(argc >=3){
   ofstream output(argv[2]);
   cout << "Fichier .dot : " << argv[2] << "\n";
   convert_to_dot(input_autom,output);
   output.close();
 }


  delete (input_autom);
  return 0;
}
