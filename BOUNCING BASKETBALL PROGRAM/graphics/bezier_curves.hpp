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
        int numberOfBounces; // Número de saltos que dará la pelota.
        // Número del salto actual.
        int currentBounce;
        // Valores máximos para x y y del salto actual.
        float currentBounceMaxX, currentBounceMaxY;
        float xMax, yMax; // y y x máximos.
        // Valor inicial para x y y, además de la velocidad inicial.
        float initialX, initialY, initialSpeed;
        float gravity;
        float speedAngle;
        float dt;
        // Matriz de Bézier. Constante.
        arma::fmat MB;
        // Estas serán las coordenadas del objeto.
        // Se debe guardar la Qt en un Vertex, y sacar sus coordenadas homogéneas.
        std::vector <arma::frowvec> Qt;
    public:
        BezierCurves(){}
        // No necesitaremos instanciar.
        BezierCurves(float _initialX, float _initialY, float _initialSpeed,
                     float _speedAngle, float _numberOfBounces, float gravity,
                     float _yMax, float _dt);
        void calculateVertices();
        // Devuelve un arreglo con los n vértices.
        std::vector <arma::frowvec> getVertices();
};

#endif
