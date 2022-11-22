/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Gramática en forma normal de Chomsky
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 22/11/2022
/// Archivo alphabet.h
/// Contiene la declaracion de la clase alphabet
/// Referencias:
/// Enlaces de interés
#ifndef ALPHABET_H_
#define ALPHABET_H_
#include "symbol.h"
#include <vector>
#include <set>

class Alphabet {
  public:
    Alphabet (std::vector<std::string>);
    Alphabet () {};
    std::set<Symbol> GetSet(void);
    bool CheckAlphabet(std::set<Symbol>);
  private:
    std::set<Symbol> alphabet_;
};
#endif /// ALPHABET_H_