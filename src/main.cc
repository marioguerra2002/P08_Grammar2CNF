/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Gramática en forma normal de Chomsky
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 22/11/2022
/// Archivo main.cc
/// Contiene el main del programa 
/// Referencias:
/// Enlaces de interés
#include "grammar.h"
#include <string.h>
#include <fstream>
#include <iostream>
/// @brief contiene el main del programa
/// @param argc es el número de argumentos
/// @param argv es el array de argumentos
/// @return 
int main(int argc, char* argv[]) {
  if (strcmp(argv[1], "--help") == 0) {
    std::cout << "Este programa lee un fichero de texto con una gramática" << std::endl;
    std::cout << "y lo transforma en una gramatica en forma normal de Chomsky" << std::endl;
    std::cout << "El programa se ejecuta de la siguiente manera:" << std::endl;
    std::cout << "./P08_Grammar2CNF fichero_entrada fichero_salida" << std::endl;
    return 0;
  } else if (argc != 3) {
    std::cout << "Modo de empleo: ./P08_Grammar2CNF input.gra output.gra" << std::endl;
    std::cout << "Pruebe ./P08_Grammar2CNF --help para más información." << std::endl;
    return 1;
  }
  std::ifstream grammarin(argv[1]);
  std::ofstream grammarout(argv[2]);
  std::string line;
  std::vector<std::string> vect_auxiliar;
  while (std::getline(grammarin, line)) {
    vect_auxiliar.push_back(line);  /// meto cada línea del fichero en un vector
  }
  Grammar grammar(vect_auxiliar);
  grammarout << grammar.ChomskyNormalForm().str();
}