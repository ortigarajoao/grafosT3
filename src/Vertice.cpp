#include "../include/Vertice.h"

#include <limits>

Vertice::Vertice(int indice, std::string rotulo){
  _indice = indice;
  _rotulo = rotulo;
}

int Vertice::indice(){
  return _indice;
}

std::string Vertice::rotulo(){
  return _rotulo;
}

int Vertice::grau(){
  return _grau;
}

std::unordered_set<Vertice*>* Vertice::adjacentes(){
  std::unordered_set<Vertice*>* r = new std::unordered_set<Vertice*>();
  for( auto it = _adjacentes.begin(); it != _adjacentes.end(); ++it){
    r->insert(it->first);
  }
  return r;
}

bool Vertice::adicionaAresta(Vertice* v, double peso){
  std::pair<Vertice*,double> p = std::make_pair(v,peso);
  if(_adjacentes.insert(p).second) {
    _grau++;
    return true;
  }
  return false;
}

bool Vertice::haAresta(Vertice* v){
  if(_adjacentes.find(v) != _adjacentes.end()){
    return true;
  } else {
    return false;
  }
}

double Vertice::peso(Vertice* v){
  if(_adjacentes.find(v) != _adjacentes.end()){
    return _adjacentes[v];
  } else {
    return std::numeric_limits<double>::max();
  }
}
