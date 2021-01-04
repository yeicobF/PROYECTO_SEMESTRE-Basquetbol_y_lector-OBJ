/* Siendo sincero, ya no sé cuáles bibliotecas utilicé y cuáles no, así que
    mejor las dejaré así. De todas formas no creo que afecte tanto al
    rendimiento, o eso espero.

   Al final mejor sí quité las que no ocupaba.
*/

/* LIBERÍAS ESENCIALES PORQUE SON LAS DE LOS GRÁFICOS. */
#include <GL/glu.h>
#include <GLFW/glfw3.h>
// Para entrada y salida (tengo varias impresiones comentadas).
#include <iostream>
// Para colores aleatorios.
#include <random>
// In order to call rand or srand you must #include <cstdlib>
#include <cstdlib>
// In order to call time, you must #include <ctime>
#include <ctime>

#include "graphic_object.hpp"

using namespace std;

//Variables PARA LA CÁMARA
float cameraAngle = 0.0f;
// Para la perspectiva en que vemos el sistema.
// Con eye cambiamos la perspectiva desde la que nosotros lo vemos.
arma::frowvec eye = {0.0, 0.0, 10.0};
arma::frowvec camera = {0.0, 0.0, 0.0};
arma::frowvec view_up = {0.0, 1.0, 0.0};
// Booleano para ver si se presionó enter.
bool was_enter_pressed = false;
// Para ver si se presionó backspace.
bool was_backspace_pressed = false;


/* Prototipo de función que detecta las teclas, para así mover la cámara y
    agregar balones. */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Constructor con los parámetros necesarios para los objetos.
GraphicObject::GraphicObject(Object _objFileInfo, float _scaleMultiplier,
                            float _initialX, float _speed, float _size,
                            float _colorR, float _colorG, float _colorB){
    objFileInfo = _objFileInfo;
    scaleMultiplier = _scaleMultiplier;
    initialX = _initialX;
    speed = _speed;
    size = _size;
    colorR = _colorR;
    colorG = _colorG;
    colorB = _colorB;
    angle = 0.0f;
    /*  "seed" the random number generator by calling srand(). This should be done
        once during your program's run -- not once every time you call rand(). This is
        often done like this:*/
    srand (static_cast <unsigned> (time(0)));
    /*
    BezierCurves(float _initialX, float _initialY, float _initialSpeed,
                 float _speedAngle, int _numberOfBounces, float gravity,
                 float _yMax, float _dt);
    */
    bezier = BezierCurves(initialX, 0.0, speed,
                          70, 6, 9.8,
                          1.0, 0.05f);
    bezier.calculateVertices(); // Calcular los vértices.
    for(int i = 0; i < bezier.getVertices().size(); i++){
        // Agregar los vértices al vector.
        // bezier.getVertices()[Número de vértice][coordenada x, y, o z]
        bezierCurveVertices.push_back(Vertex(bezier.getVertices()[i][0],
                                            bezier.getVertices()[i][1],
                                            bezier.getVertices()[i][2]));
    }
    // Si inicializo a -1 la comparación no funciona bien.
    bezierCurveVertexIndex = 0;
}

arma::fmat GraphicObject::getObjectTransform(){
    // Matriz de transformación.
    // Primero se escala con el valor base.
    arma::fmat transform = Transform::Scale(scaleMultiplier, scaleMultiplier, scaleMultiplier);
    // Se aplica la transformación completa. El orden de las multiplicaciones importa.
    transform =   Transform::Rotation(0.0f, 1.0f, 0.0f, angle)
                * Transform::Translation(initialX, 0.0, 0.0)
                * Transform::Scale(size, size, size)
                * transform;
    return transform;
}

// Para hacer TODO el proceso de dibujado de los objetos.
// Recibe un vector con todos los objetos por dibujar.
/* static */int GraphicObject::animateObjects(vector <GraphicObject> object_list){
    /* Auxiliaes de los objetos sin modificar, para cuando se generen los
        balones. */
    // Para generar un balón desde la izquierda.
    GraphicObject auxObject = object_list[0];
    // Para generar un balón desde la derecha.
    GraphicObject auxObject2 = object_list[1];
    /*FUENTE DE LOS NÚMEROS ALEATORIOS:
        https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    */
    // Se asignan colores aleatorios para distinguir los balones.
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    // Los colres van del 0 al 1, por lo que será el rango.
    std::uniform_int_distribution<> distr(0, 1); // define the range

    // Para la perspectiva en que vemos el sistema.
    // Con eye cambiamos la perspectiva desde la que nosotros lo vemos.
    eye = {0.0, 0.0, 10.0};
    camera = {0.0, 0.0, 0.0};
    view_up = {0.0, 1.0, 0.0};
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

    // //  Proyección en paralelo
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
        gluLookAt(    eye[0],     eye[1],     eye[2],
                   camera[0],  camera[1],  camera[2],
                  view_up[0], view_up[1], view_up[2]);

        /* FUNCIÓN CON LA QUE SE EVALUARÁN LAS TECLAS QUE SE PRESIONEN.
            O: Volver a la cámara inicial.
            I: Invertir la cámara.
            D: Poner la pespectiva de la cámara desde abajo (o arriba, no estoy
                seguro).
            -------- GENERAR BALONES -------------------------------------------
            - Los balones se generan con un color y tamaño aleatorios.
            ENTER: Genera un balón desde la izquierda de la pantalla.
            BACKSPACE (Retroceso): Genera un balón desde la derecha de la
                                    pantalla. */
      	glfwSetKeyCallback(window, key_callback);

        /* Ver si se presionó la tecla de retroceso o enter para agregar u
            balón a la lista.
           - Indicar que se dejó de presionar la tecla que haya sido.
        */
        if(was_backspace_pressed || was_enter_pressed){
            if(was_backspace_pressed){
                object_list.push_back(auxObject2);
                was_backspace_pressed = false;
            }
            else{ // Si no, signfica que se presionó enter.
                object_list.push_back(auxObject);
                was_enter_pressed = false;
            }
            // Generar 3 colores aleatorios (RGB) del 0 al 1.
            object_list[ object_list.size() - 1 ].setColors(distr(gen), distr(gen), distr(gen));
            /* FUENTE: https://stackoverflow.com/questions/686353/random-float-number-generation

                float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));

                Before calling rand(), you must first "seed" the random number
                generator by calling srand(). This should be done once during
                your program's run -- not once every time you call rand(). This
                is often done like this:

                    srand (static_cast <unsigned> (time(0)));

                - In order to call rand or srand you must #include <cstdlib>.

                - In order to call time, you must #include <ctime>.
            */
            // Cambiar en un rango del 0.1 al 0.7 el tamaño del objeto.
            float size = 0.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX / (0.7 - 0.1)));
            object_list[ object_list.size() - 1 ].setSize(size);
        }
        // Dibujar TODOS LOS OBJETOS.
        for(int i = 0; i < object_list.size(); i++){
            // Revisar si aún se puede dibujar el objeto.
            if(object_list[i].isObjectDrawable())
                /* Si el método regresa 1, significa que ya se dibujaron todos
                    los rebotes, por lo que hay que indicar que ya no se puede
                    dibujar el objeto. */
                if(object_list[i].drawBezier() == 1)
                    object_list[i].setObjectNotDrawable();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0 );

    glfwTerminate();

    // Si termina todo bien, regresar un 0 para indicarlo.
    return 0;
}

// Método para dibujar los objetos con curvas de Bézier.
int GraphicObject::drawBezier(){
    /* Ir aumentando el índice del punto actual de la curva de Bézier,
        hasta llegar al máximo. Esto se hace por cada rango de rebote,
        es decir, desde que toca el piso y sube, hasta que lo vuelve
        a tocar.

       - Puse la condición de esta forma, ya que inicializaba el índice como
            un valor negativo, pero al comparar

                -1 < número positivo

            me regresaba false, así que mejor lo hice así. Al parecer tiene algo
            que ver con el bit significativo.
    */
    if((bezierCurveVertices.size() - bezierCurveVertexIndex) > 1)
        bezierCurveVertexIndex++;
    /* Si ya dibujó al objeto en cada una de las posiciones del rebote, hay que
        calcular el siguiente rebote y los vértices. */
    else{
        // Reiniciar el índice.
        bezierCurveVertexIndex = 0;
        // Se vuelven a calcular los vértices.
        bezier.calculateVertices();
        // Se reinicia el vector de los vértices de la curva actual de Bézier.
        bezierCurveVertices.clear();
        /* Se agregan los vértices de la curva que se obtuvieron con
            anterioridad, al vector de vértices de la curva actual. */
        for(int i = 0; i < bezier.getVertices().size(); i++)
            // Agregar los vértices al vector.
            // bezier.getVertices()[Número de vértice][coordenada x, y, o z]
            bezierCurveVertices.push_back(Vertex(bezier.getVertices()[i][0],
                                                bezier.getVertices()[i][1],
                                                bezier.getVertices()[i][2]));
    }

    // Escalar respecto al multiplicador de escala del objeto.
    arma::fmat transform = Transform::Scale(scaleMultiplier,
                                            scaleMultiplier,
                                            scaleMultiplier);

    // Se aplica la transformación completa. El orden de las multiplicaciones importa.
    transform =   Transform::Translation(bezierCurveVertices[bezierCurveVertexIndex].getVertex()[0],
                                        bezierCurveVertices[bezierCurveVertexIndex].getVertex()[1],
                                        bezierCurveVertices[bezierCurveVertexIndex].getVertex()[2])
                * Transform::Scale(size, size, size)
                * transform;

    // Se obtienen TODOS los vértices del objeto.
    vector <Vertex> p_vertices = objFileInfo.getFacesVertices();
    // Lista de vértices del objeto ya transformados.
    vector <Vertex> object_vertices;
    /* El número máximo de vértices para ver si se dibuja por triángulos
        o por polígonos. */
    int maxVertexInFaces = 0;
    // El OBJ del balón de basket tiene 4 vértices por cara.
    for ( unsigned int i = 0; i < p_vertices.size(); i++ ) {
        // Se obtiene la coordenada homogénea del vértice actual.
        arma::fcolvec v = p_vertices[i].getHomogeneousCoordinates();
        // Se aplica la transformación a la coordenada homogénea.
        arma::fcolvec vp = transform * v;
        Vertex rv = Vertex();

        rv.setVertex(arma::trans(vp));
        // Se agrega el vértice a la lista de vértices ya transformados.
        object_vertices.push_back(rv);
    }

    /* Se recorren los vértices transformados para ver cuál es el número máximo
        de vértices por cara, para así determinar si se dibuja por triángulos
        o por polígonos. */
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
    // Si ya se hicieron todos los rebotes, terminar e indicarlo.
    if(bezier.isLastBounce())
        return 1;
    else
        return 0;
}

// IMPLEMENTACIÓN PARA MOVER LA CÁMARA, Y GENERAR NUEVO OBJETO.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // La vista inicial.
    // Al presionar O (de Opening, por ser la primera).
	if(key == GLFW_KEY_O && action == GLFW_PRESS){
        eye = {0.0, 0.0, 10.0};
        camera = {0.0, 0.0, 0.0};
        view_up = {0.0, 1.0, 0.0};

	}
	// if(key == GLFW_KEY_Z && action == GLFW_PRESS){
    //     eye = {0.0, 0.0, 10.0};
	// }
    // Al presionar I se invierte la vista.
	if(key == GLFW_KEY_I && action == GLFW_PRESS){
    	eye = {0.0, 0.0, -1.0};
	}
    // Al presionar D se ve desde abajo (o arriba, no estoy seguro).
	if(key == GLFW_KEY_D && action == GLFW_PRESS){
    	eye = {0.0, 10.0, 0.0};
    	view_up = {0.0, 0.0, -1.0};
	}
    // Revisa si se presionó ENTER.
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        was_enter_pressed = true;
    // Revisa si se presionó BACKSPACE (RETROCESO).
    if(key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
        was_backspace_pressed = true;
}
