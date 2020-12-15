#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>
#include <armadillo>

/* Los dos puntos (..) es para regresar al directorio padre y luego desde
    ahí acceder a la carpeta obj_reader. */
#include "../obj_reader/object.hpp"
#include "../graphics/transform.hpp"

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
        float distance = 0.0f;
    	float speed = 0.0f;
    	float size = 0.0f;
        float angle = 0.0f;

        // Colores en RGB
    	float colorR = 0.0f;
    	float colorG = 0.0f;
    	float colorB = 0.0f;
        // Para hacer la prueba con Bezier.
        std::vector <arma::frowvec> bezierTest;
        int bezierTestIndex = 0;
    public:
        // Constructor vacío para no tener problemas.
        GraphicObject() {}
        GraphicObject(Object _objFileInfo, float _scaleMultiplier,
                      float _distance, float _speed, float _size,
                      float _colorR, float _colorG, float _colorB);
        void drawObject(); // Para mostrar el objeto en pantalla.
        // Para obtener la transformación del objeto.
        // Recibe el multiplicador del tamaño del objeto para escalarlo en base a ese.
        arma::fmat getObjectTransform();
        // Dibuja TODOS los objectos en batallas.
        static void drawEveryObject(std::vector <GraphicObject> objects);
        // Para hacer TODO el proceso de dibujado de los objetos.
        // Recibe un vector con todos los objetos por dibujar.
        // Regresa -1 si ocurre algún error.
        static int animateObjects(std::vector <GraphicObject> _objects);
};

#endif
