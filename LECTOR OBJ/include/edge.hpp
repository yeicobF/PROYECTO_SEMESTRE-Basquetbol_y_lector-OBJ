#ifndef EDGE_HPP
#define EDGE_HPP

#include "vertex.hpp"
//class Vertex;
/* Clase que representa los aristas o edges.*/
class Edge{
	private:
		Vertex vi;
		Vertex vf;
	public:
		// Constructor de aristas con sus vértices correspondientes.
        Edge();
        Edge(Vertex va, Vertex vb);
		void imprimir();
};

#endif
