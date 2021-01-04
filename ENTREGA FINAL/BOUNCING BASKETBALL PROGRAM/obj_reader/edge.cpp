#include <iostream>
#include <string>
#include "edge.hpp" // Incluir el archivo en donde definimos la clase.

using namespace std;

Edge::Edge(){}

// Constructor de aristas con sus vértices correspondientes.
Edge::Edge(Vertex va, Vertex vb){
	vi = va;
	vf = vb;
}

/* Método ESTÁTICO que guarda la arista actual y la regresa.*/
/* static */ Edge Edge::saveEdge(vector <Vertex> v_list, vector <string> values, unsigned int actualIndex){
    Edge e;
    /* Values guarda los índices de los vértices, entonces son esos a los
        que hay que meter los valores, por eso su índice es:
            stoi(values[actualIndex].substr(0, 1)) - 1
        - Se le resta 1 porque si no, solo indicaría el vértice deseado, más
        no el índice real. Por ejemplo, el índice del vértice 1 es 0.*/

    /* Inicializar el índice del primer vértice como el número de vértice - 1
    para obtener su índice en el vector. Además, el segundo índice del que
    su valor dependerá de una condición.*/

    /* values[actualIndex].substr(0, values[0].find("/") indica que buscará
        el número completo hasta encontrar la diagonal, ya que en las líneas
        de texto que indican el número de vértices a relacionar los aristas,
        estos se delimitan con una diagonal.*/

    int indexV1 = stoi(values[actualIndex].substr(0, values[0].find("/"))) - 1, indexV2 = 0;
    // Si se llegó al índice máximo hacer último arista con primer vértice.
    if(actualIndex == (values.size() - 1)){
        // Como llegamos al último valor, relacionar con el primer vértice.
        /* El índice del segundo vértice = el vértice en el primer índice de
        values, en donde se guardaron los vértices pero restando 1 para tener
        su índice de la lista de vértices.*/
        indexV2 = stoi(values[0].substr(0, values[0].find("/"))) - 1;
        e = Edge(v_list[indexV1], v_list[indexV2]);
    }
    else{
        /* Si el primer vértice está dentro del límite,
            asignar el segundo con vértice que sigue. */
        indexV2 = stoi(values[actualIndex + 1].substr(0, values[0].find("/"))) - 1;
        e = Edge(v_list[indexV1], v_list[indexV2]);
    }
    /* Ahora regresar al número de vértice original para guardarlo en la lista
        de vértices que le corresponde a la arista.*/
    indexV1 ++;
    indexV2 ++;
    /* Establecer los vértices que le tocan a la arista. Se ocupa el setter
        porque este es un método estático y no puedo asignar los valores a las
        listas, ya que no se instancia el objeto para llamar al método.*/
    e.setVertexNums(indexV1, indexV2);
    // Regresamos el arista.
    return e;
}

// Método para obtener el primer vértice del arista.
Vertex Edge::getStartVertex(){
    return vi;
}

// Método que imprime los aristas con sus vértices.
void Edge::printEdge(){
    cout << "\n - VÉRTICES: " << vertex_nums[0] << ", " << vertex_nums[1] << endl;
	cout<< "\nVertice inicial: ";
	vi.printVertex(); // Para imprimir, llamar el método de los vértices.
	cout<< "\nVertice final: ";
	vf.printVertex();
	cout <<endl;
}

// Setter para establecer los números de vértices de la arista.
void Edge::setVertexNums(int v1, int v2){
    vertex_nums.push_back(v1);
    vertex_nums.push_back(v2);
}
