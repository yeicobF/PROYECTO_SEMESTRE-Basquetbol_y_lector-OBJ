#include <vector>

/* Estos include son para las clases que separamos en librerías
para tener el código más limpio, y ordenado.*/
#include "obj_reader/object.hpp"
#include "graphics/graphic_object.hpp"

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
    // Lista de objectos.
    vector <GraphicObject> object_list;
    // Utilizar el constructor con el nombre del archivo.
    Object objBasketBall = Object("modelsOBJ/CartoonBasketball.obj");
    objBasketBall.saveObject();
    // std::cout << "\n Terminó de guardar el objBasketBalleto.\n";
    // objBasketBall.printObject();
    /*
    GraphicObject(Object _objFileInfo, float _scaleMultiplier,
                                float _distance, float _speed, float _size,
                                float _colorR, float _colorG, float _colorB)
    */
    GraphicObject basketball = GraphicObject(objBasketBall, 0.5f,
                                             -0.9f, 2.0f, 0.5f,
                                             1.0f, 0.0f, 0.0f);

    object_list.push_back(basketball);

    // Object objReference = Object("modelsOBJ/roca.obj");
    // objReference.saveObject();
    // GraphicObject referenceObject = GraphicObject(objBasketBall, 1.0f,
    //                                          0.0f, 5.0f, 1.0f,
    //                                          1.0f, 0.5f, 0.0f);
    // object_list.push_back(referenceObject);
    // Regresa -1 si ocurre algún error.
    GraphicObject basketball2 = GraphicObject(objBasketBall, 0.5f,
                                             0.9f, 2.0f, 0.5f,
                                             1.0f, 0.5f, 0.0f);

    object_list.push_back(basketball2);
    return GraphicObject::animateObjects(object_list);

    // Para la pruba de las curvas de Bézier.
    // return GraphicObject::drawEveryBezierTest(object_list);
}
