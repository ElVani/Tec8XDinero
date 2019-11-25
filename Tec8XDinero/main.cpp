/*
* GRAFICACION - UNIDAD 3
* INTEGRANTES:
* IVAN FRANCO DELGADO
* JESUS EDUARDO SOSA DIAZ
* JOSUE TORRES AVALOS
*/

#include <GL/glut.h>
#include "Cube.h"
#include "PrismRectangular.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <time.h>

#define HEIGHT 720
#define WIDTH 1280

float float_rand(float, float);
void calculateVertexCube1(void);
void calculateVertexCube2(void);
bool collisionCube1(void);
bool collisionCube2(void);
void calculateValue(void);
//void centerDice(int, Cube);
void centerDice(int);
void centerDice1(int);

Cube cubito(5, 5, 7, 5, 5);
Cube cubote(-3, -3, 8, 5, 5);
PrismRectangular mesita(0, 0, -2, 15, 15, 2);
float anglex = 0.0, angley = 0.0, anglez = 0.0;
bool rotate = false, roll1 = false, roll2 = false;
float alto = 7.5, increment = 0.0;
bool zero = false;
float xmove = 0.0, ymove = 0.0, zmove = 0.0;
float anglerandomaux = 7.0, anglerandom = 0.0;
float moverandomaux = 5.0, moverandom = 0.0;
bool start = true, end = false;
int vertex = 0;
int orden[8];
int numDice = 0, numDice1 = 0, numDice2 = 0;
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24;


int state = 0;

bool rolling = false;
int prediction = 2;
int firstNumber;
bool toldU = false;
float anglex1, angley1, anglez1;

bool end1 = false, end2 = false;

void writeBitmapString(void* font, const char* string)
{
	const char* c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void idle_cb(int Value) {
	roll1 = true;
	roll2 = true;
	srand(time(NULL));
	anglex += rand() % 360;
	angley += rand() % 360;
	anglez += rand() % 360;
	if (anglex > 360)
	{
		anglex -= 360;
		angley -= 360;
		anglez -= 360;
	}
	anglex1 += rand() % 360;
	angley1 += rand() % 360;
	anglez1 += rand() % 360;
	/*if (anglex1 > 360)
	{
		anglex1 -= 360;
		angley1 -= 360;
		anglez1 -= 360;
	}*/
	xmove -= moverandom;
	ymove -= moverandom;
	zmove -= moverandom;

	collisionCube1();
	collisionCube2();
	glutPostRedisplay();
	if (collisionCube1())
	{
		calculateVertexCube1();
		roll1 = false;
		glutTimerFunc(1000, NULL, 0);
		end1 = true;
		//return;
	}
	if (collisionCube2())
	{
		calculateVertexCube2();
		roll2 = false;
		glutTimerFunc(1000, NULL, 0);
		end = true;
		//return;
	}
	if (end1) {
		if (end2) {
			end = true;
		}
	}
	if (end) {
		centerDice(numDice1);
		centerDice1(numDice2);
		numDice = numDice1 + numDice2;
		std::cout << "NUMERO MAMALON = " << numDice << std::endl;
		return;
	}
	glutTimerFunc(10, idle_cb, 0);
}

bool collisionCube1() {
	for (size_t i = 0; i < 8; i++)
	{
		if (cubito.getVertexPos(i).getZ() < 0)
		{
			return true;
		}
	}
	return false;
}
bool collisionCube2() {
	for (size_t i = 0; i < 8; i++)
	{
		if (cubote.getVertexPos(i).getZ() < 0)
		{
			return true;
		}
	}
	return false;
}

void calculateVertexCube1(void) {
	Vertex3d aux_pos[8];
	int contador = 0;
	Vertex3d temp;
	for (size_t i = 0; i < 8; i++)
	{
		aux_pos[i] = cubito.getVertexPos(i);
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = i+1; j < 8; j++)
		{
			if (aux_pos[j].getZ() < aux_pos[i].getZ())
			{
				temp = aux_pos[i];
				aux_pos[i] = aux_pos[j];
				aux_pos[j] = temp;
			}
		}
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (aux_pos[i].getZ() == cubito.getVertexPos(j).getZ())
			{
				orden[contador] = j;
				contador++;
			}
		}

	}
	calculateValue();
	for (size_t i = 0; i < 8; i++)
	{
		std::cout << "lower vertex " << aux_pos[i].getZ() << "\t" << orden[i] << std::endl;
		std::cout << "move = " << moverandom << std::endl;

	}
	numDice1 = numDice;
	std::cout << "numer 1: " << numDice1 << std::endl;
	std::cout << "Prediction = " << prediction << std::endl;
	std::cout << "move = " << moverandom << std::endl;
	Vertex3d origenAux = cubito.getOrigin();
	std::cout << "origin 1 = " << origenAux.getZ() << std::endl;
	origenAux = cubote.getOrigin();
	std::cout << "origin 2 = " << origenAux.getZ() << std::endl;
	//numDice = numDice1 + numDice2;
	//std::cout << "numer " << numDice << std::endl;
	//centerDice(numDice);
}

void calculateVertexCube2(void) {
	Vertex3d aux_pos[8];
	int contador = 0;
	Vertex3d temp;
	for (size_t i = 0; i < 8; i++)
	{
		aux_pos[i] = cubote.getVertexPos(i);
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = i + 1; j < 8; j++)
		{
			if (aux_pos[j].getZ() < aux_pos[i].getZ())
			{
				temp = aux_pos[i];
				aux_pos[i] = aux_pos[j];
				aux_pos[j] = temp;
			}
		}
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (aux_pos[i].getZ() == cubote.getVertexPos(j).getZ())
			{
				orden[contador] = j;
				contador++;
			}
		}

	}
	calculateValue();
	for (size_t i = 0; i < 8; i++)
	{
		std::cout << "lower vertex 2" << aux_pos[i].getZ() << "\t" << orden[i] << std::endl;

	}
	numDice2 = numDice;
	std::cout << "numer 2: " << numDice2 << std::endl;
	std::cout << "Prediction = " << prediction << std::endl;
	std::cout << "numer " << numDice << std::endl;
	//centerDice1(numDice);
}

void calculateValue() {
	switch (orden[0])
	{
	case 0:
		switch (orden[1])
		{
		case 1:
			if (orden[2] == 3)	{ numDice = 5;}
			else if(orden[2] == 4)	{ numDice = 4;}
			break;
		case 3:
			if (orden[2] == 1) { numDice = 5; }
			else if (orden[2] == 4) { numDice = 6; }
			break;
		case 4:
			if (orden[2] == 1) { numDice = 4; }
			else if (orden[2] == 3) { numDice = 6; }
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (orden[1])
		{
		case 0:
			if (orden[2] == 2) { numDice = 5; }
			else if (orden[2] == 5) { numDice = 4; }
			break;
		case 2:
			if (orden[2] == 0) { numDice = 5; }
			else if (orden[2] == 5) { numDice = 3; }
			break;
		case 5:
			if (orden[2] == 0) { numDice = 4; }
			else if (orden[2] == 2) { numDice = 3; }
			break;
		default:
		break;
	}
		break;
	case 2:
		switch (orden[1])
		{
		case 1:
			if (orden[2] == 3) { numDice = 5; }
			else if (orden[2] == 6) { numDice = 3; }
			break;
		case 3:
			if (orden[2] == 1) { numDice = 5; }
			else if (orden[2] == 6) { numDice = 2; }
			break;
		case 6:
			if (orden[2] == 1) { numDice = 3; }
			else if (orden[2] == 3) { numDice = 2; }
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (orden[1])
		{
		case 0:
			if (orden[2] == 2) { numDice = 5; }
			else if (orden[2] == 7) { numDice = 6; }
			break;
		case 2:
			if (orden[2] == 0) { numDice = 5; }
			else if (orden[2] == 7) { numDice = 2; }
			break;
		case 7:
			if (orden[2] == 0) { numDice = 6; }
			else if (orden[2] == 2) { numDice = 2; }
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (orden[1])
		{
		case 0:
			if (orden[2] == 5) { numDice = 4; }
			else if (orden[2] == 7) { numDice = 6; }
			break;
		case 5:
			if (orden[2] == 0) { numDice = 4; }
			else if (orden[2] == 7) { numDice = 1; }
			break;
		case 7:
			if (orden[2] == 0) { numDice = 6; }
			else if (orden[2] == 5) { numDice = 1; }
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (orden[1])
		{
		case 1:
			if (orden[2] == 4) { numDice = 4; }
			else if (orden[2] == 6) { numDice = 3; }
			break;
		case 4:
			if (orden[2] == 1) { numDice = 4; }
			else if (orden[2] == 6) { numDice = 1; }
			break;
		case 6:
			if (orden[2] == 1) { numDice = 3; }
			else if (orden[2] == 4) { numDice = 1; }
			break;
		default:
			break;
		}
		break;
	case 6:
		switch (orden[1])
		{
		case 2:
			if (orden[2] == 5) { numDice = 3; }
			else if (orden[2] == 7) { numDice = 2; }
			break;
		case 5:
			if (orden[2] == 2) { numDice = 3; }
			else if (orden[2] == 7) { numDice = 1; }
			break;
		case 7:
			if (orden[2] == 2) { numDice = 1; }
			else if (orden[2] == 5) { numDice = 1; }
			break;
		default:
			break;
		}
		break;
	case 7:
		switch (orden[1])
		{
		case 3:
			if (orden[2] == 4) { numDice = 6; }
			else if (orden[2] == 6) { numDice = 2; }
			break;
		case 4:
			if (orden[2] == 3) { numDice = 6; }
			else if (orden[2] == 6) { numDice = 1; }
			break;
		case 6:
			if (orden[2] == 3) { numDice = 2; }
			else if (orden[2] == 4) { numDice = 1; }
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

//void centerDice(int _numDice, Cube cubito) {
void centerDice(int _numDice) {
	//float difZ1, difZ2, difZ3, difZ4;
	Vertex3d vertexAux;
	switch (_numDice) {
	case 1:
		cubito.setVertexposZ(0, 4);		cubito.setVertexposZ(0, 5);	//	VALUES
		cubito.setVertexposZ(0, 6);		cubito.setVertexposZ(0, 7);	//	OPOSITE SIDE

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubito.getVertexPos(0);		cubito.setVertexposX(vertexAux.getX(), 4);		cubito.setVertexposY(vertexAux.getY(), 4);
		vertexAux = cubito.getVertexPos(1);		cubito.setVertexposX(vertexAux.getX(), 5);		cubito.setVertexposY(vertexAux.getY(), 5);
		vertexAux = cubito.getVertexPos(2);		cubito.setVertexposX(vertexAux.getX(), 6);		cubito.setVertexposY(vertexAux.getY(), 6);
		vertexAux = cubito.getVertexPos(3);		cubito.setVertexposX(vertexAux.getX(), 7);		cubito.setVertexposY(vertexAux.getY(), 7);

		cubito.setVertexposZ(cubito.getDimension(), 0);		cubito.setVertexposZ(cubito.getDimension(), 1);	//	VALUES
		cubito.setVertexposZ(cubito.getDimension(), 2);		cubito.setVertexposZ(cubito.getDimension(), 3);	//	SIDE OF TOP
		break;
	case 2:
		cubito.setVertexposZ(0, 3);		cubito.setVertexposZ(0, 2);
		cubito.setVertexposZ(0, 6);		cubito.setVertexposZ(0, 7);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubito.getVertexPos(0);		cubito.setVertexposX(vertexAux.getX(), 3);		cubito.setVertexposY(vertexAux.getY(), 3);
		vertexAux = cubito.getVertexPos(1);		cubito.setVertexposX(vertexAux.getX(), 2);		cubito.setVertexposY(vertexAux.getY(), 2);
		vertexAux = cubito.getVertexPos(5);		cubito.setVertexposX(vertexAux.getX(), 6);		cubito.setVertexposY(vertexAux.getY(), 6);
		vertexAux = cubito.getVertexPos(4);		cubito.setVertexposX(vertexAux.getX(), 7);		cubito.setVertexposY(vertexAux.getY(), 7);

		cubito.setVertexposZ(cubito.getDimension(), 0);		cubito.setVertexposZ(cubito.getDimension(), 1);
		cubito.setVertexposZ(cubito.getDimension(), 5);		cubito.setVertexposZ(cubito.getDimension(), 4);
		break;
	case 3:
		cubito.setVertexposZ(0, 1);		cubito.setVertexposZ(0, 6);
		cubito.setVertexposZ(0, 2);		cubito.setVertexposZ(0, 5);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubito.getVertexPos(0);		cubito.setVertexposX(vertexAux.getX(), 1);		cubito.setVertexposY(vertexAux.getY(), 1);
		vertexAux = cubito.getVertexPos(3);		cubito.setVertexposX(vertexAux.getX(), 2);		cubito.setVertexposY(vertexAux.getY(), 2);
		vertexAux = cubito.getVertexPos(7);		cubito.setVertexposX(vertexAux.getX(), 6);		cubito.setVertexposY(vertexAux.getY(), 6);
		vertexAux = cubito.getVertexPos(4);		cubito.setVertexposX(vertexAux.getX(), 5);		cubito.setVertexposY(vertexAux.getY(), 5);

		cubito.setVertexposZ(cubito.getDimension(), 0);		cubito.setVertexposZ(cubito.getDimension(), 3);
		cubito.setVertexposZ(cubito.getDimension(), 7);		cubito.setVertexposZ(cubito.getDimension(), 4);
		break;
	case 4:
		cubito.setVertexposZ(0, 0);		cubito.setVertexposZ(0, 1);
		cubito.setVertexposZ(0, 5);		cubito.setVertexposZ(0, 4);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubito.getVertexPos(3);		cubito.setVertexposX(vertexAux.getX(), 0);		cubito.setVertexposY(vertexAux.getY(), 0);
		vertexAux = cubito.getVertexPos(2);		cubito.setVertexposX(vertexAux.getX(), 1);		cubito.setVertexposY(vertexAux.getY(), 1);
		vertexAux = cubito.getVertexPos(6);		cubito.setVertexposX(vertexAux.getX(), 5);		cubito.setVertexposY(vertexAux.getY(), 5);
		vertexAux = cubito.getVertexPos(7);		cubito.setVertexposX(vertexAux.getX(), 4);		cubito.setVertexposY(vertexAux.getY(), 4);

		cubito.setVertexposZ(cubito.getDimension(), 3);		cubito.setVertexposZ(cubito.getDimension(), 2);
		cubito.setVertexposZ(cubito.getDimension(), 6);		cubito.setVertexposZ(cubito.getDimension(), 7);
		break;
	case 5:
		cubito.setVertexposZ(0, 0);		cubito.setVertexposZ(0, 1);
		cubito.setVertexposZ(0, 2);		cubito.setVertexposZ(0, 3);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubito.getVertexPos(4);		cubito.setVertexposX(vertexAux.getX(), 0);		cubito.setVertexposY(vertexAux.getY(), 0);
		vertexAux = cubito.getVertexPos(5);		cubito.setVertexposX(vertexAux.getX(), 1);		cubito.setVertexposY(vertexAux.getY(), 1);
		vertexAux = cubito.getVertexPos(6);		cubito.setVertexposX(vertexAux.getX(), 2);		cubito.setVertexposY(vertexAux.getY(), 2);
		vertexAux = cubito.getVertexPos(7);		cubito.setVertexposX(vertexAux.getX(), 3);		cubito.setVertexposY(vertexAux.getY(), 3);

		cubito.setVertexposZ(cubito.getDimension(), 4);		cubito.setVertexposZ(cubito.getDimension(), 5);
		cubito.setVertexposZ(cubito.getDimension(), 6);		cubito.setVertexposZ(cubito.getDimension(), 7);
		break;
	case 6:
		cubito.setVertexposZ(0, 0);		cubito.setVertexposZ(0, 7);
		cubito.setVertexposZ(0, 4);		cubito.setVertexposZ(0, 3);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubito.getVertexPos(1);		cubito.setVertexposX(vertexAux.getX(), 0);		cubito.setVertexposY(vertexAux.getY(), 0);
		vertexAux = cubito.getVertexPos(2);		cubito.setVertexposX(vertexAux.getX(), 3);		cubito.setVertexposY(vertexAux.getY(), 3);
		vertexAux = cubito.getVertexPos(6);		cubito.setVertexposX(vertexAux.getX(), 7);		cubito.setVertexposY(vertexAux.getY(), 7);
		vertexAux = cubito.getVertexPos(5);		cubito.setVertexposX(vertexAux.getX(), 4);		cubito.setVertexposY(vertexAux.getY(), 4);

		cubito.setVertexposZ(cubito.getDimension(), 1);		cubito.setVertexposZ(cubito.getDimension(), 2);
		cubito.setVertexposZ(cubito.getDimension(), 6);		cubito.setVertexposZ(cubito.getDimension(), 5);
		break;
	}
}

void centerDice1(int _numDice) {
	//float difZ1, difZ2, difZ3, difZ4;
	Vertex3d vertexAux;
	switch (_numDice) {
	case 1:
		cubote.setVertexposZ(0, 4);		cubote.setVertexposZ(0, 5);	//	VALUES 
		cubote.setVertexposZ(0, 6);		cubote.setVertexposZ(0, 7);	//	OPOSITE SIDE

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubote.getVertexPos(0);		cubote.setVertexposX(vertexAux.getX(), 4);		cubote.setVertexposY(vertexAux.getY(), 4);
		vertexAux = cubote.getVertexPos(1);		cubote.setVertexposX(vertexAux.getX(), 5);		cubote.setVertexposY(vertexAux.getY(), 5);
		vertexAux = cubote.getVertexPos(2);		cubote.setVertexposX(vertexAux.getX(), 6);		cubote.setVertexposY(vertexAux.getY(), 6);
		vertexAux = cubote.getVertexPos(3);		cubote.setVertexposX(vertexAux.getX(), 7);		cubote.setVertexposY(vertexAux.getY(), 7);

		cubote.setVertexposZ(cubote.getDimension(), 0);		cubote.setVertexposZ(cubote.getDimension(), 1);	//	VALUES
		cubote.setVertexposZ(cubote.getDimension(), 2);		cubote.setVertexposZ(cubote.getDimension(), 3);	//	SIDE OF TOP
		break;
	case 2:
		cubote.setVertexposZ(0, 3);		cubote.setVertexposZ(0, 2);
		cubote.setVertexposZ(0, 6);		cubote.setVertexposZ(0, 7);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubote.getVertexPos(0);		cubote.setVertexposX(vertexAux.getX(), 3);		cubote.setVertexposY(vertexAux.getY(), 3);
		vertexAux = cubote.getVertexPos(1);		cubote.setVertexposX(vertexAux.getX(), 2);		cubote.setVertexposY(vertexAux.getY(), 2);
		vertexAux = cubote.getVertexPos(5);		cubote.setVertexposX(vertexAux.getX(), 6);		cubote.setVertexposY(vertexAux.getY(), 6);
		vertexAux = cubote.getVertexPos(4);		cubote.setVertexposX(vertexAux.getX(), 7);		cubote.setVertexposY(vertexAux.getY(), 7);

		cubote.setVertexposZ(cubote.getDimension(), 0);		cubote.setVertexposZ(cubote.getDimension(), 1);
		cubote.setVertexposZ(cubote.getDimension(), 5);		cubote.setVertexposZ(cubote.getDimension(), 4);
		break;
	case 3:
		cubote.setVertexposZ(0, 1);		cubote.setVertexposZ(0, 6);
		cubote.setVertexposZ(0, 2);		cubote.setVertexposZ(0, 5);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubote.getVertexPos(0);		cubote.setVertexposX(vertexAux.getX(), 1);		cubote.setVertexposY(vertexAux.getY(), 1);
		vertexAux = cubote.getVertexPos(3);		cubote.setVertexposX(vertexAux.getX(), 2);		cubote.setVertexposY(vertexAux.getY(), 2);
		vertexAux = cubote.getVertexPos(7);		cubote.setVertexposX(vertexAux.getX(), 6);		cubote.setVertexposY(vertexAux.getY(), 6);
		vertexAux = cubote.getVertexPos(4);		cubote.setVertexposX(vertexAux.getX(), 5);		cubote.setVertexposY(vertexAux.getY(), 5);

		cubote.setVertexposZ(cubote.getDimension(), 0);		cubote.setVertexposZ(cubote.getDimension(), 3);
		cubote.setVertexposZ(cubote.getDimension(), 7);		cubote.setVertexposZ(cubote.getDimension(), 4);
		break;
	case 4:
		cubote.setVertexposZ(0, 0);		cubote.setVertexposZ(0, 1);
		cubote.setVertexposZ(0, 5);		cubote.setVertexposZ(0, 4);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubote.getVertexPos(3);		cubote.setVertexposX(vertexAux.getX(), 0);		cubote.setVertexposY(vertexAux.getY(), 0);
		vertexAux = cubote.getVertexPos(2);		cubote.setVertexposX(vertexAux.getX(), 1);		cubote.setVertexposY(vertexAux.getY(), 1);
		vertexAux = cubote.getVertexPos(6);		cubote.setVertexposX(vertexAux.getX(), 5);		cubote.setVertexposY(vertexAux.getY(), 5);
		vertexAux = cubote.getVertexPos(7);		cubote.setVertexposX(vertexAux.getX(), 4);		cubote.setVertexposY(vertexAux.getY(), 4);

		cubote.setVertexposZ(cubote.getDimension(), 3);		cubote.setVertexposZ(cubote.getDimension(), 2);
		cubote.setVertexposZ(cubote.getDimension(), 6);		cubote.setVertexposZ(cubote.getDimension(), 7);
		break;
	case 5:
		cubote.setVertexposZ(0, 0);		cubote.setVertexposZ(0, 1);
		cubote.setVertexposZ(0, 2);		cubote.setVertexposZ(0, 3);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubote.getVertexPos(4);		cubote.setVertexposX(vertexAux.getX(), 0);		cubote.setVertexposY(vertexAux.getY(), 0);
		vertexAux = cubote.getVertexPos(5);		cubote.setVertexposX(vertexAux.getX(), 1);		cubote.setVertexposY(vertexAux.getY(), 1);
		vertexAux = cubote.getVertexPos(6);		cubote.setVertexposX(vertexAux.getX(), 2);		cubote.setVertexposY(vertexAux.getY(), 2);
		vertexAux = cubote.getVertexPos(7);		cubote.setVertexposX(vertexAux.getX(), 3);		cubote.setVertexposY(vertexAux.getY(), 3);

		cubote.setVertexposZ(cubote.getDimension(), 4);		cubote.setVertexposZ(cubote.getDimension(), 5);
		cubote.setVertexposZ(cubote.getDimension(), 6);		cubote.setVertexposZ(cubote.getDimension(), 7);
		break;
	case 6:
		cubote.setVertexposZ(0, 0);		cubote.setVertexposZ(0, 7);
		cubote.setVertexposZ(0, 4);		cubote.setVertexposZ(0, 3);

		//	SET VERTEX AUXILIAR					// SET POSITION IN X			// SET POSITION IN Y

		vertexAux = cubote.getVertexPos(1);		cubote.setVertexposX(vertexAux.getX(), 0);		cubote.setVertexposY(vertexAux.getY(), 0);
		vertexAux = cubote.getVertexPos(2);		cubote.setVertexposX(vertexAux.getX(), 3);		cubote.setVertexposY(vertexAux.getY(), 3);
		vertexAux = cubote.getVertexPos(6);		cubote.setVertexposX(vertexAux.getX(), 7);		cubote.setVertexposY(vertexAux.getY(), 7);
		vertexAux = cubote.getVertexPos(5);		cubote.setVertexposX(vertexAux.getX(), 4);		cubote.setVertexposY(vertexAux.getY(), 4);

		cubote.setVertexposZ(cubote.getDimension(), 1);		cubote.setVertexposZ(cubito.getDimension(), 2);
		cubote.setVertexposZ(cubote.getDimension(), 6);		cubote.setVertexposZ(cubito.getDimension(), 5);
		break;
	}
}

void displayScreen(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);


	glViewport(150, 150, 300, 300);

	if (start)
	{
		glRotatef(-45, 1.0, 0.0, 0.0);
		glRotatef(45, 0.0, 0.0, 1.0);
		start = false;
	}

	mesita.drawFigureTable();
	glPushMatrix();

	if (roll1 && !end)
	{
		double x1 = cubito.getOrigin().getX(), y1 = cubito.getOrigin().getY(), z1 = cubito.getOrigin().getZ();

		cubito.rotateFigureX(anglex);
		cubito.rotateFigureY(angley);
		cubito.rotateFigureZ(anglez);

		cubito.setOrigin(x1 - moverandom, y1- moverandom, z1 - moverandom);
		cubito.moveFigure(moverandomaux, moverandomaux, moverandomaux);

		increment += moverandom;
	}
	if (roll2 && !end)
	{
		double x1 = cubote.getOrigin().getX(), y1 = cubote.getOrigin().getY(), z1 = cubote.getOrigin().getZ();

		cubote.rotateFigureX(anglex1);
		cubote.rotateFigureY(angley1);
		cubote.rotateFigureZ(anglez1);

		cubote.setOrigin(x1 - moverandom, y1 - moverandom, z1 - moverandom);
		cubote.moveFigure(moverandomaux, moverandomaux, moverandomaux);

		increment += moverandom;
	}

	cubito.drawFigureDice();
	cubote.drawFigureDice();
																						// AQUI SE DIBUJA EL TEXTO EN GENERAL
	glPopMatrix();
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2f(600, 600);
	writeBitmapString((void*)font, "Ingrese el numero que cree que saldra de la suma de ambos dados:");
	glRasterPos2f(600, 570);
	writeBitmapString((void*)font, "PD: Para resetear el numero presiona r");
	glRasterPos2f(600, 540);
	writeBitmapString((void*)font, std::to_string(prediction).c_str());
	glRasterPos2f(600, 510);
	writeBitmapString((void*)font, "Cuando este listo presione la letra e para empezar");
	if (rolling == true) {
		if (prediction == numDice) {
			glRasterPos2f(600, 480);
			writeBitmapString((void*)font, "Felicidades! cayo tu numero, ahora ushcale del programa");
		}
		else {
			glRasterPos2f(600, 480);
			writeBitmapString((void*)font, "Nel no salio");
			if (toldU) {
				glRasterPos2f(600, 450);
				writeBitmapString((void*)font, "Te lo dije! pinshi vato meco");	
			}
		}

	}
	if (!rolling) {
		if (prediction < 2 || prediction > 12) {
			glRasterPos2f(600, 480);
			writeBitmapString((void*)font, "Desde ya te digo que esa madre no va a caer");
			toldU = true;
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
																					// AQUI TERMINA DE DIBUJARSE EL TEXTO
	glutSwapBuffers();
}

void calculateNumber(int num) {
	if (state == 0) {
		if (num == 1) {
			prediction = num;
			state++;
		}
		else {
			prediction = num;
		}
		
		return;
	}
	if (state == 1) {
		firstNumber = prediction;
		prediction = (firstNumber * 10) + num;
		state++;
		return;
	}
	if (state == 2) {
		prediction = (firstNumber * 10) + num;
		return;
	}
	glutPostRedisplay();
}

void teclado_cb(GLubyte key, GLint x, GLint y) {
	switch (key) {
	case 27:
		exit(1);
		break;
	case 'x':
		// aqu  se procesar a la tecla <x>
		glRotatef(5.0, 1.0, 0.0, 0.0);

		break;
	case 'y':
		// aqu  se procesar a la tecla <y>

		glRotatef(5.0, 0.0, 1.0, 0.0);
		break;
	case 'z':
		// aqu  se procesar a la tecla <z>

		glRotatef(5.0, 0.0, 0.0, 1.0);
		break;
	case 'e':
		if (end)
		{
			return;
		}
		anglerandom = 5.0;
		//anglerandom = (((float) rand() / (RAND_MAX)) + 1.0) * float_rand(3.0,7.0);
		//moverandom = .05;
		moverandom = ((((float)rand() / (RAND_MAX)) + 1.0) / float_rand(1.0, 5.0));
		moverandomaux = moverandom * (-1);
		//moverandom = ((((float)rand() / (RAND_MAX)) + 1.0) / 15.0);
		glutTimerFunc(1000, idle_cb, 0);
		rolling = true;
		break;
	case 'r':
		// aqu  se procesar a la tecla <r>
		prediction = 1;
		state = 0;
		//angle = 0.0;
		break;
	case 'a':
		// aqu  se procesar a la tecla <a>
		//angle += 15;
		break;
		case 48: calculateNumber(0);	break;
		case 49: calculateNumber(1);	break;
		case 50: calculateNumber(2);	break;
		case 51: calculateNumber(3);	break;
		case 52: calculateNumber(4);	break;
		case 53: calculateNumber(5);	break;
		case 54: calculateNumber(6);	break;
		case 55: calculateNumber(7);	break;
		case 56: calculateNumber(8);	break;
		case 57: calculateNumber(9);	break;
		default:
			break;
		}
		glutPostRedisplay();
}

float float_rand(float min, float max) {
	float scale = rand() / (float)RAND_MAX;
	return min + scale * (max - min);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	srand(time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("CUBO 3D");

	initializer(); // INICIALIZA LA VENTANA

	glutDisplayFunc(displayScreen); // ACTUALIZA LA PANTALLA DE TRAZADO*/

	glutKeyboardFunc(teclado_cb);

	glutMainLoop(); // GENERA EL LOOP

	return 0;
}
