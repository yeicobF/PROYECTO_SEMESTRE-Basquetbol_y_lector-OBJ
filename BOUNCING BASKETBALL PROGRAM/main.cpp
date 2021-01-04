#include <vector>

/* Estos include son para las clases que separamos en librerías
para tener el código más limpio, y ordenado. */
#include "obj_reader/object.hpp"
#include "graphics/graphic_object.hpp"

/*
 - Francisco Jacob Flores Rodríguez
 - Lunes, 14 - 15, 16, Jueves, 17 de septiembre del 2020
 - Domingo, 4 - Lunes, 5 de octubre del 2020
 - GRAFICACIÓN POR COMPUTADORA, 5to SEMESTRE
 - PROYECTO SEMESTRAL [1er a 4to PARCIAL]
 - ANIMACIÓN DE BALÓN REBOTANDO, UTILIZANDO CURVAS DE BÉZIER.

 - TERMINADO EL: Lunes, 4 de enero del 2020 [05:37AM]
 - TERMINADO DE LIMPIAR EL CÓDIGO: Lunes, 4 de enero del 2020 [06:54AM]
    * Con esto me refiero a que solo dejé comentarios que creo necesarios o
        útiles para un futuro. Además, quité código que no servía o no
        utilizaba.
 */

int main(){
    // Lista de los objetos a utilizar.
    std::vector <GraphicObject> object_list;
    /* Se instancia el objeto con el nombre del archivo para que lo lea y
        encuentre el número de caras, los vértices, aristas, etcétera. */
    Object objBasketBall = Object("modelsOBJ/OrangeCartoon_basketball_ball_OBJ.obj");
    // Se guarda el objeto en memoria con lo indicado anteriormente.
    objBasketBall.saveObject();
    // Así se puede imprimir la información obtenida.
    // objBasketBall.printObject();

    /*
    GraphicObject(Object _objFileInfo, float _scaleMultiplier,
                                float _distance, float _speed, float _size,
                                float _colorR, float _colorG, float _colorB)
    */
    /* Se pasa como parámetro el objeto con la información del archiv OBJ en
        memoria. */
    GraphicObject basketball = GraphicObject(objBasketBall, 0.5f,
                                             -0.9f, 2.0f, 0.5f,
                                             1.0f, 0.0f, 0.0f);
    // Se agrega el objeto a la lista de los que se dibujarán.
    object_list.push_back(basketball);

    GraphicObject basketball2 = GraphicObject(objBasketBall, 0.5f,
                                             0.9f, 2.0f, 0.5f,
                                             1.0f, 0.5f, 0.0f);

    object_list.push_back(basketball2);

    /* Enviamos la lista de objetos para que los dibuje.
       Ponemos el método estático en el return, ya que devuelve un valor. */
    return GraphicObject::animateObjects(object_list);
}
