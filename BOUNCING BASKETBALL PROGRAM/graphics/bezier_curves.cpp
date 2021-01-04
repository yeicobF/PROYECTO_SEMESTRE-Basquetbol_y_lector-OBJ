#include <cmath> // Funciones matemáticas.

#include "bezier_curves.hpp"

BezierCurves::BezierCurves(float _initialX, float _initialY, float _initialSpeed,
                            float _speedAngle, int _numberOfBounces, float gravity,
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
    // La Y máxima del rebote inicial es la Y máxima en general.
    currentBounceMaxY = yMax = _yMax;
    // Matriz de Bézier. Constante.
    MB = {{-1, 3, -3, 1},
		  {3, -6, 3, 0},
		  {-3, 3, 0, 0},
		  {1, 0, 0, 0}};
}

// Método para obtener los vértices de las curvas de Bézier.
void BezierCurves::calculateVertices(){
    // cout << "\n  - CURRENT BOUNCE: " << currentBounce << endl;
    // Valor máximo para X en el salto actual.
    currentBounceMaxX =  (xMax / numberOfBounces * currentBounce);
    // Aumentar eñ número del rebote actual.
    currentBounce++;
    // PUNTOS DE CONTROL -------------------------------------------------------

    /* Se calculan 4 PUNTOS DE CONTROL:
        1.- El inicio de la trayectoria.
        2.- Un punto de control cualquiera.
        3.- Un punto de control cualquiera.
        4.- El final de la trayectoria.
    */
    arma::frowvec P1 = {initialX, 0, 0};
    // Tuve problemas con los puntos de control. No los supe emplear del todo bien.
    // Los balones avanzabann pero regresaban. Intenté arreglarlo de muchas
    //  formas, pero al final mejor lo dejé así.
    arma::frowvec P2 = {(float)(currentBounceMaxX * 0.75), currentBounceMaxY, 0};
    arma::frowvec P3 = {(float)(currentBounceMaxX * 0.75), currentBounceMaxY, 0};
    arma::frowvec P4 = {currentBounceMaxX, 0, 0};

    // La altura máxima de y irá disminuyendo respecto al número de rebotes.
    currentBounceMaxY = yMax - (yMax / numberOfBounces * currentBounce);
    // Establecer que ahora la X inicial será con la que se terminó aquí.
    initialX = currentBounceMaxX;

    // MATRIZ DE PUNTOS DE CONTROL.
    arma::fmat GB(4, 3);
    GB.row(0) = P1;
    GB.row(1) = P2;
    GB.row(2) = P3;
    GB.row(3) = P4;

    Qt.clear(); // Reiniciar vector.
    // Calcular LOS VÉRTICES DE LA CURVA.
    for(float t = 0.0, i = 0; t <= 1.0 + dt; t += dt, i++){
        // MATRIZ DE TRANSLACIÓN.
    	arma::frowvec T = {powf(t, 3), powf(t, 2), t, 1};
    	// Si no ponemos frowvec salta error
        // DERIVADA DE LA ECUACIÓN DE LA CURVA.
    	Qt.push_back( T * MB * GB );
    	// cout << "... t = " << t << " ... punto: " << Qt[i];
    }
}

// Obtener el vector de vértices.
std::vector <arma::frowvec> BezierCurves::getVertices(){
    return Qt;
}

// Regresa True si ya se hizo el último rebote.
bool BezierCurves::isLastBounce(){
    // Se cuenta un bote más porque la cuenta empieza desde 1.
    return currentBounce == (numberOfBounces + 1);
}
