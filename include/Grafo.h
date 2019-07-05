#ifndef GRAFO_H
#define GRAFO_H

#include "../include/Vertice.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

class Grafo{

public:
  Grafo();
  ~Grafo();
  Grafo(std::string arquivo);
  bool ler(std::string arquivo);

  int qtdVertices();
  int qtdArestas();
  int grau(int vertice);
  std::string rotulo(int vertice);
  std::unordered_set<Vertice*>* adjacentes(int vertice);
  bool haAresta(int vertice1, int vertice2);
  double peso(int vertice1, int vertice2);
  void imprimirVertices();
  void imprimirArestas(int vertice);
  Vertice* vertice(int v);

  std::vector<Vertice*>* EdmondsKarp(Vertice* s, Vertice* t);
  std::vector<std::pair<Vertice*,Vertice*>>* HopcroftKarp(std::vector<Vertice*>* v1,
                                                          std::vector<Vertice*>* v2,
                                                          std::unordered_set<std::pair<Vertice*,Vertice*>*>* arestas
                                                        );

  void Lawler();


 double custo(Vertice* v1, Vertice* v2);


private:
  std::vector<Vertice*>* _vertices;
  std::unordered_set<std::pair<Vertice*,Vertice*>*>* _arestas;
  std::unordered_map<std::pair<Vertice*,Vertice*>*,double>* _custo;
  int _qtdArestas = 0; //Para diminuir procuras

};

#endif //GRAFO_H
