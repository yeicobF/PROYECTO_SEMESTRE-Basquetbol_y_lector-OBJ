#include <iostream> // Aún necesitamos esta librería.
#include "vertex.hpp" //Incluimos la librería con la definición.

using namespace std; //Ponerlo en cada archivo.

/* - En el .cpp es donde pondremos la implementación, el código
que le corresponde.*/


/* Constructor de vértice sin parámetros
	para no tener problemas en clase Edges. */
Vertex::Vertex(){
	x = y = z = 0.0f;
}
// Constructor de vértice que recibe coordenadas.
Vertex::Vertex(float xi, float yi, float zi){
	x = xi;
	y = yi;
	z = zi;
}
// Método para imprimir las coordenadas del vértice.
void Vertex::imprimir(){
	cout<<"\n -> x = "<< x <<", y = "<< y <<", z = "<< z <<endl;
}
