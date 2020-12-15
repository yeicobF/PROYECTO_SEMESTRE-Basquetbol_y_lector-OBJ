#include <cmath> // Funciones matemáticas.

#include "bezier_curves.hpp"
#include "graphic_object.hpp"

using namespace std;

// Método para obtener los vértices de las curvas de Bézier.
/* static */vector <arma::frowvec>
                BezierCurves::getVertices(float initialX, float initialSpeed,
                                          float speedAngle, float gravity,
                                          float yCurve[2], float dt){
    // Hay que calcular la X máxima de acuerdo a los parámetros.
    float xMax = (pow(initialSpeed, 2) * sin(2 * speedAngle)) / gravity + initialX;
    xMax = fabs(xMax);

    // Matriz de Bézier. Constante.
    arma::fmat MB = {{-1, 3, -3, 1},
      				 {3, -6, 3, 0},
      				 {-3, 3, 0, 0},
      				 {1, 0, 0, 0}};

    // PUNTOS DE CONTROL.
    arma::frowvec P1 = {initialX, 0, 0};
    // 1/4 de trayectoria el primer PC.
    arma::frowvec P2 = {initialX / 3, yCurve[0], 0};
    // 3/4 de trayectoria el primer PC.
    arma::frowvec P3 = {initialX * 2, yCurve[1], 0};
    arma::frowvec P4 = {xMax, 0, 0};

    // MATRIZ DE PUNTOS DE CONTROL.
    arma::fmat GB(4, 3);
    GB.row(0) = P1;
    GB.row(1) = P2;
    GB.row(2) = P3;
    GB.row(3) = P4;

    vector <arma::frowvec> Qt;

    // Calcular LOS VÉRTICES DE LA CURVA.
    for(float t = 0.0; t <= 1.0 + dt; t += dt){
        // MATRIZ DE TRANSLACIÓN.
    	arma::frowvec T = {powf(t, 3), powf(t, 2), t, 1};
    	// Si no ponemos frowvec salta error
        // DERIVADA DE LA ECUACIÓN DE LA CURVA.
    	Qt.push_back( T * MB * GB );
    	// cout << "... t = " << t << " ... punto: " << Qt[i];
    }
    // Estas serán las coordenadas del objeto.
    return Qt;
}
