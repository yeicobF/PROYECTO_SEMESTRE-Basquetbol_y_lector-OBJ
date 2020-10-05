#ifndef OBJECT_HPP
#define OBJECT_HPP

//#include "edge.hpp"
#include "face.hpp"
#include <vector>
#include <string>

/* Jueves, 17 de septiembre de 2020
	-> Clase en donde se manejará todo lo que tiene que ver con los objetos.
	- La lectura de los archivos OBJ.
	- El método split() para dividir elementos de una cadena y guardarlos
	para después instanciar las clases.*/

class Object{
    private:
        // Caras para tener en el objeto. Cada una accede a sus aristas y vértices.
        std::vector<Face> face_list;
    public:
        Object(std::string OBJFileName);
        // Método que guardará todos los objetos.
        void saveObject();
        void printObject();
};

#endif
