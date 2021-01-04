/* PROGRAMA QUE MUESTRA PELOTAS REBOTANDO EN PANTALLA. Son de distintos
    colores.

 - OBTENIDO DE: https://www.youtube.com/watch?v=C5WWI4ZbL90&ab_channel=SergioSilva
    - CÓDIGO: https://files.fm/f/sw3sb3ut*/

#include <GL/glut.h>
#include <cmath>
#include<iostream>
#include <ctime>
#include<cstdlib>
#include<vector>

// -lglut32 -lglu32 -lopengl32

using namespace std;



long int inicial=time(NULL);
long int final, quadros=0;
const int FPS=60;

const int LARGURA=800;
const int ALTURA=600;

const float PI=3.1416;

class PVector
{
public:
	float x;
	float y;

	PVector()
	{
		x=0;
		y=0;
	}

	PVector(float x_, float y_)
	{
		x=x_;
		y=y_;
	}

	void soma(PVector v)
	{
		x+=v.x;
		y+=v.y;
	}
};

class Bola
{
	private:
		int aleatorio(int inicio, int fim)
	{
		return rand()%(fim-inicio+1)+inicio;
	}

	void borda()
	{
		if(posicao.y<=raio)
		{
			posicao.y=raio;
			veloc.y*=-atrito;
			veloc.x*=atrito;

		}

		if(posicao.y>=ALTURA-raio)
		{
			posicao.y=ALTURA-raio;
			veloc.y*=-atrito;
			veloc.x*=atrito;

		}

		if(posicao.x>=LARGURA-raio)
		{
			veloc.x*=-atrito;
			posicao.x=LARGURA-raio;
		}

		if(posicao.x<=raio)
		{
			veloc.x*=-atrito;
			posicao.x=raio;
		}

	}



	public:
		PVector posicao;
		float raio;
		PVector veloc;
		PVector acel;
		float cor[3];
		float atrito;

	Bola()
	{
		posicao=PVector(aleatorio(0,LARGURA), aleatorio(0,ALTURA));
		raio=aleatorio(2,3);
		veloc=PVector(aleatorio(-5,5), aleatorio(-5,5));
		acel=PVector(0,-0.2);
		cor[0]=aleatorio(0,100)/100.0;//R
		cor[1]=aleatorio(0,100)/100.0;//G
		cor[2]=aleatorio(0,100)/100.0;//B
		atrito=0.8;
	}


	Bola(int x_, int y_)
	{
		posicao=PVector(x_,y_);
		raio=aleatorio(5,8);
		veloc=PVector(aleatorio(-5,5), aleatorio(-5,5));
		acel=PVector(0,-0.2);
		cor[0]=aleatorio(0,100)/100.0;//R
		cor[1]=aleatorio(0,100)/100.0;//G
		cor[2]=aleatorio(0,100)/100.0;//B
		atrito=0.8;
	}

	void desenhaBola()
	{

		float incr=0.1;
		glColor3fv(cor);
		glBegin(GL_POLYGON);
			for(float angulo=0;angulo<2*PI;angulo+=incr)
			{
				float x=posicao.x+raio*cos(angulo);
				float y=posicao.y+raio*sin(angulo);
				glVertex2f(x,y);
			}
		glEnd();
	}



	void moveBola()
	{
		veloc.soma(acel);
		posicao.soma(veloc);
		borda();
	}


};

vector<Bola> bolas;

void desenha()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i=0; i< bolas.size(); i++)
		bolas[i].desenhaBola();

	glutSwapBuffers();

	quadros++;
	final=time(NULL);
	if(final-inicial>0)
	{
		cout<<"FPS: " <<quadros/(final-inicial)<<endl;
		quadros=0;
		inicial=final;
	}

}


void criaBola(int botao, int status, int x, int y)
{
	int yc=ALTURA-y;

	if(botao==GLUT_LEFT_BUTTON)
		if(status==GLUT_DOWN)
		{
			Bola b(x,yc);
			bolas.push_back(b);
		}
	glutPostRedisplay();
}


void init()
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(LARGURA, ALTURA);
	glutInitWindowPosition(400,50);
	glutCreateWindow("Bolas");
	glClearColor(0, 0, 0, 0);// fundo preto


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0,LARGURA,0,ALTURA);

}

void idle(int)
{
	for(int i=0;i<bolas.size();i++)
		bolas[i].moveBola();

	glutPostRedisplay();
	glutTimerFunc(1000/FPS,idle,0);
}

int main(int argc, char* argv[]) {


	glutInit(&argc, argv);
	init();
	glutDisplayFunc(desenha);
	glutTimerFunc(1000/FPS,idle,0);
	glutMouseFunc(criaBola);
	glutMainLoop();
	return 0;
}
