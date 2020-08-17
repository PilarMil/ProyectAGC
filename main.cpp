#include "Punto.h"
#include <time.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <GL/glut.h>

using namespace std; //para el uso de palabras reservadas como cout y cin

float red = 1.0, green = 0.0, blue = 0.0;//color rojo predeterminado 

int tmpx, tmpy; //Almacena los puntos para hacer linea o circulo
int tmpx2, tmpy2; //Almacena los puntos para hacer linea o circulo
int tmpx3, tmpy3; //Almacena los puntos para hacer linea o circulo
int tmpx4, tmpy4; //Almacena los puntos para hacer linea o circulo
int forma = 1; // 1:punto, 2:linea, 3:circulo
bool segundo = false;
bool tercero = false;
bool cuarto = false;

vector<Punto> puntos;//lista que va a almacenar los puntos graficados

Punto puntoscurva[10];
int npuntos=0;
GLfloat x=0,y=0;

void drawPuntos(int mousex, int mousey)//Define las posiciones donde se graficaran los puntos, se almace
{
	//push_back() = add
	Punto PuntoNuevo(mousex, 500 - mousey, red, green, blue);
	puntos.push_back(PuntoNuevo);
	//cout<<mousey<<","<<mousex<<endl;
}

void drawLinea(int x1, int y1, int x2, int y2)//Dibuja lineas
{
	bool changed = false; // Bresenham
	
	if (abs(x2 - x1) < abs(y2 - y1))
	{
		int tmp1 = x1;
		x1 = y1;
		y1 = tmp1;
		int tmp2 = x2;
		x2 = y2;
		y2 = tmp2;
		changed = true;
	}
	int dx = x2 - x1;
	int dy = y2 - y1;
	int yi = 1;
	int xi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int d = 2 * dy - dx;
	int incrE = dy * 2;
	int incrNE = 2 * dy - 2 * dx;

	int x = x1, y = y1;
	if (changed)
		drawPuntos(y, x);
	else
		drawPuntos(x, y);
	while (x != x2)
	{
		if (d <= 0)
			d += incrE;
		else
		{
			d += incrNE;
			y += yi;
		}
		x += xi;
		if (changed)
			drawPuntos(y, x);
		else
			drawPuntos(x, y);
	}
}

void drawCirculo(int x1, int y1, int x2, int y2)
{
	int r = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));//formula para hallar el radio 
	double d;
	int x, y;
	
	x = 0;
	y = r;
	d = 1.25 - r;
	//cout<<r<<endl;
//	cout<<d<<endl;

	while (x <= y)//radio positivo
	{
		//grafica el perimetro del circulo 
		drawPuntos(x1 + x, y1 + y);
		drawPuntos(x1 - x, y1 + y);
		drawPuntos(x1 + x, y1 - y);
		drawPuntos(x1 - x, y1 - y);
		drawPuntos(x1 + y, y1 + x);
		drawPuntos(x1 - y, y1 + x);
		drawPuntos(x1 + y, y1 - x);
		drawPuntos(x1 - y, y1 - x);
		x++;
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			y--;
			d += 2 * (x - y) + 5;
		}
	}
}

int factorial(int n){
			
	int salida=1;
	
	for(int i=1;i<=n;i++){
		
		salida=salida*i;
		
	}
	
	return salida;
	
}

int combinacion(int n, int i){
			
	int salida=0;
	if (i==0 || n==1){
		
		return 1;
		
	} else{
		
		salida=(factorial(n)/(factorial(i)*factorial(n-i)));
		
	}
	
	return salida;
	
}
double pot(double b, int e){
	
	if (e==0) {
		
		return 1;
		
	} else if (e==1) {
		
		return b;
		
	} else if (e>1) {
		
		double salida=1;
		
		for(int i=0;i<e;i++){
			
			salida=salida*b;
			
		}
		
		return salida;
		
	}
	
}
double bernstein(int n, double i, double t){
	
	return combinacion(n,i)*pot(t,i)*pot(1-t,n-i);
	
}
/*
void graficarbezier(){
	
	Punto c0(20,40),c1(60,40),c2(70,60),c3(120,70);
	Punto puntos[]={c0,c1,c2,c3};
	int npuntos=sizeof(puntos)/sizeof(*puntos);//HALLA EL TAMANO DEL ARREGLO
	Curva c(puntos,npuntos);
	
	c.bezier();
	
}
*/
void bezier(int a, int b, int c, int d, int e, int f, int g, int h){
	
	puntoscurva[0]=Punto(a,b,red,green,blue);
	puntoscurva[1]=Punto(c,d,red,green,blue);
	puntoscurva[2]=Punto(e,f,red,green,blue);
	puntoscurva[3]=Punto(g,h,red,green,blue);
			
	for(int j=0;j<=1000;j++){
		
		float t=(float)j/1000;
		x=0;
		y=0;
		for(int i=0;i<4;i++){
			
			GLfloat B=bernstein(4-1,i,t);
			
			x=x+puntoscurva[i].getX()*B;
			y=y+puntoscurva[i].getY()*B;
			
		}
		drawPuntos(x,y);
		
	}
	
}
void graficarcasteljau3(Punto a, Punto b, Punto c){

	float x0,y0,x1,y1,x2,y2;
		
	Punto pt0,pt1,pt2;
	
	for(double i=0.0; i<=1.0; i+=0.001){
		
		x0=(1-i)*a.getX()+(i*(b.getX()));
		y0=(1-i)*a.getY()+(i*(b.getY()));
		
		x1=(1-i)*b.getX()+(i*(c.getX()));
		y1=(1-i)*b.getY()+(i*(c.getY()));
		
		pt0.set(x0,y0);
		pt1.set(x1,y1);
		
		x2=(1-i)*pt0.getX()+(i*(pt1.getX()));
		y2=(1-i)*pt0.getY()+(i*(pt1.getY()));
		
		drawPuntos(x2,y2);

	}
	
}

void graficarhermite(Punto a, Punto b, Punto c){
	
	float x0=0,y0=0;
	float P0x=a.getX();
	float P0y=b.getY();
	float P1x=c.getX();
	float P1y=a.getY();
	float P2x=b.getX();
	float P2y=c.getY();
	
	for(int j=0; j<=1000;j++){
		
		float t=(float)j/1000;
		float H1=2*pow(t,3)-3*pow(t,2)+1;
		float H2=-2*pow(t,3)+3*pow(t,2);
		float H3=pow(t,3)-2*pow(t,2)+t;
		float H4=pow(t,3)-pow(t,2);
		
		float Pp0x=3*(P1x-P0x);
		float Pp0y=3*(P1y-P0y);
		float Pp1x=3*(P2x-P1x);
		float Pp1y=3*(P2y-P1y);
		
		x0=H1*P0x+H2*P1x+H3*Pp0x+H4*Pp1x;
		y0=H1*P0y+H2*P1y+H3*Pp0y+H4*Pp1y;
		
		drawPuntos(x0,y0);
		
		//pt.setRGB(1,0,0);
		//pt.draw(); 
		
	}
	
}

void mouse(int bin, int state, int x, int y)//state: presionado o no presionado
{
	if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//glut_left_button: click
	{		
			if (forma == 1)
			{
					drawPuntos(x, y);
			}	
			else
			{
				if(forma==1 || forma==2 || forma==3){
					
					if (!segundo)//bandera para verificar que se realiza esa funcion 
				{
					tmpx = x;
					tmpy = y;
					segundo = true;
				}
				else
				{
					if (forma == 2)
						drawLinea(tmpx, tmpy, x, y);
				
					else if (forma == 3)
						drawCirculo(tmpx, tmpy, x, y);
					segundo = false;
				}
					
				}
				
				if(forma==4){
					
					if (!segundo)//bandera para verificar que se realiza esa funcion 
				{
					tmpx = x;
					tmpy = y;
					segundo = true;
					
				}
				else
				{
					if (!tercero)//bandera para verificar que se realiza esa funcion 
					{
						tmpx2 = x;
						tmpy2 = y;
						tercero = true;
						
					}
					else
					{
						if (!cuarto)//bandera para verificar que se realiza esa funcion 
						{
							tmpx3 = x;
							tmpy3 = y;
							cuarto = true;
							
						}
						else
						{
							bezier(tmpx,tmpy,tmpx2,tmpy2,tmpx3,tmpy3,x,y);
							segundo=false;
							tercero=false;
							cuarto=false;
						}
						
					}
					
				}
				
			}
			if (forma==5){
				if (!segundo)//bandera para verificar que se realiza esa funcion 
				{
					tmpx = x;
					tmpy = y;
					segundo = true;
					
				}
				else
				{
					if (!tercero)//bandera para verificar que se realiza esa funcion 
					{
						tmpx2 = x;
						tmpy2 = y;
						tercero = true;
						
					}
					else
					{
						Punto p1(tmpx,tmpy,red,green,blue);
						Punto p2(tmpx2,tmpy2,red,green,blue);
						Punto p3(x,y,red,green,blue);
						
						graficarcasteljau3(p1,p2,p3);
						segundo = false;
						tercero= false;
					}
					
				}
			}
			if (forma==6){
				if (!segundo)//bandera para verificar que se realiza esa funcion 
				{
					tmpx = x;
					tmpy = y;
					segundo = true;
					
				}
				else
				{
					if (!tercero)//bandera para verificar que se realiza esa funcion 
					{
						tmpx2 = x;
						tmpy2 = y;
						tercero = true;
						
					}
					else
					{
						Punto p1(tmpx,tmpy,red,green,blue);
						Punto p2(tmpx2,tmpy2,red,green,blue);
						Punto p3(x,y,red,green,blue);
						
						graficarhermite(p1,p2,p3);
						segundo = false;
						tercero= false;
					}
					
				}
			}
		}	
	}
}

void Movimiento(int x, int y)//grafica puntos dinamicos-movimiento
{
		if (forma == 1)
		{
			drawPuntos(x, y);
		}
}

void clear() //limpiar pantalla
{
	puntos.clear();
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void quit(){
	exit(0);
	}
	
void LimpiarSalirMenu(int value)
{
	switch (value)
	{
	case 0:
		quit();
		break;
	case 1:
		clear();
		break;
	}
}

void ColoresMenu(int value)
{
	segundo = false;

	switch (value)
	{
	case 1: // red
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;
	case 2: // green
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;
	case 3: // blue
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
		}
}
void FormasMenu(int value)
{
	forma = value;
	segundo = false;
}

void Menu()
{
	int colorMenu = glutCreateMenu(ColoresMenu);
	glutAddMenuEntry("Rojo", 1);
	glutAddMenuEntry("Verde", 2);
	glutAddMenuEntry("Azul", 3);

	int formasMenu = glutCreateMenu(FormasMenu);
	glutAddMenuEntry("Punto", 1);
	glutAddMenuEntry("Linea", 2);
	glutAddMenuEntry("Circulo", 3);
	glutAddMenuEntry("Bezier", 4);
	glutAddMenuEntry("Cateljau", 5);
	glutAddMenuEntry("Hermite", 6);

	int main_id = glutCreateMenu(LimpiarSalirMenu);
	glutAddSubMenu("Color", colorMenu);
	glutAddSubMenu("Formas", formasMenu);
	glutAddMenuEntry("Limpiar", 1);
	glutAddMenuEntry("Salir", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display()//linea de puntos
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	glBegin(GL_POINTS);
	
	for ( int i = 0; i < puntos.size(); i++)
	{
		glColor3f(puntos[i].getR(), puntos[i].getG(), puntos[i].getB());
		glVertex2i(puntos[i].getX(), puntos[i].getY());
		
	}
	glEnd();
	glutSwapBuffers();
}


void FPS(int val)//no estatico, las rayas se mueven con suavidad
{
	glutPostRedisplay();
	glutTimerFunc(0, FPS, 0);
//	cout<<FPS;
}

void callbackInit()
{
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(Movimiento);
	glutTimerFunc(17, FPS, 0);
}

void init(void)
{
	/* background color */
	glClearColor(1,0,0,0);
	glColor3f(red, green, blue);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500, 0.0, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Paint-ProyectoFinal");
	callbackInit();
	init();
	Menu();
	glutMainLoop();
	return (0);
}
