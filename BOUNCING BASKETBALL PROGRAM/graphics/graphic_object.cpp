#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
// #include <armadillo>
#include <iostream>
#include <fstream>

#include "graphic_object.hpp"

using namespace std;

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

    /*
    BezierCurves(float _initialX, float _initialY, float _initialSpeed,
                 float _speedAngle, int _numberOfBounces, float gravity,
                 float _yMax, float _dt);
    */
    bezier = BezierCurves(distance, 0.0, speed,
                          70, 6, 9.8,
                          1.0, 0.02);
    bezier.calculateVertices(); // Calcular los vértices.
    for(int i = 0; i < bezier.getVertices().size(); i++){
        // cout << bezier.getVertices()[i][0] << ", " << bezier.getVertices()[i][1] << ", " << bezier.getVertices()[i][2] << endl;
        // Agregar los vértices al vector.
        // bezier.getVertices()[Número de vértice][coordenada x, y, o z]
        bezierTestVertices.push_back(Vertex(bezier.getVertices()[i][0],
                                            bezier.getVertices()[i][1],
                                            bezier.getVertices()[i][2]));
    }
    // Si inicializo a -1 la comparación no funciona bien.
    bezierTestIndex = 0;
}

arma::fmat GraphicObject::getObjectTransform(){
    // Matriz de transformación.
    // Primero se escala con el valor base.
    arma::fmat transform = Transform::Scale(scaleMultiplier, scaleMultiplier, scaleMultiplier);
    // Se aplica la transformación completa. El orden de las multiplicaciones importa.
    transform =   Transform::Rotation(0.0f, 1.0f, 0.0f, angle)
                * Transform::Translation(distance, 0.0, 0.0)
                * Transform::Scale(size, size, size)
                * transform;
    return transform;
}

void GraphicObject::drawObject(){
    angle = (angle < 360.0f) ? angle + speed : 0.0f;

    vector <Vertex> p_vertices = objFileInfo.getFacesVertices();

    vector <Vertex> object_vertices;
    /* El número máximo de vértices para ver si se dibuja por triángulos
        o por polígonos.*/
    int maxVertexInFaces = 0;
    // El OBJ del balón de basket tiene 4 vértices por cara.
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

    for ( unsigned int i = 0; i < object_vertices.size(); i++ )
        if(object_vertices[i].getVertex().size() > maxVertexInFaces)
            maxVertexInFaces = object_vertices[i].getVertex().size();

    glColor3f(colorR, colorG, colorB);

    // Si hay menos o igual a 3 vértices, dibujar por triángulos.
    if(maxVertexInFaces <= 3)
        glBegin(GL_TRIANGLES);
    // Si hay más de 3 vértices se dibuja por polígonos.
    else
        glBegin(GL_POLYGON);
    // Aquí se dibujan los vértices de uno por uno.
    for ( unsigned int i = 0; i < object_vertices.size(); i++ ) {
        arma::frowvec vert = object_vertices[i].getVertex();
        glVertex3f(vert[0], vert[1], vert[2]);
    }
    // Termina el dibujado.
    glEnd();
}

/* En un ciclo dibuja a cada uno de los objetos.*/
/* static */void GraphicObject::drawEveryObject(vector <GraphicObject> objects){
    for(unsigned int i = 0; i < objects.size(); i++)
        objects[i].drawObject();
}

// Para hacer TODO el proceso de dibujado de los objetos.
// Recibe un vector con todos los objetos por dibujar.
/* static */int GraphicObject::animateObjects(vector <GraphicObject> object_list){
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
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Color negro para que se vea la Luna.
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Color blanco.
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

    int count = 0;

    do {
        glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2],
               camera[0], camera[1], camera[2],
               view_up[0], view_up[1], view_up[2]);


        // object_list[0].drawObject();
        // drawEveryObject(object_list);
        if(object_list[count].drawBezier() == 1){
            // Esperar a que presione enter.
            // do{}while(glfwGetKey(window, GLFW_KEY_ENTER ) != GLFW_PRESS);
            // object_list.push_back(object_list[count]);
            // count++;
            break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Para dibujar la prueba con Bézier.

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0 );
    
    glfwTerminate();

    // Si termina todo bien, regresar un 0 para indicarlo.
    return 0;
}


/* PARA HACER PRUEBAS CON LAS CURVAS DE BÉZIER.*/

// Para probar las curvas de Bézier. Regresa 1 si ya se dibujaron los rebotes.
int GraphicObject::drawBezier(){

    angle = (angle < 360.0f) ? angle + speed : 0.0f;
    // cout << "\n Hola" << endl;
    // // Si el índice no llega a su máximo, seguir aumentando.
    // cout << "\n bezierTestVertices.size() = " << bezierTestVertices.size() << endl;
    // cout << "\n bezierTestIndex = " << bezierTestIndex << endl;
    // cout << "\nbezierTestIndex > (bezierTestVertices.size() - 1): " << (bezierTestIndex < (bezierTestVertices.size() - 1)) << endl;
    // Me sale que -1 es mayor que los positivos.
    // if(bezierTestIndex < (bezierTestVertices.size() - 1)){
    if((bezierTestVertices.size() - bezierTestIndex) > 1){
        bezierTestIndex++;
        // cout << "\n Hola 2" << endl;
    }
    else{
        // cout << "\n Hola 4" << endl;
        bezierTestIndex = 0;
        bezier.calculateVertices();
        bezierTestVertices.clear();
        for(int i = 0; i < bezier.getVertices().size(); i++)
            // Agregar los vértices al vector.
            // bezier.getVertices()[Número de vértice][coordenada x, y, o z]
            bezierTestVertices.push_back(Vertex(bezier.getVertices()[i][0],
                                                bezier.getVertices()[i][1],
                                                bezier.getVertices()[i][2]));
    }
    // cout << "\n Hola 3" << endl;
    arma::fmat transform = Transform::Scale(scaleMultiplier, scaleMultiplier, scaleMultiplier);
    // Se aplica la transformación completa. El orden de las multiplicaciones importa.
    // transform = Transform::Translation(bezierTestVertices[bezierTestIndex][0],
    //                                    bezierTestVertices[bezierTestIndex][1],
    //                                    bezierTestVertices[bezierTestIndex][2])
    //             * Transform::Scale(size, size, size)
    //             * transform;

    // cout << "\n TRANSLATION: [Index = " << bezierTestIndex << ", "
    //     << bezierTestVertices[bezierTestIndex].getVertex()[0] << ", "
    //     << bezierTestVertices[bezierTestIndex].getVertex()[1] << ", "
    //     << bezierTestVertices[bezierTestIndex].getVertex()[2] << endl;

    transform =   Transform::Translation(bezierTestVertices[bezierTestIndex].getVertex()[0],
                                        bezierTestVertices[bezierTestIndex].getVertex()[1],
                                        bezierTestVertices[bezierTestIndex].getVertex()[2])
                * Transform::Scale(size, size, size)
                * transform;
    // transform = Transform::Rotation(0.0f, 1.0f, 0.0f, angle)
    //             * Transform::Translation(bezierTestVertices[bezierTestIndex][0],
    //                                      bezierTestVertices[bezierTestIndex][1],
    //                                      bezierTestVertices[bezierTestIndex][2])
    //             * Transform::Scale(size, size, size)
    //             * transform;


    vector <Vertex> p_vertices = objFileInfo.getFacesVertices();

    vector <Vertex> object_vertices;
    /* El número máximo de vértices para ver si se dibuja por triángulos
        o por polígonos.*/
    int maxVertexInFaces = 0;
    // El OBJ del balón de basket tiene 4 vértices por cara.
    for ( unsigned int i=0; i<p_vertices.size(); i++ ) {
        arma::fcolvec v = p_vertices[i].getHomogeneousCoordinates();
        // cout << "\n - V: " << v;
        arma::fcolvec vp = transform * v;
        // cout << "\n - VP: " << vp;
        Vertex rv = Vertex();
        // cout << "\n - rv: "; rv.printVertex();
        rv.setVertex(arma::trans(vp));
        object_vertices.push_back(rv);
        // cout << "\n - cbvertex: " << object_vertices;
    }

    for ( unsigned int i = 0; i < object_vertices.size(); i++ )
        if(object_vertices[i].getVertex().size() > maxVertexInFaces)
            maxVertexInFaces = object_vertices[i].getVertex().size();

    // El color de los polígonos.
    glColor3f(colorR, colorG, colorB);

    // Si hay menos o igual a 3 vértices, dibujar por triángulos.
    if(maxVertexInFaces <= 3)
        glBegin(GL_TRIANGLES);
    // Si hay más de 3 vértices se dibuja por polígonos.
    else
        glBegin(GL_POLYGON);
    // Aquí se dibujan los vértices de uno por uno.
    for ( unsigned int i = 0; i < object_vertices.size(); i++ ) {
        arma::frowvec vert = object_vertices[i].getVertex();
        glVertex3f(vert[0], vert[1], vert[2]);
    }
    // Termina el dibujado.
    glEnd();
    // Si ya se hicieron todos los rebotes, terminar.
    if(bezier.isLastBounce())
        return 1;
    else
        return 0;
}

// Para hacer TODO el proceso de dibujado de los objetos.
// Recibe un vector con todos los objetos por dibujar.
/* static */int GraphicObject::drawEveryBezierTest(vector <GraphicObject> object_list){
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
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Color negro para que se vea la Luna.
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Color blanco.
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


    do {
        glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2],
               camera[0], camera[1], camera[2],
               view_up[0], view_up[1], view_up[2]);

        // Para dibujar la prueba con Bézier.

        object_list[0].drawBezier();
        // object_list[0].drawObject();
        // drawEveryObject(object_list);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0 );

    glfwTerminate();

    // Si termina todo bien, regresar un 0 para indicarlo.
    return 0;
}
