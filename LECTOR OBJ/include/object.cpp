#include "object.hpp"
#include <iostream>
// #include <string>
// #include <vector>
#include <fstream> // Para la lectura y manejo de archivos.

using namespace std;

// Constructor de objetos que recibe el nombre del archivo OBJ.
Object::Object(string OBJFileName){
    // Guardar el nombre del archivo.
    this -> OBJFileName = OBJFileName;
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
    Vertex v;
    Edge e;
    vector <Face> face_list;
    vector <Edge> edge_list;
    vector <Edge> edge_list_aux;
    vector <Vertex> vertex_list;
    vector <string> values;
    string linea; //El delimitador de vértices
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
         // Es el mismo delimitador para todos.

        if(isGeometricVertex(linea)){
            values = splitString(0, "  ", linea, values); //Mandar pos = 0.
            imprimeValores(values);
        /* Fuente de la conversión:
    https://www.programiz.com/cpp-programming/string-float-conversion#:~:text=help%20of%20examples.-,C%2B%2B%20string%20to%20float%20and%20double%20Conversion,convert%20string%20to%20long%20double%20.*/

            vertex_list.push_back(Vertex::saveVertex(values));
            values.clear(); // Limpia el vector. Elimina todos sus elementos.
        }
        //
        if(isFace(linea)){
            values = splitString(0, "  ", linea, values); //Mandar pos = 0.
            // Aquí trabajaré con los vértices y aristas.
            for(int i = 0; i < values.size(); i++)
                edge_list.push_back(Edge::saveEdge(vertex_list, values, i));
            edge_list_aux = edge_list;
        }
        // Meter la lista de aristas a la cara actual.
        face_list.push_back(edge_list);
        // Reiniciar la lista de aristas.
        edge_list.clear();
	}
    // imprimeVertex(vertex_list); //Imprime los vértices
	OBJFile.close(); // Cerrar el archivo.
	// return 0;
}

// Método que devuelve true si es un vértice geométrico.
bool Object::isGeometricVertex(string str){
    return str.substr(0, 3).compare("v  ") == 0;
}

// Método que devuelve true si encuentra la "f" de cara.
bool Object::isFace(string str){
    return str.substr(0, 1).compare("f") == 0;
}

void Object::printObject(){
    // Código para impresión.
}

/* Método que imprime los valores guardados en el vector de cadena.*/
void Object::imprimeValores(vector <string> v){
    vector<string>::const_iterator i;
    cout << "\n - Imprimir vector: " << endl;
    for(i = v.begin(); i != v.end(); i++)
        cout << *i << ", ";
    cout << "\n" << endl;
}
/* Función que recorrerá una línea dependiendo de los parámetros dados.
 Regresará un vector que guardará como cadena los valores para así acceder
 a ellos y utilizarlos conforme los vayamos a necesitar.*/
vector <string> Object::splitString(size_t pos, string delimitador, string linea, vector <string> values){
    string token;
    /* Ciclo que asigna la posición como el índice en donde se encuentra el
        delimitador en la cadena actual. Este avanza hasta que ya no haya nada.*/
    while ((pos = linea.find(delimitador)) != std::string::npos) {
        // Se guarda la subcadena de 0 hasta pos.
        token = linea.substr(0, pos);
        // Agregar el elemento encontrado al vector si no es la v (Luego lo haré general).
        if(token.compare("v") != 0) // Si es igual a v no se agrega, si es diferente, sí se agrega.
            values.push_back(token);
        // cout << token << endl;
        // Eliminar el último elemento que agregamos al vector de la cadena.
        linea.erase(0, pos + delimitador.length());
    }
    // cout << token << endl;
    /* Como lo último no se guía por delimitadores ya que no hay espacios
    al final, se agrega lo restante de la línea. Esto recordando que al
    agregar un elemento al vector se eliminaba de la cadena inicial.*/
    values.push_back(linea);
    return values;
}
