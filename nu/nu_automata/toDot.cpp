#include "toDot.hpp"
using namespace std;
using namespace automate;

void convert_to_dot(Automate* autom, ostream& output){
  //cout << "begin convert to dot\n";
  output << "digraph {\n";
  for(State & state : autom->states){
    int color = 0;
    if(&state == autom->start){
      color++;
    }
    for(State * endState : autom->endStates){
      if(&state == endState){
        color += 2;
      }
    }
    output << state.id << " [color=";
    switch (color) {
      case 0: output << "black";break;
      case 1: output << "blue";break;
      case 2: output << "red";break;
      case 3: output << "green";break;
    }
    output << "][label=\"";
    output << state.id;
    output << "\"]\n";
  }

  for(State & state : autom->states){
    for(Transition * trans : autom->transitions[&state]){
      output << trans->origine->id << "->" << trans->destination->id <<"[label=\"";
      output << trans->to_string();
      output << "\"]\n";
    }
  }
  output << "}";
}
