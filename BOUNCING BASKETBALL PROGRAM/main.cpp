
/* Estos include son para las clases que separamos en librerías
para tener el código más limpio, y ordenado.*/
#include "obj_reader/object.hpp"
#include "graphics/graphic_object.hpp"
#include <iostream>

using namespace std;

/*
 - Francisco Jacob Flores Rodríguez
 - Lunes, 14 - 15, 16, Jueves, 17 de septiembre del 2020
 - Domingo, 4 - Lunes, 5 de octubre del 2020
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
    // Utilizar el constructor con el nombre del archivo.
    Object objBasketBall = Object("modelsOBJ/OrangeCartoon_basketball_ball_OBJ.obj");
    objBasketBall.saveObject();
    // std::cout << "\n Terminó de guardar el objBasketBalleto.\n";
    objBasketBall.printObject();
    GraphicObject basketball = GraphicObject(objBasketBall);
}
