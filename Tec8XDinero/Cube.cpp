#include "Cube.h"
#include "Color.h"
#include "Vertex3d.h"
#include <GL/glut.h>

Cube::Cube() {
	setOrigin(0, 0, 0);
	setColor(1);
	setDimension(1);
	setNumVertex(VERTEXNUMBER);
	loadVertex();
}

Cube::Cube(double _x, double _y, double _z) {
	setOrigin(_x, _y, _z);
	setColor(1);
	setDimension(1);
	setNumVertex(VERTEXNUMBER);
	loadVertex();
}

Cube::Cube(double _x, double _y, double _z, double _dim) {
	setOrigin(_x, _y, _z);
	setColor(1);
	setDimension(_dim);
	setNumVertex(VERTEXNUMBER);
	loadVertex();
}

Cube::Cube(double _x, double _y, double _z, double _dim, int _col) {
	setOrigin(_x, _y, _z);
	setColor(_col);
	setDimension(_dim);
	setNumVertex(VERTEXNUMBER);
	loadVertex();
}

Cube::Cube(Cube& _cube) {
	Vertex3d pos = _cube.getOrigin();
	setOrigin(pos.getX(), pos.getY(), pos.getZ());
	setColor(_cube.getNumColor());
	setDimension(_cube.getDimension());
	setNumVertex(VERTEXNUMBER);
	loadVertex();
}

void Cube::loadVertex() 
{
	Vertex3d aux_origin = getOrigin();
	double aux_dimension = getDimension();
	double x1 = aux_origin.getX() + (aux_dimension / 2);
	double y1 = aux_origin.getY() - (aux_dimension / 2);
	double z1 = aux_origin.getZ() - (aux_dimension / 2);
	double x2 = x1 - aux_dimension;
	double y2 = y1 + aux_dimension;
	double z2 = z1 + aux_dimension;

	vertexPos[0].setXYZ(x1, y1, z1);		vertexPos[1].setXYZ(x1, y1, z2);
	vertexPos[2].setXYZ(x1, y2, z2);		vertexPos[3].setXYZ(x1, y2, z1);
	vertexPos[4].setXYZ(x2, y1, z1);		vertexPos[5].setXYZ(x2, y1, z2);
	vertexPos[6].setXYZ(x2, y2, z2);		vertexPos[7].setXYZ(x2, y2, z1);
}

// ----- ASIGNA LAS COORDENADAS EN X, Y, Z EN CADA VERTICE DEL CUBO ---------------------
void Cube::setVertex(double _x1, double _x2, double _y1,
	double _y2, double _z1, double _z2)
{
	vertexPos[0].setXYZ(_x1, _y1, _z1);		vertexPos[1].setXYZ(_x1, _y1, _z2);
	vertexPos[2].setXYZ(_x1, _y2, _z2);		vertexPos[3].setXYZ(_x1, _y2, _z1);
	vertexPos[4].setXYZ(_x2, _y1, _z1);		vertexPos[5].setXYZ(_x2, _y1, _z2);
	vertexPos[6].setXYZ(_x2, _y2, _z2);		vertexPos[7].setXYZ(_x2, _y2, _z1);

	vertex[0] = _x1;		vertex[1] = _y1;		vertex[2] = _z1;
	vertex[3] = _x2;		vertex[4] = _y2;		vertex[5] = _z2;

	
}

// ----- ESTABLECE LOS COLORES DEPENDIENDO DEL NUMERO DE PARAMETRO --------------------
// ENTRA A UN SWITCH QUE ASIGNA UN COLOR A CADA ELEMENTO DEL ARREGLO COLOR
void Cube::setColor(int _colorNumber)
{
	numColor = _colorNumber;
	switch (_colorNumber)
	{
	case 1:
		colors[0].setRGB(1.0, 1.0, 0.0);	colors[1].setRGB(0.0, 1.0, 1.0);
		colors[2].setRGB(1.0, 0.0, 1.0);	colors[3].setRGB(1.0, 0.0, 0.0);
		colors[4].setRGB(0.0, 1.0, 0.0);	colors[5].setRGB(0.0, 0.0, 1.0);
		break;
	case 2:
		colors[0].setRGB(1.0, 0.0, 1.0);	colors[1].setRGB(1.0, 0.0, 0.0);
		colors[2].setRGB(0.0, 0.0, 0.75);	colors[3].setRGB(0.0, 1.0, 1.0);
		colors[4].setRGB(1.0, 0.75, 0.75);	colors[5].setRGB(0.75, 1.0, 1.0);
		break;
	case 3:
		colors[0].setRGB(0.5, 0.5, 0.5);	colors[1].setRGB(0.9, 0.8, 0.7);
		colors[2].setRGB(0.6, 0.5, 0.4);	colors[3].setRGB(1.0, 1.0, 0.75);
		colors[4].setRGB(0.75, 1.0, 1.0);	colors[5].setRGB(1.0, 0.75, 1.0);
		break;
	case 4:
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
		break;
	case 5:
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(0.0, 1.0, 0.0); }
		break;
	case 6:
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(0.0, 0.0, 1.0); }
		break;
	case 7:
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(1.0, 1.0, 0.0); }
		break;
	case 8:
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(1.0, 0.0, 1.0); }
		break;
	case 9:
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(0.0, 1.0, 1.0); }
		break;
	default:
		numColor = 0;
		for (int i = 0; i < FACESNUMBER; i++) { colors[i].setRGB(0.0, 0.0, 0.0); }
		break;

	}
}

// ----- SETTERS & GETTERS ----------------------------------
void Cube::setDimension(double _dimension)
{
	if (_dimension > 0) { dimension = _dimension; }
	else { setDimension(1); }
	assignProperties();
}


Vertex3d Cube::getVertexPos(int _num) {
	if (_num >= 0 && _num < 8)
	{
		return vertexPos[_num];
	}
}

double Cube::getDimension() { return dimension; }

// ----- CALCULA LAS COORDENADAS DEL VERTICE INICIAL PARTIENDO DEL CENTRO DEL CUBO COMO ORIGEN -------
void Cube::calculateVertex()
{
	Vertex3d aux_origin = getOrigin();
	double aux_dimension = getDimension();
	double x1 = aux_origin.getX() + (aux_dimension / 2);
	double y1 = aux_origin.getY() - (aux_dimension / 2);
	double z1 = aux_origin.getZ() - (aux_dimension / 2);
	double x2 = x1 - aux_dimension;
	double y2 = y1 + aux_dimension;
	double z2 = z1 + aux_dimension;
	setVertex(x1, x2, y1, y2, z1, z2);	// LLAMA LA ASIGNACION DE LOS VERTICES
}

void Cube::assignProperties()
{
	text[0] = Texture3d((char*)"Textures/1.bmp");
	text[1] = Texture3d((char*)"Textures/2.bmp");
	text[2] = Texture3d((char*)"Textures/3.bmp");
	text[3] = Texture3d((char*)"Textures/4.bmp");
	text[4] = Texture3d((char*)"Textures/5.bmp");
	text[5] = Texture3d((char*)"Textures/6.bmp");

	for (size_t i = 0; i < FACESNUMBER; i++)
	{
		text[i].loadTexture();
	}

	volume = calculateVolume();
	calculateVertex();
}

double Cube::calculateVolume() { return (getDimension() * getDimension() * getDimension()); }

// DIBUJA LA FIGURA PINTANDO CADA UNA DE LAS CARAS CON DIFERENTE COLOR
void Cube::drawFigure()
{
	// ----- POR CADA CARA TOMA EL COLOR DEL ARREGLO ---------------------
	Color aux_color = colors[0];
	glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	for (int i = 0; i < FACESNUMBER; i++)
	{
		glVertex3f(vertexPos[i].getX(), vertexPos[i].getY(), vertexPos[i].getZ());
	}
	glEnd();

	aux_color = colors[1];
	glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
	glBegin(GL_POLYGON);
	glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
	glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
	glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
	glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
	glEnd();

	aux_color = colors[2];
	glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
	glBegin(GL_POLYGON);
	glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
	glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
	glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
	glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
	glEnd();

	aux_color = colors[3];
	glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
	glBegin(GL_POLYGON);
	glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
	glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
	glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
	glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
	glEnd();

	aux_color = colors[4];
	glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
	glBegin(GL_POLYGON);
	glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
	glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
	glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
	glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
	glEnd();

	aux_color = colors[5];
	glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
	glBegin(GL_POLYGON);
	glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
	glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
	glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
	glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
	glEnd();
}

void Cube::drawFigureDice()
{
	glEnable(GL_TEXTURE_2D);

	text[0].useTexture();
	glBindTexture(GL_TEXTURE_2D, text[0].texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
	glTexCoord2f(0.0, 1.0);
	glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
	glTexCoord2f(0.0, 0.0);
	glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
	glEnd();

	text[1].useTexture();
	glBindTexture(GL_TEXTURE_2D, text[1].texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
	glTexCoord2f(0.0, 1.0);
	glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
	glTexCoord2f(0.0, 0.0);
	glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
	glEnd();

	text[2].useTexture();
	glBindTexture(GL_TEXTURE_2D, text[2].texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
	glTexCoord2f(0.0, 1.0);
	glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
	glTexCoord2f(0.0, 0.0);
	glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
	glEnd();

	text[3].useTexture();
	glBindTexture(GL_TEXTURE_2D, text[3].texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
	glTexCoord2f(0.0, 1.0);
	glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
	glTexCoord2f(0.0, 0.0);
	glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
	glEnd();

	text[4].useTexture();
	glBindTexture(GL_TEXTURE_2D, text[4].texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
	glTexCoord2f(0.0, 1.0);
	glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
	glTexCoord2f(0.0, 0.0);
	glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
	glEnd();

	text[5].useTexture();
	glTexCoord2f(1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, text[5].texture);
	glBegin(GL_POLYGON);
	glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
	glTexCoord2f(0.0, 1.0);
	glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
	glTexCoord2f(0.0, 0.0);
	glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
	glEnd();

	/*
	for (int i = 0; i < 6; ++i) {
		//draw cube with texture images
		text[i].useTexture();
		glBindTexture(GL_TEXTURE_2D, text[i].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3fv(face[i][0]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(face[i][1]);
		glTexCoord2f(-1.0, 0.0); glVertex3fv(face[i][2]);
		glTexCoord2f(0.0, 0.0); glVertex3fv(face[i][3]);
		glEnd();
	}
	*/
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Cube::moveFigure(double _x, double _y, double _z)
{
	for (size_t i = 0; i < 8; i++)
	{
		Vertex3d aux_vertex = getVertexPos(i);
		setVertexposX(aux_vertex.getX() + _x, i);
		setVertexposY(aux_vertex.getY() + _y, i);
		setVertexposZ(aux_vertex.getZ() + _z, i);
	}
	//origin.moveVertex3d(0, 0, _z);
	//calculateVertex();
}

void Cube::scaleFigure(double _factor)
{
	setDimension(_factor * getDimension());
	calculateVertex();
}

void Cube::setVertexposX(double _pos, int _index) {
	vertexPos[_index].setX(_pos);
}

void Cube::setVertexposY(double _pos, int _index) {
	vertexPos[_index].setY(_pos);
}

void Cube::setVertexposZ(double _pos, int _index) {
	vertexPos[_index].setZ(_pos);
}

void Cube::rotateFigureX(double _angle)
{
	_angle = _angle * 3.141592 / 180.0;
	for (size_t i = 0; i < 8; i++)
	{
		Vertex3d aux_vertex = getVertexPos(i);
		double tempy = aux_vertex.getY();
		double pivoty = getOrigin().getY();
		double pivotz = getOrigin().getZ();
		setVertexposY(pivoty + (tempy - pivoty) * cos(_angle) - (aux_vertex.getZ() - pivotz) * sin(_angle), i);
		setVertexposZ(pivotz + (tempy - pivoty) * sin(_angle) + (aux_vertex.getZ() - pivotz) * cos(_angle), i);
		//setOrigin(aux_vertex.getX(), aux_vertex.getY(), aux_vertex.getZ());
	}
}


void Cube::rotateFigureY(double _angle)
{
	_angle = _angle * 3.141592 / 180.0;
	for (size_t i = 0; i < 8; i++)
	{
		Vertex3d aux_vertex = getVertexPos(i);
		double tempz = aux_vertex.getZ();
		double pivotz = getOrigin().getZ();
		double pivotx = getOrigin().getX();
		setVertexposZ(pivotz + (tempz - pivotz) * cos(_angle) - (aux_vertex.getX() - pivotx) * sin(_angle), i);
		setVertexposX(pivotx + (tempz - pivotz) * sin(_angle) + (aux_vertex.getX() - pivotx) * cos(_angle), i);
	}
}

void Cube::rotateFigureZ(double _angle)
{
	_angle = _angle * 3.141592 / 180.0;
	for (size_t i = 0; i < 8; i++)
	{
		Vertex3d aux_vertex = getVertexPos(i);
		double tempx = aux_vertex.getX();
		double pivotx = getOrigin().getX();
		double pivoty = getOrigin().getY();
		setVertexposX(pivotx + (tempx - pivotx) * cos(_angle) - (aux_vertex.getY() - pivoty) * sin(_angle), i);
		setVertexposY(pivoty + (tempx - pivotx) * sin(_angle) + (aux_vertex.getY() - pivoty) * cos(_angle), i);
	}

}

/*
void Cube::rotateFigureX(double _angle)
{
	_angle = _angle * 3.141592 / 180.0;
	Vertex3d aux_origin = getOrigin();
	double tempy = aux_origin.getY();
	aux_origin.setY(tempy * cos(_angle) - aux_origin.getZ() * sin(_angle));
	aux_origin.setZ(tempy * sin(_angle) + aux_origin.getZ() * cos(_angle));
	setOrigin(aux_origin.getX(), aux_origin.getY(), aux_origin.getZ());
}

void Cube::rotateFigureY(double _angle)
{
	_angle = _angle * 3.141592 / 180.0;
	Vertex3d aux_origin = getOrigin();
	double tempz = aux_origin.getZ();
	aux_origin.setZ(tempz * cos(_angle) - aux_origin.getX() * sin(_angle));
	aux_origin.setX(tempz * sin(_angle) + aux_origin.getX() * cos(_angle));
	setOrigin(aux_origin.getX(), aux_origin.getY(), aux_origin.getZ());
}

void Cube::rotateFigureZ(double _angle)
{
	_angle = _angle * 3.141592 / 180.0;
	Vertex3d aux_origin = getOrigin();
	double tempx = aux_origin.getX();
	aux_origin.setX(tempx * cos(_angle) - aux_origin.getY() * sin(_angle));
	aux_origin.setY(tempx * sin(_angle) + aux_origin.getY() * cos(_angle));
	setOrigin(aux_origin.getX(), aux_origin.getY(), aux_origin.getZ());
}*/

Cube::~Cube()
{
}