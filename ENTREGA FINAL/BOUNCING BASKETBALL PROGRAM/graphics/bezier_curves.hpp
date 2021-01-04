#ifndef BEZIERCURVES_HPP
#define BEZIERCURVES_HPP

#include <armadillo>
#include <vector>

/*
    CLASE EN LA QUE SE CALCULARÁN LAS CURVAS DE BÉZIER.
*/

class BezierCurves{
    private:
        // Número de saltos que dará la pelota.
        int numberOfBounces;
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
        // Constructor vacío para no tener problemas al compilar.
        BezierCurves(){}
        /* Necesitamos instanciar la clase (Podría haber sido un inicializador
            de los valores como método estático) para irlos guardando como
            progreso para el cálculo de cada rebote. */
        BezierCurves(float _initialX, float _initialY, float _initialSpeed,
                     float _speedAngle, int _numberOfBounces, float gravity,
                     float _yMax, float _dt);
        // Método para SOLO CALCULAR (NO REGRESAR) los vértices de las curvas de
        //  Bézier.
        void calculateVertices();
        // Devuelve un arreglo con los n vértices calculados con las curvas de
        //  Bézier.
        std::vector <arma::frowvec> getVertices();
        // Método para revisar si el rebote actual se trata del último.
        bool isLastBounce();
};

#endif
