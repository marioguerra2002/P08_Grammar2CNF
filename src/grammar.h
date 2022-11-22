/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Gramática en forma normal de Chomsky
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 22/11/2022
/// Archivo grammar.h
/// Contiene la declaracion de la clase grammar
/// Referencias:
/// Enlaces de interés
#ifndef GRAMMAR_H_
#define GRAMMAR_H_
#include "alphabet.h"
#include "state.h"
#include <sstream>
#include <fstream>
#include <map>
class Grammar {
  public:
    Grammar (std::vector<std::string>);
    int NumberProductionSameLeftSide(std::vector<std::string>);
    bool CheckGrammar();
    std::stringstream ChomskyNormalForm();
    std::map<Symbol, std::vector<std::vector<Symbol>>> GetProductionRules();
    bool CheckProductionRules(std::map<Symbol, std::vector<std::vector<Symbol>>>);
    /// std::map<Symbol, Symbol> SetNewStatesNames (NFA);
    /// std::set<Symbol> GetAcceptedStates (NFA);
    /// std::stringstream OutputGrammar (void);
    /// std::stringstream OutputGrammarScreen (void);
    /// int GetNumberProductions (void);
  private:
    std::set<Symbol> terminals_;
    Alphabet alphabet_;
    std::set<Symbol> nonterminals_;
    /// Mapa que relaciona los nombres antiguos de estados con nuevos alfabeticos
    std::map<Symbol, Symbol> new_names_states_; 
    std::map<Symbol, std::vector<std::vector<Symbol>>> productions_; /// esto ya no puede ser pair, sino simplemente un vector de simbolos
    std::set<Symbol> accepted_states_;
    int number_productions_{0};
};
#endif /// GRAMMAR_H_