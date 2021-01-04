#include "face.hpp"
#include <iostream>

using namespace std;

/* Clase que representa las caras o Faces.*/
// Constructor que recibe una lista como parámetro.
Face::Face(vector <Edge> _edge_list){
    // Como el this.atributo en Java.
    edge_list = _edge_list;
}

// Método que devuelve true si encuentra la "f" de cara.
/* static */bool Face::isFace(string str){
    return str.substr(0, 1).compare("f") == 0;
}

// Devuelve vector de Edges de la cara.
vector <Edge> Face::getFaceEdges(){
    return edge_list;
}

// Método que imprime las carcas con sus aristas y vértices.
void Face::printFace(){
    cout << "\n -> NÚMERO de ARISTAS en esta cara: " << edge_list.size() << endl;
    for(int i = 0; i < edge_list.size(); i++){
    	cout << "\n\t -> ARISTA: " << i + 1 << endl;
    	edge_list[i].printEdge(); // Utilizando el método de clase Edge
	}
}
