#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "face.hpp"
#include <vector>
#include <string>

/* Jueves, 17 de septiembre de 2020
    - Domingo, 4 de octubre de 2020.
    - Lunes, 5 de octubre de 2020.
	-> Clase en donde se manejará todo lo que tiene que ver con los objetos.
	- La lectura de los archivos OBJ.
	- El método split() para dividir elementos de una cadena y guardarlos
	para después instanciar las clases.*/

class Object{
    private:
        // Caras para tener en el objeto. Cada una accede a sus aristas y vértices.
        std::vector<Face> face_list;
        // Método que guardará el nombre del archivo.
        std::string OBJFileName;
        // Para el nombre del objeto.
        std::string objectName;
        // Método que verifica si la línea actual lee un nombre.
        bool isName(std::string str, std::string* notEnterValues);
        // Método que guardará el nombre del objeto
        void saveObjectName(std::vector <std::string> values);
        // Si no se especifica el nombre en el archivo, ponerle el del archivo.
        void nameNotFound(std::string OBJFileName);
        // Método que parte una cadena dada y regresa un vector de tipo string.
        std::vector <std::string> splitString(size_t pos, std::string delimitador, std::string linea,
                                                std::vector <std::string> values, std::string notEnterValues);
    public:
        Object(std::string _OBJFileName);
        // Método que guardará a los objetos.
        void saveObject();
        // Método que imprimirá al objecto.
        void printObject();
};

#endif
