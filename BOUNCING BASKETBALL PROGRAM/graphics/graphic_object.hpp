#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

/* Los dos puntos (..) es para regresar al directorio padre y luego desde
    ahí acceder a la carpeta obj_reader. */
#include "../obj_reader/object.hpp"

/*
    CLASE EN DONDE SE MANEJARÁ LA PARTE DE LOS GRÁFICOS,
        es decir, el dibujado del objeto, su movimiento, y demás.
    Esto haciendo uso de la clase Transform.
*/

class GraphicObject{
    private:
        Object object;
    public:
        GraphicObject(Object _object);

};

#endif
