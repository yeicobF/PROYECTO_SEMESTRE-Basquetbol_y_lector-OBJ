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
        // Podría hacer un arreglo en lugar de una lista, pero ya lo hice así. Tal vez luego lo cambie.
        std::vector <int> vertex_nums; // Lista que guarda los números de los vértices.
	public:
		// Constructor de aristas con sus vértices correspondientes.
        Edge();
        Edge(Vertex va, Vertex vb);
        // Método estático que guarda una arista. Se puede invocar sin instanciar al objeto.
        static Edge saveEdge(std::vector <Vertex> v_list, std::vector <std::string> values, unsigned int actualIndex);
        Vertex getStartVertex();
        // Método que imprime los vértices de una arista.
        void printEdge();
        // Método para establecer los números de los vértices del arista.
        void setVertexNums(int v1, int v2);
};

#endif
