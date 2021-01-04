#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <armadillo>

class Transform
{
    private:
        /* Crear un constructor privado para que no se pueda instanciar la clase, ya que no se requiere.

            https://stackoverflow.com/questions/9321/how-do-you-create-a-static-class-in-c

            To make your intention clear in this approach you can additionally use a private constructor. private: BitParser() {} This will prevent anyone from creating instances. – Danvil
        */
        Transform(){}
    // Todos los métodos estáticos porque no se necesita instanciar la clase. No se requiere como objeto.
    public:
        static arma::fmat Translation(float tx, float ty, float tz);
        static arma::fmat Scale(float sx, float sy, float sz);
        static arma::fmat Rotation(float ax, float ay, float az, float angle);
};

#endif
