#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>
#include <armadillo>

/* Los dos puntos (..) es para regresar al directorio padre y luego desde
    ahí acceder a la carpeta obj_reader. */
#include "../obj_reader/object.hpp"
#include "transform.hpp"
#include "bezier_curves.hpp"

/*
    CLASE EN DONDE SE MANEJARÁ LA PARTE DE LOS GRÁFICOS,
        es decir, el dibujado del objeto, su movimiento, y demás.
    Esto haciendo uso de la clase Transform.
*/

class GraphicObject{
    private:
        // En donde se guardará la info del OBJ.
        Object objFileInfo;
        float scaleMultiplier = 0.0f;
        float initialX = 0.0f;
    	float speed = 0.0f;
    	float size = 0.0f;
        float angle = 0.0f;

        // Colores en RGB
    	float colorR = 0.0f;
    	float colorG = 0.0f;
    	float colorB = 0.0f;
        /* Para hacer la prueba con Bezier. Es un vector con los vértices de la
            curva de Bézier en la que se encuentra actualmente. */
        std::vector <Vertex> bezierCurveVertices;
        /* El número de vértice de la curva en la que se encuentra el rebote
            actual. */
        int bezierCurveVertexIndex = -1;
        // Para manejar las curvas de Bézier.
        BezierCurves bezier;
        // Variable que indica si se puede dibujar un balón.
        bool drawBall = true;
        // Vector de objetos GraphicObject.
        // static std::vector <GraphicObject> object_list;
    public:
        // Constructor vacío para no tener problemas.
        GraphicObject() {}
        GraphicObject(Object _objFileInfo, float _scaleMultiplier,
                      float _initialX, float _speed, float _size,
                      float _colorR, float _colorG, float _colorB);
        void drawObject(); // Para mostrar el objeto en pantalla.
        // Para obtener la transformación del objeto.
        // Recibe el multiplicador del tamaño del objeto para escalarlo en base a ese.
        arma::fmat getObjectTransform();
        // Dibuja TODOS los objectos en batallas.
        static void drawEveryObject(std::vector <GraphicObject> _objects);
        // Para hacer TODO el proceso de dibujado de los objetos.
        // Recibe un vector con todos los objetos por dibujar.
        // Regresa -1 si ocurre algún error.
        static int animateObjects(std::vector <GraphicObject> object_list);
        // Hace todo el dibujado y movimiento.
        int drawBezier();
        static int drawEveryBezierTest(std::vector <GraphicObject> object_list);
        // Revisar si aún se puede dibujar el objeto.
        bool isObjectDrawable(){
            return drawBall;
        }
        // Establecer que ya no se pueda dibujar el objeto.
        void setObjectNotDrawable(){
            drawBall = false;
        }
        // Establecer colores del objeto.
        void setColors(float _colorR, float _colorG, float _colorB){
            colorR = _colorR;
            colorG = _colorG;
            colorB = _colorB;
        }
        // Para cambiar el tamaño del objeto.
        void setSize(float _size){
            size = _size;
        }
        // // Vector de objetos GraphicObject.
        // static std::vector <GraphicObject> get_object_list(){
        //     return object_list;
        // };
};

#endif
