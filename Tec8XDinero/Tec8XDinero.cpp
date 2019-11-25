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
#include <time.h>

#define HEIGHT 720
#define WIDTH 1280

Cube cubito(5, 5, 5, 5, 5);
PrismRectangular mesita(0, 0, -5, 15, 15, 2);
float anglex = 0.0, angley = 0.0, anglez = 0.0;
bool rotate = false, roll = false;
float alto = 7.5, increment = 0.0;
bool zero = false;
float xmove = 0.0, ymove = 0.0, zmove = 0.0;

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void idle_cb(int Value) {
	srand(time(NULL));
	roll = true;
	float anglexrand = rand() % 10, angleyrand = rand() % 10, anglezrand = rand() % 10;
	anglex += anglexrand;
	angley += angleyrand;
	anglez += anglezrand;
	xmove -= .1;
	ymove -= 0.1;
	zmove -= 0.1;
	glutPostRedisplay();
	if (cubito.getOrigin().getZ() <= 0)
	{
		roll = false;
		glutTimerFunc(1000, NULL, 0);
		//cubito.setOrigin(0 - increment, 0 -increment, 0- increment);
		//glRotatef(anglex, 1.0, 0.0, 0.0);
		//glRotatef(angley, 0.0, 1.0, 0.0);
		//glRotatef(anglez, 0.0, 0.0, 1.0);
		cubito.calculateVertex();
		zero = true;
		return;
	}
	glutTimerFunc(10, idle_cb, 0);
}

void displayScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(150, 150, 300, 300);
	mesita.drawFigureTable();
	glPushMatrix();

	if (roll)
	{
		double x1 = cubito.getOrigin().getX(), y1 = cubito.getOrigin().getY(), z1 = cubito.getOrigin().getZ();
		glTranslatef(x1, y1, z1);
		glRotatef(anglex, 1.0, 0.0, 0.0);
		glRotatef(angley, 0.0, 1.0, 0.0);
		glRotatef(anglez, 0.0, 0.0, 1.0);
		glTranslatef(-x1, -y1, -z1);
		//cubito.moveFigure(xmove, ymove, zmove);
		glTranslatef(xmove, ymove, zmove);
		cubito.setOrigin(x1 - .1, y1 - .1, z1 - .1);
		increment += .1;
		//alto -= .1;	
		//cubito.calculateVertex();
	}
	if (zero) {
		glRotatef(anglex, 1.0, 0.0, 0.0);
		glRotatef(angley, 0.0, 1.0, 0.0);
		glRotatef(anglez, 0.0, 0.0, 1.0);
		zero = false;
	}
	//cubito.calculateVertex();
	cubito.drawFigureDice();
	glPopMatrix();
	//cubito.drawFigureDice();
	/*
		glPushMatrix();
		if (rotate)
		{
			glRotatef(anglex, 1.0, 0.0, 0.0);
			glRotatef(angley, 0.0, 1.0, 0.0);
			glRotatef(anglez, 0.0, 0.0, 1.0);
			rotate = false;
		}
		cubito.drawFigureDice();
		glPopMatrix();
		*/
	glutSwapBuffers();
}

void teclado_cb(GLubyte key, GLint x, GLint y) {
	switch (key) {
	case 27:
		exit(1);
		break;
	case 'x':
		// aqu  se procesar a la tecla <x>
		glRotatef(5.0, 1.0, 0.0, 0.0);
		//rotate = true;
		//anglex += 5.0;
		//glutPostRedisplay();
		break;
	case 'y':
		// aqu  se procesar a la tecla <y>
		rotate = true;
		angley += 5.0;
		//glRotatef(5.0, 0.0, 1.0, 0.0);
		break;
	case 'z':
		// aqu  se procesar a la tecla <z>
		//rotate = true;
		//anglez += 5.0;
		glRotatef(5.0, 0.0, 0.0, 1.0);
		break;
	case 'e':
		glutTimerFunc(1000, idle_cb, 0);
		break;
	case 'r':
		// aqu  se procesar a la tecla <r>
		glLoadIdentity();
		//angle = 0.0;
		break;
	case 'a':
		// aqu  se procesar a la tecla <a>
		//angle += 15;
		break;
	default:
		break;

	}
	glutPostRedisplay();

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("CUBO 3D");

	initializer(); // INICIALIZA LA VENTANA
	glutDisplayFunc(displayScreen); // ACTUALIZA LA PANTALLA DE TRAZADO
	glutKeyboardFunc(teclado_cb);
	//glutIdleFunc(idle_cb);

	glutMainLoop(); // GENERA EL LOOP

	return 0;
}