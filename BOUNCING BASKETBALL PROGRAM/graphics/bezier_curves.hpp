#ifndef BEZIERCURVES_HPP
#define BEZIERCURVES_HPP

#include <armadillo>
#include <vector>

/*
    CLASE EN LA QUE SE CALCULARÁN LAS CURVAS DE BÉZIER.
    Se calculan 4 PUNTOS DE CONTROL.
        1.- El inicio de la trayectoria.
        2.- Un punto de control cualquiera.
        3.- Un punto de control cualquiera.
        4.- El final de la trayectoria.
*/

class BezierCurves{
    private:
        // No necesitaremos instanciar.
        BezierCurves() {}
    public:
        // Devuelve un arreglo con los n vértices.
        static std::vector <arma::frowvec>
            getVertices(float initialX, float initialSpeed, float speedAngle,
                        // yCurve es un arreglo de la y en el primer PC y en el
                        // segundo PC.
                        float gravity, float yCurve[2], float dt);
};

#endif
