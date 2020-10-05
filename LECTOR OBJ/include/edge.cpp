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

/* static */ Edge Edge::saveEdge(vector <Vertex> v_list, vector <string> values, unsigned int actualIndex){
    Edge e;
    // cout << "\n - EDGE VERTICES: " << endl;
    // for(int i = 0; i < values.size(); i++)
    //     cout << values[i] << ", " << values[i].substr(0, 1) << endl;
    /* Values guarda los índices de los vértices, entonces son esos a los
        que hay que meter los valores, por eso su índice es:
            stoi(values[indiceActual])*/
    // Si se llegó al índice máximo hacer arista con primer vértice.
    //cout << values[actualIndex].substr(0, 1) << stoi(values[actualIndex].substr(0, 1));
    int indexV1 = stoi(values[actualIndex].substr(0, 1)) - 1, indexV2 = 0;
    if(actualIndex == (values.size() - 1)){
        // indexV1 ++;
        // Como llegamos al último valor, relacionar con el primer vértice.
        indexV2 = stoi(values[0].substr(0, 1)) - 1;
        e = Edge(v_list[indexV1], v_list[indexV2]);
    }
    else{ // Si está dentro del límite, asignar con siguiente vértice.
        indexV2 = stoi(values[actualIndex + 1].substr(0, 1)) - 1;
        e = Edge(v_list[indexV1], v_list[indexV2]);
    }
    indexV1 ++;
    indexV2 ++;
    e.setVertexNums(indexV1, indexV2);
    return e;
}

void Edge::printEdge(){
    cout << "\n - VÉRTICES: " << vertex_nums[0] << ", " << vertex_nums[1] << endl;
	cout<< "\nVertice inicial: ";
	vi.printVertex(); // Para imprimir, llamar el método de los vértices.
	cout<< "\nVertice final: ";
	vf.printVertex();
	cout <<endl;
}

void Edge::setVertexNums(int v1, int v2){
    // cout << "\n Entró a setNums(), " << v1 << ", " << v2 << endl;
    vertex_nums.push_back(v1);
    vertex_nums.push_back(v2);
}
