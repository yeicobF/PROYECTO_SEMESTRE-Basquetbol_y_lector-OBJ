#include "face.hpp"
#include <iostream>
//#include <vector>

using namespace std;

/* Clase que representa las caras o Faces.*/
// Constructor que recibe una lista como parámetro.
Face::Face(vector <Edge> edge_list){
    // Como el this.atributo en Java.
    this -> edge_list = edge_list;
}
// Método que imprime las carcas con sus aristas y vértices.
void Face::imprimir(){
    for(int i = 0; i < edge_list.size(); i++){
    	cout << "\n -> Arista: " << i+1 <<endl;
    	edge_list[i].imprimir(); // Utilizando el método de clase Edge
	}
}
