#ifndef FACE_HPP
#define FACE_HPP

#include "edge.hpp"
#include <vector>
/* Clase que representa las caras o Faces.*/

//class Edge;

class Face{
	private:
        std::vector <Edge> edges;
	public:
		Face(std::vector <Edge> edge_list);
        // Método que imprime las carcas con sus aristas y vértices.
        void imprimir();
};

#endif
