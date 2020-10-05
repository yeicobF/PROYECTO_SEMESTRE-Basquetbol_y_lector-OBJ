#ifndef FACE_HPP
#define FACE_HPP

#include "edge.hpp"
#include <vector>
/* Clase que representa las caras o Faces.*/

//class Edge;

class Face{
	private:
        std::vector <Edge> edge_list;
	public:
		Face(std::vector <Edge> _edge_list);
        // Método que verifica si es una cara la línea analizada.
        static bool isFace(std::string str);
        // Método que imprime las carcas con sus aristas y vértices.
        void printFace();
};

#endif
