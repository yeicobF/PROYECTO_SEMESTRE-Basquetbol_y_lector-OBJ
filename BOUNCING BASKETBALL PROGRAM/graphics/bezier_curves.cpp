#include <cmath> // Funciones matemáticas.

#include "bezier_curves.hpp"
#include "graphic_object.hpp"

using namespace std;


BezierCurves::BezierCurves(float _initialX, float _initialY, float _initialSpeed,
                            float _speedAngle, float _numberOfBounces, float gravity,
                           float _yMax, float _dt){
    initialX = _initialX;
    initialY = _initialY;
    initialSpeed = _initialSpeed;
    speedAngle = _speedAngle;
    // Número de saltos que dará la pelota.
    numberOfBounces = _numberOfBounces;
    // Número del salto actual.
    currentBounce = 1;
    dt = _dt;

    // Hay que calcular la X máxima de acuerdo a los parámetros.
    xMax = fabs((pow(initialSpeed, 2) * sin(2 * speedAngle)) / gravity + initialX);
    currentBounceMaxY = yMax = _yMax;
    // Matriz de Bézier. Constante.
    MB = {{-1, 3, -3, 1},
		  {3, -6, 3, 0},
		  {-3, 3, 0, 0},
		  {1, 0, 0, 0}};
}

// Método para obtener los vértices de las curvas de Bézier.
void BezierCurves::calculateVertices(){
    cout << "\n Hola calculate 1" << endl;
    // Valores máximos para x y y del salto actual.
    currentBounceMaxX = xMax / numberOfBounces * currentBounce;
    // Aumentar eñ número del rebote actual.
    currentBounce++;
cout << "\n Hola calculate 2" << endl;
    // PUNTOS DE CONTROL.
    arma::frowvec P1 = {initialX, 0, 0};
    // 1/4 de trayectoria el primer PC.
    arma::frowvec P2 = {currentBounceMaxX / 4, currentBounceMaxY, 0};
    // 3/4 de trayectoria el primer PC.
    arma::frowvec P3 = {currentBounceMaxX / 4, currentBounceMaxY, 0};
    // // 1/4 de trayectoria el primer PC.
    // arma::frowvec P2 = {initialX / 4, yCurve[0], 0};
    // // 3/4 de trayectoria el primer PC.
    // arma::frowvec P3 = {initialX / 4 * 3, yCurve[1], 0};
    arma::frowvec P4 = {currentBounceMaxX, 0, 0};

    // La altura máxima de y irá disminuyendo 1/4 de la altura máxima anterior.
    currentBounceMaxY *= 0.75;
    // Establecer que ahora la X inicial será con la que se terminó aquí.
    initialX = currentBounceMaxX;

    // MATRIZ DE PUNTOS DE CONTROL.
    arma::fmat GB(4, 3);
    GB.row(0) = P1;
    GB.row(1) = P2;
    GB.row(2) = P3;
    GB.row(3) = P4;

cout << "\n Hola calculate 3" << endl;

    // Matriz de Bézier. Constante.
    MB = {{-1, 3, -3, 1},
          {3, -6, 3, 0},
          {-3, 3, 0, 0},
          {1, 0, 0, 0}};

    Qt.clear(); // Reiniciar vector.
    // Calcular LOS VÉRTICES DE LA CURVA.
    for(float t = 0.0, i = 0; t <= 1.0 + dt; t += dt, i++){
        // MATRIZ DE TRANSLACIÓN.
    	arma::frowvec T = {powf(t, 3), powf(t, 2), t, 1};
    	// Si no ponemos frowvec salta error
        // DERIVADA DE LA ECUACIÓN DE LA CURVA.
    	Qt.push_back( T * MB * GB );
    	cout << "... t = " << t << " ... punto: " << Qt[i];
    }
}

// Obtener el vector de vértices.
vector <arma::frowvec> BezierCurves::getVertices(){
    return Qt;
}
