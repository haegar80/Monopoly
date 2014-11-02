#include "stdafx.h"
#include "MapRenderer.h"
#include <GL/gl.h>
#include <sstream>
#include <cmath>
#include <qmessagebox.h>

MapRenderer::MapRenderer(GameMap& p_gameMap) :
	mc_turnMapId(50),
	m_gameMap(p_gameMap),
	m_selectionMode(false)
{
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::render(QGLWidget* p_widget) 
{
	glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glDisable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);

	// Textures setup
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	if(!m_selectionMode) {
    	renderBackgroundPolygon(p_widget->width(), p_widget->height());
		renderMap();
	}

	renderTurnMapArc();

	// Read Places from Gamemap
	std::vector<Place>& places = m_gameMap.getPlaces();
	for(uint i=0; i < places.size(); i++) {
		glEnable(GL_TEXTURE_2D);
		renderPlaceContent(places[i]);
		glDisable(GL_TEXTURE_2D);
		renderPlaceBorder(places[i]);
		if(!m_selectionMode) {
			renderPlaceText(places[i], p_widget);
		}
	}

	m_selectionMode = false;
}

void MapRenderer::renderMap()
{
	double size = static_cast<double>(m_gameMap.getSize());
	
	// front
	glColor3ub(0, 120, 0);
	glBegin(GL_POLYGON);
	glVertex3d(size, 0.0, -10.0);
	glVertex3d(size, size, -10.0);
	glVertex3d(0.0, size, -10.0);
	glVertex3d(0.0, 0.0, -10.0);
	glEnd();

	glColor3ub(0, 50, 0);
	// top
	glBegin(GL_POLYGON);
	glVertex3d(size, size, -10.0);
	glVertex3d(size, size, -100.0);
	glVertex3d(0, size, -100.0);
	glVertex3d(0, size, -10.0);
	glEnd();

	// bottom
	glBegin(GL_POLYGON);
	glVertex3d(0.0, 0.0, -10.0);
	glVertex3d(0.0, 0.0, -100.0);
	glVertex3d(size, 0.0, -100.0);
	glVertex3d(size, 0.0, -10.0);
	glEnd();

	// right
	glBegin(GL_POLYGON);
	glVertex3d(size, 0.0, -10.0);
	glVertex3d(size, 0.0, -100.0);
	glVertex3d(size, size, -100.0);
	glVertex3d(size, size, -10.0);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glVertex3d(0.0, size, -10.0);
	glVertex3d(0.0, size, -100.0);
	glVertex3d(0.0, 0.0, -100.0);
	glVertex3d(0.0, 0.0, -10.0);
	glEnd();
}

void MapRenderer::renderTurnMapArc()
{
	double size = static_cast<double>(m_gameMap.getSize());
	float startAngle = 0.0;
	float endAngle = 359.0;
	float deltaAngle = 1.0;
	float radius = 10.0;
	const double PI = 3.14159265;
	double rate = PI / 180;  // PI / 180 in Radiant entspricht 1� 
	glLoadName(mc_turnMapId);
	glColor3ub(0, 0, 0);
	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	float angleRadiant = 0.0;
	for(float angle = startAngle; angle < endAngle; angle += deltaAngle) {
		angleRadiant = angle * rate;
		glVertex2f(size + radius * cosf(angleRadiant), 0 + radius * sinf(angleRadiant));
	}
	glEnd();

	float lineAngle1 = 0.0;
	angleRadiant = lineAngle1 * rate;
	float crossStartX = size + radius * cosf(angleRadiant);
	float crossStartY = radius * sinf(angleRadiant);
	glBegin(GL_LINES);
	glVertex2f(crossStartX, crossStartY);
	glVertex2f(crossStartX - 2 * radius, crossStartY);
	glEnd();

    float lineAngle2 = 90.0;
	angleRadiant = lineAngle2 * rate;
	crossStartX = size + radius * cosf(angleRadiant);
	crossStartY = radius * sinf(angleRadiant);
	glBegin(GL_LINES);
	glVertex2f(crossStartX, crossStartY);
	glVertex2f(crossStartX, crossStartY - 2 * radius);
	glEnd();
}

void MapRenderer::renderPlaceContent(Place& p_place)
{
	/*Color color = p_place.getColor();
	glColor3ub(color.redValue, color.greenValue, color.blueValue);*/

	// integer precise is enough
	int height = p_place.getHeight();
	int width = p_place.getWidth();
	int posX = p_place.getPosX();
	int posY = p_place.getPosY();

	glLoadName(p_place.getSelectionNumber());

	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Original image
	QImage placePictureOrig;
	std::string fileNameString = "Images/" + p_place.getCity() + "_" + p_place.getName() + ".png";
	QString filename(fileNameString.c_str());
	if(!placePictureOrig.load(filename)) {
		return;
	}

	QImage placePicture;
	placePicture = QGLWidget::convertToGLFormat(placePictureOrig);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, placePicture.width(), placePicture.height(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, placePicture.bits() );

	switch(p_place.getMapDirection()) {
	case MapDirection_Bottom:
		renderPlaceBottom(height, width, posX, posY);
		break;
	case MapDirection_Left:
		renderPlaceLeft(height, width, posX, posY);
		break;
	case MapDirection_Top:
		renderPlaceTop(height, width, posX, posY);
		break;
	case MapDirection_Right:
		renderPlaceRight(height, width, posX, posY);
		break;
	}
}

void MapRenderer::renderPlaceBorder(Place& p_place)
{
	// integer precise is enough
	int height = p_place.getHeight();
	int width = p_place.getWidth();
	int posX = p_place.getPosX();
	int posY = p_place.getPosY();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(1.0);
	if(p_place.isSelected()) {
		glColor3ub(255, 0, 0);
	}
	else {
		glColor3ub(0, 0, 0);
	}
	
	glBegin(GL_LINE_LOOP);
	glVertex3i(posX, posY - height, -2);
	glVertex3i(posX, posY, -2);
	glVertex3i(posX + width, posY, -2);
	glVertex3i(posX + width, posY - height, -2);
	glEnd();
}

void MapRenderer::renderPlaceText(Place& p_place, QGLWidget* p_widget)
{
	std::string name = p_place.getCity() + " " + p_place.getName();
	int height = p_place.getHeight();
	int width = p_place.getWidth();
	int posX = p_place.getPosX();
	int posY = p_place.getPosY();
	int posYText = posY - (height / 2);
	p_widget->renderText(posX, posYText, -2, QString::fromUtf8(p_place.getCity().c_str()));
	posYText += 10;
	p_widget->renderText(posX, posYText, -2, QString::fromUtf8(p_place.getName().c_str()));
	posYText += 20;
	int price = p_place.getPrice();
	std::stringstream priceString;
    priceString << price;
	p_widget->renderText(posX, posYText, -2, QString::fromUtf8(priceString.str().c_str()));
}

void MapRenderer::renderBackgroundPolygon(int p_width, int p_height)
{
	glColor3ub(0, 0, 0);

	glBegin(GL_POLYGON);
	glVertex3i(0, 0, -200);
	glVertex3i(0, p_height, -200);
	glVertex3i(p_width, p_height, -200);
	glVertex3i(p_width, 0, -200);
	glEnd();
}

void MapRenderer::setSelectionMode()
{
	m_selectionMode = true;
}

void MapRenderer::selectObjects(std::vector<int>& p_selectedObjects)
{
	std::vector<Place>& places = m_gameMap.getPlaces();
	for(uint selectedObjectIndex = 0; selectedObjectIndex < p_selectedObjects.size(); selectedObjectIndex++) {
    	for(uint placeIndex = 0; placeIndex < places.size(); placeIndex++) {
			places[placeIndex].setSelected(p_selectedObjects[selectedObjectIndex]);
		}
	}
}

void MapRenderer::renderPlaceBottom(int p_height, int p_width, int p_posX, int p_posY)
{
	glPushMatrix();

	int pixelOffset = 1;

	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0);
	glVertex3i(p_posX + pixelOffset, p_posY - p_height + pixelOffset, -2);
	glTexCoord2i(0, 1);
	glVertex3i(p_posX + pixelOffset, p_posY - pixelOffset, -2);
	glTexCoord2i(1, 1);
	glVertex3i(p_posX + p_width - pixelOffset, p_posY - pixelOffset, -2);
	glTexCoord2i(1, 0);
	glVertex3i(p_posX + p_width - pixelOffset, p_posY - p_height + pixelOffset, -2);

	glEnd();

	glPopMatrix();
}

void MapRenderer::renderPlaceLeft(int p_height, int p_width, int p_posX, int p_posY)
{
	int widthColor = p_width / 4;
	int posXColor = p_posX + p_width - widthColor;

	glBegin(GL_POLYGON);
	int pixelOffset = 1;
	glVertex3i(posXColor + pixelOffset, p_posY - pixelOffset, -2);
	glVertex3i(posXColor + pixelOffset, p_posY - p_height + pixelOffset, -2);
	glVertex3i(posXColor + widthColor - pixelOffset, p_posY - p_height + pixelOffset, -2);
	glVertex3i(posXColor + widthColor - pixelOffset, p_posY - pixelOffset, -2);
	glEnd();
}

void MapRenderer::renderPlaceTop(int p_height, int p_width, int p_posX, int p_posY)
{
	int heightColor = p_height / 4;
	int posYColor = p_posY;

	glBegin(GL_POLYGON);
	int pixelOffset = 1;
	glVertex3i(p_posX + pixelOffset, posYColor - heightColor + pixelOffset, -2);
	glVertex3i(p_posX + pixelOffset, posYColor - pixelOffset, -2);
	glVertex3i(p_posX + p_width - pixelOffset, posYColor - pixelOffset, -2);
	glVertex3i(p_posX + p_width - pixelOffset, posYColor - heightColor + pixelOffset, -2);
	glEnd();
}

void MapRenderer::renderPlaceRight(int p_height, int p_width, int p_posX, int p_posY)
{
	int heightColor = p_height / 4;
	int posYColor = p_posY;

	glBegin(GL_POLYGON);
	int pixelOffset = 1;
	glVertex3i(p_posX + pixelOffset, posYColor - heightColor + pixelOffset, -2);
	glVertex3i(p_posX + pixelOffset, posYColor - pixelOffset, -2);
	glVertex3i(p_posX + p_width - pixelOffset, posYColor - pixelOffset, -2);
	glVertex3i(p_posX + p_width - pixelOffset, posYColor - heightColor + pixelOffset, -2);
	glEnd();
}