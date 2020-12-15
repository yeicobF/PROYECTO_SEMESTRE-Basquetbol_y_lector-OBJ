#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include <iostream>
#include <fstream>

#include "graphic_object.hpp"

GraphicObject::GraphicObject(Object _objFileInfo, float _scaleMultiplier,
                            float _distance, float _speed, float _size,
                            float _colorR, float _colorG, float _colorB){
    objFileInfo = _objFileInfo;
    scaleMultiplier = _scaleMultiplier;
    distance = _distance;
    speed = _speed;
    size = _size;
    colorR = _colorR;
    colorG = _colorG;
    colorB = _colorB;
    angle = 0.0f;
}

arma::fmat getObjectTransform(){
    // Matriz de transformación.
    // Primero se escala con el valor base.
    arma::fmat transform = Transform::S(scaleMultiplier, scaleMultiplier, scaleMultiplier);
    // Se aplica la transformación completa. El orden de las multiplicaciones importa.
    transform =   Transform::R(0.0f, 1.0f, 0.0f, angle)
                * Transform::T(distance, 0.0, 0.0)
                * Transform::S(size, size, size)
                * transform;
    return transform;
}

void GraphicObject::drawObject(){
    angle = (angle < 360.0f) ? angle + speed : 0.0f;

    vector< Vertex > p_vertices = objFileInfo.getFacesVertices();

    std::vector< Vertex > object_vertices;

    for ( unsigned int i=0; i<p_vertices.size(); i++ ) {
        arma::fcolvec v = p_vertices[i].getHomogeneousCoordinates();
        // cout << "\n - V: " << v;
        arma::fcolvec vp = getObjectTransform() * v;
        // cout << "\n - VP: " << vp;
        Vertex rv = Vertex();
        // cout << "\n - rv: "; rv.printVertex();
        rv.setVertex(arma::trans(vp));
        object_vertices.push_back(rv);
        // cout << "\n - cbvertex: " << object_vertices;
    }

    glColor3f(colorR, colorG, colorB);
    glBegin(GL_TRIANGLES);
    for ( unsigned int i=0; i<object_vertices.size(); i++ ) {
        arma::frowvec vert = object_vertices[i].getVertex();
        glVertex3f(vert[0], vert[1], vert[2]);
    }
    glEnd();
}

/* En un ciclo dibuja a cada uno de los objetos.*/
/* static */void drawEveryObject(std::vector <GraphicObject> objects){
    for(unsigned int i = 0; i < objects.size(); i++)
        objects[i].drawObject();
}

// Para hacer TODO el proceso de dibujado de los objetos.
// Recibe un vector con todos los objetos por dibujar.
/* static */void animateObjects(std::vector <GraphicObject> object_list){
    // Para la perspectiva en que vemos el sistema.
    // Con eye cambiamos la perspectiva desde la que nosotros lo vemos.
    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    arma::frowvec view_up = {0.0, 1.0, 0.0};
    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Fallo al inicializar GLFW\n" );
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Sistema Solar", NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Cambiar color del fondo de la ventana. Lo quiero blanco.
    // glClearColor(0.0,0.0,1.0,0.0); // Dark blue
    // glClearColor(1.0f, 0.0f, 1.0f, 0.0f); // Purple
    // glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // Light Blue
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Color negro para que se vea la Luna.
    // glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Color blanco.
    //Clear the screen to this color.
    glClear(GL_COLOR_BUFFER_BIT);

    //  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

    //  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

    //  Proyección en perspectiva
    //glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Transform Tr = Transform();
    float t_angle = 0.0f;
    do {
        glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2],
               camera[0], camera[1], camera[2],
               view_up[0], view_up[1], view_up[2]);

        drawEveryObject(object_list);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0 );

    glfwTerminate();
}
