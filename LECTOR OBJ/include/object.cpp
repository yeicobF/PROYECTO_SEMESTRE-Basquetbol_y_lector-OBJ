#include "object.hpp"
#include <iostream>
#include <fstream> // Para la lectura y manejo de archivos.

using namespace std;

// Constructor de objetos que recibe el nombre del archivo OBJ.
Object::Object(string _OBJFileName){
    // Guardar el nombre del archivo.
    OBJFileName = _OBJFileName;
    objectName = "";
}

// Método que guardará todos los objetos.
void Object::saveObject(){
    /* PASOS PARA LEER Y ACOMODAR OBJETOS CON UN .obj:
		1.- Abrir archivo OBJ
		2.- Recorrer archivo línea a línea
		3.- Si v: Crear objeto Vertex
		4.- Si f: Crear objeto Edge
		5.- 		Crear objeto Face*/
    vector <Edge> edge_list;
    vector <Vertex> vertex_list;
    vector <string> values;
    // notEnter para lo que no queremos meter en values.
    string linea, notEnterValues = ""; //El delimitador de vértices
    // string delimitador = "  "; //No lo necesito porque lo paso como parámetro.
    // size_t pos = 0; //El inicio de posición para std::string::find()
	// 1.- Abrir archivo OBJ
    // string archivo = "";
    // cout << "Nombre del archivo: " << endl;
    // cin << archivo;
	ifstream OBJFile(OBJFileName);
    //cout << "\nHola: Compilación complida\n" << endl;
    // 2.- Recorrer archivo línea a línea
	while(getline(OBJFile, linea)){
        // posValores = 0; //La posición de dicho vector se reinicia.
        // cout << "Linea : " << numLinea << endl;
        // numLinea++;
        /* En la conidición que sigue comparo la subcadena de los primeros
         3 caracteres de la linea extraída para ver si son iguales a los
         del vértice en el archivo OBJ.*/
         // notEnterValues por referencia para obtener la "o" o la "g".
        if(isName(linea, &notEnterValues))
            // Aquí guardamos lo que guarda el splitString.
            saveObjectName(splitString(0, " ", linea, values, notEnterValues));
        if(Vertex::isGeometricVertex(linea)){
            notEnterValues = "v";
            values = splitString(0, " ", linea, values, notEnterValues); //Mandar pos = 0.
            //imprimeValores(values);
        /* Fuente de la conversión:
    https://www.programiz.com/cpp-programming/string-float-conversion#:~:text=help%20of%20examples.-,C%2B%2B%20string%20to%20float%20and%20double%20Conversion,convert%20string%20to%20long%20double%20.*/

            vertex_list.push_back(Vertex::saveVertex(values));
        }
        //
        if(Face::isFace(linea)){
            notEnterValues = "f";
            values = splitString(0, " ", linea, values, notEnterValues); //Mandar pos = 0.
            // Eliminamos el primer elemento, el cual es la f.
            //cout << "\n\n ENTRÓ AL isFace()\n\n" << endl;
            // Aquí trabajaré con los vértices y aristas.
            for(unsigned int i = 0; i < values.size(); i++)
                // Mandamos el índice i+1 porque el 0 es la f de face_list.
                edge_list.push_back(Edge::saveEdge(vertex_list, values, i));
            // Meter la lista de aristas a la cara actual.
            face_list.push_back(edge_list);
            // Reiniciar la lista de aristas.
            edge_list.clear();
        }
        values.clear(); // Limpia el vector. Elimina todos sus elementos.
	}
    nameNotFound(OBJFileName);
	OBJFile.close(); // Cerrar el archivo.
	// return 0;
}

/* Método que imprime al objeto:
    - NOMBRE
    - NÚMERO DE CARA
    - ARISTAS QUE CONFORMAN LA CARA
    - VÉRTICES QUE CONFORMAN A LAS ARISTAS
    - NÚMERO DE CARAS TOTALES*/
void Object::printObject(){
    unsigned int i;
    cout << "\n\t-----------------------" << endl;
    cout << "\n\t -> NOMBRE DEL OBJETO: " << objectName << endl;
    cout << "\n\t-----------------------" << endl;
    // Impresión de cada cara
    for(i = 0; i < face_list.size(); i++){
        cout << "\n - CARA " << (i + 1) << endl;
        // Impresión de cada cara.
        face_list[i].printFace();
        // Poner un separador para identificar cada cara con mayor facilidad.
        cout << "------------------------------\n" << endl;
    }
    cout << " - ESTE OBJETO TIENE " << i << " CARAS -\n" << endl;
}

// Método que verifica si la línea actual lee un nombre.
/* El nombre se representa por una "o", aunque también puede ser con la "g",
    que también denota un grupo.
    - Recibe notEnterValues por referencia para que guarde la letra que
        corresponde al nombre del objeto y así no incluirla en el nombre del
        objeto.*/
bool Object::isName(string str, string* notEnterValues){
    // Si el primer caracter de la cadena es "o" o "g", devuelve true.
    // Guardar la letra en cadena para no incluirla en la cadena del nombre.
    if(str.substr(0, 1).compare("o") == 0)
        *notEnterValues = "o";
    if(str.substr(0, 1).compare("g") == 0)
        *notEnterValues = "g";
    return str.substr(0, 1).compare("o") == 0 || str.substr(0, 1).compare("g") == 0;
}

// Método que guardará el nombre del objeto.
void Object::saveObjectName(vector <string> values){
    // Este ciclo por si guardó más de un valor el splitString se vaya concatenando.
    for(unsigned int i = 0; i < values.size(); i++)
        objectName += values[i];
}

// Si no se especifica el nombre en el archivo, ponerle el del archivo.
void Object::nameNotFound(string OBJFileName){
    // Si el archivo aún no tiene nombre.
    if(objectName.compare("") == 0){
        /* Hay que ver si está dentro de una carpeta para quitar su nombre.
            Y que sea la última incidencia de la diagonal que representa una
            carpeta.*/
        size_t posFolder = OBJFileName.find_last_of("/");
        // Find the position of the extension not to include it.
        size_t posExt = OBJFileName.find(".obj");
        // if(posFolder < 0)
        //     objectName =
        // Establecer el nombre del objeto como el del archivo sin su extensión.
        // Si no pongo posFolder + 1, se imprime la diagonal.
        /* Como la subcadena con 2 parámetros es para:
                string.substr(índice, largo);
            - Al restar el encuentro de la extensión con el encuentro de la
            última diagonal - 1, el largo de hace de la cantidad necesaria
            para no imprimir la extensión.
                - FUENTE: Stack Overflow: C++ Get String between two
                    delimiter String.*/
        objectName = OBJFileName.substr(posFolder + 1, posExt - posFolder - 1);
    }
}

/* Función que recorrerá una línea dependiendo de los parámetros dados.
 Regresará un vector que guardará como cadena los valores para así acceder
 a ellos y utilizarlos conforme los vayamos a necesitar.*/
vector <string> Object::splitString(size_t pos, string delimitador, string linea,
                                    vector <string> values, string notEnterValues){
    string token;
    /* Ciclo que asigna la posición como el índice en donde se encuentra el
        delimitador en la cadena actual. Este avanza hasta que ya no haya nada.*/
    while ((pos = linea.find(delimitador)) != std::string::npos) {
        if(linea.substr(0, 1).compare(" ") == 0){
            pos = linea.find(delimitador);
            linea.erase(0, pos + delimitador.length());
            continue;
        }
        // Se guarda la subcadena de 0 hasta pos.
        token = linea.substr(0, pos);
        //if(token.compare(" ") == 0) continue;
        // Agregar el elemento encontrado al vector si no es la v (Luego lo haré general).
        // Si es igual a notEnterValues no se agrega, si es diferente, sí se agrega.
        // Si es un espacio en blanco no se agrega.
        if(token.compare(notEnterValues) != 0)
            values.push_back(token);
        // cout << token << endl;
        // Eliminar el último elemento que agregamos al vector de la cadena.
        linea.erase(0, pos + delimitador.length());
    }
    // cout << token << endl;
    /* Como lo último no se guía por delimitadores ya que no hay espacios
    al final, se agrega lo restante de la línea. Esto recordando que al
    agregar un elemento al vector se eliminaba de la cadena inicial.*/

    if(linea.compare("") != 0)
        values.push_back(linea);
    // values = eraseEmptyValues(values, " ");
    // cout << "\n\n" << notEnterValues << endl;
    // for(unsigned int i = 0; i < values.size(); i++)
    //     cout << values[i] << ", " << endl;
    return values;
}

/* Método que quitará los espacios en blanco o cosas que estorben en un vector.*/
vector <string> Object::eraseEmptyValues(vector <string> values, string valueToErase){
    unsigned int i;
    for(i = 0; i < values.size(); i++)
        if(values[i].compare(valueToErase) == 0);
            values.erase(values.begin() + i);
    return values;
}
