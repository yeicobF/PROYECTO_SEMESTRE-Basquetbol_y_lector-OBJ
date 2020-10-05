#ifndef OBJECT_HPP
#define OBJECT_HPP

//#include "edge.hpp"
#include "face.hpp"
#include <vector>
#include <string>

/* Jueves, 17 de septiembre de 2020
    - Domingo, 4 de octubre de 2020.
	-> Clase en donde se manejará todo lo que tiene que ver con los objetos.
	- La lectura de los archivos OBJ.
	- El método split() para dividir elementos de una cadena y guardarlos
	para después instanciar las clases.*/

class Object{
    private:
        // Caras para tener en el objeto. Cada una accede a sus aristas y vértices.
        std::vector<Face> face_list;
        std::string OBJFileName;
        // Para el nombre del objeto.
        std::string objectName;

        void imprimeValores(std::vector <std::string> v);
        std::vector <std::string> splitString(size_t pos, std::string delimitador, std::string linea,
                                                std::vector <std::string> values, std::string notEnterValues);
        // Método que guardará el nombre del objeto
        void saveObjectName(std::vector <std::string> values);
        // Método que verifica si la línea actual lee un nombre.
        bool isName(std::string str, std::string* notEnterValues);
        // Si no se especifica el nombre en el archivo, ponerle el del archivo.
        void nameNotFound(std::string OBJFileName);
    public:
        Object(std::string _OBJFileName);
        // Método que guardará todos los objetos.
        void saveObject();
        void printObject();
};

#endif
