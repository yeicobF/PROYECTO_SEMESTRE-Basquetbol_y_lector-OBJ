#ifndef EDGE_HPP
#define EDGE_HPP

#include "vertex.hpp"
#include <vector>
#include <string>
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
        static Edge saveEdge(std::vector <Vertex> v_list, std::vector <std::string> values, int actualIndex);
        void printEdge();
};

#endif
