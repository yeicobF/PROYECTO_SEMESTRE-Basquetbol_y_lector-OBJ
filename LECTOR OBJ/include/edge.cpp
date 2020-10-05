#include <iostream>
#include "edge.hpp" // Incluir el archivo en donde definimos la clase.

using namespace std;

// Constructor de aristas con sus vértices correspondientes.
Edge::Edge(){}
Edge::Edge(Vertex va, Vertex vb){
	vi = va;
	vf = vb;
}

/* static */ Edge Edge::saveEdge(vector <Vertex> v_list, vector <string> values, int actualIndex){
    Edge e;
    /* Values guarda los índices de los vértices, entonces son esos a los
        que hay que meter los valores, por eso su índice es:
            stoi(values[indiceActual])*/
    // Si se llegó al índice máximo hacer arista con primer vértice.
    if(actualIndex == (values.size() - 1))
        e = Edge(v_list[stoi(values[actualIndex])], v_list[stoi(values[0])]);
    else // Si está dentro del límite, asignar con siguiente vértice.
        e = Edge(v_list[stoi(values[actualIndex])], v_list[stoi(values[actualIndex]) + 1]);
    return e;
}

void Edge::imprimir(){
	cout<< "\nVertice inicial: ";
	vi.imprimir(); // Para imprimir, llamar el método de los vértices.
	cout<< "\nVertice final: ";
	vf.imprimir();
	cout <<endl;
}
