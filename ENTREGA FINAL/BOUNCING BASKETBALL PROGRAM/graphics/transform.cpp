#include <cmath>
#include "transform.hpp"

#define PI 3.14159265

/*static*/ arma::fmat Transform::Translation(float tx, float ty, float tz) {
    return( arma::fmat( {{1.0f, 0.0f, 0.0f, tx},
                        {0.0f, 1.0f, 0.0f, ty},
                        {0.0f, 0.0f, 1.0f, tz},
                        {0.0f, 0.0f, 0.0f, 1.0}} )
    );
}

/*static*/ arma::fmat Transform::Scale(float sx, float sy, float sz) {
    return( arma::fmat( {{sx, 0.0f, 0.0f, 0.0f},
                        {0.0f, sy, 0.0f, 0.0f},
                        {0.0f, 0.0f, sz, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0}} )
    );
}

/* Aquí solo se hace la rotación del último valor que se haya definido. */
/*static*/ arma::fmat Transform::Rotation(float ax, float ay, float az, float angle) {
    float ang = angle * PI / 180.0f;
    arma::fmat Rot;

    Rot.eye(4, 4);

    if (ax)
        Rot = arma::fmat( {{1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, cosf(ang), -sinf(ang), 0.0f},
                        {0.0f, sinf(ang), cosf(ang), 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0}} );
    if (ay)
        Rot = arma::fmat( {{cosf(ang), 0.0f, sinf(ang), 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {-sinf(ang), 0.0, cosf(ang), 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0}} );
    if (az)
        Rot = arma::fmat( {{cosf(ang), -sinf(ang), 0.0f, 0.0f},
                        {sinf(ang), cosf(ang), 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0}} );

    return(Rot);
}
