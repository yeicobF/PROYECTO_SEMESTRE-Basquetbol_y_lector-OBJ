#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Para la lectura y manejo de archivos.
/* Estos include son para las clases que separamos en librerías
para tener el código más limpio, y ordenado.*/
#include "include/vertex.hpp"
#include "include/edge.hpp"
#include "include/face.hpp"

using namespace std;

/*
 - Francisco Jacob Flores Rodríguez
 - Lunes, 14 - 15, 16, Jueves, 17 de septiembre de 2020
 - Graficación por computadora, 1er parcial
 - IMPLEMENTACIÓN DE ARCHIVOS OBJ EN C++.

 INSTRUCCIONES:
 - En esta ocasión comenzamos a trabajar con el archivo OBJ. De esta forma
 podremos crear los objetos tomando los datos de dicho arcivo. El lunes solo
 comenzamos con la lectura e impresión de archivo, pero ya lo implementaremos
 completamente en los próximos días.
 - Reutilizamos los archivos del ejercicio de Cubo unitario, ahí ya tenemos
 las clases implementadas para el manejo de los polígonos.
 */

vector <string> splitString(size_t pos, string delimitador, string linea, vector <string> valores);
void imprimeValores(vector <string> v);
void imprimeVertex(vector <Vertex> v);

int main(){
	/* PASOS PARA LEER Y ACOMODAR OBJETOS CON UN .obj:
		1.- Abrir archivo OBJ
		2.- Recorrer archivo línea a línea
		3.- Si v: Crear objeto Vertex
		4.- Si f: Crear objeto Edge
		5.- 		Crear objeto Face*/
    Vertex v;
    vector <Vertex> vertex_list;
    vector <string> valores;
    string linea; //El delimitador de vértices
    // string delimitador = "  "; //No lo necesito porque lo paso como parámetro.
    // size_t pos = 0; //El inicio de posición para std::string::find()
	// 1.- Abrir archivo OBJ
	ifstream archivoOBJ("models/cube.obj");
    // 2.- Recorrer archivo línea a línea
	while(getline(archivoOBJ, linea)){
        // posValores = 0; //La posición de dicho vector se reinicia.
        // cout << "Linea : " << numLinea << endl;
        // numLinea++;
        /* En la conidición que sigue comparo la subcadena de los primeros
         3 caracteres de la linea extraída para ver si son iguales a los
         del vértice en el archivo OBJ.*/
        if(linea.substr(0, 3).compare("v  ") == 0){
            valores = splitString(0, "  ", linea, valores); //Mandar pos = 0.
        //imprimeValores(valores);
        /* Fuente de la conversión:
    https://www.programiz.com/cpp-programming/string-float-conversion#:~:text=help%20of%20examples.-,C%2B%2B%20string%20to%20float%20and%20double%20Conversion,convert%20string%20to%20long%20double%20.*/
            float x = stof(valores[0]); // std::stof(str); No pongo std por el namespace
            float y = stof(valores[1]);
            float z = stof(valores[2]);
            v = Vertex(x, y, z);
            vertex_list.push_back(v);
        }
        valores.clear(); // Limpia el vector. Elimina todos sus elementos.
	}
    imprimeVertex(vertex_list); //Imprime los vértices
	archivoOBJ.close(); // Cerrar el archivo.
	return 0;
}

/* Función que recorrerá una línea dependiendo de los parámetros dados.
 Regresará un vector que guardará como cadena los valores para así acceder
 a ellos y utilizarlos conforme los vayamos a necesitar.*/
vector <string> splitString(size_t pos, string delimitador, string linea, vector <string> valores){
    string token;
    /* Ciclo que asigna la posición como el índice en donde se encuentra el
        delimitador en la cadena actual. Este avanza hasta que ya no haya nada.*/
    while ((pos = linea.find(delimitador)) != std::string::npos) {
        // Se guarda la subcadena de 0 hasta pos.
        token = linea.substr(0, pos);
        // Agregar el elemento encontrado al vector si no es la v (Luego lo haré general).
        if(token.compare("v") != 0) // Si es igual a v no se agrega.
            valores.push_back(token);
        // cout << token << endl;
        // Eliminar el último elemento que agregamos al vector de la cadena.
        linea.erase(0, pos + delimitador.length());
    }
    // cout << token << endl;
    /* Como lo último no se guía por delimitadores ya que no hay espacios
    al final, se agrega lo restante de la línea. Esto recordando que al
    agregar un elemento al vector se eliminaba de la cadena inicial.*/
    valores.push_back(linea);
    return valores;
}

/* Método que imprime los valores guardados en el vector de cadena.*/
void imprimeValores(vector <string> v){
    vector<string>::const_iterator i;
    cout << "\n - Imprimir vector: " << endl;
    for(i = v.begin(); i != v.end(); ++i)
        cout << *i << ", ";
    cout << "\n" << endl;
}

/* Método que imprime los valores guardados en el vector de cadena.*/
void imprimeVertex(vector <Vertex> v){
    cout << "\n - Imprimir Vector de Vértices: " << endl;
    for(size_t i = 0; i < v.size(); i++){
        cout << "Vertice " << i << ": ";
        v[i].imprimir();
        cout << "\n" << endl;
    }
    cout << "\n" << endl;
}
