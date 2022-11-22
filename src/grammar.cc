/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Gramática en forma normal de Chomsky
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 22/11/2022
/// Archivo grammar.cc
/// Contiene las definiciones de los metodos de la clase grammar
/// Referencias:
/// Enlaces de interés
#include "grammar.h"
Symbol kInitialState_ = Symbol("S");
std::string kInitialString_ = "S";
/// @brief constructor de la clase grammar
/// @param dfa_ automata finito determinista
Grammar::Grammar(std::vector<std::string> input) {
  std::vector<std::string> auxiliar_vect;
  int number_of_terminal{std::stoi(input[0])}; /// numero de terminales
  input.erase(input.begin()); /// borramos el numero de terminales
  for (int i{0}; i < number_of_terminal; ++i) {
    terminals_.insert(Symbol(input[i]));
    auxiliar_vect.push_back(input[i]); /// guardamos los terminales en un vector auxiliar para meterlos en el alfabeto
  }
  input.erase(input.begin(), input.begin() + number_of_terminal); /// borramos los terminales
  alphabet_ = Alphabet(auxiliar_vect); /// creamos el alfabeto
  for (auto& i : auxiliar_vect) {
    terminals_.insert(Symbol(i));
  }
  /// aqui ya tenemos los terminales
  auxiliar_vect.clear(); /// vaciamos el vector auxiliar (no creo que sea necesario, pero por si acaso)
  int number_of_nonterminal{std::stoi(input[0])}; /// numero de no terminales
  input.erase(input.begin()); /// borramos el numero de no terminales
  for (int i{0}; i < number_of_nonterminal; ++i) {
    nonterminals_.insert(Symbol(input[i])); /// insertamos los no terminales
  }
  input.erase(input.begin(), input.begin() + number_of_nonterminal); /// borramos los no terminales
  /// aqui ya tenemos los no terminales
  input.erase(input.begin()); /// borramos el numero de reglas
  std::vector<std::vector<Symbol>> each_productions;
  std::vector<Symbol> auxiliar;
  std::string auxiliar_string;
  Symbol initial_symbol;
  int number_of_productions_repeted;
  while (!input.empty()) {
    number_of_productions_repeted = NumberProductionSameLeftSide(input);
    auxiliar_string += input[0][0]; /// guardamos el simbolo inicial de la regla
    initial_symbol = Symbol(auxiliar_string);
    auxiliar_string = "";
    for (int i{0}; i < number_of_productions_repeted; ++i) {
      for (unsigned long int j{5}; j < input[i].size(); j++) {
        if (input[i][j] != kSpace) {
          auxiliar_string += input[i][j];
        }
        auxiliar.push_back(Symbol(auxiliar_string));
        auxiliar_string = "";
      }
      each_productions.push_back(auxiliar);
      auxiliar.clear();
    }
    productions_.insert(std::pair<Symbol, std::vector<std::vector<Symbol>>>(initial_symbol, each_productions));
    for (int i{0}; i < number_of_productions_repeted; ++i) {
      input.erase(input.begin());  /// borramos la regla
    }
    each_productions.clear();
  }
}
/// @brief Calcula el numero de producciones que tienen el mismo lado izquierdo (producciones del mismo simbolo)
/// @param input 
/// @return entero con el numero de producciones con el mismo lado izquierdo
int Grammar::NumberProductionSameLeftSide(std::vector<std::string> input) {
  int number_production_same_symbol{1};
  for (unsigned long int i{0}; i < input.size(); ++i) {
    /// evitar oveerflow
    if (i + 1 < input.size()) {
      if (input[i][0] == input[i + 1][0]) {
        number_production_same_symbol++;
      } else {
        return number_production_same_symbol;
      }
    }
  }
  return number_production_same_symbol;
} 
/// @brief comprueba que no tiene producciones vacias y que no tiene producciones unitarias
/// @return bool 
bool Grammar::CheckGrammar() {
  for (auto& i : productions_) {
    for (auto& j : i.second) {
      if (j.size() == 1) {
        /// si tiene producciones vacias y no es la inicial
        if (j[0].GetSymbol() == kEpsilon && i.first.GetSymbol() != kInitialString_) { 
          return false;
        }
      }
    }
  }
  for (auto& i : productions_) {
    for (auto& j : i.second) {
      if (j.size() == 1) {
        /// si tiene producciones unitarias
        if (j[0].GetSymbol() != kEpsilon && nonterminals_.find(j[0]) != nonterminals_.end()) {
          return false;
        }
      }
    }
  }
  return true;
}

std::stringstream Grammar::ChomskyNormalForm() {
  std::stringstream output;
  std::vector<std::vector<Symbol>> total_productions;
  std::vector<Symbol> auxiliar;
  if (!CheckGrammar()) {
    output << "La gramatica no es correcta" << std::endl;
    output << "Asegurate de que no tenga producciones vacias y " << std::endl;
    output << "que no tenga producciones unitarias" << std::endl;
    std::cout << "La gramatica no es correcta" << std::endl;
    std::cout << "Asegurate de que no tenga producciones vacias y" << std::endl;
    std::cout << "que no tenga producciones unitarias" << std::endl;
    return output;
  } else {
    int counter_non_terminals{0};
    for (auto& i : productions_) {
      /// recorremos las producciones
      for (auto& j : i.second) {  
        if (j.size() >= 2) {
          int counter{0};
          /// recorremos los símbolos de cada producción de la regla
          for (auto& k : j) {
            /// si es terminal
            if (terminals_.find(k) != terminals_.end()) {
              /// añadimos el terminal a la produccion auxiliar
              auxiliar.push_back(k);
              /// borramos el terminal. Counter es la posicion del terminal
              j.erase(j.begin() + counter);
              std::string new_non_terminal;
              
              if (counter_non_terminals >= 25) {
                /// si ya hemos usado todas las letras del abecedario, volvemos a empezar
                counter_non_terminals = 0;
                new_non_terminal = ('A' + counter_non_terminals);
                new_non_terminal += "'";
              }
              /// creamos un nuevo no terminal
              new_non_terminal = ('A' + counter_non_terminals);
              /// si no existe el no terminal
              if (nonterminals_.find(Symbol(new_non_terminal)) == nonterminals_.end()) {
                /// lo añadimos al conjunto de no terminales
                nonterminals_.insert(Symbol(new_non_terminal));
              } else {
                counter_non_terminals++;
                new_non_terminal = ('A' + counter_non_terminals);
                nonterminals_.insert(Symbol(new_non_terminal));
              }
              /// insertamos el nuevo no terminal en la posicion del terminal
              j.insert(j.begin() + counter, Symbol(new_non_terminal));
              /// añadimos la produccion auxiliar a las producciones totales
              total_productions.push_back(auxiliar);
              /// añadimos la nueva regla
              productions_.insert(std::pair<Symbol, std::vector<std::vector<Symbol>>>(Symbol(new_non_terminal), total_productions));
              auxiliar.clear();
              total_productions.clear();
              counter_non_terminals++;
              ++counter;
            } else { /// en caso de que no sea terminal, solo aumentamos el contador (seguimos recorriendo la produccion)
              ++counter;
            }
          }
        }
      }
    }
    while (CheckProductionRules(productions_) == false) {
      for (auto& i : productions_) {
        /// recorremos las producciones
        for (auto& j : i.second) { 
          if (j.size() >= 3) {
            unsigned long int counter{0};
            /// recorremos las producciones
            for (auto& k : j) { 
              if (j.size() >= 3) {
                /// si es no terminal
                if (nonterminals_.find(k) != nonterminals_.end()) { 
                  for (unsigned long int l{counter}; l < j.size(); ++l) {
                    if (l + 1 < j.size()) {
                      /// añadimos el terminal a la produccion auxiliar
                      auxiliar.push_back(j[l + 1]); 
                    }
                  };
                  for (unsigned long int l{counter}; l <= j.size(); ++l) {
                    /// borramos no terminales de la producción. Counter es la posicion del terminal
                    j.pop_back(); 
                  }
                  std::string new_non_terminal;
                  if (counter_non_terminals >= 25) {
                    counter_non_terminals = 0;
                    new_non_terminal = ('A' + counter_non_terminals);
                    new_non_terminal += "'";
                  }
                  new_non_terminal = ('A' + counter_non_terminals);
                  if (nonterminals_.find(Symbol(new_non_terminal)) == nonterminals_.end()) {
                    nonterminals_.insert(Symbol(new_non_terminal));
                  } else {
                    counter_non_terminals++;
                    new_non_terminal = ('A' + counter_non_terminals);
                    nonterminals_.insert(Symbol(new_non_terminal));
                  }
                  /// insertamos el nuevo no terminal
                  j.push_back(Symbol(new_non_terminal));
                  /// añadimos la produccion auxiliar a las producciones totales
                  total_productions.push_back(auxiliar);
                  /// añadimos la nueva regla
                  productions_.insert(std::pair<Symbol, std::vector<std::vector<Symbol>>>(Symbol(new_non_terminal), total_productions)); 
                  total_productions.clear();
                  auxiliar.clear();
                } else {  /// en caso de que sea terminal, solo aumentamos el contador (seguimos recorriendo la produccion)
                  ++counter;
                }
              }
            }
          }
        }
      }
    }
  }
  output << "S -> ";
  /// recorro el vector de producciones de la regla S
  for (unsigned long int i{0}; i < productions_[Symbol("S")].size(); ++i) {  
    /// recorro el vector de símbolos de cada producción
    for (unsigned long int j{0}; j < productions_[Symbol("S")][i].size(); ++j) {
      output << productions_[Symbol("S")][i][j].GetSymbol();
    }
    if (i + 1 < productions_[Symbol("S")].size()) {
      output << " | ";
    } 
  }
  output << std::endl;
  for (auto& i : productions_) {
    if (i.first.GetSymbol() != "S") {
      output << i.first.GetSymbol() << " -> ";
      for (unsigned long int j{0}; j < i.second.size(); ++j) {
        for (unsigned long int k{0}; k < i.second[j].size(); ++k) {
          output << i.second[j][k].GetSymbol();
        }
        if (j + 1 < i.second.size()) {
          output << " | ";
        }
      }
      output << std::endl;
    }
  }
  return output;
}

std::map<Symbol, std::vector<std::vector<Symbol>>> Grammar::GetProductionRules() {
  return productions_;
}
/// @brief comprobar si todas las producciones tienen menos de 3 símbolos
/// @return bool
bool Grammar::CheckProductionRules(std::map<Symbol, std::vector<std::vector<Symbol>>> productions) {
  for (auto& i : productions) {
    for (auto& j : i.second) {
      if (j.size() >= 3) {
        return false;
      }
    }
  }
  return true;
}