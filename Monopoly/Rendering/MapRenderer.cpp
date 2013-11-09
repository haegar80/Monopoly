#include "stdafx.h"
#include "MapRenderer.h"
#include <GL/gl.h>
#include <sstream>

MapRenderer::MapRenderer(GameMap& p_gameMap) :
	m_gameMap(p_gameMap),
	m_selectionMode(false)
{
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::render(QGLWidget* p_widget) 
{
	if(!m_selectionMode) {
		renderMap();
	}

	// Read Places from Gamemap
	std::vector<Place>& places = m_gameMap.getPlaces();
	for(uint i=0; i < places.size(); i++) {
		renderPlaceColor(places[i]);
		
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
	glColor3ub(150, 200, 150);
	glBegin(GL_POLYGON);
	glVertex3d(size, 0.0, -2.0);
	glVertex3d(size, size, -2.0);
	glVertex3d(0.0, size, -2.0);
	glVertex3d(0.0, 0.0, -2.0);
	glEnd();

	// top
	glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON);
	glVertex3d(size, size, -2.0);
	glVertex3d(size, size, -200.0);
	glVertex3d(0, size, -200.0);
	glVertex3d(0, size, -2.0);
	glEnd();

	// bottom
	glColor3ub(0, 255, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0.0, 0.0, -2.0);
	glVertex3d(0.0, 0.0, -200.0);
	glVertex3d(size, 0.0, -200.0);
	glVertex3d(size, 0.0, -2.0);
	glEnd();

	// right
	glColor3ub(255, 255, 0);
	glBegin(GL_POLYGON);
	glVertex3d(size, 0.0, -2.0);
	glVertex3d(size, 0.0, -200.0);
	glVertex3d(size, size, -200.0);
	glVertex3d(size, size, -2.0);
	glEnd();

	// left
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0.0, size, -2.0);
	glVertex3d(0.0, size, -200.0);
	glVertex3d(0.0, 0.0, -200.0);
	glVertex3d(0.0, 0.0, -2.0);
	glEnd();
}

void MapRenderer::renderPlaceColor(Place& p_place)
{
	Color color = p_place.getColor();
	glColor3ub(color.redValue, color.greenValue, color.blueValue);
	// integer precise is enough
	int height = p_place.getHeight();
	int heightColor = height / 4;
	int width = p_place.getWidth();
	int posX = p_place.getPosX();
	int posY = p_place.getPosY();
	int posYColor = posY;

	glDisable(GL_CULL_FACE);
	glLoadName(p_place.getSelectionNumber());
	glBegin(GL_POLYGON);
	glVertex3i(posX, posYColor - heightColor, -2);
	glVertex3i(posX, posYColor, -2);
	glVertex3i(posX + width, posYColor, -2);
	glVertex3i(posX + width, posYColor - heightColor, -2);
	glEnd();
	glEnable(GL_CULL_FACE);

	if(p_place.isSelected()) {
		glColor3ub(255, 0, 0);
	}
	else {
		glColor3ub(40, 40, 40);
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