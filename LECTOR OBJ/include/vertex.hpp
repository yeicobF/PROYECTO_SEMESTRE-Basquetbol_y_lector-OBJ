#ifndef VERTEX_HPP
#define VERTEX_HPP

/* - En este .hpp solo podemos tener la definición de la clase,
no la implementación.*/

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
		// Método para imprimir las coordenadas del vértice.
		void imprimir();
};

#endif
