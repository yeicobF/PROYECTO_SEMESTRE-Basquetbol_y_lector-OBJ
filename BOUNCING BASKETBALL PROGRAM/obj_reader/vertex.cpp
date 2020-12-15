#include <iostream> // Aún necesitamos esta librería.
#include <armadillo> // Para los fcolvec, frowvec, y demás.
#include "vertex.hpp" //Incluimos la librería con la definición.

using namespace std; //Ponerlo en cada archivo.

/* - En el .cpp es donde pondremos la implementación, el código
que le corresponde.*/


/* Constructor de vértice sin parámetros
	para no tener problemas en clase Edges. */
Vertex::Vertex(){
	x = y = z = 0.0f;

    vertex = {x, y, z};
}
// Constructor de vértice que recibe coordenadas.
Vertex::Vertex(float xi, float yi, float zi){
	x = xi;
	y = yi;
	z = zi;

    vertex = {x, y, z};
}

/* No debo redeclarar que es estático el método.
 https://stackoverflow.com/questions/31305717/member-function-with-static-linkage*/
/* static */Vertex Vertex::saveVertex(vector <string> values){
    float x = stof(values[0]); // std::stof(str); No pongo std por el namespace
    float y = stof(values[1]);
    float z = stof(values[2]);
    return Vertex(x, y, z);
}

// Método que devuelve true si es un vértice geométrico.
bool Vertex::isGeometricVertex(string str){
    return str.substr(0, 2).compare("v ") == 0;
}

// Método para imprimir las coordenadas del vértice.
void Vertex::printVertex(){
	cout<<"\n -> x = "<< x <<", y = "<< y <<", z = "<< z <<endl;
}

void Vertex::setVertex(arma::frowvec _vertex){
	x = _vertex[0];
	y = _vertex[1];
	z = _vertex[2];
	vertex = _vertex;
}

arma::frowvec Vertex::getVertex(){
	return vertex;
}

// Devuelve las coordenadas homogéneas del vértice.
arma::fcolvec Vertex::getHomogeneousCoordinates(){
	arma::fcolvec hom = {{vertex[0]}, {vertex[1]}, {vertex[2]}, {1.0}};
	return hom;

}
