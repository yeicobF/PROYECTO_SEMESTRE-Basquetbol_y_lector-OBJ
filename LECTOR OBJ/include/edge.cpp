#include <iostream>
#include <string>
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
    // cout << "\n - EDGE VERTICES: " << endl;
    for(int i = 0; i < values.size(); i++)
        cout << values[i] << ", " << values[i].substr(0, 1) << endl;
    /* Values guarda los índices de los vértices, entonces son esos a los
        que hay que meter los valores, por eso su índice es:
            stoi(values[indiceActual])*/
    // Si se llegó al índice máximo hacer arista con primer vértice.
    //cout << values[actualIndex].substr(0, 1) << stoi(values[actualIndex].substr(0, 1));
    int index1 = stoi(values[actualIndex].substr(0, 1)), index2;
    if(actualIndex == (values.size() - 1)){
        index2 = stoi(values[0].substr(0, 1));
        e = Edge(v_list[index1], v_list[index2]);
    }
    else{ // Si está dentro del límite, asignar con siguiente vértice.
        index2 = stoi(values[actualIndex].substr(0, 1)) + 1;
        e = Edge(v_list[index1], v_list[index2]);
    }
    return e;
}

void Edge::printEdge(){
	cout<< "\nVertice inicial: ";
	vi.printVertex(); // Para imprimir, llamar el método de los vértices.
	cout<< "\nVertice final: ";
	vf.printVertex();
	cout <<endl;
}
