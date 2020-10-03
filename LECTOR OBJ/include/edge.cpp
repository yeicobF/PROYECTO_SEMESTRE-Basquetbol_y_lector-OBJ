#include <iostream>
#include "edge.hpp" // Incluir el archivo en donde definimos la clase.

using namespace std;

// Constructor de aristas con sus vértices correspondientes.
Edge::Edge(){}
Edge::Edge(Vertex va, Vertex vb){
	vi = va;
	vf = vb;
}
void Edge::imprimir(){
	cout<< "\nVertice inicial: ";
	vi.imprimir(); // Para imprimir, llamar el método de los vértices.
	cout<< "\nVertice final: ";
	vf.imprimir();
	cout <<endl;
}
