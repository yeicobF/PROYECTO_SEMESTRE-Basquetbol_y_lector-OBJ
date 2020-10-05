
/* Estos include son para las clases que separamos en librerías
para tener el código más limpio, y ordenado.*/
#include "include/object.hpp"

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

int main(){
    // Utilizar el constructr con el nombre del archivo.
    Object obj = Object("models/cube.obj");
}
