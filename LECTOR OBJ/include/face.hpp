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
		Face(std::vector <Edge> edge_list);
        static bool isFace(std::string str);
        // Método que imprime las carcas con sus aristas y vértices.
        void printFace();
};

#endif
