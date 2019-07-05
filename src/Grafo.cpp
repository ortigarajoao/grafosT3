#include <fstream>
#include <iostream>
#include <limits>
#include <queue>

#include "../include/Grafo.h"

Grafo::Grafo(std::string arquivo){
  std::ifstream _arquivo(arquivo);

  if(_arquivo.is_open()){
    std::string strAux;
    int pos;
    std::getline (_arquivo, strAux);
    if(strAux.compare(0,9, "*vertices") == 0){
      int nVertices = std::stoi(strAux.substr(10));
      if(nVertices){
        _vertices = new std::vector<Vertice*>(nVertices);
        _arestas = new std::unordered_set<std::pair<Vertice*,Vertice*>*>();
        _custo = new std::unordered_map<std::pair<Vertice*,Vertice*>*,double>();
        for(int i = 1; i <= nVertices; i++){
          std::getline(_arquivo, strAux);
          pos = strAux.find_first_of(" ");
          if(pos != std::string::npos){
            (*_vertices)[i] = new Vertice(i,strAux.substr(pos+1));
          } else {
            std::cout << "Erro na formatacao da linha: " << i << std::endl;
          }
        }
        std::getline(_arquivo, strAux);
        if(strAux.compare("*edges") == 0){
          std::getline(_arquivo, strAux);
          while(_arquivo.good()){
            _qtdArestas++;
            pos = strAux.find_first_of(" ");
            int vertice1 = std::stoi(strAux.substr(0,pos));
            int pos2 = strAux.find_first_of(" ",pos+1);
            int vertice2 = std::stoi(strAux.substr(pos+1,pos2-pos-1));
            double peso = std::stod(strAux.substr(pos2+1));
            (*_vertices)[vertice1]->adicionaAresta((*_vertices)[vertice2], peso);
            (*_vertices)[vertice2]->adicionaAresta((*_vertices)[vertice1], peso);
            std::pair<Vertice*,Vertice*>* p = new std::pair<Vertice*,Vertice*>((*_vertices)[vertice1], (*_vertices)[vertice2]);
            std::pair<Vertice*,Vertice*>* p2 = new std::pair<Vertice*,Vertice*>((*_vertices)[vertice2], (*_vertices)[vertice1]);
            _arestas->insert(p);
            _arestas->insert(p2);
            (*_custo)[p] = peso;
            (*_custo)[p2] = peso;
            std::getline(_arquivo, strAux);
          }
        } else if (strAux.compare("*arcs") == 0){
          std::getline(_arquivo, strAux);
          while(_arquivo.good()){
            _qtdArestas++;
            pos = strAux.find_first_of(" ");
            int vertice1 = std::stoi(strAux.substr(0,pos));
            int pos2 = strAux.find_first_of(" ",pos+1);
            int vertice2 = std::stoi(strAux.substr(pos+1,pos2-pos-1));
            double peso = std::stod(strAux.substr(pos2+1));
            (*_vertices)[vertice1]->adicionaAresta((*_vertices)[vertice2], peso);
            std::pair<Vertice*,Vertice*>* p = new std::pair<Vertice*,Vertice*>((*_vertices)[vertice1], (*_vertices)[vertice2]);
            _arestas->insert(p);
            (*_custo)[p] = peso;
            std::getline(_arquivo, strAux);
        }
       } else {
          std::cout << "Erro de formatacao de *edges ou *arcs" << std::endl;
        }
      } else {
          std::cout << "Erro de transformacao de valor numerico da linha: 1" << std::endl;
      }
    } else {
      std::cout << "Erro na formatacao da linha: 1" << std::endl;
    }
  } else {
    std::cout << "Erro ao abir arquivo" << std::endl;
  }
}

Grafo::~Grafo(){
  delete _vertices;
  delete _arestas;
}

int Grafo::qtdVertices(){
  return _vertices->size();
}

int Grafo::qtdArestas(){
  return _qtdArestas;
}

int Grafo::grau(int vertice){
  return (*_vertices)[vertice]->grau();
}

std::string Grafo::rotulo(int vertice){
  return (*_vertices)[vertice]->rotulo();
}

std::unordered_set<Vertice*>* Grafo::adjacentes(int vertice){
  return (*_vertices)[vertice]->adjacentes();
}

bool Grafo::haAresta(int vertice1, int vertice2){
  return (*_vertices)[vertice1]->haAresta((*_vertices)[vertice2]);
}

double Grafo::peso(int vertice1, int vertice2){
  if(this->haAresta(vertice1,vertice2)){
    return (*_vertices)[vertice1]->peso((*_vertices)[vertice2]);
  } else {
    return std::numeric_limits<double>::max();
  }
}

void Grafo::imprimirVertices(){
  for (int i = 1; i <= (*_vertices).size(); i++){
    std::cout << "Vertice: " << (*_vertices)[i]->indice() << ", Rotulo: " << (*_vertices)[i]->rotulo() << '\n';
  }
}

void Grafo::imprimirArestas(int vertice){
  std::unordered_set<Vertice*>* adj = (*_vertices)[vertice]->adjacentes();
  for (auto it = adj->begin(); it != adj->end(); ++it){
    std::cout << (*it)->indice() << ", ";
  }
  std::cout << '\n';
}

Vertice* Grafo::vertice(int v){
  return (*_vertices)[v];
}

std::vector<Vertice*>* Grafo::EdmondsKarp(Vertice* s, Vertice* t){
  std::vector<bool> visitados(_vertices->size(), false);
  std::vector<int> antecessor(_vertices->size(), -1);
  visitados[s->indice()] = true;
  std::queue<Vertice*> q;
  q.push(s);
  while(!q.empty()){
    Vertice* u = q.front();
    q.pop();
    std::unordered_set<Vertice*>* adj = u->adjacentes();
    for(Vertice* v : *adj){
      if(visitados[v->indice()] == false || this->custo(u,v) > 0){
        visitados[v->indice()] = true;
        antecessor[v->indice()] = u->indice();
        if (v == t){
          std::vector<Vertice*>* p = new std::vector<Vertice*>();
          p->push_back(t);
          Vertice* w = t;
          while(w != s){
            w = this->vertice(antecessor[w->indice()]);
            p->push_back(w);
          }
          return p;
        }
        q.push(v);
      }
    }
  }
  return nullptr;
}

std::vector<std::pair<Vertice*,Vertice*>>* Grafo::HopcroftKarp(std::vector<Vertice*>* v1,
                                                              std::vector<Vertice*>* v2,
                                                              std::unordered_set<std::pair<Vertice*,Vertice*>*>* arestas
                                                      ){




  return nullptr;
}

void Grafo::Lawler(){

}

double Grafo::custo(Vertice* v1, Vertice* v2){
  std::pair<Vertice*,Vertice*>* p = new std::pair<Vertice*,Vertice*>(v1,v2);
  return (*_custo)[p];
}
