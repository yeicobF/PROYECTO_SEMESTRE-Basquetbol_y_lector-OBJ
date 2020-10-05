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
         // Es el mismo delimitador para todos.

        if(Vertex::isGeometricVertex(linea)){
            notEnterValues = "v";
            values = splitString(0, "  ", linea, values, notEnterValues); //Mandar pos = 0.
            //imprimeValores(values);
        /* Fuente de la conversión:
    https://www.programiz.com/cpp-programming/string-float-conversion#:~:text=help%20of%20examples.-,C%2B%2B%20string%20to%20float%20and%20double%20Conversion,convert%20string%20to%20long%20double%20.*/

            vertex_list.push_back(Vertex::saveVertex(values));
        }
        //
        if(Face::isFace(linea)){
            notEnterValues = "f";
            values = splitString(0, "  ", linea, values, notEnterValues); //Mandar pos = 0.
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
    // imprimeVertex(vertex_list); //Imprime los vértices
	OBJFile.close(); // Cerrar el archivo.
	// return 0;
}

void Object::printObject(){
    unsigned int i;
    // Código para impresión.
    // Impresión de cada cara
    for(i = 0; i < face_list.size(); i++){
        cout << "\n - CARA " << (i + 1) << endl;
        // Impresión de cada arista.
        face_list[0].printFace();
        // for(int j = 0; i < face_list[i].size(); j++){
        //     cout << "\n\t - ARISTA " << j << endl;
        //     face_list[i].printEdge();
        cout << endl;
        }
    cout << " - ESTE OBJETO TIENE " << i << " CARAS -" << endl;
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
vector <string> Object::splitString(size_t pos, string delimitador, string linea,
                                    vector <string> values, string notEnterValues){
    string token;
    /* Ciclo que asigna la posición como el índice en donde se encuentra el
        delimitador en la cadena actual. Este avanza hasta que ya no haya nada.*/
    while ((pos = linea.find(delimitador)) != std::string::npos) {
        // Se guarda la subcadena de 0 hasta pos.
        token = linea.substr(0, pos);
        // Agregar el elemento encontrado al vector si no es la v (Luego lo haré general).
        if(token.compare(notEnterValues) != 0) // Si es igual a v o f no se agrega, si es diferente, sí se agrega.
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
    cout << "\n\n" << notEnterValues << endl;
    for(unsigned int i = 0; i < values.size(); i++)
        cout << values[i] << ", " << endl;
    return values;
}
