#ifndef VERTICE_H
#define VERTICE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class Vertice{

private:
  int _indice;
  std::string _rotulo;
  int _grau; //diminuir buscas
  std::unordered_map<Vertice*,double> _adjacentes;
  //std::unordered_map<int,Vertice> _antecessores; //maybe map
  //std::unordered_map<int,Vertice> _sucessores;  //maybe map

public:
  Vertice();
  ~Vertice() { }
  Vertice(int indice, std::string rotulo);

  int indice();
  std::string rotulo();
  int grau();
  std::unordered_set<Vertice*>* adjacentes();
  bool adicionaAresta(Vertice* v, double peso);
  bool haAresta(Vertice* v);
  double peso(Vertice* v);
  //std::unordered_map<int,Vertice> antecessores();
  //std::unordered_map<int,Vertice> sucessores();
};

#endif //VERTICE_H
