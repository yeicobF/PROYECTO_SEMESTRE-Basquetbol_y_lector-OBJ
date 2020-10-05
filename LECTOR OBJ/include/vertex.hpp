#ifndef VERTEX_HPP
#define VERTEX_HPP

/* - En este .hpp solo podemos tener la definición de la clase,
no la implementación.*/

#include <vector>
#include <string>

/* Clase que representa los vértices o vertex.*/
class Vertex{
	private: //Lo que le sigue es privado hasta donde empieza el public.
		//Atributos en cada línea para que esté todo mejor organizado.
		float x;
		float y;
		float z;
	public: //Todo lo que le sigue es público.
		/* Constructor de vértice sin parámetros
			para no tener problemas en clase Edges. */
		Vertex();
		// Constructor de vértice que recibe coordenadas.
		Vertex(float xi, float yi, float zi);
		// Método estático para guardar valores de vértice y regresarlos.
        /* https://stackoverflow.com/questions/31305717/member-function-with-static-linkage*/
        static Vertex saveVertex(std::vector <std::string> values);
        static bool isGeometricVertex(std::string str);
        void printVertex();
};



#endif
